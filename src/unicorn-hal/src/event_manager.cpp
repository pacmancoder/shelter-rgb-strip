#include <hal/event_manager.hpp>

#include <map>

#include <esp_event_loop.h>

#include <unithread/mutex.hpp>

using namespace Unicorn::Hal;
using namespace Unicorn::NetworkModel;

namespace
{
    struct Event
    {
        EventManager::UserContext userContext;
        std::function<void(system_event_info_t&, void* userData)> action;

        // Will be assigned on Impl::AddEvent
        EventManager::EventHandle eventHandle = 0;
    };
}

namespace Unicorn { namespace Hal
{
    struct EventManager::Impl
    {
    public:
        static esp_err_t EspEventLoop(void* userData, system_event_t* event);

    public:
        EventManager::EventHandle AddEvent(system_event_id_t id, Event&&);
        void RemoveEvent(EventManager::EventHandle handle);

    private:
        Unithread::Mutex eventsMutex_;
        std::multimap<system_event_id_t, Event> events;
        EventManager::EventHandle nextEventHandle = 0;
    };
}}

esp_err_t EventManager::Impl::EspEventLoop(void* userData, system_event_t* event)
{
    auto& info = event->event_info;
    auto* eventManager = reinterpret_cast<EventManager::Impl*>(userData);

    auto lock = eventManager->eventsMutex_.ScopedLock();

    const auto foundRange = eventManager->events.equal_range(event->event_id);

    for (auto it = foundRange.first; it != foundRange.second; ++it)
    {
        it->second.action(info, &(it->second));
    }

    return ESP_OK;
}

EventManager::EventHandle EventManager::Impl::AddEvent(system_event_id_t id, Event&& event)
{
    auto lock = eventsMutex_.ScopedLock();
    auto newEventHandle = nextEventHandle++;

    event.eventHandle = newEventHandle;
    events.emplace(id, std::move(event));

    return newEventHandle;
}

void EventManager::Impl::RemoveEvent(EventManager::EventHandle handle)
{
    for (auto it = events.begin(); it != events.end(); ++it)
    {
        if (it->second.eventHandle == handle)
        {
            events.erase(it);
            return;
        }
    }
}

EventManager::EventManager()
    : impl_(std::make_unique<Impl>())
{
    esp_event_loop_init(Impl::EspEventLoop, impl_.get());
}

EventManager::~EventManager() = default;

EventManager::EventHandle EventManager::RegisterWifiStaStartEvent(
    EventManager::WifiStaStartCallback&& callback,
    EventManager::UserContext userContext
)
{
    return impl_->AddEvent(
        SYSTEM_EVENT_STA_START,
        Event{
            userContext,
            [callback = std::move(callback)](system_event_info_t&, void* userData)
            {
                auto* event = reinterpret_cast<Event*>(userData);
                callback(WifiStaStartContext{}, event->userContext);
            }
        }
    );
}

EventManager::EventHandle EventManager::RegisterWifiStaGotIp(
    EventManager::WifiStaGotIpCallback&& callback,
    EventManager::UserContext userContext
)
{
    return impl_->AddEvent(
        SYSTEM_EVENT_STA_GOT_IP,
        Event{
            userContext,
            [callback = std::move(callback)](system_event_info_t& info, void* userData)
            {
                auto* event = reinterpret_cast<Event*>(userData);
                callback(
                    WifiStaGotIpContext{
                        Ip(info.got_ip.ip_info.ip.addr),
                        Ip(info.got_ip.ip_info.netmask.addr),
                    },
                    event->userContext
                );
            }
        }
    );
}

EventManager::EventHandle EventManager::RegisterWifiStaDisconnect(
    EventManager::WifiStaDisconnectedCallback&& callback,
    EventManager::UserContext userContext
)
{
    return impl_->AddEvent(
        SYSTEM_EVENT_STA_DISCONNECTED,
        Event{
            userContext,
            [callback = std::move(callback)](system_event_info_t& info, void* userData)
            {
                auto* event = reinterpret_cast<Event*>(userData);
                callback(
                    WifiStaDisconnectedContext{
                        static_cast<WifiDisconnectReason>(info.disconnected.reason)
                    },
                    event->userContext
                );
            }
        }
    );
}

EventManager::EventHandle EventManager::RegisterWifiApStart(
    EventManager::WifiApStartCallback&& callback,
    EventManager::UserContext userContext
)
{
    return impl_->AddEvent(
        SYSTEM_EVENT_AP_START,
        Event{
            userContext,
            [callback = std::move(callback)](system_event_info_t&, void* userData)
            {
                auto* event = reinterpret_cast<Event*>(userData);
                callback(
                    WifiApStartContext{},
                    event->userContext
                );
            }
        }
    );
}

void EventManager::UnregisterEvent(EventHandle handle)
{
    impl_->RemoveEvent(handle);
}

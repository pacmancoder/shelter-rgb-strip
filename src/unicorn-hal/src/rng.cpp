#include <hal/rng.hpp>

#include <limits>
#include <esp_system.h>

using namespace Unicorn::Hal;

Rng::result_type Rng::min()
{
    return std::numeric_limits<result_type>::min();
}

Rng::result_type Rng::max()
{
    return std::numeric_limits<result_type>::max();
}

Rng::result_type Rng::operator()()
{
    return esp_random();
}

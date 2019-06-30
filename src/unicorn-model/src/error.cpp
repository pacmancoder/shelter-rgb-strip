#include <model/error.hpp>

using namespace Unicorn::Model;

Error::Error(const char* description)
    : description_(description) {}

Error::Error(std::string&& description)
    : description_(std::move(description)) {}

const char* Error::GetDescription()
{
    return description_.map<const char*>(
        exl::when_exact<CString>(
            [](const CString& value)
            {
                return value.value;
            }
        ),
        exl::when_exact<std::string>(
            [](const std::string& value)
            {
                return value.c_str();
            }
        )
    );
}

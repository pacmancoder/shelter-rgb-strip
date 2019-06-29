#pragma once

#include <exl/mixed.hpp>

#include <string>

namespace Unicorn { namespace Model
{
    class Error
    {
    public:
        explicit Error(const char* description);
        explicit Error(std::string&& description);

        const char* GetDescription();

    private:
        struct CString
        {
            const char* value;
        };

        using ErrorDescription = exl::mixed<std::string, CString>;

    private:
        ErrorDescription description_;
    };

    class ConfigurationError : public Error { using Error::Error; };
}}
#pragma once

#include "tzbuild.h"
#include "Version.hpp"

namespace tkacz {
    class Tkacz {

    public:

        enum class LogLevel : int {
            _NONE   =   0,
            FINEST  =   10,
            FINE    =   20,
            INFO    =   30,
            MESSAGE =   40,
            WARNING =   50,
            SEVERE  =   60,
            FATAL   =   70,
            _ALL    =   1024
        };

        const Version version {
            TZ_VERSION_MAJOR,
            TZ_VERSION_MINOR,
            TZ_VERSION_PATCH,
            Version::Maturity::TZ_VERSION_MATURITY,
            TZ_VERSION_PREVERSION,
            TZ_VERSION_NAME };

        static void init();
        
    };
    
}
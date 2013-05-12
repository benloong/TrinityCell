//
//  logger.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-12.
//
//

#ifndef __TrinityCell__logger__
#define __TrinityCell__logger__
#include <memory>

namespace cell {
    class LoggerImpl;
    class Logger
    {
        std::unique_ptr<LoggerImpl> pImpl;
    public:
        Logger(const char * file);
        ~Logger();
        void Log(const char *s);
        void LogError(const char *err);
        void LogWarning(const char *warn);
    };
}

#endif /* defined(__TrinityCell__logger__) */

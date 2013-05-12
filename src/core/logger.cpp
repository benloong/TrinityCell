//
//  logger.cpp
//  TrinityCell
//
//  Created by he qianjun on 13-5-12.
//
//

#include "logger.h"
#include <fstream>
#include "thread_pool.h"

namespace cell {
    class LoggerImpl{
        std::ofstream  file;
        ThreadPool*    thread;
        
    public:
        LoggerImpl(const char *log_file):thread(new ThreadPool(1))
        {
            file.open(log_file);
        }
        ~LoggerImpl()
        {
            delete thread;
            file.close();
        }
        void Log(const char *info)
        {
            thread->enqueue([this, info]{
                this->_Log(info);
            });
        }
        
        void LogError(const char *err)
        {
            thread->enqueue([this, err]{
                this->_LogError(err);
            });
        }
        
        void LogWarning(const char *warn)
        {
            thread->enqueue([this, warn]{
                this->_LogWarning(warn);
            });
        }
        
        void _Log(const char *info)
        {
            file <<"[INFO]:"<< info << std::endl;
        }
        void _LogError(const char *err)
        {
            file <<"[ERROR]:"<<err<<std::endl;
        }
        void _LogWarning(const char *warn)
        {
            file <<"[WARNING]:"<<warn<<std::endl;
        }
    };
    
    
    Logger::Logger(const char *log_file):pImpl(new LoggerImpl(log_file))
    {
        
    }
    Logger::~Logger()
    {
        
    }
    
    void Logger::Log(const char *text)
    {
        pImpl->Log(text);
    }
    
    void Logger::LogError(const char *err)
    {
        pImpl->LogError(err);
    }
    
    void Logger::LogWarning(const char *warn)
    {
        pImpl->LogWarning(warn);
    }
}
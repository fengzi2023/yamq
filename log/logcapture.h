#ifndef _YAMQ_LOG_LOGCAPTURE
#define _YAMQ_LOG_LOGCAPTURE 

#include "log/logstream.h"
//#include "log/logging.h"

namespace yamq {
namespace log {
/*
 * 日志解析模块，日志存储模块交互接口
 */
typedef void (*MsgOutputFunc)(const char *msg,size_t msg_len);
typedef void (*MsgFlushFunc)();

extern MsgOutputFunc g_outputFunc;
extern MsgFlushFunc g_flushFunc;

class LogCapture final {
    public:
        LogCapture(const char *file, const int line, const char *function, int level);
        ~LogCapture();
        LogStream &stream() {return _stream;}

    private:
        LogStream _stream;
        const char *_file;
        const int _line;
        const char *_function;
        const int _level;
};
} // log
} // yamq


#endif /* ifndef _YAMQ_LOG_LOGCAPTURE */

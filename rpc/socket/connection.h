#pragma once
#include "rpc/channel.h"
#include "rpc/socket/socket_utilties.h"
#include <functional>
#include "rpc/io_buffer.h"
#include <memory>

class Connection;
typedef std::shared_ptr<Connection> ConnectionPtr;

const int CONNECTING = 1,CONNECTED = 2,CLOSING = 3,CLOSED = 4;

class Connection : public Channel, public std::enable_shared_from_this<Connection> {
    public:
        using ConnectCallback = std::function<void (const ConnectionPtr &)>;
        using MessageCallback = std::function<void (const ConnectionPtr &,char *buf,int len)>;
        using CloseCallback = std::function<void (const ConnectionPtr &)>;

        Connection(int64_t id,EventDispatcher *evd,int fd,const InetAddr &local_side,const InetAddr &remote_side);
        ~Connection();

        void SetMessageCb(MessageCallback cb) {_message_cb = cb;}
        void SetCloseCb(CloseCallback cb) {_close_cb = cb;}

        virtual void HandleRead() override;
        virtual void HandleWrite() override;
        
        // MUST thread safe
        void Write(const char *data,size_t len);

        int64_t GetId() { return _id;}
        const InetAddr & GetRemoteSide() const { return _remote_side; }
        const InetAddr & GetLocalSide() const { return _local_side; }

        void SetStatus(int status) { _status = status; }
        
    private:
        int64_t _id;

        const InetAddr _local_side;
        const InetAddr _remote_side;

        MessageCallback _message_cb;
        CloseCallback _close_cb;

        int _status;

        std::unique_ptr<IoBuffer> _input_buf;
        std::unique_ptr<IoBuffer> _output_buf;
};

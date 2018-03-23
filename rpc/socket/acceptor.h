#pragma once
#include "rpc/channel.h"
#include "rpc/socket/socket_utilties.h"

class EventDispatcher;
class Connection;
class Acceptor : public Channel {
    // 用胶水functor来做吧！
    public:
        Acceptor(EventDispatcher *evd,const InetAddr &addr);
        ~Acceptor();

        virtual void HandleRead() override;

        void Listen();
        void SetConnectCb(ConnectCallback cb) { _conn_cb = cb;}
        const InetAddr & GetInetAddr() const {return _inet_addr;} 
    private:
        bool _listening;
        ConnectCallback _conn_cb;
        InetAddr _inet_addr;
};

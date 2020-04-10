#ifndef _WXH_OFFER_ANSWER_SERVER_H_
#define _WXH_OFFER_ANSWER_SERVER_H_


#include <websocketpp/config/asio_no_tls.hpp>

#include <websocketpp/server.hpp>

#include <iostream>
#include <set>

/*#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>*/
#include <websocketpp/common/thread.hpp>
#include "webrtc_server.h"

typedef websocketpp::server<websocketpp::config::asio> websocket_server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;


class offer_answer_server 
{
public:
    offer_answer_server(boost::asio::io_service* ptr_io_service, uint16_t port);
    void on_open(connection_hdl hdl) ;
    void on_close(connection_hdl hdl) ;
    void on_message(connection_hdl hdl, websocket_server::message_ptr msg); 
    
public:    
    websocket_server m_server;//public是线程函数要用
    WebRtcServer m_WebRtcServer;
    connection_hdl m_hdl;
};

#endif

#include "offer_answer_server.h"
#include <stdlib.h>
#include <stdio.h>


offer_answer_server::offer_answer_server(boost::asio::io_service* ptr_io_service, uint16_t port) 
{
    m_WebRtcServer.Start();
    // Initialize Asio Transport
    m_server.init_asio(ptr_io_service);

    // Register handler callbacks
    m_server.set_open_handler(bind(&offer_answer_server::on_open,this,::_1));
    m_server.set_close_handler(bind(&offer_answer_server::on_close,this,::_1));
    m_server.set_message_handler(bind(&offer_answer_server::on_message,this,::_1,::_2));
    m_server.listen(port);
    m_server.start_accept();
}

DWORD WINAPI SendProc(LPVOID lpParam)
{
    string sdp("");
    offer_answer_server *poffer_answer_server = (offer_answer_server *)lpParam;

    while(1)
    {
        if(0 == poffer_answer_server->m_WebRtcServer.GetSDP(&sdp))
        {
            poffer_answer_server->m_server.send(poffer_answer_server->m_hdl, sdp.c_str(), websocketpp::frame::opcode::text);
            break;
        }
        Sleep(1);
    }
    return 0;
}

void offer_answer_server::on_open(connection_hdl hdl) 
{    
    websocket_server::connection_ptr conn = m_server.get_con_from_hdl(hdl);
    std::cout << conn->get_uri()->str() << " : " << conn->get_uri()->get_resource() << " - "<< conn->get_remote_endpoint() << std::endl;

    m_hdl = hdl;
    HANDLE hThread = CreateThread(NULL, 0, SendProc, this, 0, NULL);
    CloseHandle(hThread);
}

void offer_answer_server::on_close(connection_hdl hdl) 
{        
    std::cout << "on_close" << std::endl;
}

void offer_answer_server::on_message(connection_hdl hdl, websocket_server::message_ptr msg) 
{        
    std::cout << "on_message" << std::endl;            
    //m_server.send(hdl, "this great\r\n", websocketpp::frame::opcode::text);
    std::cout << msg->get_payload();
    m_WebRtcServer.SendMsg(msg->get_payload().c_str());
}

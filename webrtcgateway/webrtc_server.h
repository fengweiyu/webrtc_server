

#ifndef WEBRTC_SERVER_H
#define WEBRTC_SERVER_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "winsock2.h"
#include <string>



using std::string;

/*****************************************************************************
-Class			: TcpServer
-Description	: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
class TcpServer 
{
public:
    TcpServer();
    ~TcpServer();
    int Init(unsigned short i_wPort,char * ip=NULL);    
    SOCKET Accept();
    int Send(char * i_acSendBuf,int i_iSendLen,SOCKET i_iClientSocketFd);
    int Recv(char *o_acRecvBuf,int *o_piRecvLen,int i_iRecvBufMaxLen,SOCKET i_iClientSocketFd);
    int Close(SOCKET i_iClientSocketFd);
    
private:
    SOCKET      m_iServerSocketFd;
};
    

/*****************************************************************************
-Class			: WebRtcServer
-Description	: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
class WebRtcServer : public TcpServer
{
public:
	WebRtcServer();
	~WebRtcServer();	
	int Start();
	int Proc();
	int GetSDP(string *sdp);
	int SendMsg(const char * i_strMsg);
private:
	SOCKET	  	m_iClientSocketFd;
	string 		m_strSDP;
};


#endif

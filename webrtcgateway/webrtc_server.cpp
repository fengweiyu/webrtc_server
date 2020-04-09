
#include "webrtc_server.h"

#define WEBRTC_SERVER_PORT 9898


/*****************************************************************************
-Fuction		: TcpServer
-Description	: TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
TcpServer::TcpServer()
{

}

/*****************************************************************************
-Fuction		: ~TcpServer
-Description	: ~TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
TcpServer::~TcpServer()
{
}


/*****************************************************************************
-Fuction		: TcpServer
-Description	: TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
int TcpServer::Init(unsigned short i_wPort,char * ip)
{
    //创建用于监听的套接字,即服务端的套接字
    SOCKET iServerSocketFd = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(i_wPort); //1024以上的端口号
    /**
    * INADDR_ANY就是指定地址为0.0.0.0的地址，这个地址事实上表示不确定地址，或“所有地址”、“任意地址”。 一般来说，在各个系统中均定义成为0值。
    */
    if(NULL == ip)
    {
        addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    }
    else
    {
        addrSrv.sin_addr.S_un.S_addr = inet_addr(ip);
    }

    int retVal = bind(iServerSocketFd, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
    if(retVal == SOCKET_ERROR)
    {
        printf("连接失败:%d\n", WSAGetLastError());
        closesocket(iServerSocketFd);
        return -1;
    }
    if(listen(iServerSocketFd,10) ==SOCKET_ERROR)
    {
        printf("监听失败:%d", WSAGetLastError());
        closesocket(iServerSocketFd);
        return -1;
    }
    m_iServerSocketFd = iServerSocketFd;
    return 0;
}

/*****************************************************************************
-Fuction		: TcpServer
-Description	: TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
SOCKET TcpServer::Accept()
{
    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);
    //等待客户请求到来
    SOCKET sockConn = accept(m_iServerSocketFd, (SOCKADDR *) &addrClient, &len);
    if(sockConn == SOCKET_ERROR)
    {
        printf("等待请求失败:%d", WSAGetLastError());
    }
    else
    {
        printf("客户端的IP是:[%s]\n", inet_ntoa(addrClient.sin_addr));
    }
    return sockConn;
}

/*****************************************************************************
-Fuction		: TcpServer
-Description	: TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
int TcpServer::Send(char * i_acSendBuf,int i_iSendLen,SOCKET i_iClientSocketFd)
{
    int iSend = send(i_iClientSocketFd, i_acSendBuf,i_iSendLen, 0);
    if(iSend == SOCKET_ERROR)
    {
        printf("发送失败");
    }
    return iSend;
}

/*****************************************************************************
-Fuction		: TcpServer
-Description	: TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
int TcpServer::Recv(char *o_acRecvBuf,int *o_piRecvLen,int i_iRecvBufMaxLen,SOCKET i_iClientSocketFd)
{
    *o_piRecvLen=recv(i_iClientSocketFd, o_acRecvBuf,i_iRecvBufMaxLen, 0);
    return 0;
}

/*****************************************************************************
-Fuction		: TcpServer
-Description	: TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
int TcpServer::Close(SOCKET i_iClientSocketFd)
{
    closesocket(i_iClientSocketFd);
    return 0;
}

/*****************************************************************************
-Fuction		: TcpServer
-Description	: TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
WebRtcServer::WebRtcServer()
{

}

/*****************************************************************************
-Fuction		: ~TcpServer
-Description	: ~TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
WebRtcServer::~WebRtcServer()
{
    CloseHandle(hThread);
}

/*****************************************************************************
-Fuction		: ~TcpServer
-Description	: ~TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
int WebRtcServer::Start()
{
    HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);

}
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
    MYDATA *pmd = (MYDATA *)lpParam;
    printf("%d\n", pmd->val1);
    printf("%d\n", pmd->val2);
    return 0;
}

/*****************************************************************************
-Fuction		: ~TcpServer
-Description	: ~TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
int WebRtcServer::Proc()
{
    char acRecvBuf[8*1024];
    int iRecvLen=0;
    memset(acRecvBuf,0,sizeof(acRecvBuf));
    Init(WEBRTC_SERVER_PORT,NULL);
    m_iClientSocketFd = Accept();
    int iRet=Recv(acRecvBuf,&iRecvLen,sizeof(acRecvBuf),m_iClientSocketFd);
    m_strSDP.assign(acRecvBuf);

}

/*****************************************************************************
-Fuction		: ~TcpServer
-Description	: ~TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
int WebRtcServer::GetSDP()
{

}

/*****************************************************************************
-Fuction		: ~TcpServer
-Description	: ~TcpServer
-Input			: 
-Output 		: 
-Return 		: 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/09/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
int WebRtcServer::Send()
{

}


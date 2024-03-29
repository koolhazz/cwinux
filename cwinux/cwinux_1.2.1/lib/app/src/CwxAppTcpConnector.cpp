#include "CwxAppFramework.h"
CWINUX_BEGIN_NAMESPACE

///构造函数
CwxAppTcpConnector::CwxAppTcpConnector (CwxAppFramework* pApp, CwxAppReactor *reactor)
:m_pApp(pApp), m_reactor(reactor)
{

}
///析构函数
CwxAppTcpConnector::~CwxAppTcpConnector()
{

}

int CwxAppTcpConnector::connect(CwxAppHandler4TcpConn* pHandler,
                            char const* szAddr,
                            CWX_UINT16 unPort,
                            int iFamily)
{
    CwxTimeValue timeout;
    CwxTimeouter timer(&timeout);
    CwxSockConnector connector;
    CwxSockStream stream;
    CwxINetAddr addr(unPort, szAddr, iFamily);
    int ret = connector.connect (stream,
        addr,
        CwxAddr::sap_any,
        &timer,
        0,
        true);
    if (0 == ret)
    {
        pHandler->setHandle(stream.getHandle());
        pHandler->getConnInfo().setState(CwxAppConnInfo::ESTABLISHING);
        if (-1 == pHandler->open(NULL)) return -1;
        return 1;
    }
    if (EWOULDBLOCK == errno)
    {
        pHandler->setHandle(stream.getHandle());
        pHandler->getConnInfo().setState(CwxAppConnInfo::CONNECTING);
        if (-1 == pHandler->open(NULL)) return -1;
        return 0;
    }
    CWX_ERROR(("Failure to connect to:ip=%s port=%u errno=%d",
        szAddr,
        unPort,
        errno));
    pHandler->setHandle(CWX_INVALID_HANDLE);
    stream.close();
    return -1;
}

CWINUX_END_NAMESPACE


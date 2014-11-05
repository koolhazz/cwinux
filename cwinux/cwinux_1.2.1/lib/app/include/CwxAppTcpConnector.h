#ifndef __CWX_APP_TCP_CONNECTOR_H__
#define __CWX_APP_TCP_CONNECTOR_H__

/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppTcpConnector.h
@brief Tcp�����ӹ�����󣬸����������ӵĽ��������
@author cwinux@gmail.com
@version 0.1
@date 2009-07-20
@warning
@bug
*/

#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxAppConfig.h"
#include "CwxAppMacro.h"
#include "CwxAppHandler4TcpConn.h"
#include "CwxAppReactor.h"

CWINUX_BEGIN_NAMESPACE
class CwxAppFramework;
/**
@class CwxAppTcpConnector
@brief Tcp�����ӹ�����󣬸����������ӵĽ��������
*/
class CWX_API CwxAppTcpConnector
{
public:
	///���캯��
	CwxAppTcpConnector (CwxAppFramework* pApp, CwxAppReactor *reactor);
    ///��������
	~CwxAppTcpConnector ();
public:
    //�������ӣ� -1��ʧ�ܣ�0���ȴ����ӣ�1����������
    int connect (CwxAppHandler4TcpConn* pHandler, ///<conn handler
        char const* szAddr, ///<connect addr
        CWX_UINT16 unPort, ///<connect port
        int iFamily=AF_UNSPEC ///<family
        );
private:
    CwxAppFramework* m_pApp;
    CwxAppReactor * m_reactor;

};

CWINUX_END_NAMESPACE

#include "CwxPost.h"


#endif

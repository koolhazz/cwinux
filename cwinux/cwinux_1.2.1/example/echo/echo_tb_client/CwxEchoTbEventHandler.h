#ifndef __CWX_ECHO_TB_EVENT_HANDLER_H__
#define __CWX_ECHO_TB_EVENT_HANDLER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
#include "CwxAppCommander.h"
#include "CwxAppTss.h"
#include "CwxGlobalMacro.h"

CWINUX_USING_NAMESPACE

class CwxEchoTbClientApp;
///echo����Ĵ���handle��Ϊcommand��handle
class CwxEchoTbEventHandler : public CwxAppCmdOp 
{
public:
    ///���캯��
    CwxEchoTbEventHandler(CwxEchoTbClientApp* pApp):m_pApp(pApp)
    {
    }
    ///��������
    virtual ~CwxEchoTbEventHandler()
    {

    }
public:
    ///�յ�echo����Ĵ�����
    virtual int onRecvMsg(CwxMsgBlock*& msg,///<echo���ݰ�����ص�����������Ϣ
                            CwxAppTss* pThrEnv///<�����̵߳�thread-specific-store
                            );
    virtual int onConnClosed(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    virtual int onEndSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    virtual int onFailSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    virtual int onTimeoutCheck(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
private:
    CwxEchoTbClientApp*     m_pApp;  ///<app����
};

#endif 

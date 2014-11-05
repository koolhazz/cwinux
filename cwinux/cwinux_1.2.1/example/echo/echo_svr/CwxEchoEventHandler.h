#ifndef __CWX_ECHO_EVENT_HANDLER_H__
#define __CWX_ECHO_EVENT_HANDLER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
#include "CwxAppCommander.h"

CWINUX_USING_NAMESPACE

class CwxEchoApp;
///echo����Ĵ���handle��Ϊcommand��handle
class CwxEchoEventHandler : public CwxAppCmdOp 
{
public:
    ///���캯��
    CwxEchoEventHandler(CwxEchoApp* pApp):m_pApp(pApp)
    {
        m_ullMsgNum = 0;
    }
    ///��������
    virtual ~CwxEchoEventHandler()
    {

    }
public:
    ///�յ�echo����Ĵ�����
    virtual int onRecvMsg(CwxMsgBlock*& msg,///<echo���ݰ�����ص�����������Ϣ
                            CwxAppTss* pThrEnv///<�����̵߳�thread-specific-store
                            );
private:
    CwxEchoApp*     m_pApp;  ///<app����
    CWX_UINT64      m_ullMsgNum;
};

#endif 

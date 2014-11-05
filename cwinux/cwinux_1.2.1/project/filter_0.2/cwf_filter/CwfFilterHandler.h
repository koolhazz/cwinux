#ifndef __CWF_FILTER_HANDLER_H__
#define __CWF_FILTER_HANDLER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
#include "CwxAppCommander.h"
#include "CwfFilterMacro.h"

class CwfFilterApp;

///filter ����Ĵ���handle��Ϊcommand��handle
class CwfFilterHandler : public CwxAppCmdOp
{
public:
    ///���캯��
    CwfFilterHandler(CwfFilterApp* pApp):m_pApp(pApp)
    {

    }
    ///��������
    virtual ~CwfFilterHandler()
    {

    }
public:
    ///�յ�echo����Ĵ�����
    virtual int onRecvMsg(CwxMsgBlock*& msg,///<echo���ݰ�����ص�����������Ϣ
                         CwxAppTss* pThrEnv///<�����̵߳�thread-specific-store
                        );
private:
    void reply(CwxMsgHead const& header,
        CWX_UINT32 uiConnId,
        int ret,
        CWX_UINT8 ucLevel,
        char const* szWord,
        CWX_UINT32 uiWordLen,
        char const* szErrMsg,
        CwxAppTss* pThrEnv);
private:
    CwfFilterApp*     m_pApp;  ///<app����
};

#endif 

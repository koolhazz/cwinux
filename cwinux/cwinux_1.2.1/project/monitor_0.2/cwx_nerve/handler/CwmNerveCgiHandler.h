#ifndef __CWM_NERVE_CGI_HANDLER_H__
#define __CWM_NERVE_CGI_HANDLER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmNerveCgiHandler.h
@brief Nerve����CGIͨ�ŵ�handle��
@author cwinux@gmail.com
@version 0.1
@date 2009-10-26
@warning
@bug
*/
#include "CwxAppCommander.h"
#include "CwxAppFramework.h"
#include "CwxMsgBlock.h"

#include "CwmCmnMacro.h"
#include "CwmNerveTss.h"
#include "CwmNerveServiceStatus.h"
#include "CwmNerveActionStatus.h"
class CwmNerveApp;

/**
@class CwmNerveCgiHandler
@brief  Nerve����CGIͨ�ŵ�handle��
*/
class CwmNerveCgiHandler : public CwxAppCmdOp
{
    ///fork��handle�������ڽ�pipe��io handle��script���ݵ�child process
    class ForkHandler
    {
    public:
        ForkHandler()
        {
            m_filedes[0] = -1;
            m_filedes[1] = -1;
        }
        ~ForkHandler()
        {
            if (-1 != m_filedes[0]) close(m_filedes[0]);
            if (-1 != m_filedes[1]) close(m_filedes[1]);
        }
    public:
        int        m_filedes[2]; ///<pipe��read/write io handle
        string     m_strCgiScript; ///<child's execute script
    };
public:
    ///���캯��
    CwmNerveCgiHandler(CwmNerveApp* pApp):m_pApp(pApp)
    {

    }
    ///��������
    ~CwmNerveCgiHandler()
    {

    }
public:
    /**
    @brief ����CGI���ӹرյ��¼�,��ʱ��ζ��child process�˳���
    @param [in] msg ���ӹرյ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onConnClosed(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ͨ��pipe���յ�CGI��������ݡ�
    @param [in] msg �յ�ͨ�����ݰ����¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
public:
    ///framework��fork����Ҫ��forkPrepare API
    static void forkPrepare(CwxAppFramework* pParentApp, void* handle);
    ///framework��fork����Ҫ��forkChild API
    static void forkChild(void* handle);
public:
    ///��̬����������service��action�����֣�ִ��cgi�ű���ִ�У�������nerve��cgi���͵�query
    static bool queryCgi(CwmNerveApp* pApp,
        CwxAppTss* pThrEnv,
        string const& strSystem,
        string const& strService,
        string const& strAction,
        string& strErr,
        CwxMsgBlock*& queryMsg);
    ///��̬����������action����ִ��cgi�ű���ִ�У�������nerve��cgi���͵�poll
    static bool queryCgi(CwmNerveApp* pApp, CwxAppTss* pThrEnv, CwmNerveServiceStatus* pService, CwmNerveActionStatus* pAction, string& strErr);
private:
    CwmNerveApp*      m_pApp; ///app����
};


#endif

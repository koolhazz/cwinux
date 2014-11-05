#ifndef __CWM_NERVE_SERVER_HANDLER_H__
#define __CWM_NERVE_SERVER_HANDLER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmNerveServerHandler.h
@brief Nerve����server��tcpͨ�ŵ�handle��
@author cwinux@gmail.com
@version 0.1
@date 2009-10-26
@warning
@bug
*/
#include "CwxAppCommander.h"
#include "CwxMsgBlock.h"
#include "CwmNerveServiceStatus.h"
#include "CwmNerveActionStatus.h"
#include "CwmNerveTss.h"
class CwmNerveApp;

/**
@class CwmNerveServerHandler
@brief Server���͵�ACTION��Handler
*/

class CwmNerveServerHandler : public CwxAppCmdOp
{
public:
    ///���캯��
    CwmNerveServerHandler(CwmNerveApp* pApp):m_pApp(pApp)
    {

    }
    ///��������
    ~CwmNerveServerHandler()
    {

    }
public:
    /**
    @brief ���ӽ����¼��Ĵ�������
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onConnCreated(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ����Server���ӹرյ��¼���
    @param [in] msg ���ӹرյ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onConnClosed(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ��Ϣ��������¼��Ĵ�������
    @param [in] msg ��Ϣ������ϵ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onEndSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ��Ϣ����ʧ���¼��Ĵ�������
    @param [in] msg ��Ϣ����ʧ�ܵ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onFailSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief �յ����ݲ�ѯ��
    @param [in] msg �յ�ͨ�����ݰ����¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
public:
    ///�������ֲ�ѯserver
    static bool queryServer(CwxAppTss* pThrEnv,
        CwmNerveApp* pApp,
        string const& strSystem,
        string const& strService,
        string const& strAction,
        string& strErr,
        CwxMsgBlock*& queryMsg);
    ///���ݶ�����ѯserver
    static bool queryServer(CwxAppTss* pThrEnv,
        CwmNerveApp* pApp,
        CwmNerveServiceStatus* pService,
        CwmNerveActionStatus* pAction,
        string& strErr,
        CwxMsgBlock*& queryMsg);
    ///ִ�в�ѯ����
    static bool execQuery(CwxAppTss* pThrEnv,
        CwmNerveApp* pApp,
        CwmNerveServiceStatus* pService,
        CwmNerveActionStatus* pAction,
        CWX_UINT32 uiTaskId);
    ///������ѯ�Ľ��
    static bool analyseReply(CwxAppTss* pThrEnv,
        int& status,
        string& strLevel,
        CwxKeyValueItem & record,
        string& strErr);
private:
    CwmNerveApp*      m_pApp;///<app����
};


#endif

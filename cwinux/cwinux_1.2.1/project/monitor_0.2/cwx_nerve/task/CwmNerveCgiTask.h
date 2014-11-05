#ifndef __CWM_NERVE_CGI_TASK_H__
#define __CWM_NERVE_CGI_TASK_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmNerveCgiTask.h
@brief CGI��ACTION��Task���塣
@author cwinux@gmail.com
@version 0.1
@date 2009-10-25
@warning
@bug
*/

#include "CwmNerveTss.h"
#include "CwxAppTaskBoard.h"
#include "CwmNerveConfig.h"
#include "CwmNerveServiceStatus.h"
#include "CwmNerveActionStatus.h"
#include "CwmNerveConfig.h"
class CwmNerveApp;
/**
@class CwmNerveCgiTask
@brief Cgi���͵�ACTION��task������CGIͨ��
*/
class CwmNerveCgiTask : public CwxAppTaskBoardTask
{
public:
    enum
    {
        TASK_STATE_WAITING = CwxAppTaskBoardTask::TASK_STATE_USER
    };
    CwmNerveCgiTask(CwmNerveApp* pApp, CwxAppTaskBoard* pTaskBoard):CwxAppTaskBoardTask(pTaskBoard),m_pApp(pApp)
    {
        this->setTaskState(CwxAppTaskBoardTask::TASK_STATE_INIT);
        m_pMsg = NULL;
        m_pActionInfo = NULL;
        m_pServiceInfo = NULL;
        m_pService = NULL;
        m_pAction = NULL;
        m_bSuccess = false;

    }
    ~CwmNerveCgiTask()
    {
        if (m_pMsg) CwxMsgBlockAlloc::free(m_pMsg);
    }
public:
    /**
    @brief ֪ͨTask�Ѿ���ʱ
    @param [in] pThrEnv �����̵߳�Thread-env
    @return void
    */
    virtual void noticeTimeout(CwxAppTss* pThrEnv);
    /**
    @brief ֪ͨTask���յ�һ�����ݰ���
    @param [in] msg �յ�����Ϣ
    @param [in] pThrEnv �����̵߳�Thread-env
    @param [out] bConnAppendMsg �յ���Ϣ�������ϣ��Ƿ��д����յ�������Ϣ��true���ǣ�false��û��
    @return void
    */
    virtual void noticeRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv, bool& bConnAppendMsg);
    /**
    @brief ֪ͨTask���ⷢ�͵�һ�����ݰ�����ʧ�ܡ�
    @param [in] msg �յ�����Ϣ
    @param [in] pThrEnv �����̵߳�Thread-env
    @return void
    */
    virtual void noticeFailSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ֪ͨTaskͨ��ĳ�����ӣ�������һ�����ݰ���
    @param [in] msg ���͵����ݰ�����Ϣ
    @param [in] pThrEnv �����̵߳�Thread-env
    @param [out] bConnAppendMsg ������Ϣ�������ϣ��Ƿ��еȴ��ظ�����Ϣ��true���ǣ�false��û��
    @return void
    */
    virtual void noticeEndSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv, bool& bConnAppendMsg);
    /**
    @brief ֪ͨTask�ȴ��ظ���Ϣ��һ�����ӹرա�
    @param [in] uiSvrId �ر����ӵ�SVR-ID
    @param [in] uiHostId �ر����ӵ�HOST-ID
    @param [in] uiConnId �ر����ӵ�CONN-ID
    @param [in] pThrEnv �����̵߳�Thread-env
    @return void
    */
    virtual void noticeConnClosed(CWX_UINT32 uiSvrId, CWX_UINT32 uiHostId, CWX_UINT32 uiConnId, CwxAppTss* pThrEnv);
    /**
    @brief ����Task����Task����ǰ��Task��Task�Ĵ����߳���ӵ�С�
    ������ǰ��Task���Խ����Լ����첽��Ϣ�������ܴ���
    ��ʱ��Taskboard��noticeActiveTask()�ӿڵ��õġ�
    @param [in] pThrEnv �����̵߳�Thread-env
    @return 0���ɹ���-1��ʧ��
    */
    virtual int noticeActive(CwxAppTss* pThrEnv);
    /**
    @brief ִ��Task���ڵ��ô�APIǰ��Task��Taskboard�в����ڣ�Ҳ����˵�Ա���̲߳��ɼ���
    TaskҪô�Ǹմ���״̬��Ҫô�������ǰһ���׶εĴ����������״̬��
    ͨ���˽ӿڣ���Task�Լ������Լ���step����ת����������ϵTask�����ͼ�������̡�
    @param [in] pTaskBoard ����Task��Taskboard
    @param [in] pThrEnv �����̵߳�Thread-env
    @return void
    */
    virtual void execute(CwxAppTss* pThrEnv);
public:
    CwmNerveApp* getApp()
    {
        return m_pApp;
    }
    void setSuccess(bool bSuccess)
    {
        m_bSuccess = bSuccess;
    }
    void setErrMsg(string const& strErrMsg)
    {
        m_strErrMsg = strErrMsg;
    }
public:
    CwxMsgBlock*  m_pMsg;
    CwmNerveActionInfo const*  m_pActionInfo;
    CwmNerveServiceInfo const* m_pServiceInfo;
    CwmNerveServiceStatus* m_pService;
    CwmNerveActionStatus* m_pAction;
private:
    CwmNerveApp*    m_pApp;
    string         m_strResultXml;
    bool           m_bSuccess;
    string         m_strErrMsg;
};


#endif

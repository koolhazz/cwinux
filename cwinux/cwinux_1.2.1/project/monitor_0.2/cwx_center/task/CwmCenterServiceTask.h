#ifndef __CWM_CENTER_SERVICE_TASK_H__
#define __CWM_CENTER_SERVICE_TASK_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterServiceTask.h
@brief ��ѯ����ʾһ��System�����service��Ϣ��Task���塣
@author cwinux@gmail.com
@version 0.1
@date 2009-11-06
@warning
@bug
*/

#include "CwxAppTaskBoard.h"
#include "CwxHtmlTmplLoop.h"
#include "CwxHtmlTmpl.h"
#include "CwmCenterTss.h"
#include "CwmCenterNerveStatus.h"
#include "CwmCenterActionLoop.h"

class CwmCenterApp;

class CwmCenterServiceTask : public CwxAppTaskBoardTask, CwxHtmlTmplLoop
{
public:
    enum
    {
        TASK_STATE_QUERYING = CwxAppTaskBoardTask::TASK_STATE_USER ///<����״̬������ִ�в�ѯ
    };
    ///���캯��
    CwmCenterServiceTask(CwmCenterApp* pApp, CwxAppTaskBoard* pTaskBoard)
        :CwxAppTaskBoardTask(pTaskBoard),m_pApp(pApp)
    {
        m_queryMsg = NULL;
        m_pTss = NULL;
        m_pHostAction = NULL;
        m_uiHostNum = 0;
        m_uiSendMsgNum = 0;
        m_uiRecvMsgNum = 0;
        m_bSuccess = true;
        this->setTaskState(CwxAppTaskBoardTask::TASK_STATE_INIT);
    }
    ///��������
    ~CwmCenterServiceTask()
    {
        if (m_queryMsg) CwxMsgBlockAlloc::free(m_queryMsg);
        m_queryMsg = NULL;
        if (m_pHostAction) delete [] m_pHostAction;
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
    /**
    @brief ��Ϊglobal��loop����û����һ��
    @return 0��û����һ�����ݼ�¼��1���Ƶ�����һ�����ݼ�¼
    */
    virtual int next();
    /**
    @brief ��ȡglobal �����һ��������
    @param [in] szName ����������
    @param [in] ucSysAttr ������ϵͳ���ԣ���CwxHtmlTmplValSysAttr�����˶���
    @param [in] szUserAttr  �û��Լ��ı�������
    @param [in] iLengthLimit ������������ĳ������ƣ�<0��������ַ��������ܳ����˾���ֵ
    0��û�����ƣ�>0��������ֽ������ܳ�������ֵ
    @param [in] pEscape ������escape�任����
    @param [in] szArgs ��������ʱ���õĲ���
    @param [in] pRepl ģ����ַ��滻����
    @param [in] bVal true����Ϊ����ȡֵ��false����Ϊ�Ƚ�ȡֵ
    @return NULL�����������ڣ�����Ϊ��������ֵ
    */
    virtual char const* val(char const* szName,
        bool bAttrName,
        CWX_UINT8 ucSysAttr,
        char const* szUserAttr,
        int iLengthLimit,
        CwxHtmlTmplEscape* pEscape,
        char const* szArgs,
        CwxReplBase* pRepl,
        bool bVal);
    /**
    @brief ����system��loop����
    @param [in] szLoop loop���������
    @param [in] attrs loop�������ʱ�����õ�LOOP�����Զ�
    @return NULL��loop���󲻴��ڣ�����Ϊ��������Ӧ��LOOP����
    */
    virtual CwxHtmlTmplLoop* loop(char const* szLoop,
        list<pair<char*, char*> >const& attrs);
private:
    ///�ظ�UI��ѯ
    void reply();
    ///����ģ�嶨�壬�γɲ�ѯ������
    int  outputTemplate(string& strType);
public:
    CwxMsgBlock*    m_queryMsg; ///<��ѯ��package
    string            m_strSystem; ///<��ѯ��system��
    string            m_strService; ///<��ѯ��service��
    string            m_strAction; ///<��ѯ��actionming
private:
    CwmCenterSystem const*    m_pSystem; ///<system����Ӧ��system����
    CwmCenterService const*   m_pService; ///<service����Ӧ��service����
    CwmCenterActionLoopData* m_pHostAction; ///<��ѯ��nerve���������
    CWX_UINT32               m_uiHostNum; ///<nerve���������
    CWX_UINT32               m_uiSendMsgNum;///<���͵Ĳ�ѯnerve������
    CWX_UINT32               m_uiRecvMsgNum; ///<�յ���nerve�Ļظ�
    bool                    m_bSuccess; ///<��ѯ�Ƿ�ɹ�
    string                   m_strErrMsg; ///<ʧ�ܵĴ�����Ϣ
    CwmCenterApp*    m_pApp; ///<app����
    CwmCenterTss*    m_pTss; ///<tss����
};


#endif

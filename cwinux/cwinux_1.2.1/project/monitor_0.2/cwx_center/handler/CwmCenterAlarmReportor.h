#ifndef __CWM_CENTER_ALARM_REPORTOR_H__
#define __CWM_CENTER_ALARM_REPORTOR_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterAlarmReportor.h
@brief �澯����Ĵ���handle��
@author cwinux@gmail.com
@version 0.1
@date 2009-11-05
@warning
@bug
*/
#include "CwxAppCommander.h"
#include "CwxMutexLock.h"
#include "CwxLockGuard.h"
#include "CwmCenterTss.h"
#include "CwmCmnAlarm.h"
#include "CwmCenterAlarmTask.h"
class CwmCenterApp;
/**
@class CwmCenterAlarmReportor
@brief �澯����Ĵ���handle
*/
class CwmCenterAlarmReportor : public CwxAppCmdOp
{
public:
    enum
    {
        MSG_TYPE_ALARM_REPORT = 1 ///<�澯�������Ϣ����
    };
public:
    ///���캯��
    CwmCenterAlarmReportor(CwmCenterApp* pApp):m_pApp(pApp)
    {
        m_bReporting = false;
    }
    ///��������
    ~CwmCenterAlarmReportor()
    {

    }
public:
    /**
    @brief ����澯���ӵĽ�����
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onConnCreated(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ����澯���ӵĹرա�
    @param [in] msg ���ӹرյ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onConnClosed(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief �����յ��澯�Ļظ���
    @param [in] msg �յ�ͨ�����ݰ����¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief �澯��������¼��Ĵ�������
    @param [in] msg ��Ϣ������ϵ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onEndSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief �澯����ʧ���¼��Ĵ�������
    @param [in] msg ��Ϣ����ʧ�ܵ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onFailSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
public:
    ///��ȡ������
    CwxMutexLock& getLock()
    {
        return m_lock;
    };
    ///�������ڱ���澯
    void _setReporting(bool bReporting)
    {
        m_bReporting = bReporting;
    }
    ///����Ƿ����ڱ���澯
    bool _isReporting() const
    {
        return m_bReporting;
    }
    ///����ܷ񱨸�澯
    bool _isEnableReport() const 
    {
        return !m_bReporting && !m_connIds.empty();
    }
    ///��ȡ��ǰ����澯������id
    CWX_UINT32 _getReportConnId()
    {
        if (m_connIds.empty()) return CWX_APP_INVALID_CONN_ID;
        return *m_connIds.begin();
    }
    ///����avg�澯����ģʽ�����Ѿ�����澯�����ӷŵ����ӳص�β��
    void _switchConnToEnd()
    {
        if (!m_connIds.empty())
        {
            m_connIds.push_back(*m_connIds.begin());
            m_connIds.pop_front();
        }
    }
public:
    ///������һ���澯
    static void reportNextAlarm(CwmCenterApp* pApp, CwxAppTss* pThrEnv);
    ///����һ������
    static bool sendAlarm(CwmCenterApp* pApp,
        CwxAppTss* pThrEnv,
        CWX_UINT32 uiConnId,
        CWX_UINT32 uiTaskId,
        string const& strMails,
        CwmCmnAlarm const& alarm);
private:
    CwxMutexLock       m_lock; ///<����m_bReporting��m_connIds����
    CwmCenterApp*      m_pApp; ///<app����
    bool              m_bReporting; ///<�Ƿ����ڱ���澯
    list<CWX_UINT32>    m_connIds; ///<����澯������ID�Ķ���
};


#endif

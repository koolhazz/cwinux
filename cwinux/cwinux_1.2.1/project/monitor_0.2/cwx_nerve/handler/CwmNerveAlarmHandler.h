#ifndef __CWM_NERVE_ALARM_HANDLER_H__
#define __CWM_NERVE_ALARM_HANDLER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmNerveAlarmHandler.h
@brief Nerve�ĸ澯���洦��handle��
@author cwinux@gmail.com
@version 0.1
@date 2009-10-26
@warning
@bug
*/
#include "CwxAppCommander.h"
#include "CwmNerveTss.h"
#include "CwmCmnAlarm.h"
class CwmNerveApp;

/**
@class CwmNerveAlarmHandler
@brief Nerve�ĸ澯���洦��handle�������澯Э��ķ�װ
*/
class CwmNerveAlarmHandler : public CwxAppCmdOp
{
public:
    enum
    {
        MSG_TYPE_ALARM_REPORT = 1 ///<���͸澯����Ϣ����
    };
public:
    ///���캯��
    CwmNerveAlarmHandler(CwmNerveApp* pApp):m_pApp(pApp)
    {
        ///��ʼ״̬�Ǹ澯û�б��棬�澯�ı���ʱ���н��еġ�
        m_bReply = true;
        ///�澯������ID����ʼֵΪ������״̬
        m_uiAlarmConnId = CWX_APP_INVALID_CONN_ID;
    }
    ///��������
    ~CwmNerveAlarmHandler()
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
    @brief �����յ��澯����Ļظ���Ϣ��
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
    ///�Ƿ��յ��澯����Ļظ�����û�У��򲻷�����һ���澯�����ǳ�ʱ 
    bool isReportReply() const
    {
        return m_bReply;
    }
    ///���ñ���ĸ澯�Ƿ�ظ�
    void setReportReply(bool bReply)
    {
        m_bReply = bReply;
    }
    ///��ȡ�澯���������id
    CWX_UINT32 getAlarmConnId() const
    {
        return m_uiAlarmConnId;
    }
public:
    ///��̬��������װ�澯�����Э��
    static bool sendAlarm(CwmNerveApp* pApp, CwxAppTss* pThrEnv, CwmCmnAlarm const& alarm);
    ///��̬��������װ������һ���澯���߼�
    static void reportNextAlarm(CwmNerveApp* pApp, CwxAppTss* pThrEnv);
private:
    CwmNerveApp*      m_pApp; ///<Ӧ�õ�APP����
    bool             m_bReply; ///<�Ƿ��յ���һ���澯�Ļظ�
    CWX_UINT32        m_uiAlarmConnId; ///<�澯���������ID
};


#endif

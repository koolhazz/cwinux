#ifndef __CWM_CMN_ALARM_STATUS_H__
#define __CWM_CMN_ALARM_STATUS_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCmnAlarmStatus.h
@brief Alarm��״̬��������塣
@author cwinux@gmail.com
@version 0.1
@date 2009-10-28
@warning
@bug
*/
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxPackage.h"
#include "CwmCmnMacro.h"
#include "CwmCmnRecord.h"
#include "CwmCmnAlarm.h"
#include "CwmCmnAlarmRule.h"

/**
@class CwmCmnAlarmStatus
@brief Alarm״̬������
*/
class CwmCmnAlarmStatus
{
public:
    ///���캯��
    CwmCmnAlarmStatus()
    {
        m_uiWid =0;
        m_ucAlarm = CwmCmnAlarm::ALARM_CLEAR;
        m_llLastPollTime = 0;
        m_uiSuccessCount = 0;
        m_uiFailCount = 0;
        m_bFault = false;
        m_isPolling = false;
        m_uiPWid = 0;
        m_ucPAlarm = CwmCmnAlarm::ALARM_CLEAR;
        m_pAlarmRule =  NULL;
    }
    ///��������
    ~CwmCmnAlarmStatus()
    {

    }
public:
    /**
    @brief ����poll�ķ��ؽ��������action��״̬�����澯Level�����ı䣬�򷵻ظ澯��
    @param [in] strStatus poll���ص�statues
    @param [in] strLevel poll���ص�level
    @param [in] strErrMsg poll���صĴ�����Ϣ
    @return true���γ����µĸ澯��false���澯״̬û�иı�
    */
    bool update(string const& strStatus,
        string const& strLevel,
        string const& strErrMsg);
public:
    ///��ȡ��ǰ�澯��WID
    CWX_UINT32 getWid() const
    {
        return m_uiWid;
    }
    ///���õ�ǰ�澯��WID
    void setWid(CWX_UINT32 uiWid)
    {
        m_uiWid = uiWid;
    }
    ///��ȡ״̬
    CWX_UINT8 getAlarm() const
    {
        return m_ucAlarm;
    }
    ///����alarm
    void setAlarm(CWX_UINT8 ucAlarm)
    {
        m_ucAlarm = ucAlarm;
    }
    ///��ȡ��һ��poll��ʱ��
    CWX_UINT64 getLastPollTime() const
    {
        return m_llLastPollTime;
    }
    ///������һ��poll��ʱ��
    void setLastPollTime(CWX_UINT64 ullTime)
    {
        m_llLastPollTime = ullTime;
    }
    ///��ȡ��ʧ��״̬�£������ɹ��Ĵ���
    CWX_UINT32 getSuccessCount() const
    {
        return m_uiSuccessCount;
    }
    ///������ʧ��״̬�£������ɹ��Ĵ���
    void setSuccesCount(CWX_UINT32 uiCount)
    {
        m_uiSuccessCount = uiCount;
    }
    ///��ȡ�ڵ�ǰ״̬�£�����ʧ�ܵĴ���
    CWX_UINT32 getFailCount() const
    {
        return m_uiFailCount;
    }
    ///�����ڵ�ǰ״̬�£�����ʧ�ܵĴ���
    void setFailCount(CWX_UINT32 uiCount)
    {
        m_uiFailCount = uiCount;
    }
    ///��ȡǰһ���澯��WID
    CWX_UINT32 getPWid() const
    {
        return m_uiPWid;
    }
    ///����ǰһ���澯��WID
    void setPWid(CWX_UINT32 uiWid)
    {
        m_uiPWid = uiWid;
    }
    ///��ȡǰһ���澯��״̬
    CWX_UINT8 getPAlarm() const
    {
        return m_ucPAlarm;
    }
    ///����ǰһ���澯��״̬
    void setPAlarm(CWX_UINT8 ucPAlarm)
    {
        m_ucPAlarm = ucPAlarm;
    }
    ///��ȡ�Ƿ��д�����
    bool isFault() const
    {
        return m_bFault;
    }
    ///�����д�����
    void setFault(bool bFault)
    {
        m_bFault = bFault;
    }
    ///��ȡ������Ϣ
    string const& getErrMsg() const
    {
        return m_strErrMsg;
    }
    ///���ô�����Ϣ
    void setErrMsg(string const& strErrMsg)
    {
        m_strErrMsg = strErrMsg;
    }
    ///��ȡalarm����
    CwmCmnAlarmRule const* getAlarmRule() const
    {
        return m_pAlarmRule;
    }
    ///����alarm����
    void setAlarmRule(CwmCmnAlarmRule const* pRule)
    {
        m_pAlarmRule = pRule;
    }
    ///��ȡϵͳ������
    string const& getSystemName() const
    {
        return m_strSystemName;
    }
    ///����ϵͳ������
    void setSystemName(string const& strName)
    {
        m_strSystemName = strName;
    }
    ///��ȡ���������
    string const& getServiceName() const
    {
        return m_strServiceName;
    }
    ///���÷��������
    void setServiceName(string const& strName)
    {
        m_strServiceName = strName;
    }
    ///��ȡaction������
    string const& getActionName() const
    {
        return m_strActionName;
    }
    ///����action������
    void setActionName(string const& strName)
    {
        m_strActionName = strName;
    }
    ///��ȡ�澯������
    string const& getAlarmType() const 
    {
        return m_strAlarmType;
    }
    ///���ø澯������
    void setAlarmType(string const& strAlarmType)
    {
        m_strAlarmType = strAlarmType;
    }
    ///����Ƿ�����ִ��polling
    bool isPolling() const
    {
        return m_isPolling;
    }
    ///�����Ƿ�����polling
    void setPolling(bool bPolling)
    {
        m_isPolling = bPolling;
    }
    ///����Ƿ�Ӧ�ý���״̬��ѯ
    bool isNeedPoll(CWX_UINT64 ullNow) const
    {
        return m_llLastPollTime/1000000 + m_pAlarmRule->getPollSecond() <= ullNow/1000000;
    }
    ///����action����Ϣ����ʼ���澯��Ϣ
    void formActionAlarm(string const& strHost,
        CWX_UINT32 uiWid,
        CWX_UINT32 uiPid,
        CwmCmnAlarm& alarm) const;
    ///����action����Ϣ����ʼ����¼��Ϣ
    void formActionRecord(string const& strHost,
        CWX_UINT32 uiWid,
        CWX_UINT32 uiPid,
        CwxKeyValueItem const& kvRecord,
        CwmCmnRecord& record) const;
private:
    ///���õ�ָ���ĸ澯����
    void toAlarmLevel(CWX_UINT8 ucNewLevel);
private:
    ///��ֹ��������
    CwmCmnAlarmStatus(CwmCmnAlarmStatus const& )
    {

    }
    ///��ֹ��ֵ����
    CwmCmnAlarmStatus & operator=(CwmCmnAlarmStatus const& )
    {
        return *this;
    }
private:
    CWX_UINT32    m_uiWid; ///<��ǰ�澯��Wid
    CWX_UINT8      m_ucAlarm;///<��ǰ�ĸ澯״̬
    CWX_UINT64     m_llLastPollTime;///<�ϴ���ѯ��ʱ��
    CWX_UINT32     m_uiSuccessCount;///<�����ɹ��Ĵ���
    CWX_UINT32     m_uiFailCount; ///<����Ч״̬״̬���������۵�ʧ�ܴ���
    bool           m_bFault; ///<������ALARM_CLEAR��Ҳ���ܷ������󣬴��Ǽ�¼�Ƿ��д�����
    string         m_strErrMsg; ///<�澯�Ĵ�����Ϣ
    CwmCmnAlarmRule const*  m_pAlarmRule;///<�澯����
    string          m_strSystemName; ///<�澯��system����
    string          m_strServiceName;///<�澯��service����
    string          m_strActionName;///<�澯��action����
    string          m_strAlarmType;///<�澯������
    CWX_UINT32  m_uiPWid; ///<ǰһ���澯ID��
    CWX_UINT8   m_ucPAlarm; ///<ǰһ���澯��״̬
    bool           m_isPolling; ///<��ǰ�澯��action�Ƿ�������ѯ��
};



#endif

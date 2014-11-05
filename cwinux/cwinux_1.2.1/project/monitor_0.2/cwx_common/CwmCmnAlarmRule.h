#ifndef __CWM_CMN_ALARM_RULE_H__
#define __CWM_CMN_ALARM_RULE_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCmnAlarmRule.h
@brief �澯�����塣
@author cwinux@gmail.com
@version 0.1
@date 2009-10-24
@warning
@bug
*/
#include "CwxType.h"
#include "CwxStl.h"
#include "CwmCmnMacro.h"
#include "CwmCmnAlarm.h"

/**
@class CwmCmnAlarmRule
@brief �澯�������
*/
class CwmCmnAlarmRule
{
    enum{
        DEF_POLL_SECOND = 10, ///<ȱʡ��pollʱ����
        DEF_CLEAR_TIME  = 2, ///<ȱʡ�澯�������������
        DEF_WARNING_TIME = 2, ///<���쳣״̬�����ٴ��쳣����Ϊwarning�澯
        DEF_MINOR_TIME = 30, ///<��warning״̬�����ٴ��쳣����ΪMINOR�澯
        DEF_MAJOR_TIME = 60, ///<��minor״̬�����ٴ��쳣����ΪMAJOR�澯
        DEF_CRITICAL_TIME = 120, ///<��major״̬�����ٴ��쳣����ΪCRITICAL�澯
        DEF_FATAL_TIME = 240, ///<��Critical״̬�����ٴ��쳣����ΪFATAL�澯
    };
public:
    ///Ĭ�Ϲ��캯��
    CwmCmnAlarmRule()
    {
        m_uiPollSecond = DEF_POLL_SECOND;
        m_uiClearTime = DEF_CLEAR_TIME;
        m_uiWarningTime = DEF_WARNING_TIME;
        m_uiMinorTime = DEF_MINOR_TIME;
        m_uiMajorTime = DEF_MAJOR_TIME;
        m_uiCriticalTime = DEF_CRITICAL_TIME;
        m_uiFatalTime = DEF_FATAL_TIME;
    }
    ///���캯��
    CwmCmnAlarmRule(string const& name,
                   CWX_UINT32  uiPollSecond = DEF_POLL_SECOND,
                   CWX_UINT32  uiClearTime = DEF_CLEAR_TIME,
                   CWX_UINT32  uiWarningTime = DEF_WARNING_TIME,
                   CWX_UINT32  uiMinorTime = DEF_MINOR_TIME,
                   CWX_UINT32  uiMajorTime = DEF_MAJOR_TIME,
                   CWX_UINT32  uiCriticalTime = DEF_CRITICAL_TIME,
                   CWX_UINT32  uiFatalTime = DEF_FATAL_TIME)
    {
        m_strName = name;
        m_uiPollSecond = uiPollSecond;
        m_uiClearTime = uiClearTime;
        m_uiWarningTime = uiWarningTime;
        m_uiMinorTime = uiMinorTime;
        m_uiMajorTime = uiMajorTime;
        m_uiCriticalTime = uiCriticalTime;
        m_uiFatalTime = uiFatalTime;
    }
    ///��������
    CwmCmnAlarmRule(CwmCmnAlarmRule const& obj)
    {
        m_strName = obj.m_strName;
        m_uiPollSecond = obj.m_uiPollSecond;
        m_uiClearTime = obj.m_uiClearTime;
        m_uiWarningTime = obj.m_uiWarningTime;
        m_uiMinorTime = obj.m_uiMinorTime;
        m_uiMajorTime = obj.m_uiMajorTime;
        m_uiCriticalTime = obj.m_uiCriticalTime;
        m_uiFatalTime = obj.m_uiFatalTime;
    }
    ///��ֵ����
    CwmCmnAlarmRule& operator=(CwmCmnAlarmRule const& obj)
    {
        if (this != &obj)
        {
            m_strName = obj.m_strName;
            m_uiPollSecond = obj.m_uiPollSecond;
            m_uiClearTime = obj.m_uiClearTime;
            m_uiWarningTime = obj.m_uiWarningTime;
            m_uiMinorTime = obj.m_uiMinorTime;
            m_uiMajorTime = obj.m_uiMajorTime;
            m_uiCriticalTime = obj.m_uiCriticalTime;
            m_uiFatalTime = obj.m_uiFatalTime;
        }
        return *this;
    }
    ///��Ȳ���
    inline bool operator == (CwmCmnAlarmRule const& obj) const
    {
        return m_strName == obj.m_strName;
    }
public:
    ///��������
    inline void setName(string const& strName)
    {
        m_strName = strName;
    }
    ///��ȡ����
    inline string const& getName() const
    {
        return m_strName;
    }
    ///����poll���
    inline void setPollSecond(CWX_UINT32 uiSecond)
    {
        m_uiPollSecond = uiSecond;
    }
    ///��ȡpoll���
    inline CWX_UINT32 getPollSecond() const
    {
        return m_uiPollSecond;
    }
    ///���ø澯����������
    inline void setClearTime(CWX_UINT32 uiTime)
    {
        m_uiClearTime = uiTime;
    }
    ///��ȡ�澯���������
    inline CWX_UINT32 getClearTime() const
    {
        return m_uiClearTime;
    }
    ///����Warning�澯������
    inline void setWarningTime(CWX_UINT32 uiTime)
    {
        m_uiWarningTime = uiTime;
    }
    ///��ȡWarning�澯������
    inline CWX_UINT32 getWarningTime() const
    {
        return m_uiWarningTime;
    }
    ///����Minor�澯������
    inline void setMinorTime(CWX_UINT32 uiTime)
    {
        m_uiMinorTime = uiTime;
    }
    ///��ȡMinor�澯������
    inline CWX_UINT32 getMinorTime() const
    {
        return m_uiMinorTime;
    }
    ///����Major�澯������
    inline void setMajorTime(CWX_UINT32 uiTime)
    {
        m_uiMajorTime = uiTime;
    }
    ///��ȡMajor�澯������
    inline CWX_UINT32 getMajorTime() const
    {
        return m_uiMajorTime;
    }
    ///����Critical�澯������
    inline void setCriticalTime(CWX_UINT32 uiTime)
    {
        m_uiCriticalTime = uiTime;
    }
    ///��ȡCritical�ĸ澯����
    inline CWX_UINT32 getCriticalTime() const
    {
        return m_uiCriticalTime;
    }
    ///����fatal�ĸ澯����
    inline void setFatalTime(CWX_UINT32 uiTime)
    {
        m_uiFatalTime = uiTime;
    }
    ///��ȡfatal�ĸ澯����
    inline CWX_UINT32 getFatalTime() const
    {
        return m_uiFatalTime;
    }
    ///�жϸ澯�Ƿ����clear
    inline bool isAlarmClear(CWX_UINT32 uiSuccessTime) const
    {
        return uiSuccessTime>=m_uiClearTime;
    }
    ///�жϸ澯�Ƿ���Ҫ����
    inline bool isAlarmUp(CWX_UINT8 ucLevel,
        CWX_UINT32 uiFailTime,
        CWX_UINT8& ucNewAlarm) const
    {
        bool bUp=false;
        switch(ucLevel)
        {
            case CwmCmnAlarm::ALARM_CLEAR:
                if (uiFailTime >= m_uiWarningTime)
                {
                    bUp = true;
                    ucNewAlarm = CwmCmnAlarm::ALARM_WARNING;
                }
                break;
            case CwmCmnAlarm::ALARM_WARNING:
                if (uiFailTime >= m_uiMinorTime)
                {
                    bUp = true;
                    ucNewAlarm = CwmCmnAlarm::ALARM_MINOR;
                }
                break;
            case CwmCmnAlarm::ALARM_MINOR:
                if (uiFailTime >= m_uiMajorTime)
                {
                    bUp = true;
                    ucNewAlarm = CwmCmnAlarm::ALARM_MAJOR;
                }
                break;
            case CwmCmnAlarm::ALARM_MAJOR:
                if (uiFailTime >= m_uiCriticalTime)
                {
                    bUp = true;
                    ucNewAlarm = CwmCmnAlarm::ALARM_CRITICAL;
                }
                break;
            case CwmCmnAlarm::ALARM_CRITICAL:
                if (uiFailTime >= m_uiFatalTime)
                {
                    bUp = true;
                    ucNewAlarm = CwmCmnAlarm::ALARM_FATAL;
                }
                break;
            case CwmCmnAlarm::ALARM_FATAL:
                if (uiFailTime >= m_uiFatalTime)
                {
                    bUp = true;
                    ucNewAlarm = CwmCmnAlarm::ALARM_FATAL;
                }
                break;
            default: ///��ALARM_FATAL��ʽ����
                if (uiFailTime >= m_uiFatalTime)
                {
                    bUp = true;
                    ucNewAlarm = CwmCmnAlarm::ALARM_FATAL;
                }
                break;
        }
        return bUp;
    }
public:
    ///��ն���
    inline void reset()
    {
        m_strName.erase();
        m_uiPollSecond = DEF_POLL_SECOND;
        m_uiClearTime = DEF_CLEAR_TIME;
        m_uiWarningTime = DEF_WARNING_TIME;
        m_uiMinorTime = DEF_MINOR_TIME;
        m_uiMajorTime = DEF_MAJOR_TIME;
        m_uiCriticalTime = DEF_CRITICAL_TIME;
        m_uiFatalTime = DEF_FATAL_TIME;
    }
private:
    string         m_strName; ///<rule������
    CWX_UINT32     m_uiPollSecond; ///<poll's internal
    CWX_UINT32     m_uiClearTime; ///<reset alarm's poll count
    CWX_UINT32     m_uiWarningTime; ///<��ѯʧ�ܶ��ٴκ�����Ϊ�澯
    CWX_UINT32     m_uiMinorTime; ///<��warning��ʼ����ѯʧ�ܶ��ٴκ�����ΪMinor
    CWX_UINT32     m_uiMajorTime; ///<��Minor��ʼ����ѯʧ�ܶ��ٴκ�����ΪMajor
    CWX_UINT32     m_uiCriticalTime; ///<��Major��ʼ����ѯʧ�ܶ��ٴκ�����ΪCritical
    CWX_UINT32     m_uiFatalTime; ///<��Critical��ʼ����ѯʧ�ܶ��ٴκ�����ΪFatal
};



#endif

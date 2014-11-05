#ifndef __CWM_CMN_ALARM_H__
#define __CWM_CMN_ALARM_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCmnAlarm.h
@brief �澯����Ķ����ļ���
@author cwinux@gmail.com
@version 0.1
@date 2009-10-27
@warning
@bug
*/
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwmCmnMacro.h"


/**
@class CwmCmnAlarm
@brief Nerve�ĸ澯����
*/

class CwmCmnAlarm
{
public:
    enum
    {
        ALARM_CLEAR = 0, ///<�澯���
        ALARM_WARNING = 1, ///<���漶�澯
        ALARM_MINOR = 2, ///<minor���澯
        ALARM_MAJOR = 3, ///<major���澯
        ALARM_CRITICAL = 4, ///<critical���澯
        ALARM_FATAL = 5, ///<fatal���澯
        ALARM_NUM = 6 ///<�澯���������
    };
    enum
    {
        ALARM_STATE_INIT = 0, ///<δ����״̬
        ALARM_STATE_REPORTED = 1, ///<�Ѿ�����
        ALARM_STATE_DEL = 2 ///<ɾ��״̬
    };
public:
    ///���캯��
    CwmCmnAlarm()
    {
        m_uiWid = 0;
        m_uiPid = 0;
        m_ucLevel = ALARM_CLEAR;
        m_ucState = ALARM_STATE_INIT;
        m_uiPWid = 0;
        m_ucPLevel = ALARM_CLEAR;
    }
    ///��������
    ~CwmCmnAlarm()
    {

    }
    ///���캯��
    CwmCmnAlarm(string const& strHost,
                 CWX_UINT32 uiWid,
                 CWX_UINT32 uiPid,
                 string const& strDatetime,
                 CWX_UINT8 ucLevel,
                 string const& strSystem,
                 string const& strService,
                 string const& strAction,
                 string const& strType,
                 CWX_UINT8 ucState,
                 CWX_UINT32 uiPWid,
                 CWX_UINT8 ucPLevel,
                 string const& strErr)
    {
        m_strHost = strHost;
        m_uiWid = uiWid;
        m_uiPid = uiPid;
        m_strDatetime = strDatetime;
        m_ucLevel = ucLevel;
        m_strSystem = strSystem;
        m_strService = strService;
        m_strAction = strAction;
        m_strType = strType;
        m_ucState = ucState;
        m_uiPWid = uiPWid;
        m_ucPLevel = ucPLevel;
        m_strError = strErr;
    }
    ///��������
    CwmCmnAlarm(CwmCmnAlarm const& obj)
    {
        m_strHost = obj.m_strHost;
        m_uiWid = obj.m_uiWid;
        m_uiPid = obj.m_uiPid;
        m_strDatetime = obj.m_strDatetime;
        m_ucLevel = obj.m_ucLevel;
        m_strSystem = obj.m_strSystem;
        m_strService = obj.m_strService;
        m_strAction = obj.m_strAction;
        m_strType = obj.m_strType;
        m_ucState = obj.m_ucState;
        m_uiPWid = obj.m_uiPWid;
        m_ucPLevel = obj.m_ucPLevel;
        m_strError = obj.m_strError;
    }
    ///��ֵ����
    CwmCmnAlarm& operator=(CwmCmnAlarm const& obj)
    {
        if (this != &obj)
        {
            m_strHost = obj.m_strHost;
            m_uiWid = obj.m_uiWid;
            m_uiPid = obj.m_uiPid;
            m_strDatetime = obj.m_strDatetime;
            m_ucLevel = obj.m_ucLevel;
            m_strSystem = obj.m_strSystem;
            m_strService = obj.m_strService;
            m_strAction = obj.m_strAction;
            m_strType = obj.m_strType;
            m_ucState = obj.m_ucState;
            m_uiPWid = obj.m_uiPWid;
            m_ucPLevel = obj.m_ucPLevel;
            m_strError = obj.m_strError;
        }
        return *this;
    }
    ///��ȱȽ�
    bool operator == (CwmCmnAlarm const& obj) const
    {
        return (m_strHost == obj.m_strHost) && (m_uiWid == obj.m_uiWid);
    }
    ///С�ڱȽ�
    bool operator < (CwmCmnAlarm const& obj) const
    {
        if (m_strHost < obj.m_strHost) return true;
        if (m_strHost > obj.m_strHost) return false;
        return m_uiWid < obj.m_uiWid;
    }
public:
    ///��ȡ�澯��host
    string const& getHost() const
    {
        return m_strHost;
    }
    ///���ø澯��host
    void setHost(string const& strHost)
    {
        m_strHost = strHost;
    }
    ///��ȡ�澯��id
    CWX_UINT32 getWid() const
    {
        return m_uiWid;
    }
    ///���ø澯��id
    void setWid(CWX_UINT32 uiId)
    {
        m_uiWid = uiId;
    }
    ///��ȡ�澯��Ӧ������ID
    CWX_UINT32 getPid() const
    {
        return m_uiPid;
    }
    ///���ø澯��Ӧ������ID
    void setPid(CWX_UINT32 uiId)
    {
        m_uiPid = uiId;
    }
    ///��ȡ�澯��ʱ��
    string const& getDatetime() const
    {
        return m_strDatetime;
    }
    ///���ø澯��ʱ��
    void setDatetime(string const& strDatetime)
    {
        m_strDatetime = strDatetime;
    }
    ///��ȡ�澯�ļ���
    CWX_UINT8 getLevel() const
    {
        return m_ucLevel;
    }
    ///���ø澯�ļ���
    void setLevel(CWX_UINT8 ucLevel)
    {
        m_ucLevel = ucLevel;
    }
    ///���ø澯����
    void setLevel(string const& strLevel)
    {
        m_ucLevel = getAlarmCode(strLevel);
    }
    ///��ȡ�澯������system
    string const& getSystem() const 
    {
        return m_strSystem;
    }
    ///���ø澯������system
    void setSystem(string const& strSystem)
    {
        m_strSystem = strSystem;
    }
    ///��ȡ�澯������service
    string const& getService() const
    {
        return m_strService;
    }
    ///���ñ���������service
    void setService(string const& strService)
    {
        m_strService = strService;
    }
    ///��ȡ�澯������action
    string const& getAction() const
    {
        return m_strAction;
    }
    ///���ø澯������action
    void setAction(string const& strAction)
    {
        m_strAction = strAction;
    }
    ///��ȡ�澯����
    string const& getType() const
    {
        return m_strType;
    }
    ///���ø澯����
    void setType(string const& strType)
    {
        m_strType = strType;
    }
    ///��ȡ�澯��״̬
    CWX_UINT8 getState() const
    {
        return m_ucState;
    }
    ///���ø澯��״̬
    void setState(CWX_UINT8 ucState)
    {
        m_ucState = ucState;
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
    ///��ȡǰһ���澯��LEVEL
    CWX_UINT8 getPLevel() const
    {
        return m_ucPLevel;
    }
    ///����ǰһ���澯��LEVEL
    void setPLevel(CWX_UINT8 ucLevel)
    {
        m_ucPLevel = ucLevel;
    }
    ///��ȡ�澯�Ĵ�������
    string const& getError() const
    {
        return m_strError;
    }
    ///���ø澯�Ĵ�������
    void setError(string const& strErr)
    {
        m_strError = strErr;
    }
public:
    ///���ݸ澯��code����ȡ�澯���ַ���
    inline static string const& getAlarmString(CWX_UINT8 ucLevel)
    {
        if (ucLevel > ALARM_FATAL) ucLevel = ALARM_FATAL;
        return m_arrAlarms[ucLevel];
    }
    ///���ݸ澯���ַ�������ȡ�澯��code
    inline static CWX_UINT8 getAlarmCode(string const& strLevel)
    {
        for (CWX_UINT8 i=0; i<ALARM_NUM; i++)
        {
            if (strcasecmp(strLevel.c_str(), m_arrAlarms[i].c_str()) == 0)
            {
                return i;
            }
        }
        return ALARM_FATAL;
    }
    ///�ж�ָ���ĸ澯�����Ƿ�һ����Ч�ļ���
    inline static bool isExistAlarm(string const& strLevel)
    {
        for (CWX_UINT8 i=0; i<ALARM_NUM; i++)
        {
            if (strcasecmp(strLevel.c_str(), m_arrAlarms[i].c_str()) == 0)
            {
                return true;
            }
        }
        return false;
    }
private:
    string      m_strHost; ///<�澯������
    CWX_UINT32  m_uiWid;///<�澯��id
    CWX_UINT32  m_uiPid; ///<�澯��Ӧ�����ܼ�¼id
    string      m_strDatetime; ///<�澯������ʱ��
    CWX_UINT8   m_ucLevel; ///<�澯�ļ���
    string      m_strSystem; ///<�����澯��ϵͳ
    string      m_strService; ///<�����澯�ķ���
    string      m_strAction; ///<�����澯��action
    string      m_strType; ///<�澯����
    CWX_UINT8   m_ucState; ///<�澯��״̬
    string      m_strError; ///<�澯��������Ϣ
    CWX_UINT32  m_uiPWid; ///<ǰһ���澯ID��
    CWX_UINT8   m_ucPLevel; ///<ǰһ���澯��Level
    static string  m_arrAlarms[ALARM_NUM];
};

#endif

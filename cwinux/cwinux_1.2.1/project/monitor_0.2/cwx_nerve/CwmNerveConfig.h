#ifndef __CWM_NERVE_CONFIG_H__
#define __CWM_NERVE_CONFIG_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmNerveConfig.h
@brief Nerve������������ļ���
@author cwinux@gmail.com
@version 0.1
@date 2009-10-25
@warning
@bug
*/

#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxXmlFileConfigParser.h"
#include "CwmCmnMacro.h"
#include "CwmCmnAlarm.h"
#include "CwmCmnAlarmRule.h"

/**
@class CwmNerveActionInfo
@brief Nerve��Action������
*/
class CwmNerveActionInfo
{
public:
    ///Ĭ�Ϲ��캯��
    CwmNerveActionInfo();
    ///CGI����ACTION�Ĺ��캯��
    CwmNerveActionInfo(string const& strName,
        CwmCmnAlarmRule const& alarmRule,
        string const& strAlarmType,
        string const& strCgi,
        bool bPoll = true);
    ///SERVER����ACTION�Ĺ��캯��
    CwmNerveActionInfo(string const& strName,
        CwmCmnAlarmRule const& alarmRule,
        string const& strAlarmType,
        CWX_UINT16 unMsgType,
        bool bPoll = true);
    ///��������
    CwmNerveActionInfo(CwmNerveActionInfo const& obj);
    ///��ֵ����
    CwmNerveActionInfo &operator=(CwmNerveActionInfo const& obj);
    ///��ͬ�Ƚ�
    bool operator ==(CwmNerveActionInfo const& obj) const
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
    ///���ø澯��������
    inline void setAlarmRule(CwmCmnAlarmRule const& alarmRule)
    {
        m_alarmRule = alarmRule;
    }
    ///��ȡ�澯��������
    inline CwmCmnAlarmRule const& getAlarmRule() const
    {
        return m_alarmRule;
    }
    ///�����Ƿ�ִ��poll
    inline void setPoll(bool bPoll)
    {
        m_bPoll = bPoll;
    }
    ///��ȡ�Ƿ�ִ��poll
    inline bool isPoll() const
    {
        return m_bPoll;
    }
    ///�����Ƿ�ΪCGI ACTION
    inline void setCgi(bool bCgi)
    {
        m_bCgiAction = bCgi;
    }
    ///��ȡ�Ƿ�ΪCGI ACTION
    inline bool isCgi() const
    {
        return m_bCgiAction;
    }
    ///���ø澯����
    inline void setAlarmType(string const strType)
    {
        m_strAlarmType = strType;
    }
    ///��ȡ�澯leixing
    inline string const& getAlarmType() const
    {
        return m_strAlarmType;
    }
    ///����CGI������
    inline void setCgiCmd(string const& strCmd)
    {
        m_strCgi = strCmd;
    }
    ///��ȡCGI������
    inline string const& getCgiCmd() const
    {
        return m_strCgi;
    }
    ///������Ϣ����
    inline void setMsgType(CWX_UINT16 unMsgType)
    {
        m_unMsgType = unMsgType;
    }
    ///��ȡ��Ϣ����
    inline CWX_UINT16 getMsgType() const
    {
        return m_unMsgType;
    }
    ///�����Ϣ����
    inline void addArg(string const& strName, string const& strData)
    {
        m_args.push_back(pair<string, string>(strName, strData));
    }
    ///��ȡ��Ϣ����
    inline list<pair<string, string> >const& getArg() const
    {
        return m_args;
    }
    ///�����Ϣ����
    inline void clearArg()
    {
        m_args.clear();
    }
public:
    inline void reset()
    {
        m_strName.erase();
        m_alarmRule.reset();
        m_bPoll = true;
        m_bCgiAction = false;
        m_strAlarmType.erase();
        m_strCgi.erase();
        m_unMsgType = 0;
        m_args.clear();
    }
private:
    string          m_strName; ///<action������
    CwmCmnAlarmRule  m_alarmRule; ///<action�ĸ澯����
    bool            m_bPoll; ///<�Ƿ���Ҫ����poll��ѯ
    bool            m_bCgiAction; ///<�Ƿ�ΪCGI���͵�action
    string          m_strAlarmType; ///<�澯����
    string          m_strCgi; ///<cgi����action��cgi�ű�
    CWX_UINT16      m_unMsgType; ///<��cgi����action����Ϣ����
    list<pair<string, string> > m_args; ///<��cgi����action�Ĳ���
};

/**
@class CwmNerveServiceInfo
@brief Nerve��Service������
*/

class CwmNerveServiceInfo
{
public:
    ///ȱʡ���캯��
    CwmNerveServiceInfo();
    ///cgiģʽ�Ĺ��캯��
    CwmNerveServiceInfo(string const& strName,
        string const& strSystem,
        CwmCmnAlarmRule const& alarmRule);
    ///serverģʽ�Ĺ��캯��
    CwmNerveServiceInfo(string const& strName,
        string const& strSystem,
        CwmCmnAlarmRule const& alarmRule,
        string const& strServerIp,
        CWX_UINT16 unPort);
    ///��������
    CwmNerveServiceInfo(CwmNerveServiceInfo const& obj);
    ///��ֵ����
    CwmNerveServiceInfo& operator=(CwmNerveServiceInfo const& obj);
    ///��ȱȽϲ���
    bool operator==(CwmNerveServiceInfo const& obj) const
    {
        return (m_strName == obj.m_strName) && (m_strSystem == obj.m_strSystem);
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
    ///����ϵͳ��
    inline void setSystem(string const& strSystem)
    {
        m_strSystem = strSystem;
    }
    ///��ȡϵͳ��
    inline string const& getSystem() const
    {
        return m_strSystem;
    }
    ///�����Ƿ�ΪCGI
    inline void setCgi(bool bCgi)
    {
        m_bCgi = bCgi;
    }
    ///��ȡ�Ƿ�ΪCGI
    inline bool isCgi() const
    {
        return m_bCgi;
    }
    ///���ø澯����
    inline void setAlarmRule(CwmCmnAlarmRule const& alarmRule)
    {
        m_alarmRule = alarmRule;
    }
    ///��ȡ�澯����
    inline CwmCmnAlarmRule const& getAlarmRule() const
    {
        return m_alarmRule;
    }
    ///����server ip
    inline void setServerIp(string const& strIp)
    {
        m_strServeIp = strIp;
    }
    ///��ȡserver ip
    inline string const& getServerIp() const
    {
        return m_strServeIp;
    }
    ///����server port
    inline void setPort(CWX_UINT16 unPort)
    {
        m_unPort = unPort;
    }
    ///��ȡserver port
    inline CWX_UINT16 getPort() const
    {
        return m_unPort;
    }
    ///���action
    inline void addAction(CwmNerveActionInfo const& action)
    {
        m_actions.push_back(action);
    }
    ///��ȡһ��action
    inline CwmNerveActionInfo const* getAction(string const& strName) const
    {
        list<CwmNerveActionInfo>::const_iterator iter = m_actions.begin();
        while(iter != m_actions.end())
        {
            if (iter->getName() == strName) return &(*iter);
            iter++;
        }
        return NULL;
    }
    ///��ȡaction �б�
    inline list<CwmNerveActionInfo> const& getActions() const
    {
        return m_actions;
    }
    ///���action
    inline void clearAction()
    {
        m_actions.clear();
    }
public:
    inline void reset()
    {
        m_strName.erase();
        m_strSystem.erase();
        m_bCgi = false;
        m_alarmRule.reset();
        m_strServeIp.erase();
        m_unPort = 0;
        m_actions.clear();
    }

private:
    string   m_strName; ///<service������
    string   m_strSystem; ///<service��ϵͳ����
    bool     m_bCgi; ///<�Ƿ�Ϊcgi
    CwmCmnAlarmRule  m_alarmRule; ///<service�ĸ澯����
    string   m_strServeIp; ///<���ڷ������͵ķ���IP
    CWX_UINT16 m_unPort; ///<���ڷ������͵�port
    list<CwmNerveActionInfo> m_actions; ///<�����action�б�
};

/**
@class CwmNerveConfig
@brief Nerve��������ء��������
*/
class CwmNerveConfig
{
public:
    enum
    {
        DEF_TIMEOUT_SECOND = 10///<ȱʡ�ĳ�ʱʱ��
    };
public:
    CwmNerveConfig()
    {
        m_uiTimeout = DEF_TIMEOUT_SECOND;
        memset(m_szErrMsg, 0x00, sizeof(m_szErrMsg));
    }    
    ~CwmNerveConfig()
    {

    }
public:
    //���������ļ�.false:failure, true:success
    bool loadConfig(string const & strConfFile);
    //��������ļ�
    void outputConfig();
    //��ȡ���������ļ���ʧ�ܴ�����Ϣ
    char const* getErrMsg()
    {
        return m_szErrMsg;
    }
public:
    ///��������Ŀ¼
    inline void setDataPath(string const& strDataPath)
    {
        m_strDbFilePath = strDataPath;
    }
    ///��ȡ����Ŀ¼
    inline string const& getDataPath() const
    {
        return m_strDbFilePath;
    }
    ///���ù���Ŀ¼
    inline void setWorkDir(string const& strWorkDir)
    {
        m_strWorkDir = strWorkDir;
    }
    ///��ȡ����Ŀ¼
    inline string const& getWorkDir() const
    {
        return m_strWorkDir;
    }
    ///���ò�ѯ����
    inline void setQueryListen(CwxHostInfo const& host)
    {
        m_queryListen = host;
    }
    ///��ȡ��ѯ����
    inline CwxHostInfo const& getQueryListen() const
    {
        return m_queryListen;
    }
    ///���ù���˿ڵļ���
    inline void setMgrListen(CwxHostInfo const& host)
    {
        m_mgrListen = host;
    }
    ///��ȡ����˿ڵļ���
    inline CwxHostInfo const& getMgrListen() const
    {
        return m_mgrListen;
    }
    ///���ø澯host
    inline void setAlarmListen(CwxHostInfo const& host)
    {
        m_alarmListen = host;
    }
    ///��ȡ�澯host
    inline CwxHostInfo const& getAlarmListen() const
    {
        return m_alarmListen;
    }
    ///���ó�ʱ
    inline void setTimeout(CWX_UINT32 uiTimeout)
    {
        m_uiTimeout = uiTimeout;
    }
    ///��ȡ��ʱ
    inline CWX_UINT32 getTimeout() const
    {
        return m_uiTimeout;
    }
    ///���ýڵ��host������
    inline void setHostName(string const& strHostName)
    {
        m_strHostName = strHostName;
    }
    ///��ȡ�ڵ��host������
    inline string const& getHostName() const
    {
        return m_strHostName;
    }
    ///���һ���澯����
    inline void addAlarmRule(CwmCmnAlarmRule const& rule)
    {
        m_alarmRules[rule.getName()] = rule;
    }
    ///ɾ��һ���澯����
    inline bool eraseAlarmRule(string const& strName)
    {
        map<string, CwmCmnAlarmRule>::iterator iter=m_alarmRules.find(strName);
        if (iter != m_alarmRules.end())
        {
            m_alarmRules.erase(iter);
            return true;
        }
        return false;
    }
    ///��ȡһ���澯����
    inline CwmCmnAlarmRule const* getAlarmRule(string const& strName) const
    {
        map<string, CwmCmnAlarmRule>::const_iterator iter=m_alarmRules.find(strName);
        if (iter != m_alarmRules.end())
        {
            return &iter->second;
        }
        return NULL;
    }
    ///�޸�һ���澯����
    inline bool modifyAlarmRule(CwmCmnAlarmRule const& rule)
    {
        map<string, CwmCmnAlarmRule>::iterator iter=m_alarmRules.find(rule.getName());
        if (iter != m_alarmRules.end())
        {
            iter->second = rule;
            return true;
        }
        return false;
    }
    ///��ȡ���еĹ���
    map<string, CwmCmnAlarmRule> const& getAlarmRules() const
    {
        return m_alarmRules;
    }
    ///������и澯����
    inline void clearAlarmRule()
    {
        m_alarmRules.clear();
    }
    ///���һ��service
    inline void addService(CwmNerveServiceInfo const& service)
    {
        pair<string, string> key(service.getSystem(), service.getName());
        m_services[key] = service;
    }
    ///ɾ��һ��service
    inline bool eraseService(string const& strSystem, string const& strName)
    {
        pair<string, string> key(strSystem, strName);
        map<pair<string, string> , CwmNerveServiceInfo>::iterator iter=m_services.find(key);
        if (iter != m_services.end())
        {
            m_services.erase(iter);
            return true;
        }
        return false;
    }
    ///��ȡһ��service
    inline CwmNerveServiceInfo const* getService(string const& strSystem, string const& strName) const
    {
        pair<string, string> key(strSystem, strName);
        map<pair<string,string>, CwmNerveServiceInfo>::const_iterator iter=m_services.find(key);
        if (iter != m_services.end())
        {
            return &iter->second;
        }
        return NULL;
    }
    ///�޸�һ��service
    inline bool modifyService(CwmNerveServiceInfo const& service)
    {
        pair<string, string> key(service.getSystem(), service.getName());
        map<pair<string,string>, CwmNerveServiceInfo>::iterator iter=m_services.find(key);
        if (iter != m_services.end())
        {
            iter->second = service;
            return true;
        }
        return false;
    }
    ///��ȡ���е�service
    map<pair<string,string>, CwmNerveServiceInfo> const& getServices() const
    {
        return m_services;
    }
    ///�������service
    inline void clearService()
    {
        m_services.clear();
    }
public:
    void reset()
    {
        m_strWorkDir.erase();
        m_queryListen.reset();
        m_mgrListen.reset();
        m_alarmListen.reset();
        m_uiTimeout = DEF_TIMEOUT_SECOND;
        m_strHostName.erase();
        m_alarmRules.clear();
        m_services.clear();
        m_szErrMsg[0] = 0x00;
    }
private:
    CwmNerveConfig& operator=(CwmNerveConfig const& )
    {
        return *this;
    }

private:
    string              m_strWorkDir; ///<����Ŀ¼
    string              m_strDbFilePath; ///<db file
    CwxHostInfo       m_queryListen; ///<��ѯ�����˿�
    CwxHostInfo       m_mgrListen; ///<����˿ڵļ���
    CwxHostInfo       m_alarmListen; ///<CWX_CENTER�ĸ澯���ն˿�
    CWX_UINT32           m_uiTimeout; ///<timeoutֵ
    string               m_strHostName; ///<������
    map<string, CwmCmnAlarmRule> m_alarmRules; ///<�澯�������map
    map<pair<string,string>, CwmNerveServiceInfo> m_services; ///<��ص�service
    char                m_szErrMsg[512];///<������Ϣbuf
};

#endif

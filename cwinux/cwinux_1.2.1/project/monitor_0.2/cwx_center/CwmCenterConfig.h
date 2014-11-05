#ifndef __CWM_CENTER_CONFIG_H__
#define __CWM_CENTER_CONFIG_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterConfig.h
@brief Center������������ļ���
@author cwinux@gmail.com
@version 0.1
@date 2009-11-2
@warning
@bug
*/

#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxXmlFileConfigParser.h"
#include "CwxHtmlTmpl.h"
#include "CwmCmnMacro.h"
#include "CwmCmnAlarm.h"
#include "CwmCmnAlarmRule.h"

/**
@class CwmCenterTemplate
@brief �����е�ģ�������
*/

class CwmCenterTemplate
{
public:
    ///���캯��
    CwmCenterTemplate()
    {

    }
    ///���캯��
    CwmCenterTemplate(string const& strName, string const& strFile, string const& strType):
    m_strName(strName), m_strFile(strFile), m_strType(strType)
    {
    }
    ///��������
    ~CwmCenterTemplate()
    {

    }
public:
    ///��ȡ����
    string const& getName() const
    {
        return m_strName;
    }
    ///��������
    void setName(string const& strName)
    {
        m_strName = strName;
    }
    ///��ȡģ���ļ�������
    string const& getFileName() const 
    {
        return m_strFile;
    }
    ///����ģ���ļ�������
    void setFileName(string const& strFile)
    {
        m_strFile = strFile;
    }
    ///��ȡģ��������ı����ͣ�ΪMIME
    string const& getType() const
    {
        return m_strType;
    }
    ///����ģ��������ı�����
    void setType(string const& strType)
    {
        m_strType = strType;
    }
    ///��ȡtemplate
    CwxHtmlTmpl const* getParser() const
    {
        return &m_parser;
    }
private:
    ///��������
    CwmCenterTemplate(CwmCenterTemplate const& )
    {

    }
    ///��ֵ����
    CwmCenterTemplate& operator=(CwmCenterTemplate const& )
    {
        return *this;
    }
private:
    string         m_strName;///<ģ�������
    string         m_strFile; ///<ģ����ļ���
    string         m_strType; ///<ģ����������ͣ�ΪMIME�����Ͷ��壬ȱʡΪtext/html
    CwxHtmlTmpl    m_parser; ///<template�Ľ�������ʵ���ı��Ķ�̬���
};

/**
@class CwmCenterAlarmMail
@brief ���岻ͬ���͸澯�ķ���email,����ͬһ���𣬿������ö��email����ͬemailͨ����;���ָ�
*/
class CwmCenterAlarmMail
{
public:
    ///���캯��
    CwmCenterAlarmMail()
    {

    }
    ///��������
    ~CwmCenterAlarmMail()
    {

    }
    ///��������
    CwmCenterAlarmMail(CwmCenterAlarmMail const& obj)
    {
        m_strName = obj.m_strName;
        m_warning = obj.m_warning;
        m_minor = obj.m_minor;
        m_major = obj.m_major;
        m_critical = obj.m_critical;
        m_fatal = obj.m_fatal;
    }
    ///��ֵ����
    CwmCenterAlarmMail& operator=(CwmCenterAlarmMail const& obj)
    {
        if (this != &obj)
        {
            m_strName = obj.m_strName;
            m_warning = obj.m_warning;
            m_minor = obj.m_minor;
            m_major = obj.m_major;
            m_critical = obj.m_critical;
            m_fatal = obj.m_fatal;
        }
        return *this;
    }
public:
    ///��ȡ���������
    string const& getName() const 
    {
        return m_strName;
    }
    ///���ù��������
    void setName(string const& strName)
    {
        m_strName = strName;
    }
    ///��ȡ�澯��email, ucLevelΪCwmCmnAlarm::ALARM_WARNING~CwmCmnAlarm::ALARM_FATAL
    list<string> const& getAlarmEmails(CWX_UINT8 ucLevel) const;
    ///��ȡ�澯��email, ucLevelΪCwmCmnAlarm::ALARM_WARNING~CwmCmnAlarm::ALARM_FATAL
    string& getAlarmEmails(CWX_UINT8 ucLevel, string& strAlarms) const;
    ///���ݵ�ǰ�澯level��ǰһ��level����ȡ�澯��mail
    void getAlarmEmails(CWX_UINT8 ucPLevel, CWX_UINT8 ucLevel, set<string>& emails) const;
    ///���ݵ�ǰ�澯level��ǰһ��level����ȡ�澯��mail
    string& getAlarmEmails(CWX_UINT8 ucPLevel, CWX_UINT8 ucLevel, string& strEmails) const;
    ///���ø澯��email����Ϊȫ�滻ģʽ
    void setAlarmEmails(CWX_UINT8 ucLevel, string const& strEmails);
    ///��Ӹ澯email����Ϊappendģʽ
    void appendAlarmEmails(CWX_UINT8 ucLevel, string const& strEmails);
public:
    void reset()
    {
        m_strName.erase();
        m_warning.clear();
        m_minor.clear();
        m_major.clear();
        m_critical.clear();
        m_fatal.clear();

    }
private:
    void setEmails(list<string>& emails, string const& strEmails);
    void appendEmails(list<string>& emails, string const& strEmails);
private:
    string          m_strName; ///<���������
    list<string>     m_warning; ///<warning����澯��email�����б�
    list<string>     m_minor;  ///<minor����澯��email�����б�
    list<string>     m_major;  ///<major����澯��email�����б�
    list<string>     m_critical; ///<critical����澯��email�����б�
    list<string>     m_fatal; ///<fatal����澯��email�����б�
};

class CwmCenterHost;
/**
@class CwmCenterService
@brief Center�����ϵͳ
*/
class CwmCenterService
{
public:
    ///���캯��
    CwmCenterService()
    {
        m_pAlarmMail = NULL;
    }
    ///��������
    ~CwmCenterService()
    {

    }
    ///��������
    CwmCenterService(CwmCenterService const& obj)
    {
        m_strName = obj.m_strName;
        m_lsActions = obj.m_lsActions;
        m_pAlarmMail = obj.m_pAlarmMail;
        m_actions = obj.m_actions;
    }
    ///��ֵ����
    CwmCenterService& operator=(CwmCenterService const& obj)
    {
        if (this != &obj)
        {
            m_strName = obj.m_strName;
            m_lsActions = obj.m_lsActions;
            m_pAlarmMail = obj.m_pAlarmMail;
            m_actions = obj.m_actions;
        }
        return *this;
    }
public:
    ///��ȡservice������
    string const& getName() const
    {
        return m_strName;
    }
    ///����service������
    void setName(string const& strName)
    {
        m_strName = strName;
    }
    ///��ȡ�澯�Ĺ���
    inline CwmCenterAlarmMail const* getMailRule() const
    {
        return m_pAlarmMail;
    }
    ///���ø澯�Ĺ���
    inline void setMailRule(CwmCenterAlarmMail const* pRule)
    {
        m_pAlarmMail = pRule;
    }
    ///��ȡservice��action�б�
    inline list<string> const& getActions() const
    {
        return m_lsActions;
    }
    inline bool isExistAction(string const& strAction)
    {
        return m_actions.find(strAction) != m_actions.end();
    }
    ///���һ��action�Ķ���
    inline void addAction(string const& strAction)
    {
        m_lsActions.push_back(strAction);
        m_actions.insert(strAction);
    }
    ///��ȡ���е�����
    inline map<string/*ip*/, CwmCenterHost const*> const& getHosts() const
    {
        return m_hosts;
    }
    ///����������Ip����ȡָ��������
    inline CwmCenterHost const* getHost(string const& ip) const
    {
        map<string/*ip*/, CwmCenterHost const*>::const_iterator iter = m_hosts.find(ip);
        if (iter == m_hosts.end()) return NULL;
        return iter->second;
    }
    ///���һ��host
    bool addHost(CwmCenterHost const* pHost);
public:
    ///��ն���
    void reset()
    {
        m_actions.clear();
        m_hosts.clear();
        m_pAlarmMail = NULL;
        m_strName.erase();
    }
private:
    string     m_strName; ///<service������
    CwmCenterAlarmMail const*  m_pAlarmMail; ///<����ĸ澯email����
    set<string> m_actions; ///<service������action�б�
    list<string> m_lsActions; ///<�������ô����action�б�
    map<string/*ip*/, CwmCenterHost const*> m_hosts; ///<ϵͳ�Ļ���
};

/**
@class CwmCenterServiceKey
@brief Center��ص�system��service map��Key����
*/
class CwmCenterServiceKey
{
public:
    ///���캯��
    CwmCenterServiceKey()
    {

    }
    ///���캯��
    CwmCenterServiceKey(string const& strSystem, string const& strService)
    {
        m_strSystem = strSystem;
        m_strService = strService;
    }
    ///��������
    ~CwmCenterServiceKey()
    {

    }
    ///��������
    CwmCenterServiceKey(CwmCenterServiceKey const& obj)
    {
        m_strSystem = obj.m_strSystem;
        m_strService = obj.m_strService;
    }
    ///��ֵ����
    CwmCenterServiceKey& operator=(CwmCenterServiceKey const& obj)
    {
        if (this != &obj)
        {
            m_strSystem = obj.m_strSystem;
            m_strService = obj.m_strService;
        }
        return *this;
    }
    ///С�ڲ���
    bool operator<(CwmCenterServiceKey const& obj) const
    {
        if (m_strSystem < obj.m_strSystem) return true;
        if (m_strSystem > obj.m_strSystem) return true;
        return m_strService < obj.m_strService;
    }
    ///���ڲ���
    bool operator==(CwmCenterServiceKey const& obj) const
    {
        return (m_strSystem == obj.m_strSystem)&& (m_strService == obj.m_strService);
    }
public:
    ///��ȡsystem����
    inline string const& getSystem() const
    {
        return m_strSystem;
    }
    ///����system����
    inline void setSystem(string const& strSystem)
    {
        m_strSystem = strSystem;
    }
    ///��ȡservice����
    inline string const& getService() const
    {
        return m_strService;
    }
    ///����service����
    inline void setService(string const& strService)
    {
        m_strService = strService;
    }
private:
    string     m_strSystem; ///<service��system����
    string     m_strService; ///<service������
};

/**
@class CwmCenterHost
@brief Center��ص�host����
*/
class CwmCenterHost
{
public:
    ///���캯��
    CwmCenterHost()
    {
        m_unPort = 0;
        m_pAlarmRule = NULL;
        m_pMailRule = NULL;
    }
    ///��������
    ~CwmCenterHost()
    {

    }
public:
    ///��ȡ����
    inline string const& getName() const
    {
        return m_strName;
    }
    ///��������
    inline void setName(string const& strName)
    {
        m_strName = strName;
    }
    ///��ȡIP
    inline string const& getIp() const
    {
        return m_strIp;
    }
    ///����IP
    inline void setIp(string const& strIp)
    {
        m_strIp = strIp;
    }
    ///��ȡport
    inline CWX_UINT16 getPort() const
    {
        return m_unPort;
    }
    ///����port
    inline void setPort(CWX_UINT16 unPort)
    {
        m_unPort = unPort;
    }
    ///��ȡ�澯�Ĺ���
    inline CwmCmnAlarmRule const* getAlarmRule() const
    {
        return m_pAlarmRule;
    }
    ///���ø澯�Ĺ���
    inline void setAlarmRule(CwmCmnAlarmRule const* pRule)
    {
        m_pAlarmRule = pRule;
    }
    ///��ȡ�澯mail�Ĺ���
    inline CwmCenterAlarmMail const* getMailRule() const
    {
        return m_pMailRule;
    }
    ///���ø澯mail�Ĺ���
    inline void setMailRule(CwmCenterAlarmMail const* pMail)
    {
        m_pMailRule = pMail;
    }
    ///��ȡ�����ϵ�����system������service
    inline map<CwmCenterServiceKey, CwmCenterService*> const& getServices() const
    {
        return m_serviceMap;
    }
    ///���һ��system��service
    inline bool addService(string const& strSystem,
        string const& strService,
        CwmCenterService* pService)
    {
        CwmCenterServiceKey key(strSystem, strService);
        map<CwmCenterServiceKey, CwmCenterService*>::iterator iter = m_serviceMap.find(key);
        if (iter != m_serviceMap.end()) return false;
        m_serviceMap[key] = pService;
        return true;
    }
    ///��ȡָ����service
    inline CwmCenterService const* getService(string const& strSystem,
        string const& strService) const
    {
        CwmCenterServiceKey key(strSystem, strService);
        map<CwmCenterServiceKey, CwmCenterService*>::const_iterator iter = m_serviceMap.find(key);
        if (iter != m_serviceMap.end())
        {
            return iter->second;
        }
        return NULL;
    }
private:
    ///��������
    CwmCenterHost(CwmCenterHost const& )
    {

    }
    ///��ֵ����
    CwmCenterHost& operator=(CwmCenterHost const& )
    {
        return *this;
    }
private:
    string       m_strName;///<����������
    string       m_strIp; ///<������ip
    CWX_UINT16    m_unPort; ///<������PORT
    CwmCmnAlarmRule const*   m_pAlarmRule; ///<�澯����
    CwmCenterAlarmMail const*  m_pMailRule; ///<�澯��email����
    map<CwmCenterServiceKey, CwmCenterService*> m_serviceMap; ///<system��service��map
};


/**
@class CwmCenterSystem
@brief Center�����ϵͳ
*/
class CwmCenterSystem
{
public:
    ///���캯��
    CwmCenterSystem()
    {

    }
    ///���캯��
    CwmCenterSystem(string const& strName, string const& strDesc)
    {
        m_strName = strName;
        m_strDesc = strDesc;
    }
    ///��������
    ~CwmCenterSystem()
    {
        reset();
    }
public:
    ///��ȡϵͳ������
    inline string const& getName() const
    {
        return m_strName;
    }
    ///����ϵͳ������
    inline void setName(string const& strName)
    {
        m_strName = strName;
    }
    ///��ȡϵͳ������
    inline string const& getDesc() const
    {
        return m_strDesc;
    } 
    ///����ϵͳ�����Ѻ�
    inline void setDesc(string const& strDesc)
    {
        m_strDesc = strDesc;
    }
    ///��ȡϵͳ�������ļ���
    inline string const& getFileName() const
    {
        return m_strFile;
    }
    ///����ϵͳ�������ļ���
    inline void setFileName(string const& strFile)
    {
        m_strFile = strFile;
    }
    ///��ȡϵͳ�����и澯����
    inline map<string/*alarm name*/, CwmCmnAlarmRule*> const& getAlarmRules() const
    {
        return m_alarmRules;
    }
    ///��ȡָ���ĸ澯����
    inline CwmCmnAlarmRule const* getAlarmRule(string const& strName) const
    {
        map<string/*alarm name*/, CwmCmnAlarmRule*>::const_iterator iter = m_alarmRules.find(strName);
        if (iter == m_alarmRules.end()) return NULL;
        return iter->second;
    }
    ///��Ӹ澯����
    inline bool addAlarmRule(CwmCmnAlarmRule* pAlarmRule)
    {
        map<string/*alarm name*/, CwmCmnAlarmRule*>::iterator iter = m_alarmRules.find(pAlarmRule->getName());
        if (iter != m_alarmRules.end()) return false;
        m_alarmRules[pAlarmRule->getName()] = pAlarmRule;
        return true;
    }
    ///��ȡ����email�Ĺ���
    inline map<string/*mail name*/, CwmCenterAlarmMail*> const& getAlarmMails() const
    {
        return m_alarmMails;
    }
    ///��ȡָ���ĸ澯email����
    inline CwmCenterAlarmMail const* getAlarmMail(string const& strMailName) const 
    {
        map<string/*mail name*/, CwmCenterAlarmMail*>::const_iterator iter = m_alarmMails.find(strMailName);
        if (iter == m_alarmMails.end()) return NULL;
        return iter->second;
    }
    ///���mail����
    inline bool addAlarmMail(CwmCenterAlarmMail* pAlarmMail)
    {
        map<string/*mail name*/, CwmCenterAlarmMail*>::iterator iter = m_alarmMails.find(pAlarmMail->getName());
        if (iter != m_alarmMails.end()) return false;
        m_alarmMails[pAlarmMail->getName()] = pAlarmMail;
        return true;
    }
    ///��ȡ���е�service
    inline map<string/*service name*/, CwmCenterService*> const& getServices() const
    {
        return m_services;
    }
    ///��ȡָ����service
    inline CwmCenterService const* getService(string const& strName) const
    {
        map<string/*service name*/, CwmCenterService*>::const_iterator iter = m_services.find(strName);
        if (iter == m_services.end()) return NULL;
        return iter->second;
    }
    ///���service
    inline bool addService(CwmCenterService* pService)
    {
        map<string/*service name*/, CwmCenterService*>::const_iterator iter = m_services.find(pService->getName());
        if (iter != m_services.end()) return false;
        m_services[pService->getName()] = pService;
        return true;
    }
public:
    void reset()
    {
        {
            map<string/*alarm name*/, CwmCmnAlarmRule*>::iterator iter = m_alarmRules.begin();
            while(iter != m_alarmRules.end())
            {
                delete iter->second;
                iter++;
            }
            m_alarmRules.clear();
        }
        {
            map<string/*mail name*/, CwmCenterAlarmMail*>::iterator iter = m_alarmMails.begin();
            while(iter != m_alarmMails.begin())
            {
                delete iter->second;
                iter++;
            }
            m_alarmMails.clear();
        }
        {
            map<string/*service name*/, CwmCenterService*>::iterator iter=m_services.begin();
            while(iter != m_services.end())
            {
                delete iter->second;
                iter++;
            }
            m_services.clear();
        }
    }
private:
    ///��������
    CwmCenterSystem(CwmCenterSystem const& )
    {

    }
    ///��ֵ����
    CwmCenterSystem & operator=(CwmCenterSystem const&)
    {
        return *this;
    }
private:
    string      m_strName;///<ϵͳ������
    string      m_strDesc; ///<ϵͳ������
    string      m_strFile; ///<ϵͳ�������ļ�
    map<string/*alarm name*/, CwmCmnAlarmRule*>  m_alarmRules; ///<ϵͳ�ĸ澯����
    map<string/*mail name*/, CwmCenterAlarmMail*> m_alarmMails; ///<ϵͳ��email����
    map<string/*service name*/, CwmCenterService*>  m_services; ///<ϵͳ�����ķ���
};

/**
@class CwmCenterConfig
@brief Center��������ء��������
*/
class CwmCenterConfig
{
public:
    enum
    {
        DEF_TIMEOUT_SECOND = 10,///<ȱʡ�ĳ�ʱʱ��
        DEF_THREAD_NUM = 2 ///<ȱʡ��thread������
    };
public:
    CwmCenterConfig()
    {
        m_uiThreadNum = DEF_THREAD_NUM;
        m_uiQueryTimeout = DEF_TIMEOUT_SECOND;
        m_uiAlarmTimeout = DEF_TIMEOUT_SECOND;
        m_bAvgReport = true;
        memset(m_szErrMsg, 0x00, 512);
    }    
    ~CwmCenterConfig()
    {
        this->reset();
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
    ///��ȡ����Ŀ¼
    inline string const& getWorkDir() const
    {
        return m_strWorkDir;
    }
    ///��ȡquery��listen
    inline CwxHostInfo const& getQueryListen() const
    {
        return  m_queryListen;
    }
    ///��ȡ����˿ڵļ���
    inline CwxHostInfo const& getMgrListen() const
    {
        return m_mgrListen;
    }
    ///��ȡ�澯����listen
    inline CwxHostInfo const& getAlarmAccept() const
    {
        return m_alarmAccept;
    }
    ///��ȡ�澯�ַ�listen
    inline CwxHostInfo const& getAlarmReport() const
    {
        return m_alarmReport;
    }
    ///�Ƿ����report�澯
    inline bool isAvgReport() const
    {
        return m_bAvgReport;
    }
    ///��ȡ�����̵߳�����
    inline CWX_UINT32 getThreadNum() const
    {
        return m_uiThreadNum;
    }
    ///��ȡquery�ĳ�ʱʱ��
    inline CWX_UINT32 getQueryTimeout() const
    {
        return m_uiQueryTimeout;
    }
    ///����query�ĳ�ʱʱ��
    inline void setQueryTimeout(CWX_UINT32 uiTimeout)
    {
        m_uiQueryTimeout = uiTimeout;
    }
    ///��ȡalarm timeoutʱ��
    inline CWX_UINT32  getAlarmTimeout() const
    {
        return m_uiAlarmTimeout;
    }
    ///��ȡ�����ļ���Ŀ¼
    inline string const& getDbFilePath() const
    {
        return m_strDbFilePath;
    }
    ///��ȡҳ���WEB url
    inline string const& getWebUrl() const
    {
        return m_strWebUrl;
    }  
    ///��ȡ����ģ���ļ���map
    inline map<string/*name*/, CwmCenterTemplate*> const& getTemplates() const
    {
        return m_templates;
    }
    ///����ģ��������ȡģ������ָ��
    inline CwmCenterTemplate const* getTemplate(string const& strName) const
    {
        map<string/*name*/, CwmCenterTemplate*>::const_iterator iter=m_templates.find(strName);
        if (iter != m_templates.end()) return iter->second;
        return NULL;
    }
    ///��ȡ���еĸ澯����
    inline map<string/*name*/, CwmCmnAlarmRule*> const& getAlarmRules() const
    {
        return m_alarmRules;
    }
    ///��ȡָ���ĸ澯����NULL��ʾ������
    inline CwmCmnAlarmRule const* getAlarmRule(string const& strRuleName) const
    {
        map<string/*name*/, CwmCmnAlarmRule*>::const_iterator iter = m_alarmRules.find(strRuleName);
        if (iter == m_alarmRules.end()) return NULL;
        return iter->second;
    }
    ///��ȡ���еĸ澯email����
    inline map<string/*name*/, CwmCenterAlarmMail*> const& getAlarmMails() const
    {
        return m_alarmMails;
    }
    ///��ȡָ���ĸ澯email�����NULL��ʾ������
    inline CwmCenterAlarmMail const* getAlarmMail(string const& strMailName) const
    {
        map<string/*name*/, CwmCenterAlarmMail*>::const_iterator iter = m_alarmMails.find(strMailName);
        if (iter == m_alarmMails.end()) return NULL;
        return iter->second;
    }
    ///��ȡָ��system��service��email����
    inline CwmCenterAlarmMail const* getAlarmMail(string const& strSystem, string const& strService) const
    {
        CwmCenterAlarmMail const* pEmail = NULL;
        CwmCenterSystem const* pSystem = getSystem(strSystem);
        if (!pSystem)
        {
            return getAlarmMail(CWM_CMN_DEFAULT);
        }
        CwmCenterService const* pService = pSystem->getService(strService);
        if (!pService)
        {
            pEmail = pSystem->getAlarmMail(CWM_CMN_DEFAULT);
            if (pEmail) return pEmail;
            return getAlarmMail(CWM_CMN_DEFAULT);
        }
        return pService->getMailRule();
    }
    ///��ȡ�����������ϵͳ
    inline map<string/*system name*/, CwmCenterSystem*> const& getSystems() const
    {
        return m_systems;
    }
    ///��ȡָ����ϵͳ��NULL��ʾ������
    inline CwmCenterSystem const* getSystem(string const& strName) const
    {
        map<string/*system name*/, CwmCenterSystem*>::const_iterator iter = m_systems.find(strName);
        if (iter == m_systems.end()) return NULL;
        return iter->second;
    }
    ///��ȡ���е�����
    inline map<string/*ip*/, CwmCenterHost*> const& getHosts() const
    {
        return m_hosts;
    }
    ///����������Ip����ȡָ��������
    inline CwmCenterHost * getHost(string const& ip)
    {
        map<string/*ip*/, CwmCenterHost*>::iterator iter = m_hosts.find(ip);
        if (iter == m_hosts.end()) return NULL;
        return iter->second;
    }
public:
    void reset();
private:
    bool loadTemplate(CwxXmlTreeNode const* pNode, CwmCenterTemplate& tmpt);
    bool loadAlarmRule(CwxXmlTreeNode const* pNode, CwmCmnAlarmRule& alarmRule);
    bool loadAlarmMail(CwxXmlTreeNode const* pNode, CwmCenterAlarmMail& alarmMail);
    bool loadSystem(string const& strName, string const& strFile, CwmCenterSystem& system);
private:
    ///���ù���Ŀ¼
    inline void setWorkDir(string const& strWorkDir)
    {
        m_strWorkDir = strWorkDir;
    }
    ///����query��listen
    inline void setQueryListen(CwxHostInfo const& listen)
    {
        m_queryListen = listen;
    }
    ///���ù���˿ڵļ���
    inline void setMgrListen(CwxHostInfo const& host)
    {
        m_mgrListen = host;
    }
    ///���ø澯����listen
    inline void setAlarmAccept(CwxHostInfo const& listen)
    {
        m_alarmAccept = listen;
    }
    ///���ø澯�ַ�listen
    inline void setAlarmReport(CwxHostInfo const& listen)
    {
        m_alarmReport = listen;
    }
    ///���ù����̵߳�����
    inline void setThreadNum(CWX_UINT32 uiNum)
    {
        m_uiThreadNum = uiNum;
    }
    ///����alarm timeoutʱ��
    inline void setAlarmTimeout(CWX_UINT32 uiTimeout)
    {
        m_uiAlarmTimeout = uiTimeout;
    }
    ///���������ļ���Ŀ¼
    inline void setDbFilePath(string const& strPath)
    {
        m_strDbFilePath = strPath;
    }
    ///����WEBҳ���URL
    inline void setWebUrl(string const& strUrl)
    {
        m_strWebUrl = strUrl;
    }
    ///���ģ�壬����ֵ��true���ɹ���false��ʧ��
    inline bool addTemplate(CwmCenterTemplate* pTemplate)
    {
        if (m_templates.find(pTemplate->getName()) != m_templates.end()) return false;
        m_templates[pTemplate->getName()] = pTemplate;
        return true;
    }
    ///��Ӹ澯����
    inline bool addAlarmRule(CwmCmnAlarmRule* pRule)
    {
        map<string/*name*/, CwmCmnAlarmRule*>::iterator iter = m_alarmRules.find(pRule->getName());
        if (iter != m_alarmRules.end()) return false;
        m_alarmRules[pRule->getName()] = pRule;
        return true;
    }
    ///��Ӹ澯email����
    inline bool addAlarmMail(CwmCenterAlarmMail* pMail)
    {
        map<string/*name*/, CwmCenterAlarmMail*>::iterator iter = m_alarmMails.find(pMail->getName());
        if (iter != m_alarmMails.end()) return false;
        m_alarmMails[pMail->getName()] = pMail;
        return true;
    }
    ///���һ��ϵͳ
    inline bool addSystem(CwmCenterSystem* pSystem)
    {
        map<string/*system name*/, CwmCenterSystem*>::iterator iter = m_systems.find(pSystem->getName());
        if (iter != m_systems.end()) return false;
        m_systems[pSystem->getName()] = pSystem;
        return true;
    }
    ///���һ��host
    inline bool addHost(CwmCenterHost* pHost)
    {
        map<string/*ip*/, CwmCenterHost*>::iterator iter = m_hosts.find(pHost->getIp());
        if (iter != m_hosts.end()) return false;
        m_hosts[pHost->getIp()] = pHost;
        return true;
    }

private:
    CwmCenterConfig(CwmCenterConfig const&)
    {

    }
    CwmCenterConfig& operator=(CwmCenterConfig const& )
    {
        return *this;
    }
private:
    string              m_strWorkDir; ///<����Ŀ¼
    string               m_strDbFilePath; ///<db file
    CwxHostInfo        m_mgrListen; ///<��������˿�
    CwxHostInfo       m_queryListen; ///<��ѯ�����˿�
    CwxHostInfo       m_alarmAccept; ///<�澯���յļ����˿�
    CwxHostInfo       m_alarmReport; ///<�澯�ַ��ļ����˿�
    bool                m_bAvgReport; ///<�Ƿ�����������ĸ澯���ն˾��ȷ���
    CWX_UINT32           m_uiThreadNum; ///<�����̵߳�����
    CWX_UINT32           m_uiQueryTimeout; ///<��ѯ��timeoutֵ
    CWX_UINT32           m_uiAlarmTimeout; ///<�澯������timeoutֵ
    string               m_strWebUrl; ///<ҳ�������URL
    map<string/*name*/, CwmCenterTemplate*> m_templates; ///<ģ���ļ���
    map<string/*name*/, CwmCmnAlarmRule*>  m_alarmRules; ///<�澯�����map
    map<string/*name*/, CwmCenterAlarmMail*> m_alarmMails; ///<�澯email�Ĺ���
    map<string/*system name*/, CwmCenterSystem*> m_systems; ///<ϵͳ����
    map<string/*ip*/, CwmCenterHost*> m_hosts; ///<����Ļ���
    char                m_szErrMsg[512];///<������Ϣbuf
};

#endif

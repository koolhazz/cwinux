#ifndef __CWM_NERVE_APP_H__
#define __CWM_NERVE_APP_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmNerveApp.h
@brief ���ϵͳ�е�Nerve�����App�����ļ���
@author cwinux@gmail.com
@version 0.1
@date 2009-10-25
@warning
@bug
*/

#include "CwxAppFramework.h"
#include "CwxAppHandler4Msg.h"
#include "CwmCmnMacro.h"
#include "CwmNerveConfig.h"
#include "CwmNerveAlarmHandler.h"
#include "CwmNerveCgiHandler.h"
#include "CwmNerveQueryHandler.h"
#include "CwmNerveServerHandler.h"
#include "CwmNerveServiceStatus.h"
#include "CwmCmnDataMgr.h"

/**
@class CwmNerveApp
@brief Nerve��App��
*/
class CwmNerveApp : public CwxAppFramework
{
public:
    enum
    {
        LOG_FILE_SIZE = 30, ///<ÿ��ѭ��������־�ļ���MBTYE
        LOG_FILE_NUM = 7,///<ѭ����־�ļ�������
        SVR_TYPE_QUERY = CwxAppFramework::SVR_TYPE_USER_START, ///<Monitor��ѯ��svr-id����
        SVR_TYPE_ALARM = CwxAppFramework::SVR_TYPE_USER_START + 1, ///<�澯�����svr-id
        SVR_TYPE_SERVER_ACTION = CwxAppFramework::SVR_TYPE_USER_START + 2, ///<server����action��svr-id
        SVR_TYPE_CGI_ACTION = CwxAppFramework::SVR_TYPE_USER_START + 3 ///<CGI����action��svr-id
    };
    ///���캯��
	CwmNerveApp();
    ///��������
	virtual ~CwmNerveApp();
    //��ʼ��app, -1:failure, 0 success;
    virtual int init(int argc, char** argv);
public:
    ///����ͨ���̵߳�tss
    virtual CwxAppTss* onTssEnv();
    ///ʱ����Ӧ����
    virtual void onTime(CwxTimeValue const& current);
    ///�ź���Ӧ����
    virtual void onSignal(int signum);
    ///���ӽ�������
    virtual int onConnCreated(CwxAppHandler4Msg& conn, bool& bSuspendConn, bool& bSuspendListen);
    ///���ӹر�
    virtual int onConnClosed(CwxAppHandler4Msg const& conn);
    ///�յ�������Ϣ
    virtual int onRecvMsg(CwxMsgBlock* msg, CwxAppHandler4Msg const& conn, CwxMsgHead const& header, bool& bSuspendConn);
    ///��Ϣ�������
    virtual CWX_UINT32 onEndSendMsg(CwxMsgBlock*& msg, CwxAppHandler4Msg const& conn);
    ///��������ʧ��
    virtual void onFailSendMsg(CwxMsgBlock*& msg);
public:
    ///��ȡ��һ��TASK ID�������ǵ��̣߳���˲���Ҫ������
    CWX_UINT32 nextTaskId()
    {
        m_uiTaskId++;
        if (!m_uiTaskId) m_uiTaskId = 1;
        return m_uiTaskId;
    }
    ///��ȡ����cgi����Ϣ��Ӧ��handler
    CwmNerveCgiHandler*   getCgiHandler()
    {
        return m_pCgiHandler;
    }
    ///��ȡ����serverͨ�ŵ���Ϣ��Ӧ��handler
    CwmNerveServerHandler*  getServerHandler()
    {
        return m_pServerHandler;
    }
    ///��ȡ����澯�������Ϣ��Ӧ��handler
    CwmNerveAlarmHandler* getAlarmHandler()
    {
        return m_pAlarmHandler;
    }
    ///��ȡ�������ݲ�ѯ����Ϣ��Ӧ��handler
    CwmNerveQueryHandler* getQueryHandler()
    {
        return m_pQueryHandler;
    }
    ///��ȡ�澯���������ݹ����manager
    CwmCmnDataMgr* getDataMgr()
    {
        return   m_pDataMgr;
    }
    ///��ȡnerve��config����
    CwmNerveConfig const& getConfig() const
    {
        return m_config;
    }
    ///��ȡָ��system��service���ֶ�Ӧ��service�����������ڣ��򷵻�NULL��
    CwmNerveServiceStatus* getService(string const& strSystem, string const& strName)
    {
        list<CwmNerveServiceStatus*>::iterator iter = m_lsService.begin();
        while(iter != m_lsService.end())
        {
            if (((*iter)->getServiceInfo()->getName() == strName) &&
                ((*iter)->getServiceInfo()->getSystem() == strSystem))
            {
                return *iter;
            }
            iter++;
        }
        return NULL;
    }
    ///��ȡȫ����service���б�
    list<CwmNerveServiceStatus*>& getServices()
    {
        return m_lsService;
    }
protected:
    ///init the Enviroment before run.0:success, -1:failure.
	virtual int initRunEnv();
    ///�ͷ�nerve app�еĶ���
    virtual void destroy();
private:
    ///ʵ����Ϣ�ķַ�
    void dispatch(CwxMsgBlock* msg);
private:
    CwmNerveConfig               m_config; ///<�����ļ�����
    CWX_UINT32                  m_uiAlarmConnId; ///<�澯������ID
    CWX_UINT32                   m_uiTaskId; ///<task id�ļ�����
    list<CwmNerveServiceStatus*>    m_lsService; ///<Service���б�
    CwmNerveAlarmHandler*         m_pAlarmHandler; ///<����alarm�����ͨ�Ź���handler
    CwmNerveCgiHandler*           m_pCgiHandler;///<����cgi�ܵ�ͨ�ŵ�handler
    CwmNerveServerHandler*        m_pServerHandler;///<������serverͨ�ŵ�handler
    CwmNerveQueryHandler*         m_pQueryHandler;///<�����ѯ��Ϣ��handler
    CwmCmnDataMgr*               m_pDataMgr;///<���ݹ�����
};

#endif


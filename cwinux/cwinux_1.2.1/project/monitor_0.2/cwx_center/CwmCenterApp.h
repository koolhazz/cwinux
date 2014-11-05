#ifndef __CWM_CENTER_APP_H__
#define __CWM_CENTER_APP_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterApp.h
@brief ���ϵͳ�е�Center�����App�����ļ���
@author cwinux@gmail.com
@version 0.1
@date 2009-11-02
@warning
@bug
*/

#include "CwxAppFramework.h"
#include "CwxAppHandler4Msg.h"
#include "CwxAppThreadPoolEx.h"
#include "CwxHtmlTmpl.h"
#include "CwmCmnMacro.h"
#include "CwmCenterConfig.h"
#include "CwmCenterAlarmAcceptor.h"
#include "CwmCenterAlarmReportor.h"
#include "CwmCenterNerveQuery.h"
#include "CwmCenterUiQuery.h"
#include "CwmCmnDataMgr.h"
#include "CwmCenterNerveStatus.h"

/**
@class CwmCenterApp
@brief Center��App��
*/
class CwmCenterApp : public CwxAppFramework
{
public:
    enum
    {
        LOG_FILE_SIZE = 30, ///<ÿ��ѭ��������־�ļ���MBTYE
        LOG_FILE_NUM = 7,///<ѭ����־�ļ�������
        SVR_TYPE_UI_QUERY = CwxAppFramework::SVR_TYPE_USER_START, ///<Monitor��ѯ��svr-id����
        SVR_TYPE_ALARM_ACCEPT = CwxAppFramework::SVR_TYPE_USER_START + 1, ///<�澯���յ�svr-id
        SVR_TYPE_ALARM_REPORT = CwxAppFramework::SVR_TYPE_USER_START + 2, ///<�澯�����svr-id
        SVR_TYPE_NERVE_QUERY = CwxAppFramework::SVR_TYPE_USER_START + 3 ///<Nerve��ѯ��svr-id
    };
    ///���캯��
	CwmCenterApp();
    ///��������
	virtual ~CwmCenterApp();
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
    ///��ȡ��һ��task id�����ڲ�ѯ��alarm report
    CWX_UINT32 nextTaskId()
    {
        CwxMutexGuard<CwxMutexLock> lock(&m_lock);
        m_uiTaskId++;
        if (!m_uiTaskId) m_uiTaskId = 1;
        return m_uiTaskId;
    }
    ///��ȡ���ݹ�����
    CwmCmnDataMgr* getDataMgr()
    {
        return m_pDataMgr;
    }
    ///��ȡ������Ϣ
    CwmCenterConfig const& getConfig() const
    {
        return  m_config;
    }
    ///��ȡ�澯����handler
    CwmCenterAlarmAcceptor* getAlarmAccptor()
    {
        return m_pAlarmAcceptor;
    }
    ///��ȡ�澯report��handler
    CwmCenterAlarmReportor* getAlarmReportor()
    {
        return m_pAlarmReportor;
    }
    ///��ȡ��ѯnerve��handler
    CwmCenterNerveQuery*  getNerveQuery()
    {
        return m_pNerveQuery;
    }
    ///��ȡ����UI��ѯ��handler
    CwmCenterUiQuery*  getUiQuery()
    {
        return m_pUiQuery;
    }
    ///��ȡcenter�����������nerve��map
    map<CWX_UINT32, CwmCenterNerveStatus*>&  getNerves()
    {
        return m_nerves;
    }
    ///��ȡָ��IP��nerve����
    CwmCenterNerveStatus* getNerve(string const& strIp)
    {
        map<string, CwmCenterNerveStatus*>::iterator iter = m_nervesIndex.find(strIp);
        if (iter != m_nervesIndex.end()) return iter->second;
        return NULL;
    }
protected:
    //init the Enviroment before run.0:success, -1:failure.
	virtual int initRunEnv();
    ///�ͷ�center app����Դ
    virtual void destroy();
private:
   CWX_UINT32      m_uiTaskId; ///<taskid
   CwxMutexLock    m_lock; ///<��
   CwmCenterConfig  m_config; ///<������Ϣ
   CwmCmnDataMgr*   m_pDataMgr; ///<���ݹ�����
   CwmCenterAlarmAcceptor* m_pAlarmAcceptor; ///<�澯���յ�handler
   CwmCenterAlarmReportor* m_pAlarmReportor; ///<�澯�����handler
   CwmCenterNerveQuery*    m_pNerveQuery; ///<nerve��ѯ��handler
   CwmCenterUiQuery*       m_pUiQuery; ///<ui ��ѯ��handler
   map<CWX_UINT32, CwmCenterNerveStatus*> m_nerves; ///<nerve״̬map��keyΪnerve������ID
   map<string, CwmCenterNerveStatus*> m_nervesIndex; ///<��nerve��ipΪKEY��������nerve���������
   CwxAppThreadPoolEx*      m_pThreadPool; ///<���԰��߳̽���������ȵ��̳߳ض���
};

#endif


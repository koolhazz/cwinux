#ifndef __CWX_APP_MGR_INTERFACE_H__
#define __CWX_APP_MGR_INTERFACE_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppMgrInterface.h
@brief ���������صĽӿڶ���
@author cwinux@gmail.com
@version 0.1
@date 2009-07-20
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxPackageReader.h"
#include "CwxMsgBlock.h"
#include "CwxAppConfig.h"
#include "CwxAppMacro.h"
#include "CwxAppCommander.h"

CWINUX_BEGIN_NAMESPACE

class CwxAppFramework;
#define CWX_APP_MGR_CMD_NAME_HELP "help"
#define CWX_APP_MGR_CMD_NAME_SET_LEVEL "set_level"
#define CWX_APP_MGR_CMD_NAME_GET_LEVEL "get_level"
#define CWX_APP_MGR_CMD_NAME_FILE_NO "log_file"
#define CWX_APP_MGR_CMD_NAME_CHECK "check"
#define CWX_APP_MGR_CMD_NAME_DETAIL "detail"

///�������ѯ������ݰ��У�ÿ��ϵͳ֧�ֵ���������ݵ�KEY
#define CWX_APP_MGR_CMD  "cmd"
///�������ѯ������ݰ��У��������Ϣ���͵�KEY
#define CWX_APP_MGR_CMD_MSG_TYPE  "type"
///�������ѯ������ݰ��У���������ֵ�KEY
#define CWX_APP_MGR_CMD_MSG_NAME  "name"
///�������ѯ������ݰ��У�������������KEY
#define CWX_APP_MGR_CMD_ARG   "arg"
///�������ѯ������ݰ��У��������������KEY
#define CWX_APP_MGR_CMD_DESC  "desc"
///���û��ѯ������־�����key
#define CWX_APP_MGR_LOG_LEVEL "level"
///���ý�����־�ļ���ŵ�key
#define CWX_APP_MGR_LOG_FILE_NO "no"
///����汾�ŵ�KEY
#define CWX_APP_MGR_APP_VERSION "version"
///����汾�����޸�ʱ���KEY
#define CWX_APP_MGR_APP_MODIFY_TIME "modify_time"
///����汾���±���ʱ���KEY
#define CWX_APP_MGR_COMPILE_TIME "compile_time"
///�̳߳���
#define CWX_APP_MGR_THREAD_POOLS "thread_pools"
///�̳߳�
#define CWX_APP_MGR_THREAD_POOL "thread_pool"
///�����߳���Ϣ��KEY
#define CWX_APP_MGR_THREAD "thread"
///level��ȱʡֵ
#define CWX_APP_MGR_DEFAULT "default"
///status�ĺ궨��
#define CWX_APP_MGR_STATUS  "status"
///level�ĺ궨��
#define CWX_APP_MGR_LEVEL   "level"
///error�ĺ궨��
#define CWX_APP_MGR_ERROR   "error"
///record�ĺ궨��
#define CWX_APP_MGR_RECORD  "record"

/**
@class CwxAppMgrInterface
@brief �����ء����Ƶ�ͨ�Žӿڶ��壬��������µĹ��ܣ�
1����ȡ����֧�ֵļ�ء�����ָ�
2��ֹͣ����
3����������
4�����÷����������־����
5����ѯ�����������־����
6�����Ʒ����л�������־�ļ�
7����ѯ��������״̬�Ƿ�����
8����ѯ�������е���ϸ��Ϣ
9��֧���û���չ�Լ�����������
*/
class CWX_API CwxAppMgrInterface : public CwxAppCmdOp 
{
public:
    class CwxAppMgrReply
    {
    public:
        CwxAppMgrReply()
        {
           m_status = 0;
           m_strLevel = CWX_APP_MGR_DEFAULT;
           m_strError = "";
           m_pRecord = NULL;
        }
        ~CwxAppMgrReply()
        {
            if (m_pRecord) delete m_pRecord;
            m_pRecord = NULL;
        }
    public:
        void reset()
        {
            m_status = 0;
            m_strLevel = CWX_APP_MGR_DEFAULT;
            m_strError = "";
            if (m_pRecord) delete m_pRecord;
            m_pRecord = NULL;
        }
    public:
        CWX_INT32        m_status; ///<���ص�״̬��0��success��-1��with error
        string           m_strLevel; ///<����ʱ��alarm��level
        string           m_strError; ///<����ʱ�Ĵ�����Ϣ
        CwxPackageWriter* m_pRecord;  ///<��ѯ����
    };
    ///��ء������������Ϣ���ͣ��ظ�����Ϣ����Ϊ��Ӧ����Ϣ���� + 1
    enum{
        MSG_TYPE_HELP = 1,///<��������������Ϣ����
        MSG_TYPE_STOP = 3,///<ֹͣ�����������Ϣ����
        MSG_TYPE_RESTART = 5,///<�������������������Ϣ����
        MSG_TYPE_SET_LOG_LEVEL = 7,///<���÷���������־�������Ϣ����
        MSG_TYPE_GET_LOG_LEVEL = 9,///<��ȡ����������־�������Ϣ����
        MSG_TYPE_NEXT_LOG_FILE = 11,///<֪ͨ�����л�������־�ļ�����Ϣ����
        MSG_TYPE_RUN_CHECK = 13,///<����������״̬����Ϣ����
        MSG_TYPE_RUN_DETAIL = 15,///<��ѯ����������ϸ״������Ϣ����
        MSG_TYPE_USER_BEGIN = 101,///<�û�ָ��Ŀ�ʼ��Ϣ����
        MSG_TYPE_UNKNOWN = 65533///<��֧���������͵Ļظ�����Ϣ����
    };
public:
    ///���캯������ָ�������APP������
    CwxAppMgrInterface(CwxAppFramework* pApp)
        :m_pApp(pApp)
    {

    }
    ///��������
    virtual ~CwxAppMgrInterface()
    {

    }
public:
    /**
    @brief Packһ������İ�����Ϣ
    @param [in] reply reply�Ķ��󣬱���ӿڵĳ�Ա��Ϣ��
    @param [in] cmdPackage �γ�����package��package-writer
    @param [in] unMsgType ��Ҫpack���������Ϣ����
    @param [in] szCmdName ��Ҫpack�����������
    @param [in] args ��Ҫpack������Ĳ�������ʽΪ arg1:�Ƿ��ѡ(y/n):type(n/c)|arg2...��n��ʾ���֣�c��ʾΪ�ַ�
    @param [in] desc ��Ҫpack�������������Ϣ
    @return false��ʧ�ܣ� true���ɹ�
    */
    bool packHelpCmd(CwxAppMgrReply& reply,
        CwxPackageWriter& cmdPackage,
        CWX_UINT16 unMsgType, 
        char const* szCmdName,
        char const* args,
        char const* desc);
    /**
    @brief �ظ�һ���Ĺ�������
    @param [in] uiSvrId �ظ�������svr-id
    @param [in] uiHostId �ظ�������host-id
    @param [in] uiConnId �ظ�������conn-id
    @param [in] header �ظ�����Ϣ��ͷ
    @param [in,out] reply �ظ���package����ص���Ϣ��
    @return void
    */
    void replyCmd(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId, 
        CWX_UINT32 uiConnId, 
        CwxMsgHead const & header, 
        CwxAppMgrReply& reply);
public:
    /**
    @brief ����һ����help����Ի�ȡ�Զ˷���֧�ֵĲ�������
    @param [in] uiSvrId ��Ϣ���͵�����svr-id
    @param [in] uiHostId ��Ϣ���͵�����host-id
    @param [in] uiConnId ��Ϣ���͵�����conn-id
    @param [in] uiTaskId ��Ϣ���͵�Task-id
    @return false��ʧ�ܣ� true���ɹ�
    */
    bool sendCmdHelp(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId,
        CWX_UINT32 uiConnId,
        CWX_UINT32 uiTaskId);
    /**
    @brief ����һ����stop�����ֹͣ�Զ˷���
    @param [in] uiSvrId ��Ϣ���͵�����svr-id
    @param [in] uiHostId ��Ϣ���͵�����host-id
    @param [in] uiConnId ��Ϣ���͵�����conn-id
    @param [in] uiTaskId ��Ϣ���͵�Task-id
    @return false��ʧ�ܣ� true���ɹ�
    */
    bool sendCmdStop(CWX_UINT32 uiSvrId, 
        CWX_UINT32 uiHostId, 
        CWX_UINT32 uiConnId,
        CWX_UINT32 uiTaskId);
    /**
    @brief ����һ����restart����������Զ˷���
    @param [in] uiSvrId ��Ϣ���͵�����svr-id
    @param [in] uiHostId ��Ϣ���͵�����host-id
    @param [in] uiConnId ��Ϣ���͵�����conn-id
    @param [in] uiTaskId ��Ϣ���͵�Task-id
    @return false��ʧ�ܣ� true���ɹ�
    */
    bool sendCmdRestart(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId,
        CWX_UINT32 uiConnId,
        CWX_UINT32 uiTaskId);
    /**
    @brief ����һ�������öԶ˷���Log ���������
    @param [in] uiSvrId ��Ϣ���͵�����svr-id
    @param [in] uiHostId ��Ϣ���͵�����host-id
    @param [in] uiConnId ��Ϣ���͵�����conn-id
    @param [in] uiTaskId ��Ϣ���͵�Task-id
    @param [in] uiLevel ���õ�Log ����
    @return false��ʧ�ܣ� true���ɹ�
    */
    bool sendCmdSetLogLevel(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId,
        CWX_UINT32 uiConnId,
        CWX_UINT32 uiTaskId,
        CWX_UINT32 uiLevel);
    /**
    @brief ����һ���Ļ�ȡ�Զ˷���Log ���������
    @param [in] uiSvrId ��Ϣ���͵�����svr-id
    @param [in] uiHostId ��Ϣ���͵�����host-id
    @param [in] uiConnId ��Ϣ���͵�����conn-id
    @param [in] uiTaskId ��Ϣ���͵�Task-id
    @return false��ʧ�ܣ� true���ɹ�
    */
    bool sendCmdQueryLogLevel(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId,
        CWX_UINT32 uiConnId,
        CWX_UINT32 uiTaskId);
    /**
    @brief ����һ�����л��Զ˷�����־�ļ�������
    @param [in] uiSvrId ��Ϣ���͵�����svr-id
    @param [in] uiHostId ��Ϣ���͵�����host-id
    @param [in] uiConnId ��Ϣ���͵�����conn-id
    @param [in] uiTaskId ��Ϣ���͵�Task-id
    @param [in] unFileNo ��־�ļ������
    @return false��ʧ�ܣ� true���ɹ�
    */
    bool sendCmdNextLogFile(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId, 
        CWX_UINT32 uiConnId, 
        CWX_UINT32 uiTaskId,
        CWX_UINT16 unFileNo);
    /**
    @brief ����һ���Ĳ�ѯ�Զ˷�������״��������
    @param [in] uiSvrId ��Ϣ���͵�����svr-id
    @param [in] uiHostId ��Ϣ���͵�����host-id
    @param [in] uiConnId ��Ϣ���͵�����conn-id
    @param [in] uiTaskId ��Ϣ���͵�Task-id
    @return false��ʧ�ܣ� true���ɹ�
    */
    bool sendCmdRunCheck(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId, 
        CWX_UINT32 uiConnId,
        CWX_UINT32 uiTaskId);
    /**
    @brief ����һ���Ĳ�ѯ�Զ˷���������ϸ��Ϣ������
    @param [in] uiSvrId ��Ϣ���͵�����svr-id
    @param [in] uiHostId ��Ϣ���͵�����host-id
    @param [in] uiConnId ��Ϣ���͵�����conn-id
    @param [in] uiTaskId ��Ϣ���͵�Task-id
    @return false��ʧ�ܣ� true���ɹ�
    */
    bool sendCmdRunDetail(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId,
        CWX_UINT32 uiConnId,
        CWX_UINT32 uiTaskId);

public:
    ///��ȡapp����
    CwxAppFramework* getApp()
    {
        return m_pApp;
    }
private:
    CwxAppFramework*     m_pApp;  ///<app����
};

CWINUX_END_NAMESPACE
#include "CwxPost.h"

#endif 

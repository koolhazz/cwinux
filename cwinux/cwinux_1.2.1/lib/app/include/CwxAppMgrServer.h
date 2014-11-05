#ifndef __CWX_APP_MGR_SERVER_H__
#define __CWX_APP_MGR_SERVER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppMgrServer.h
@brief �����ع��������CwxAppMgrServer��Ķ���
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
#include "CwxAppMgrInterface.h"
#include "CwxAppHandler4Msg.h"

CWINUX_BEGIN_NAMESPACE
/**
@class CwxAppMgrServer
@brief �������Թ���˿ڵļ�ؿ�������û��������ش˶����Ըı�Ĭ�ϵĴ�����򣬲����ӷ�������Ŀ������
msg-type=1����ȡ����֧�ֵļ�ء�����ָ�
msg-type=3��ֹͣ����
msg-type=5����������
msg-type=7�����÷����������־����
msg-type=9����ѯ�����������־����
msg-type=11�����Ʒ����л�������־�ļ�
msg-type=13����ѯ��������״̬�Ƿ�����
msg-type=15����ѯ�������е���ϸ��Ϣ
msg-type=������֧���û���չ�Լ�����������
*/
class CWX_API CwxAppMgrServer : public CwxAppMgrInterface 
{
public:
    ///���캯��
    CwxAppMgrServer(CwxAppFramework* pApp)
        :CwxAppMgrInterface(pApp)
    {

    }
    ///��������
    virtual ~CwxAppMgrServer()
    {

    }
public:
    /**
    @brief help�������Ӧ����
    @param [in] msg msg�������ݰ�
    @param [in] pThrEnv �̵߳�Thread-env��
    @param [in] reply �ظ���package����ص���Ϣ��
    @return false�����ظ����ر����ӣ� true���ظ�
    */
    virtual bool onCmdHelp(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        CwxAppMgrReply& reply);
    /**
    @brief �û��Զ����help�������Ӧ����
    @param [in] pThrEnv �̵߳�Thread-env��
    @param [in] reply �ظ���package����ص���Ϣ��
    @param [in] cmdPackage cmd����ʱpackage���û���һ��command���
    @return false��ʧ�ܣ� true���ɹ�
    */
    virtual bool onCmdHelpUser(CwxAppTss* pThrEnv,
        CwxAppMgrReply& reply,
        CwxPackageWriter& cmdPackage);
    /**
    @brief stop�������Ӧ����
    @param [in] msg msg�������ݰ�
    @param [in] pThrEnv �̵߳�Thread-env��
    @param [in] reply �ظ���package����ص���Ϣ��
    @return false�����ظ����ر����ӣ� true���ظ�
    */
    virtual bool onCmdStop(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        CwxAppMgrReply& reply);
    /**
    @brief restart�������Ӧ����
    @param [in] msg msg�������ݰ�
    @param [in] pThrEnv �̵߳�Thread-env��
    @param [in] reply �ظ���package����ص���Ϣ��
    @return false�����ظ����ر����ӣ� true���ظ�
    */
    virtual bool onCmdRestart(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        CwxAppMgrReply& reply);
    /**
    @brief ����������־Level�������Ӧ����
    @param [in] msg msg�������ݰ�
    @param [in] pThrEnv �̵߳�Thread-env��
    @param [in] reply �ظ���package����ص���Ϣ��
    @return false�����ظ����ر����ӣ� true���ظ�
    */
    virtual bool onCmdSetLogLevel(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        CwxAppMgrReply& reply);
    /**
    @brief ��ȡ������־Level�������Ӧ����
    @param [in] msg msg�������ݰ�
    @param [in] pThrEnv �̵߳�Thread-env��
    @param [in] reply �ظ���package����ص���Ϣ��
    @return false�����ظ����ر����ӣ� true���ظ�
    */
    virtual bool onCmdGetLogLevel(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        CwxAppMgrReply& reply);
    /**
    @brief �л�������־�ļ��������Ӧ����
    @param [in] msg msg�������ݰ�
    @param [in] pThrEnv �̵߳�Thread-env��
    @param [in] reply �ظ���package����ص���Ϣ��
    @return false�����ظ����ر����ӣ� true���ظ�
    */
    virtual bool onCmdNextLogfile(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv, 
        CwxAppMgrReply& reply);
    /**
    @brief ��ȡ��������״̬�������Ӧ����
    @param [in] msg msg�������ݰ�
    @param [in] pThrEnv �̵߳�Thread-env��
    @param [in] reply �ظ���package����ص���Ϣ��
    @return false�����ظ����ر����ӣ� true���ظ�
    */
    virtual bool onCmdRunCheck(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv, 
        CwxAppMgrReply& reply);
    /**
    @brief ��ȡ������ϸ������Ϣ�������Ӧ����
    @param [in] msg msg�������ݰ�
    @param [in] pThrEnv �̵߳�Thread-env��
    @param [in] reply �ظ���package����ص���Ϣ��
    @return false�����ظ����ر����ӣ� true���ظ�
    */
    virtual bool onCmdRunDetail(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        CwxAppMgrReply& reply);
    /**
    @brief �û��Զ����������Ӧ����
    @param [in] msg msg�������ݰ�
    @param [in] pThrEnv �̵߳�Thread-env��
    @param [in] reply �ظ���package����ص���Ϣ��
    @return false�����ظ����ر����ӣ� true���ظ�
    */
    virtual bool onCmdUser(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv, 
        CwxAppMgrReply& reply);
public:
    /**
    @brief �յ������������Ӧ��������������CwxAppCmdOp::noticeRecvMsg()
    @param [in] msg msg�������ݰ�
    @param [in] conn �յ���Ϣ�����ӡ�
    @param [in] header �յ���Ϣ����Ϣͷ��
    @param [in] pThrEnv �̵߳�Thread-env��
    @return false��ʧ�ܣ� true���ɹ�
    */
    virtual int onRecvMsg(CwxMsgBlock*& msg,
        CwxAppHandler4Msg const& conn,
        CwxMsgHead const& header, 
        CwxAppTss* pThrEnv);
    ///��������CwxAppCmdOp::onConnCreated()��������󲻴���
    virtual int onConnCreated(CwxMsgBlock*& ,
        CwxAppTss* )
    {
        return 1;
    }
    ///��������CwxAppCmdOp::onConnClosed()��������󲻴���
    virtual int onConnClosed(CwxMsgBlock*& , CwxAppTss* )
    {
        return 1;
    }
    ///��������CwxAppCmdOp::onEndSendMsg()��������󲻴���
    virtual int onEndSendMsg(CwxMsgBlock*& , CwxAppTss* )
    {
        return 1;
    }
    ///��������CwxAppCmdOp::onFailSendMsg()��������󲻴���
    virtual int onFailSendMsg(CwxMsgBlock*& , CwxAppTss* )
    {
        return 1;
    }
    ///��������CwxAppCmdOp::onTimeoutCheck()��������󲻴���
    virtual int onTimeoutCheck(CwxMsgBlock*& , CwxAppTss* )
    {
        return 1;
    }
    ///��������CwxAppCmdOp::onEvent4Handle()��������󲻴���
    virtual int onEvent4Handle(CwxMsgBlock*& , CwxAppTss* )
    {
        return 1;
    }
    ///��������CwxAppCmdOp::onUserEvent()��������󲻴���
    virtual int onUserEvent(CwxMsgBlock*& , CwxAppTss* )
    {
        return 1;
    }
};

CWINUX_END_NAMESPACE
#include "CwxPost.h"


#endif 

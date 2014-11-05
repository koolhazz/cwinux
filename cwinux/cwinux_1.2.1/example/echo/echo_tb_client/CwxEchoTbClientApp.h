#ifndef __CWX_ECHO_TB_CLIENT_APP_H__
#define __CWX_ECHO_TB_CLIENT_APP_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
#include "CwxAppFramework.h"
#include "CwxEchoTbClientConfig.h"
#include "CwxEchoTbEventHandler.h"
#include "CwxEchoTbClientTask.h"
#include "CwxAppThreadPoolEx.h"

#define ECHO_TB_CLIENT_APP_VERSION "1.0"
#define ECHO_TB_CLIENT_MODIFY_DATE "2010-08-29"

CWINUX_USING_NAMESPACE;

///echo��ѹ������app
class CwxEchoTbClientApp : public CwxAppFramework
{
public:
    enum
    {
        LOG_FILE_SIZE = 30, ///<ÿ��ѭ��������־�ļ���MBTYE
        LOG_FILE_NUM = 7,///<ѭ����־�ļ�������
        SVR_TYPE_ECHO_BASE = CwxAppFramework::SVR_TYPE_USER_START ///<echo��ѯ��svr-id����
    };
    enum
    {
        SEND_MSG_TYPE = 1, ///<echo���͵���Ϣ����
        RECV_MSG_TYPE =2 ///<echo�ظ�����Ϣ����
    };

    ///���캯��
	CwxEchoTbClientApp();
    ///��������
	virtual ~CwxEchoTbClientApp();
    //��ʼ��app, -1:failure, 0 success;
    virtual int init(int argc, char** argv);
public:
    //ʱ����Ӧ����
    virtual void onTime(CwxTimeValue const& current);
    //�ź���Ӧ����
    virtual void onSignal(int signum);
    //echo���ӽ�������
    virtual int onConnCreated(CwxAppHandler4Msg& conn, bool& bSuspendConn, bool& bSuspendListen);
    //echo���ص���Ӧ����
    virtual int onRecvMsg(CwxMsgBlock* msg, CwxAppHandler4Msg const& conn, CwxMsgHead const& header, bool& bSuspendConn);
    //���ӹر�
    virtual int onConnClosed(CwxAppHandler4Msg const& conn);
    //��Ϣ�������
    virtual CWX_UINT32 onEndSendMsg(CwxMsgBlock*& msg,
        CwxAppHandler4Msg const& conn);
    //��Ϣ����ʧ��
    virtual void onFailSendMsg(CwxMsgBlock*& msg);
public:
    CwxEchoTbClientConfig const& getConfig() const { return m_config;}
    CWX_UINT16 getEchoGroupNum() const { return m_unEchoGroupNum;}
    CWX_UINT32 getEchoGroupSvrId(CWX_UINT16 unGroup) { return SVR_TYPE_ECHO_BASE + unGroup;}
    CwxMsgBlock* packEchoMsg(CWX_UINT32 uiSvrId, CWX_UINT32 uiTaskId)
    {
        CwxMsgHead header;
        ///����echo����Ϣ����
        header.setMsgType(SEND_MSG_TYPE);
        ///����echo�����ݰ�����
        header.setDataLen(m_config.m_uiDataSize);
        ///����echo���ݰ���taskid����ʹ�÷��͵��������кţ���ǰû��
        header.setTaskId(uiTaskId);
        ///���䷢����Ϣ����block
        CwxMsgBlock* pBlock = CwxMsgBlockAlloc::pack(header, m_szBuf100K, m_config.m_uiDataSize);
        ///������Ϣ�ķ��ͷ�ʽ
        ///������Ϣ��svr-id
        pBlock->send_ctrl().setSvrId(uiSvrId);
        ///������Ϣ��host-id
        pBlock->send_ctrl().setHostId(0);
        ///������Ϣ���͵�����id
        pBlock->send_ctrl().setConnId(0);
        ///������Ϣ���͵�user-data
        pBlock->send_ctrl().setUserData(NULL);
        ///������Ϣ���ͽ׶ε���Ϊ��������ʼ�����Ƿ�֪ͨ����������Ƿ�֪ͨ������ʧ���Ƿ�֪ͨ
        pBlock->send_ctrl().setMsgAttr(CwxMsgSendCtrl::FAIL_FINISH_RETRY);
        ///����taskid
        pBlock->event().setTaskId(uiTaskId);
        return pBlock;
    }
    CWX_UINT32 getNextTaskId()
    {
        CwxMutexGuard<CwxMutexLock>  lock(&m_lock);
        m_uiTaskId++;
        if (!m_uiTaskId) m_uiTaskId = 1;
        return m_uiTaskId;
    }
    void incRecvMsg()
    {
        CwxMutexGuard<CwxMutexLock>  lock(&m_lock);
        m_uiRecvNum++;
        if (!(m_uiRecvNum % 10000))
        {
            CWX_INFO(("Send query msg num:%u", m_uiRecvNum));
        }
    }

protected:
    //init the Enviroment before run.0:success, -1:failure.
	virtual int initRunEnv();
    virtual void destroy();
private:
    CwxEchoTbClientConfig          m_config; ///<�����ļ�����
    CwxEchoTbEventHandler*         m_pEventHandle; ///�¼�����handler
    char                           m_szBuf100K[64 * 1024*1024+1]; ///<���͵�echo����buf������
    CWX_UINT32                     m_uiTaskId;
    CWX_UINT32                     m_uiRecvNum;///<���յ�echo�ظ�������
    CwxMutexLock                   m_lock; ///<m_uiRecvNum�ı�����
    CWX_UINT16                     m_unEchoGroupNum; ///echo����ķ�������
    CwxAppThreadPoolEx*            m_threadPool;///<�̳߳ض���
};

#endif


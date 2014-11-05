#ifndef __CWX_APP_COMMANDER_H__
#define __CWX_APP_COMMANDER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppCommander.h
@brief �ܹ�Commandģʽ����Ķ��壬Command�����¼���Event-type�������¼��ķַ�
@author cwinux@gmail.com
@version 0.1
@date 2009-07-20
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxStl.h"
#include "CwxStlFunc.h"
#include "CwxMsgBlock.h"

#include "CwxAppMacro.h"
#include "CwxAppConfig.h"
#include "CwxAppTss.h"

CWINUX_BEGIN_NAMESPACE

class CWX_API CwxAppCommander;
/**
@class CwxAppCmdOp
@brief ����SVR-ID���¼��Ĵ���HANDLE�Ľӿڶ��塣
*/
class CWX_API CwxAppCmdOp
{
public:
    ///���캯��
    CwxAppCmdOp()
    {
    }
    ///��������
    virtual ~CwxAppCmdOp()
    {

    }
public:
    /**
    @brief ���ӽ����¼��Ĵ�������
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onConnCreated(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
    {
        CWX_UNUSED_ARG(msg);
        CWX_UNUSED_ARG(pThrEnv);
        return 0;
    }
    /**
    @brief ���ӹر��¼��ĵĺ�����
    @param [in] msg ���ӹرյ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onConnClosed(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
    {
        CWX_UNUSED_ARG(msg);
        CWX_UNUSED_ARG(pThrEnv);
        return 0;
    }
    /**
    @brief �յ�ͨ�����ݰ��¼��Ĵ�������
    @param [in] msg �յ�ͨ�����ݰ����¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
    {
        CWX_UNUSED_ARG(msg);
        CWX_UNUSED_ARG(pThrEnv);
        return 0;
    }
    /**
    @brief ��Ϣ��������¼��Ĵ�������
    @param [in] msg ��Ϣ������ϵ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onEndSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
    {
        CWX_UNUSED_ARG(msg);
        CWX_UNUSED_ARG(pThrEnv);
        return 0;
    }
    /**
    @brief ��Ϣ����ʧ���¼��Ĵ�������
    @param [in] msg ��Ϣ����ʧ�ܵ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onFailSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
    {
        CWX_UNUSED_ARG(msg);
        CWX_UNUSED_ARG(pThrEnv);
        return 0;
    }
    /**
    @brief ��ʱ����¼��Ĵ�������
    @param [in] msg ��ʱ�����¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onTimeoutCheck(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
    {
        CWX_UNUSED_ARG(msg);
        CWX_UNUSED_ARG(pThrEnv);
        return 0;
    }
    /**
    @brief HANDLE��READY���¼��Ĵ�������
    @param [in] msg HANDLE��READY���¼����¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onEvent4Handle(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
    {
        CWX_UNUSED_ARG(msg);
        CWX_UNUSED_ARG(pThrEnv);
        return 0;
    }
    /**
    @brief �û��Զ����¼��Ĵ�������
    @param [in] msg �û��Զ����¼����¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onUserEvent(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
    {
        CWX_UNUSED_ARG(msg);
        CWX_UNUSED_ARG(pThrEnv);
        return 0;
    }
};

/**
@class CwxAppCommander
@brief Command�࣬�����¼���SVR-ID��ʵ���¼����䴦��Handle��ӳ�䡣
*/
class  CWX_API CwxAppCommander
{
    ///��Ϣӳ�亯�����Ͷ���
    typedef int (*fnEventApi)(CwxAppCmdOp* pEventOp, CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    ///SVR-ID���䴦��Handle��ӳ��Hash
    typedef hash_map<CWX_UINT32, CwxAppCmdOp*, CwxNumHash<CWX_UINT32> > CwxEventCommandHash;
public:
    ///���캯��
    CwxAppCommander()
        :m_msgHash(1024)
    {
        m_arrEvent[CwxEventInfo::DUMMY] = NULL;
        m_arrEvent[CwxEventInfo::CONN_CREATED] = &CwxAppCommander::onConnCreated;
        m_arrEvent[CwxEventInfo::CONN_CLOSED] = &CwxAppCommander::onConnClosed;
        m_arrEvent[CwxEventInfo::RECV_MSG] = &CwxAppCommander::onRecvMsg;
        m_arrEvent[CwxEventInfo::END_SEND_MSG] = &CwxAppCommander::onEndSendMsg;
        m_arrEvent[CwxEventInfo::FAIL_SEND_MSG] = &CwxAppCommander::onFailSendMsg;
        m_arrEvent[CwxEventInfo::TIMEOUT_CHECK] = &CwxAppCommander::onTimeoutCheck;
        m_arrEvent[CwxEventInfo::EVENT_4_HANDLE] = &CwxAppCommander::onEvent4Handle;
        m_arrEvent[CwxEventInfo::SYS_EVENT_NUM] = &CwxAppCommander::onUserEvent;
    }
    ///��������
    ~CwxAppCommander()
    {
        m_msgHash.clear();
    }
public:
    ///ע��SVR-IDΪuiSvrID���¼��Ĵ�����������ֵ��0:success, -1: ��SVR-ID�Ѿ�����
    int regHandle(CWX_UINT32 uiSvrID, CwxAppCmdOp* pHandle);
    /**
    @brief ����Ϣ�ַ����䴦��Handle
    @param [in] msg Ҫ�ַ����¼�
    @param [in] pThrEnv �̵߳�TSS����
    @param [in] iRet Handle����Ϣ�Ĵ�������-1������ʧ�ܣ�0��ָ����Handle��������¼���1������ɹ���
    @return true������Ϣ�ַ�����ָ���Ĵ���Handle��false��û��handle�������Ϣ
    */
    bool dispatch(CwxMsgBlock*& msg, CwxAppTss* pThrEnv, int& iRet);
    ///���Commandע���SVR-ID
    void reset()
    {
        m_msgHash.clear(); 
    }
private:
    /**
    @brief �����ӽ����¼��ַ����¼�����Handle��
    @param [in] pEventOp �¼��Ĵ���Handle��
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1��Handle����ʧ�ܣ�0��Handle��������¼���1��Handle�ɹ�������¼���
    */
    static int onConnCreated(CwxAppCmdOp* pEventOp, CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief �����ӹر��¼��ַ����¼�����Handle��
    @param [in] pEventOp �¼��Ĵ���Handle��
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1��Handle����ʧ�ܣ�0��Handle��������¼���1��Handle�ɹ�������¼���
    */
    static int onConnClosed(CwxAppCmdOp* pEventOp, CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ���յ�ͨ�����ݰ��¼��ַ����¼�����Handle��
    @param [in] pEventOp �¼��Ĵ���Handle��
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1��Handle����ʧ�ܣ�0��Handle��������¼���1��Handle�ɹ�������¼���
    */
    static int onRecvMsg(CwxAppCmdOp* pEventOp, CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ��ͨ�����ݰ���������¼��ַ����¼�����Handle��
    @param [in] pEventOp �¼��Ĵ���Handle��
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1��Handle����ʧ�ܣ�0��Handle��������¼���1��Handle�ɹ�������¼���
    */
    static int onEndSendMsg(CwxAppCmdOp* pEventOp, CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ��ͨ�����ݰ�����ʧ���¼��ַ����¼�����Handle��
    @param [in] pEventOp �¼��Ĵ���Handle��
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1��Handle����ʧ�ܣ�0��Handle��������¼���1��Handle�ɹ�������¼���
    */
    static int onFailSendMsg(CwxAppCmdOp* pEventOp, CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ����ʱ����¼��ַ����¼�����Handle��
    @param [in] pEventOp �¼��Ĵ���Handle��
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1��Handle����ʧ�ܣ�0��Handle��������¼���1��Handle�ɹ�������¼���
    */
    static int onTimeoutCheck(CwxAppCmdOp* pEventOp, CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ��IO Handle Ready�¼��ַ����¼�����Handle��
    @param [in] pEventOp �¼��Ĵ���Handle��
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1��Handle����ʧ�ܣ�0��Handle��������¼���1��Handle�ɹ�������¼���
    */
    static int onEvent4Handle(CwxAppCmdOp* pEventOp, CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ���û��¼��ַ����¼�����Handle��
    @param [in] pEventOp �¼��Ĵ���Handle��
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1��Handle����ʧ�ܣ�0��Handle��������¼���1��Handle�ɹ�������¼���
    */
    static int onUserEvent(CwxAppCmdOp* pEventOp, CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
private:
    ///��ȡSVR-ID�Ĵ���Handle
    CwxAppCmdOp* getEventOp(CWX_UINT32 uiSvrID);
private:
    fnEventApi          m_arrEvent[CwxEventInfo::SYS_EVENT_NUM + 1];///�¼������봦��API��ӳ��
    CwxEventCommandHash   m_msgHash;///<�¼�SVR-ID���¼�����Hanlde��ӳ��
};

CWINUX_END_NAMESPACE

#include "CwxAppCommander.inl"
#include "CwxPost.h"
#endif


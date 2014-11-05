#ifndef __CWM_CENTER_NERVE_QUERY_H__
#define __CWM_CENTER_NERVE_QUERY_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterNerveQuery.h
@brief Center��Nerve���в�ѯ�Ĵ���handle��
@author cwinux@gmail.com
@version 0.1
@date 2009-11-05
@warning
@bug
*/
#include "CwxAppCommander.h"
#include "CwxAppTss.h"
#include "CwmCenterTss.h"
class CwmCenterApp;
/**
@class CwmCenterNerveQuery
@brief  Center��ѯNerve�Ĵ���handle��
*/
class CwmCenterNerveQuery: public CwxAppCmdOp
{
public:
    enum
    {
        MSG_TYPE_SERVICE_QUERY = 1 ///<��ѯnerve����Ϣ����
    };
public:
    ///���캯��
    CwmCenterNerveQuery(CwmCenterApp* pApp):m_pApp(pApp)
    {

    }
    ///��������
    ~CwmCenterNerveQuery()
    {

    }
public:
    /**
    @brief Nerve�����ӽ����Ĵ�������
    @param [in] msg ���ӽ������¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onConnCreated(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief Nerve�����ӹرյĴ�������
    @param [in] msg ���ӹرյ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onConnClosed(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ����Nerve��ѯ�ظ��Ĵ�������
    @param [in] msg �յ�ͨ�����ݰ����¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief Nerve��ѯ��Ϣ������ϵ��¼��Ĵ�������
    @param [in] msg ��Ϣ������ϵ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onEndSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief Nerve��ѯ��Ϣ����ʧ�ܵĴ�������
    @param [in] msg ��Ϣ����ʧ�ܵ��¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onFailSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
public:
    ///����Nerve�Ĳ�ѯ��Ϣ
    static bool queryAction(CwmCenterApp* pApp, 
        CwxAppTss* pThrEnv,
        CWX_UINT32 uiConnId,
        CWX_UINT32 uiTaskId,
        char const* szSystem,
        char const* szService,
        char const* szAction);
private:
    CwmCenterApp*      m_pApp; ///<app����
};


#endif

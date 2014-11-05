#ifndef __CWM_NERVE_QUERY_HANDLER_H__
#define __CWM_NERVE_QUERY_HANDLER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmNerveQueryHandler.h
@brief Nerve���ղ�ѯ�Ĵ���handle��
@author cwinux@gmail.com
@version 0.1
@date 2009-10-26
@warning
@bug
*/
#include "CwxAppCommander.h"
#include "CwxAppTss.h"
#include "CwmNerveTss.h"
class CwmNerveApp;
/**
@class CwmNerveQueryHandler
@brief  Nerve���ղ�ѯ�Ĵ���handle��
*/
class CwmNerveQueryHandler : public CwxAppCmdOp
{
public:
    enum
    {
        MSG_TYPE_ONLINE_DATA = 1 ///��ѯ����Ϣ����
    };
public:
    ///���캯��
    CwmNerveQueryHandler(CwmNerveApp* pApp):m_pApp(pApp)
    {

    }
    ///��������
    ~CwmNerveQueryHandler()
    {

    }
public:
    /**
    @brief �յ����ݲ�ѯ��
    @param [in] msg �յ�ͨ�����ݰ����¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    /**
    @brief ��ʱ��ѯ��ʱ��action��ʱ��
    @param [in] msg ��ʱ�����¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onTimeoutCheck(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
public:
    ///ִ�в�ѯ
    void queryOnlineData(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
public:
    ///��ѯ��������ʱ���ظ���ѯ����
    static void replyError(CwmNerveApp* pApp,
        CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        char const* szErrMsg);
    ///��ѯ��ȷ����ʱ���ظ���ѯ�����ݡ�
    static void replyQuery(CwmNerveApp* pApp,
        CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        int status,
        string const& strLevel,
        string const& strErr,
        CwxKeyValueItem& record);
private:
    CwmNerveApp*      m_pApp;
};


#endif

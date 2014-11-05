#ifndef __CWM_CENTER_UI_QUERY_H__
#define __CWM_CENTER_UI_QUERY_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterUiQuery.h
@brief Center���ղ�ѯ�Ĵ���handle��
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
@class CwmCenterUiQuery
@brief  Center���ղ�ѯ�Ĵ���handle��
*/
class CwmCenterUiQuery : public CwxAppCmdOp
{
public:
    enum
    {
        MSG_TYPE_QUERY = 1 ///<UI��ѯ����Ϣ����
    };
public:
    ///���캯��
    CwmCenterUiQuery(CwmCenterApp* pApp):m_pApp(pApp)
    {

    }
    ///��������
    ~CwmCenterUiQuery()
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
    ///�ظ�UI��ѯ�Ľ��
    static void replyQuery(CwmCenterApp* pApp, 
        CwxAppTss* pThrEnv,
        CWX_UINT32 uiConnId,
        CwxMsgHead const& recvHeader,
        int code,
        char const* szType,
        char const* szContent,
        CWX_UINT32 uiContentLen);
private:
    ///ui��ѯ���������
    void uiQuery(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
private:
    CwmCenterApp*      m_pApp; ///<app����
};


#endif

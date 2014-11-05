#ifndef __CWM_CENTER_ALARM_ACCEPTOR_H__
#define __CWM_CENTER_ALARM_ACCEPTOR_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterAlarmAcceptor.h
@brief �澯���յĴ���handle��
@author cwinux@gmail.com
@version 0.1
@date 2009-11-05
@warning
@bug
*/
#include "CwxAppCommander.h"
#include "CwmCenterTss.h"
#include "CwmCmnAlarm.h"
class CwmCenterApp;
/**
@class CwmCenterAlarmAcceptor
@brief �澯���յĴ���handle
*/
class CwmCenterAlarmAcceptor : public CwxAppCmdOp
{
public:
    enum
    {
        MSG_TYPE_ALARM_ACCEPT = 1 ///<�澯�������Ϣ����
    };
public:
    ///���캯��
    CwmCenterAlarmAcceptor(CwmCenterApp* pApp):m_pApp(pApp)
    {

    }
    ///��������
    ~CwmCenterAlarmAcceptor()
    {

    }
public:
    /**
    @brief �յ��澯�Ĵ�������
    @param [in] msg �յ�ͨ�����ݰ����¼�����
    @param [in] pThrEnv �̵߳�TSS����
    @return -1������ʧ�ܣ�0����������¼���1��������¼���
    */
    virtual int onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
private:
    ///���͸澯����Ļظ�
    void replyAlarm(CwxAppTss* pThrEnv,
        CWX_UINT32 uiConnId,
        CwxMsgHead const& recvHeader,
        CWX_UINT32 uiWid);
private:
    CwmCenterApp*      m_pApp;///<app����
};


#endif

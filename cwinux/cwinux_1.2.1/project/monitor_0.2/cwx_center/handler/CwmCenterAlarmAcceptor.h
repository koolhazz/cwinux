#ifndef __CWM_CENTER_ALARM_ACCEPTOR_H__
#define __CWM_CENTER_ALARM_ACCEPTOR_H__
/*
版权声明：
    本软件为个人所有，遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html），
但有以下例外：
    腾讯公司及与腾讯公司有直接业务与合作关系的公司不得使用此软件。原因可参考：
http://it.sohu.com/20100903/n274684530.shtml
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterAlarmAcceptor.h
@brief 告警接收的处理handle。
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
@brief 告警接收的处理handle
*/
class CwmCenterAlarmAcceptor : public CwxAppCmdOp
{
public:
    enum
    {
        MSG_TYPE_ALARM_ACCEPT = 1 ///<告警报告的消息类型
    };
public:
    ///构造函数
    CwmCenterAlarmAcceptor(CwmCenterApp* pApp):m_pApp(pApp)
    {

    }
    ///析构函数
    ~CwmCenterAlarmAcceptor()
    {

    }
public:
    /**
    @brief 收到告警的处理函数。
    @param [in] msg 收到通信数据包的事件对象。
    @param [in] pThrEnv 线程的TSS对象。
    @return -1：处理失败，0：不处理此事件，1：处理此事件。
    */
    virtual int onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
private:
    ///发送告警报告的回复
    void replyAlarm(CwxAppTss* pThrEnv,
        CWX_UINT32 uiConnId,
        CwxMsgHead const& recvHeader,
        CWX_UINT32 uiWid);
private:
    CwmCenterApp*      m_pApp;///<app对象
};


#endif

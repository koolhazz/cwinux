#ifndef __CWM_CENTER_NERVE_STATUS_H__
#define __CWM_CENTER_NERVE_STATUS_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterNerveStatus.h
@brief Nerve�ڵ������״̬���塣
@author cwinux@gmail.com
@version 0.1
@date 2009-11-06
@warning
@bug
*/
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwmCmnMacro.h"
#include "CwmCenterConfig.h"
#include "CwmCmnAlarmStatus.h"

///Nerve���ӵ�״̬���ƶ���
class CwmCenterNerveStatus
{
public:
    ///���캯��
    CwmCenterNerveStatus()
    {
        m_uiConnId = 0;
        m_pHost = NULL;
        m_bConnected = false;
    }
    ///��������
    ~CwmCenterNerveStatus()
    {

    }
public:
    ///����nerve�ڵ������ID
    void setConnId(CWX_UINT32 uiConnId)
    {
        m_uiConnId = uiConnId;
    }
    ///��ȡnerve�ڵ������id
    CWX_UINT32 getConnId() const
    {
        return m_uiConnId;
    }
    ///����host��������Ϣ
    void setHostInfo(CwmCenterHost const* pHost)
    {
        m_pHost = pHost;
        if (pHost)
        {
            m_hostStatus.setAlarmRule(pHost->getAlarmRule());
            m_hostStatus.setSystemName("Center");
            m_hostStatus.setServiceName("Nerve");
            m_hostStatus.setActionName("connection");
            m_hostStatus.setAlarmType("lost");
        }
    }
    ///��ȡhost��������Ϣ
    CwmCenterHost const* getHostInfo() const
    {
        return m_pHost;
    }
    ///��ȡhost��״̬
    CwmCmnAlarmStatus& getStatus()
    {
        return m_hostStatus;
    }
    ///��������״̬
    void setConnected(bool bConnected)
    {
        m_bConnected = bConnected;
    }
    ///��ȡ�Ƿ�����
    bool isConnected() const
    {
        return m_bConnected;
    }
private:
    ///��ֹ��������
    CwmCenterNerveStatus(CwmCenterNerveStatus const& )
    {

    }
    ///��ֹ��ֵ����
    CwmCenterNerveStatus& operator=(CwmCenterNerveStatus const& )
    {
        return *this;
    }

private:
    CWX_UINT32            m_uiConnId; ///<Nerve�ڵ������ID
    CwmCenterHost const*   m_pHost; ///<Nerve�ڵ��host��Ϣ
    CwmCmnAlarmStatus     m_hostStatus; ///<host��״̬
    bool                  m_bConnected; ///<��nerve�������Ƿ���
};

#endif

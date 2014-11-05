#ifndef __CWM_NERVE_SERVICE_STATUS_H__
#define __CWM_NERVE_SERVICE_STATUS_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmNerveServiceStatus.h
@brief Service״̬���塣
@author cwinux@gmail.com
@version 0.1
@date 2009-10-24
@warning
@bug
*/
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwmCmnMacro.h"
#include "CwmCmnAlarmStatus.h"
#include "CwmNerveActionStatus.h"
#include "CwmCmnAlarmRule.h"

/**
@class CwmNerveServiceStatus
@brief Service��״̬������
*/
class CwmNerveServiceStatus
{
public:
    ///���캯��
    CwmNerveServiceStatus();
    ///��������
    ~CwmNerveServiceStatus();
public:
    ///����service������ID
    void setConnId(CWX_UINT32 uiConnId)
    {
        m_uiServerConnId = uiConnId;
    }
    ///��ȡ����id
    CWX_UINT32 getConnId() const
    {
        return m_uiServerConnId;
    }
    ///����service��service-info
    void setServiceInfo(CwmNerveServiceInfo const* pServiceInfo)
    {
        m_pServiceInfo = pServiceInfo;
        if (pServiceInfo)
        {
            m_alarmStatus.setSystemName(pServiceInfo->getSystem());
            m_alarmStatus.setServiceName(pServiceInfo->getName());
            m_alarmStatus.setAlarmType("lost");
            m_alarmStatus.setActionName(pServiceInfo->isCgi()?"cgi":"server");
        }
    }
    ///��ȡservice��service-info
    CwmNerveServiceInfo const* getServiceInfo() const
    {
        return m_pServiceInfo;
    }
    ///��ȡserver���͵�service�����action
    CwmCmnAlarmStatus& getSelfStatus()
    {
        return m_alarmStatus;
    }
    ///��ӹ����CwmNerveActionStatus
    void addActionStatus(CwmNerveActionStatus* pActionStatus)
    {
        m_lsActStatus.push_back(pActionStatus);
    }
    ///��ȡȫ����action-status
    list<CwmNerveActionStatus*>& getActionStatus()
    {
        return m_lsActStatus;
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
    CwmNerveServiceStatus(CwmNerveServiceStatus const& )
    {

    }
    ///��ֹ���Ʋ���
    CwmNerveServiceStatus& operator=(CwmNerveServiceStatus const& )
    {
        return *this;
    }

private:
    CWX_UINT32                  m_uiServerConnId; ///<���ڷ������͵�service������id
    CwmNerveServiceInfo const*    m_pServiceInfo; ///<�������Ϣ
    CwmCmnAlarmStatus            m_alarmStatus; ///<service�����״̬����������server���͵����ӵĸ澯
    list<CwmNerveActionStatus*>    m_lsActStatus; ///<service��action��״̬
    bool                       m_bConnected; ///<�����Ƿ���
};

#endif

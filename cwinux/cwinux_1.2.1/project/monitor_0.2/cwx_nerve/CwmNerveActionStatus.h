#ifndef __CWM_NERVE_ACTION_STATUS_H__
#define __CWM_NERVE_ACTION_STATUS_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmNerveActionStatus.h
@brief Action��״̬��������塣
@author cwinux@gmail.com
@version 0.1
@date 2009-10-28
@warning
@bug
*/
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxPackage.h"
#include "CwmCmnMacro.h"
#include "CwmCmnRecord.h"
#include "CwmCmnAlarm.h"
#include "CwmCmnAlarmRule.h"
#include "CwmCmnAlarmStatus.h"
#include "CwmNerveConfig.h"

class CwmNerveServiceStatus;
/**
@class CwmNerveActionStatus
@brief Action״̬������
*/
class CwmNerveActionStatus
{
public:
    ///���캯��
    CwmNerveActionStatus();
    ///��������
    ~CwmNerveActionStatus();
public:
    ///��ȡ�澯��״̬
    CwmCmnAlarmStatus& getAlarmStatus()
    {
        return m_alarmStatus;
    }
    ///��ȡAction��������Ϣ
    CwmNerveActionInfo const* getActionInfo() const
    {
        return m_pActionInfo;
    }
    ///����Action��������Ϣ
    void setActionInfo(CwmNerveActionInfo const* pActionInfo)
    {
        if (pActionInfo)
        {
            m_alarmStatus.setAlarmRule(&pActionInfo->getAlarmRule());
            m_alarmStatus.setActionName(pActionInfo->getName());
            m_alarmStatus.setAlarmType(pActionInfo->getAlarmType());
        }
        m_pActionInfo = pActionInfo;
    }
    ///��ȡservice status
    CwmNerveServiceStatus const* getServiceStatus() const
    {
        return m_pServiceStatus;
    }
    ///����service status
    void setServiceStatus(CwmNerveServiceStatus const* pServiceStatus);
private:
    ///��ֹ��������
    CwmNerveActionStatus(CwmNerveActionStatus const& )
    {

    }
    ///��ֹ���Ʋ���
    CwmNerveActionStatus & operator=(CwmNerveActionStatus const& )
    {
        return *this;
    }
private:
    CwmCmnAlarmStatus        m_alarmStatus; ///<action�ĸ澯���ƶ���
    CwmNerveActionInfo const* m_pActionInfo; ///<action����Ϣ
    CwmNerveServiceStatus const* m_pServiceStatus; ///<action������service����
};



#endif

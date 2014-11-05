#include "CwmNerveActionStatus.h"
#include "CwmNerveServiceStatus.h"
#include "CwxDate.h"

///���캯��
CwmNerveActionStatus::CwmNerveActionStatus()
{
}
///��������
CwmNerveActionStatus::~CwmNerveActionStatus()
{

}
///����action��service����
void CwmNerveActionStatus::setServiceStatus(CwmNerveServiceStatus const* pServiceStatus)
{
    if (pServiceStatus)
    {
        m_alarmStatus.setSystemName(pServiceStatus->getServiceInfo()->getSystem());
        m_alarmStatus.setServiceName(pServiceStatus->getServiceInfo()->getName());
    }
    m_pServiceStatus=pServiceStatus;
} 

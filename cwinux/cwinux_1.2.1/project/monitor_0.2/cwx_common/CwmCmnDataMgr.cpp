#include "CwmCmnDataMgr.h"

///��ʼ��������������ֵ��true���ɹ���false��ʧ��
bool CwmCmnDataMgr::init(string const& )
{
    m_alarms.clear();
    return true;
}
///���һ���澯������ֵ��-1��ʧ�ܣ�0�����ڣ�1�����һ��
int CwmCmnDataMgr::insert(CwmCmnAlarm const& alarm)
{
    CwxMutexGuard<CwxMutexLock> lock(&m_lock);
    if (alarm.getState() == CwmCmnAlarm::ALARM_STATE_INIT)
    {
        m_alarms.push_back(alarm);
        return 1;
    }
    return 0;
}
///���һ�����ݡ�����ֵ��-1��ʧ�ܣ�0�����ڣ�1�����һ��
int CwmCmnDataMgr::insert(CwmCmnRecord const& )
{
    CwxMutexGuard<CwxMutexLock> lock(&m_lock);
    return 1;
}
///��ȡ��һ��δ����ĸ澯������ֵ��-1��ʧ�ܣ�0�������ڣ�1����ȡһ��
int CwmCmnDataMgr::nextReportAlarm(CwmCmnAlarm& alarm)
{
    CwxMutexGuard<CwxMutexLock> lock(&m_lock);
    if (m_alarms.begin() != m_alarms.end())
    {
        alarm = *m_alarms.begin();
        m_alarms.pop_front();
        return 1;
    }
    return 0;
}
///���������һ���澯�ı��档����ֵ��-1��ʧ�ܣ�0�������ڣ�1���޸��˸澯��״̬
int CwmCmnDataMgr::setAlarmReported(string const& strHost, CWX_UINT32 uiWid)
{
    CwxMutexGuard<CwxMutexLock> lock(&m_lock);
    list<CwmCmnAlarm>::iterator iter = m_alarms.begin();
    while(iter != m_alarms.end())
    {
        if ((strHost == iter->getHost())&& (uiWid == iter->getWid()))
        {
            m_alarms.erase(iter);
            return 1;
        }
        iter++;
    }
    return 0;
}

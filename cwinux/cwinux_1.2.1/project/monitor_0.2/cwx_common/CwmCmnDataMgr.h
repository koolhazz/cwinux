#ifndef __CWM_CMN_DATA_MGR_H__
#define __CWM_CMN_DATA_MGR_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCmnDataMgr.h
@brief �澯�������������ݵ����ݹ�������ʵ�����ݵĴ洢����ѯ���޸ġ�
@author cwinux@gmail.com
@version 0.1
@date 2009-10-27
@warning
@bug
*/
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxMutexLock.h"
#include "CwxLockGuard.h"
#include "CwmCmnMacro.h"
#include "CwmCmnAlarm.h"
#include "CwmCmnRecord.h"


/**
@class CwmCmnDataMgr
@brief ���ݹ������ʵ�ָ澯���������ݵĴ洢����ѯ�Ȳ���
*/

class CwmCmnDataMgr
{
public:
    ///���캯��
    CwmCmnDataMgr()
    {
        m_uiMaxPid = time(NULL);
        m_uiMaxWid = time(NULL);
        memset(m_strErrMsg, 0x00, sizeof(m_strErrMsg));
    }
    ///��������
    ~CwmCmnDataMgr()
    {

    }
public:
    ///��ʼ��������������ֵ��true���ɹ���false��ʧ��
    bool init(string const& strFileName);
    ///���һ���澯������ֵ��-1��ʧ�ܣ�0�����ڣ�1�����һ��
    int insert(CwmCmnAlarm const& alarm);
    ///���һ�����ݡ�����ֵ��-1��ʧ�ܣ�0�����ڣ�1�����һ��
    int insert(CwmCmnRecord const& record);
    ///��ȡ��һ��δ����ĸ澯������ֵ��-1��ʧ�ܣ�0�������ڣ�1����ȡһ��
    int nextReportAlarm(CwmCmnAlarm& alarm);
    ///���������һ���澯�ı��档����ֵ��-1��ʧ�ܣ�0�������ڣ�1���޸��˸澯��״̬
    int setAlarmReported(string const& strHost, CWX_UINT32 uiWid);
    ///��ȡ��һ��wid
    CWX_UINT32 nextWid()
    {
        return m_uiMaxWid++;
    }
    ///��ȡ��һ��pid
    CWX_UINT32 nextPid()
    {
        return m_uiMaxPid++;
    }
    ///��ȡ������Ϣ
    char const* getErrMsg() const
    {
        return m_strErrMsg;
    }
private:
    ///��ֹ��������
    CwmCmnDataMgr(CwmCmnDataMgr const& )
    {

    }
    ///��ֹ��ֵ����
    CwmCmnDataMgr& operator=(CwmCmnDataMgr const& )
    {
        return *this;
    }

private:
    CwxMutexLock      m_lock; ///<������
    CWX_UINT32        m_uiMaxWid;///<��ǰ����wid
    CWX_UINT32        m_uiMaxPid;///<��ǰ����pid
    list<CwmCmnAlarm>  m_alarms;///<�����ĸ澯�б�
    string            m_strFile;///<�����ļ�����
    char              m_strErrMsg[512];///<������Ϣ
    
};

#endif

#ifndef __CWM_CMN_RECORD_H__
#define __CWM_CMN_RECORD_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCmnRecord.h
@brief �ɼ������ݶ���Ķ����ļ���
@author cwinux@gmail.com
@version 0.1
@date 2009-10-27
@warning
@bug
*/
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwmCmnMacro.h"


/**
@class CwmCmnRecord
@brief Nerve�ĸ澯����
*/

class CwmCmnRecord{
public:
    enum{
        DATA_ALIGN = 128 ///<����buf�Ķ���߽�
    };
    
public:
    ///���캯��
    CwmCmnRecord(){
        m_uiPid = 0;
        m_uiWid = 0;
        m_uiDataLen = 0;
        m_uiBufLen = 0;
        m_pData = NULL; ///<�ɼ����������ݡ�
    }
    ///��������
    ~CwmCmnRecord(){
        if (m_pData) delete [] m_pData;
    }
    ///���캯��
    CwmCmnRecord(string const& strHost,
                 CWX_UINT32 uiPid,
                 CWX_UINT32 uiWid,
                 string const& strDatetime,
                 string const& strSystem,
                 string const& strService,
                 string const& strAction,
                 char const* pData,
                 CWX_UINT32 uiDataLen,
                 string const& strErr)
    {
        m_strHost = strHost;
        m_uiPid = uiPid;
        m_uiWid = uiWid;
        m_strDatetime = strDatetime;
        m_strSystem = strSystem;
        m_strService = strService;
        m_strAction = strAction;
        m_uiDataLen = 0;
        m_uiBufLen = 0;
        m_pData = NULL;
        setData(pData, uiDataLen);
        m_strError = strErr;
    }
    ///��������
    CwmCmnRecord(CwmCmnRecord const& obj){
        m_strHost = obj.m_strHost;
        m_uiPid = obj.m_uiPid;
        m_uiWid = obj.m_uiWid;
        m_strDatetime = obj.m_strDatetime;
        m_strSystem = obj.m_strSystem;
        m_strService = obj.m_strService;
        m_strAction = obj.m_strAction;
        m_uiDataLen = 0;
        m_uiBufLen = 0;
        m_pData = NULL;
        setData(obj.m_pData, obj.m_uiDataLen);
        m_strError = obj.m_strError;
    }
    ///��ֵ����
    CwmCmnRecord& operator=(CwmCmnRecord const& obj){
        if (this != &obj){
            m_strHost = obj.m_strHost;
            m_uiPid = obj.m_uiPid;
            m_uiWid = obj.m_uiWid;
            m_strDatetime = obj.m_strDatetime;
            m_strSystem = obj.m_strSystem;
            m_strService = obj.m_strService;
            m_strAction = obj.m_strAction;
            setData(obj.m_pData, obj.m_uiDataLen);
            m_strError = obj.m_strError;
        }
        return *this;
    }
public:
    ///��ȡ���ݵ�host
    string const& getHost() const { return m_strHost;}
    ///�������ݵ�host
    void setHost(string const& strHost){ m_strHost = strHost;}
    ///��ȡ����ID
    CWX_UINT32 getPid() const { return m_uiPid;}
    ///��������ID
    void setPid(CWX_UINT32 uiId) { m_uiPid = uiId;}
    ///��ȡ���ݵĸ澯id
    CWX_UINT32 getWid() const { return m_uiWid;}
    ///�������ݵĸ澯��id
    void setWid(CWX_UINT32 uiId) { m_uiWid = uiId;}
    ///��ȡ���ݵ�ʱ��
    string const& getDatetime() const { return m_strDatetime;}
    ///�������õ�ʱ��
    void setDatetime(string const& strDatetime) { m_strDatetime = strDatetime;}
    ///��ȡ����������system
    string const& getSystem() const { return m_strSystem;}
    ///��������������system
    void setSystem(string const& strSystem) { m_strSystem = strSystem;}
    ///��ȡ����������service
    string const& getService() const { return m_strService;}
    ///��������������service
    void setService(string const& strService) { m_strService = strService;}
    ///��ȡ����������action
    string const& getAction() const { return m_strAction;}
    ///��������������action
    void setAction(string const& strAction) { m_strAction = strAction;}
    ///��ȡ���ݴ���ʱ�Ĵ�������
    string const& getError() const { return m_strError;}
    ///�������ݴ���ʱ�Ĵ�������
    void setError(string const& strErr) { m_strError = strErr;}
    ///��ȡ���ݵ�data
    char const* getData() const { return m_pData;}
    ///��ȡ���ݵĳ���
    CWX_UINT32  getDataLen() const { return m_uiDataLen;}
    ///��ȡ���ݵ�buf����
    CWX_UINT32 getDataBufLen() const { return m_uiBufLen;}
    ///��������
    void setData(char const* pData, CWX_UINT32 uiDataLen){
        if (uiDataLen > m_uiBufLen){
           if (m_pData) delete [] m_pData;
           m_uiBufLen = uiDataLen - (uiDataLen%DATA_ALIGN) + DATA_ALIGN;
           m_pData = new char[m_uiBufLen];
        }
        if (uiDataLen) memcpy(m_pData, pData, uiDataLen);
        m_uiDataLen = uiDataLen;
    }

private:
    string      m_strHost; ///<���ݵ�����
    CWX_UINT32  m_uiPid;///<���ݵ�id
    CWX_UINT32  m_uiWid; ///<���и澯�����Ӧ�澯id
    string      m_strDatetime; ///<���ݲɼ���ʱ��
    string      m_strSystem; ///<����������ϵͳ
    string      m_strService; ///<���������ķ���
    string      m_strAction; ///<����������action
    string      m_strError; ///<�����ݲɼ��д�����Ϊ���������
    CWX_UINT32  m_uiBufLen; ///data��buf��С
    CWX_UINT32  m_uiDataLen; ///<�ɼ������ݵĳ���
    char*        m_pData; ///<�ɼ����������ݡ�
};

#endif

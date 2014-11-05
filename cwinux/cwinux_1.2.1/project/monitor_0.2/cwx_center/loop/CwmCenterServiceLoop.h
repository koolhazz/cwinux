#ifndef __CWM_CENTER_SERVICE_LOOP_H__
#define __CWM_CENTER_SERVICE_LOOP_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterServiceLoop.h
@brief ģ���loop����ʵ��Center�������һ��system��service��Ϣ�����
@author cwinux@gmail.com
@version 0.1
@date 2009-11-06
@warning
@bug
*/

#include "CwxHtmlTmplLoop.h"
#include "CwxHtmlTmpl.h"
#include "CwmCenterTss.h"
#include "CwmCenterConfig.h"
class CwmCenterApp;
/**
@class CwmCenterServiceLoop
@brief ��ѯ����ʾCenter�����������system��Task
*/
class CwmCenterServiceLoop : public  CwxHtmlTmplLoop
{
public:
    CwmCenterServiceLoop()
    {
        m_bFirst = false;
        m_pService = NULL;
        m_pTss = NULL;
    }
    ~CwmCenterServiceLoop()
    {
    }
public:
    ///��ʼ��loop����
    void init(CwmCenterTss* pTss, map<string/*service name*/, CwmCenterService*> const* pServices);
public:
    /**
    @brief ��Ϊglobal��loop����û����һ��
    @return 0��û����һ�����ݼ�¼��1���Ƶ�����һ�����ݼ�¼
    */
    virtual int next();
    /**
    @brief ��ȡglobal �����һ��������
    @param [in] szName ����������
    @param [in] bAttrName �������Ƿ��ǵ�ǰ�����������
    @param [in] ucSysAttr ������ϵͳ���ԣ���CwxHtmlTmplValSysAttr�����˶���
    @param [in] szUserAttr  �û��Լ��ı�������
    @param [in] iLengthLimit ������������ĳ������ƣ�<0��������ַ��������ܳ����˾���ֵ
    0��û�����ƣ�>0��������ֽ������ܳ�������ֵ
    @param [in] pEscape ������escape�任����
    @param [in] szArgs ��������ʱ���õĲ���
    @param [in] pRepl ģ����ַ��滻����
    @param [in] bVal true����Ϊ����ȡֵ��false����Ϊ�Ƚ�ȡֵ
    @return NULL�����������ڣ�����Ϊ��������ֵ
    */
    virtual char const* val(char const* szName,
        bool bAttrName,
        CWX_UINT8 ucSysAttr,
        char const* szUserAttr,
        int iLengthLimit,
        CwxHtmlTmplEscape* pEscape,
        char const* szArgs,
        CwxReplBase* pRepl,
        bool bVal);
    /**
    @brief ����system��loop����
    @param [in] szLoop loop���������
    @param [in] attrs loop�������ʱ�����õ�LOOP�����Զ�
    @return NULL��loop���󲻴��ڣ�����Ϊ��������Ӧ��LOOP����
    */
    virtual CwxHtmlTmplLoop* loop(char const* szLoop,
        list<pair<char*, char*> >const& attrs);
public:
    ///��ȡservice���������ֵ
    static char const* getServiceAttr(CwmCenterService const* pService, char const* szAttr, char* szBuf64k);
private:
    bool           m_bFirst; ///<�Ƿ��ǵ�һ��loop
    map<string/*service name*/, CwmCenterService*> const* m_pService; ///<service������б�
    map<string/*service name*/, CwmCenterService*>::const_iterator m_service_iter; ///<loop�ĵ�ǰservice
    CwmCenterTss*    m_pTss;///<tss����
};


#endif

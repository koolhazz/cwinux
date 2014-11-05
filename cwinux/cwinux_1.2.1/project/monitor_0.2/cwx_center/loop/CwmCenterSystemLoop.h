#ifndef __CWM_CENTER_SYSTEM_LOOP_H__
#define __CWM_CENTER_SYSTEM_LOOP_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterSystemLoop.h
@brief ģ���loop����ʵ��Center�������system����Ϣ�����
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
#include "CwmCenterTss.h"
#include "CwmCenterConfig.h"
class CwmCenterApp;
/**
@class CwmCenterSystemLoop
@brief ģ���loop����ʵ��Center�������system����Ϣ���
*/
class CwmCenterSystemLoop : public  CwxHtmlTmplLoop
{
public:
    ///���캯��
    CwmCenterSystemLoop()
    {
        m_pSystems = NULL;
        m_pTss = NULL;
        m_bFirst = true;
    }
    ///��������
    ~CwmCenterSystemLoop()
    {

    }
public:
    ///��ʼ��loop����
    void init(CwmCenterTss* pTss, map<string/*system name*/, CwmCenterSystem*> const* pSystems);
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
    ///��ȡsystem������ֵ
    static char const* getSystemAttr(CwmCenterSystem const* pSystem, char const* szAttr, char* szBuf64k);
private:
    bool           m_bFirst; ///<�ǲ��ǵ�һ��ִ��loop
    map<string/*system name*/, CwmCenterSystem*> const* m_pSystems; ///<system���б�
    map<string/*system name*/, CwmCenterSystem*>::const_iterator m_system_iter; ///<��ǰloop��system
    CwmCenterTss*    m_pTss; ///<tss����
};


#endif

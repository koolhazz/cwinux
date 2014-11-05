#ifndef __CWM_CENTER_ACTION_LOOP_H__
#define __CWM_CENTER_ACTION_LOOP_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterActionLoop.h
@brief ģ���loop����ʵ��Center�������һ��service�µ�actionʵʱ��Ϣ�������
@author cwinux@gmail.com
@version 0.1
@date 2009-11-06
@warning
@bug
*/

#include "CwxHtmlTmplLoop.h"
#include "CwxHtmlTmpl.h"
#include "CwxPackageReader.h"
#include "CwxMsgBlock.h"
#include "CwmCenterTss.h"
#include "CwmCenterConfig.h"
#include "CwmCenterNerveStatus.h"

class CwmCenterApp;
/**
@class CwmCenterActionLoopData
@brief Never�Ĳ�ѯ�������
*/
class CwmCenterActionLoopData
{
public:
    ///���캯��
    CwmCenterActionLoopData()
    {
        m_pRecvMsg = NULL;
        m_pNerve = NULL;
    }
    ///��������
    ~CwmCenterActionLoopData()
    {
        if (m_pRecvMsg) CwxMsgBlockAlloc::free(m_pRecvMsg);
        m_pRecvMsg = NULL;
    }
public:
    CwxMsgBlock*   m_pRecvMsg;///<��nerve�յ��Ĳ�ѯ��Ϣ��NULL��ʾ��ѯʧ��
    string           m_strErrMsg; ///<��ѯʧ��ʱ��ʧ������
    CwmCenterNerveStatus*    m_pNerve; ///<��ѯ��nerve����
};
/**
@class CwmCenterActionLoop
@brief ģ���loop����ʵ��Center�������һ��service�µ�actionʵʱ��Ϣ�������
*/
class CwmCenterActionLoop : public  CwxHtmlTmplLoop
{
public:
    CwmCenterActionLoop()
    {
        m_pActions = NULL;
        m_uiActioNum = 0;
        m_uiIndex = 0;
        m_pTss = NULL;
        m_bValid = false;
        m_pNerve = NULL;
    }
    ~CwmCenterActionLoop()
    {
    }
public:
    ///��ʼ��loop����
    void init(CwmCenterTss* pTss,
        string const& strName,
        CwmCenterActionLoopData* pActions,
        CWX_UINT32 uiActioNum);
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
    ///��ȡhost��������Ե�ֵ
    static char const* getNerveAttr(CwmCenterNerveStatus const* pNever,
        char const* szAttr,
        char* szBuf64k);
    ///��ȡaction���������ֵ
    static char const* getActionAttr(string const& strName,
        CwxPackageReader const& actionReader,
        char const* szAttr,
        char* szBuf64k);
private:
    string      m_strName; ///<action������
    CwmCenterActionLoopData* m_pActions; ///<nerve���ص�����
    CwxPackageReader        m_packReader; ///<����package��reader
    bool                   m_bValid; ///<��ǰ��action�ķ���ֵ�Ƿ���Ч
    string                 m_strErrMsg;///<��ǰaction��Ч��ԭ��
    CwmCenterNerveStatus*   m_pNerve; ///<��ǰ��¼��nerve����
    CWX_UINT32  m_uiActioNum; ///<loop��nerve����
    CWX_UINT32   m_uiIndex; ///<loop�ĵ�ǰindex
    CwmCenterTss*    m_pTss;///<tss����
};


#endif

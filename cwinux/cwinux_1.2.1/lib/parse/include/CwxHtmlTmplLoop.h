#ifndef __CWX_HTML_TMPL_LOOP_H__
#define __CWX_HTML_TMPL_LOOP_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxHtmlTmplLoop.h
@brief �����ı��滻ģ���loop����ӿڣ�ģ����һ��Ĭ�ϵĸ�LOOP����
@author cwinux@gmail.com
@version 0.1
@date 2009-10-10
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxType.h"
#include "CwxStl.h"
#include "CwxReplMachine.h"
#include "CwxHtmlTmplEscape.h"

CWINUX_BEGIN_NAMESPACE
/**
@class CwxHtmlTmplLoop
@brief �ı��滻ģ���LOOP����Ľӿ��࣬Ϊ����LOOP����Ļ��ࡣ
*/
class CWX_API CwxHtmlTmplLoop
{
public:
    ///���캯��
    CwxHtmlTmplLoop()
    {

    }
    ///��������
    virtual ~CwxHtmlTmplLoop()
    {

    }
public:
    /**
    @brief ��ȡLOOP�������һ�����ݼ�¼���ɵĻ�������
    @return 0��û����һ�����ݼ�¼��1���Ƶ�����һ�����ݼ�¼
    */
    virtual int next() =0;
    /**
    @brief ��LOOP�����У���ȡһ����������ֵ��
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
        bool bVal)=0;
    /**
    @brief ����LOOP�����֣���ȡLOOP����ʵ����
    @param [in] szLoop loop���������
    @param [in] attrs loop�������ʱ�����õ�LOOP�����Զ�
    @return NULL��loop���󲻴��ڣ�����Ϊ��������Ӧ��LOOP����
    */
    virtual CwxHtmlTmplLoop* loop(char const* szLoop,
        list<pair<char*, char*> >const& attrs) = 0;
};



CWINUX_END_NAMESPACE

#include "CwxPost.h"

#endif

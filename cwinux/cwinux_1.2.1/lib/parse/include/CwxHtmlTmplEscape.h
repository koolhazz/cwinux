#ifndef __CWX_HTML_TMPL_ESCAPE_H__
#define __CWX_HTML_TMPL_ESCAPE_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxHtmlTmplEscape.h
@brief �����ı��滻ģ���Escape��������Ľӿڣ���ʵ��һЩ���õ�Escape��������
@author cwinux@gmail.com
@version 0.1
@date 2009-10-10
@warning
@bug
*/

#include "CwxPre.h"
#include "CwxType.h"
#include "CwxStl.h"
#include "CwxStlFunc.h"
#include "CwxChrType.h"

CWINUX_BEGIN_NAMESPACE

class CwxHtmlTmpl;
class CwxHtmlTmplEnv;
/**
@class CwxHtmlTmplEscape
@brief �ı��滻ģ���Escape��������Ľӿ��࣬Ϊ����CwxHtmlTmplEscape��������Ļ��ࡣ<br>
�˶�����뱣֤���̰߳�ȫ
*/
class CWX_API CwxHtmlTmplEscape
{
public:
    ///���캯��
    CwxHtmlTmplEscape(string const& strName):m_strName(strName)
    {

    }
    ///��������
    virtual ~CwxHtmlTmplEscape()
    {

    }
public:
    /**
    @brief ESCACPE������
    @param [in] szSrc ������ֵ
    @param [in] szOutBuf ����escape�����buffer
    @param [in,out] uiBufLen  ����szOutBuf�Ĵ�С������γɵ�escape�ַ����ĳ���
    @param [in] len ��������ʱ���õġ���������ݵĳ�������
    @param [in] szArgs ģ���﷨�����õ�args��NULL��ʾû������
    @param [in] pHtmlTmpl ��������������ģ�����
    @param [in] pHtmlTmplEnv ģ���γɵĻ�������
    @return true��encode�ɹ���false��szOutBuf̫С
    */
    virtual bool escape(char const* szSrc,
        char* szOutBuf,
        CWX_UINT32& uiBufLen,
        int len,
        char const* szArgs,
        CwxHtmlTmpl* pHtmlTmpl,
        CwxHtmlTmplEnv* pHtmlTmplEnv)=0;
public:
    ///��ȡescape������
    string const& getName() const
    {
        return m_strName;
    }
private:
    string     m_strName;
};
///����escape���������map
typedef map<string const, CwxHtmlTmplEscape*> CwxHtmlTmplEscapeMap;


CWINUX_END_NAMESPACE

#include "CwxPost.h"
#endif

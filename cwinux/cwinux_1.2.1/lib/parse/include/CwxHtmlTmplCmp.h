#ifndef __CWX_HTML_TMPL_CMP_H__
#define __CWX_HTML_TMPL_CMP_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxHtmlTmplCmp.h
@brief �����ı��滻ģ��ıȽϺ�������Ľӿڣ���ʵ��һЩ���õıȽϺ�������
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

CWINUX_BEGIN_NAMESPACE

class CwxHtmlTmpl;
class CwxHtmlTmplEnv;

/**
@class CwxHtmlTmplCmp
@brief �ı��滻ģ��ıȽϺ�������Ľӿ��࣬Ϊ���бȽϺ����Ļ��ࡣ<br>
       �˶�����뱣֤���̰߳�ȫ
*/
class CWX_API CwxHtmlTmplCmp
{
public:
    ///���캯��
    CwxHtmlTmplCmp(string const& strName):m_strName(strName)
    {

    }
    ///��������
    virtual ~CwxHtmlTmplCmp()
    {

    }
public:
    /**
    @brief �ȽϺ�����
    @param [in] szSrc ����Ƚϵĵ�һ��������Ҳ����ģ���﷨�ı�����ֵ, NULL��ʾ������
    @param [in] szDest ����Ƚϵĵڶ���������Ҳ����ģ���﷨�ıȽϳ�����NULL��ʾ������
    @param [in] args  ģ���﷨�����õ�args��NULL��ʾû������
    @param [in] pHtmlTmpl ��������������ģ�����
    @param [in] pHtmlTmplEnv ģ���γɵĻ�������
    @return true��szSrcС��szDest��false��szSrc��С��szDest
    */
    virtual bool compare(char const* szSrc,
        char const* szDest,
        char const* args,
        CwxHtmlTmpl const* pHtmlTmpl,
        CwxHtmlTmplEnv* pHtmlTmplEnv)=0;
public:
    ///��ȡ�ȽϺ����Ķ�����
    string const& getName() const
    {
        return m_strName;
    }
private:
    string     m_strName;
};

///����ģ��ȽϺ��������ģ��
typedef map<string const, CwxHtmlTmplCmp*, CwxCaseStringLess> CwxHtmlTmplCmpMap;

/**
@class CwxHtmlTmplCmpEqual
@brief ��ȱȽϣ�������char��int��length���͡�
*/
class CWX_API CwxHtmlTmplCmpEqual:public CwxHtmlTmplCmp
{
public:
    CwxHtmlTmplCmpEqual():CwxHtmlTmplCmp("=")
    {

    }
public:
    /**
    @brief ��Ⱥ�����
    @param [in] szSrc ����Ƚϵĵ�һ��������Ҳ����ģ���﷨�ı�����ֵ, NULL��ʾ������
    @param [in] szDest ����Ƚϵĵڶ���������Ҳ����ģ���﷨�ıȽϳ���, NULL��ʾ������
    @param [in] args  �Ƚϵ����ͣ��ֱ�Ϊchar,casechar, int, uint, length,ȱʡΪchar
    @param [in] pHtmlTmpl ��������������ģ�����
    @param [in] pHtmlTmplEnv ģ���γɵĻ�������
    @return true��szSrcС��szDest��false��szSrc��С��szDest
    */
    bool compare(char const* szSrc,
        char const* szDest,
        char const* args,
        CwxHtmlTmpl const* pHtmlTmpl,
        CwxHtmlTmplEnv* pHtmlTmplEnv);
};


/**
@class CwxHtmlTmplCmpLess
@brief С�ڱȽϣ�������char��int��length���͡�
*/
class CWX_API CwxHtmlTmplCmpLess:public CwxHtmlTmplCmp
{
public:
    CwxHtmlTmplCmpLess():CwxHtmlTmplCmp("<")
    {

    }
public:
    /**
    @brief С�ں�����
    @param [in] szSrc ����Ƚϵĵ�һ��������Ҳ����ģ���﷨�ı�����ֵ, NULL��ʾ������
    @param [in] szDest ����Ƚϵĵڶ���������Ҳ����ģ���﷨�ıȽϳ���, NULL��ʾ������
    @param [in] args  �Ƚϵ����ͣ��ֱ�Ϊchar,casechar, int, uint, length,ȱʡΪchar
    @param [in] pHtmlTmpl ��������������ģ�����
    @param [in] pHtmlTmplEnv ģ���γɵĻ�������
    @return true��szSrcС��szDest��false��szSrc��С��szDest
    */
    bool compare(char const* szSrc,
        char const* szDest,
        char const* args,
        CwxHtmlTmpl const* pHtmlTmpl,
        CwxHtmlTmplEnv* pHtmlTmplEnv);
};


/**
@class CwxHtmlTmplCmpMore
@brief ���ڱȽϣ�������char��int��length���͡�
*/
class CWX_API CwxHtmlTmplCmpMore:public CwxHtmlTmplCmp
{
public:
    CwxHtmlTmplCmpMore():CwxHtmlTmplCmp(">")
    {

    }
public:
    /**
    @brief С�ں�����
    @param [in] szSrc ����Ƚϵĵ�һ��������Ҳ����ģ���﷨�ı�����ֵ, NULL��ʾ������
    @param [in] szDest ����Ƚϵĵڶ���������Ҳ����ģ���﷨�ıȽϳ���, NULL��ʾ������
    @param [in] args  �Ƚϵ����ͣ��ֱ�Ϊchar,casechar, int, uint, length,ȱʡΪchar
    @param [in] pHtmlTmpl ��������������ģ�����
    @param [in] pHtmlTmplEnv ģ���γɵĻ�������
    @return true��szSrcС��szDest��false��szSrc��С��szDest
    */
    bool compare(char const* szSrc,
        char const* szDest,
        char const* args,
        CwxHtmlTmpl const* pHtmlTmpl,
        CwxHtmlTmplEnv* pHtmlTmplEnv);
};

/**
@class CwxHtmlTmplCmpPrefix
@brief �����Ǳ���ǰ׺��У�顣
*/
class CWX_API CwxHtmlTmplCmpPrefix:public CwxHtmlTmplCmp
{
public:
    CwxHtmlTmplCmpPrefix():CwxHtmlTmplCmp("prefix")
    {

    }
public:
    /**
    @brief �����Ǳ���ǰ׺��У�顣
    @param [in] szSrc ����Ƚϵĵ�һ��������Ҳ����ģ���﷨�ı�����ֵ, NULL��ʾ������
    @param [in] szDest ����Ƚϵĵڶ���������Ҳ����ģ���﷨�ıȽϳ���, NULL��ʾ������
    @param [in] args  case����Сд�����У�����Ϊ��Сд����
    @param [in] pHtmlTmpl ��������������ģ�����
    @param [in] pHtmlTmplEnv ģ���γɵĻ�������
    @return true��szDest��szSrc��ǰ׺��false��szDest����szSrc��ǰ׺
    */
    bool compare(char const* szSrc,
        char const* szDest,
        char const* args,
        CwxHtmlTmpl const* pHtmlTmpl,
        CwxHtmlTmplEnv* pHtmlTmplEnv);
};


/**
@class CwxHtmlTmplCmpRPrefix
@brief �����ǳ���ǰ׺��У�顣
*/
class CWX_API CwxHtmlTmplCmpRPrefix:public CwxHtmlTmplCmp
{
public:
    CwxHtmlTmplCmpRPrefix():CwxHtmlTmplCmp("r-prefix")
    {

    }
public:
    /**
    @brief �����ǳ���ǰ׺��У�顣
    @param [in] szSrc ����Ƚϵĵ�һ��������Ҳ����ģ���﷨�ı�����ֵ, NULL��ʾ������
    @param [in] szDest ����Ƚϵĵڶ���������Ҳ����ģ���﷨�ıȽϳ���, NULL��ʾ������
    @param [in] args  case����Сд�����У�����Ϊ��Сд����
    @param [in] pHtmlTmpl ��������������ģ�����
    @param [in] pHtmlTmplEnv ģ���γɵĻ�������
    @return true��szSrc��szDest��ǰ׺��false��szSrc����szDest��ǰ׺
    */
    bool compare(char const* szSrc,
        char const* szDest,
        char const* args,
        CwxHtmlTmpl const* pHtmlTmpl,
        CwxHtmlTmplEnv* pHtmlTmplEnv);
};

/**
@class CwxHtmlTmplCmpSuffix
@brief �����Ǳ�����׺��У�顣
*/
class CWX_API CwxHtmlTmplCmpSuffix:public CwxHtmlTmplCmp
{
public:
    CwxHtmlTmplCmpSuffix():CwxHtmlTmplCmp("suffix")
    {

    }
public:
    /**
    @brief �����Ǳ�����׺��У�顣
    @param [in] szSrc ����Ƚϵĵ�һ��������Ҳ����ģ���﷨�ı�����ֵ, NULL��ʾ������
    @param [in] szDest ����Ƚϵĵڶ���������Ҳ����ģ���﷨�ıȽϳ���, NULL��ʾ������
    @param [in] args  case����Сд�����У�����Ϊ��Сд����
    @param [in] pHtmlTmpl ��������������ģ�����
    @param [in] pHtmlTmplEnv ģ���γɵĻ�������
    @return true��szDest��szSrc�ĺ�׺��false��szDest����szSrc�ĺ�׺
    */
    bool compare(char const* szSrc,
        char const* szDest,
        char const* args,
        CwxHtmlTmpl const* pHtmlTmpl,
        CwxHtmlTmplEnv* pHtmlTmplEnv);
};

/**
@class CwxHtmlTmplCmpRSuffix
@brief �����ǳ����ĺ�׺��У�顣
*/
class CWX_API CwxHtmlTmplCmpRSuffix:public CwxHtmlTmplCmp
{
public:
    CwxHtmlTmplCmpRSuffix():CwxHtmlTmplCmp("suffix")
    {

    }
public:
    /**
    @brief �����ǳ����ĺ�׺��У�顣
    @param [in] szSrc ����Ƚϵĵ�һ��������Ҳ����ģ���﷨�ı�����ֵ, NULL��ʾ������
    @param [in] szDest ����Ƚϵĵڶ���������Ҳ����ģ���﷨�ıȽϳ���, NULL��ʾ������
    @param [in] args  case����Сд�����У�����Ϊ��Сд����
    @param [in] pHtmlTmpl ��������������ģ�����
    @param [in] pHtmlTmplEnv ģ���γɵĻ�������
    @return true��szSrc��szDest�ĺ�׺��false��szSrc����szDest�ĺ�׺
    */
    bool compare(char const* szSrc,
        char const* szDest,
        char const* args,
        CwxHtmlTmpl const* pHtmlTmpl,
        CwxHtmlTmplEnv* pHtmlTmplEnv);
};

/**
@class CwxHtmlTmplCmpIn
@brief ��������������У�顣
*/
class CWX_API CwxHtmlTmplCmpIn:public CwxHtmlTmplCmp
{
public:
    CwxHtmlTmplCmpIn():CwxHtmlTmplCmp("suffix")
    {

    }
public:
    /**
    @brief ��������������У�顣
    @param [in] szSrc ����Ƚϵĵ�һ��������Ҳ����ģ���﷨�ı�����ֵ, NULL��ʾ������
    @param [in] szDest ����Ƚϵĵڶ���������Ҳ����ģ���﷨�ıȽϳ���, NULL��ʾ������
    @param [in] args  case����Сд�����У�����Ϊ��Сд����
    @param [in] pHtmlTmpl ��������������ģ�����
    @param [in] pHtmlTmplEnv ģ���γɵĻ�������
    @return true��szSrc�а���szDest��false��szSrc�в�����szDest
    */
    bool compare(char const* szSrc,
        char const* szDest,
        char const* args,
        CwxHtmlTmpl const* pHtmlTmpl,
        CwxHtmlTmplEnv* pHtmlTmplEnv);
};

/**
@class CwxHtmlTmplCmpRIn
@brief ��������������У�顣
*/
class CWX_API CwxHtmlTmplCmpRIn:public CwxHtmlTmplCmp
{
public:
    CwxHtmlTmplCmpRIn():CwxHtmlTmplCmp("suffix")
    {

    }
public:
    /**
    @brief ��������������У�顣
    @param [in] szSrc ����Ƚϵĵ�һ��������Ҳ����ģ���﷨�ı�����ֵ, NULL��ʾ������
    @param [in] szDest ����Ƚϵĵڶ���������Ҳ����ģ���﷨�ıȽϳ���, NULL��ʾ������
    @param [in] args  case����Сд�����У�����Ϊ��Сд����
    @param [in] pHtmlTmpl ��������������ģ�����
    @param [in] pHtmlTmplEnv ģ���γɵĻ�������
    @return true��szDest�а���szSrc��false��szDest�в�����szSrc
    */
    bool compare(char const* szSrc,
        char const* szDest,
        char const* args,
        CwxHtmlTmpl const* pHtmlTmpl,
        CwxHtmlTmplEnv* pHtmlTmplEnv);
};

CWINUX_END_NAMESPACE

#include "CwxPost.h"
#endif

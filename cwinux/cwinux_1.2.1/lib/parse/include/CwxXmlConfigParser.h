#ifndef __CWX_XML_CONFIG_PARSER_H__
#define __CWX_XML_CONFIG_PARSER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxXmlConfigParser.h
@brief ������CwxXmlConfigParser�࣬��XML��BUF������CwxXmlTreeNode��֯�Ľڵ�����
@author cwinux@gmail.com
@version 0.1
@date 2009-10-10
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxStl.h"
#include "CwxGlobalMacro.h"
#include "CwxCommon.h"
#include "CwxGbkUnicodeMap.h"
#include "CwxCharPool.h"
#include "CwxXmlTreeNode.h"
#include "CwxParseMacro.h"
#include <expat.h>


CWINUX_BEGIN_NAMESPACE

/**
@class CwxXmlConfigParser
@brief ��XML��BUF������CwxXmlTreeNode��֯�Ľڵ���������֧��expatĬ��֧�ֵ��ַ�������֧��GBK��gb2312�ַ���
*/
class CWX_API CwxXmlConfigParser
{
public:
    /**
    @brief ���캯����
    @param [in] uiAvgTokenLen XML�е����ݽڵ��ƽ������
    @param [in] uiAvgXmlSize Ҫ������XML��ƽ����С
    */
    CwxXmlConfigParser(CWX_UINT32 uiAvgTokenLen=1024, CWX_UINT32 uiAvgXmlSize=4096);
    ///��������
    ~CwxXmlConfigParser();
public:
    /**
    @brief ��szXml�����XML�ı���������CwxXmlTreeNode�Ľڵ�����
    @param [in] szXml XML
    @return true�������ɹ���false������ʧ��
    */
    bool parse(char const* szXml);
    /**
    @brief ��ȡһ��XML�ڵ�����ԡ�
    @param [in] szPath XML�Ľڵ㣬����key:key1:key2�ĸ�ʽ�������ڵ��ԡ�:���ָ�
    @param [in] szAttr �ڵ��������
    @return NULL�������ڣ�����Ϊ�ڵ����Ե���ֵ
    */
    char const* getElementAttr(char const* szPath, char const* szAttr) const;
    /**
    @brief ��ȡһ��XML�ڵ���������ԡ�
    @param [in] szPath XML�Ľڵ㣬����key:key1:key2�ĸ�ʽ�������ڵ��ԡ�:���ָ�
    @param [in] attrs �ڵ��������������pair��firstΪ��������secondΪ���Ե�ֵ
    @return false���ڵ㲻���ڣ����򷵻ؽڵ�������б�
    */
    bool getElementAttrs(char const* szPath, list<pair<char*, char*> >& attrs) const;
    /**
    @brief ��ȡ[\<aa\>xxxx\</aa\>]����ʽ�Ľڵ������xxxx��
    @param [in] szPath XML�Ľڵ㣬����key:key1:key2�ĸ�ʽ�������ڵ��ԡ�:���ָ�
    @param [in] strData �ڵ������
    @return false���ڵ㲻���ڻ���\<aa\>xxxx\</aa\>�ĸ�ʽ���ڵ���ڶ���Ϊ�˸�ʽ
    */
    bool getElementData(char const* szPath, string& strData) const;
    /**
    @brief ��ȡ�ڵ��Tree Node��
    @param [in] szPath XML�Ľڵ㣬����key:key1:key2�ĸ�ʽ�������ڵ��ԡ�:���ָ�
    @return NULL���ڵ㲻���ڣ�·���Ľڵ�
    */
    CwxXmlTreeNode const* getElementNode(char const* szPath) const;
    ///��ȡ�ڵ�ĸ�
    CwxXmlTreeNode const * getRoot() const
    {
        return m_root; 
    }
    ///�ж�xml�ı����Ƿ�ΪGBK
    bool isGbk() const 
    {
        return m_bGbk;
    }
private:
    /**
    @brief ֪ͨ����һ��XML�����ݽڵ㡣
    @param [in] name XML�ڵ������
    @param [in] atts XML�ڵ�����ԣ�atts[2n]Ϊ���Ե����֣�atts[2n+1]Ϊ���Ե�ֵ����atts[2n]ΪNULL����ʾ���Խ���
    @return void
    */
    void startElement(const XML_Char *name, const XML_Char **atts);
    /**
    @brief ֪ͨ�뿪һ��XML�����ݽڵ㡣
    @param [in] name XML�ڵ������
    @return void
    */
    void endElement(const XML_Char *name);
    /**
    @brief ֪ͨһ���ڵ��ڵ����ݡ�
    @param [in] s ���ݵ����ݣ������ΪUTF8�ı���
    @param [in] len ���ݵ����ݵĳ��ȡ�
    @return void
    */
    void characterData(const XML_Char *s, int len);
    /**
    @brief ���ַ���ΪGBK��gb2312����expat��UTF-8�����ΪGBK��gb2312�ı����ʽ��
    @param [in] value expat�����UTF-8���ַ���
    @param [in] uiValueLen value�ĳ���
    @return ����GBK��gb2312������ַ���
    */
    char const* charsetValue(XML_Char const* value, CWX_UINT32 uiValueLen);
private:
    ///ע�����е�expat���¼�������
    void regDefHandlers(void);
    ///����һ��XML�ڵ���¼�������
    static XMLCALL void elementStartHandler(void *userData,
        const XML_Char *name, const XML_Char **atts);
    ///�뿪һ��XML�ڵ���¼�������
    static XMLCALL void elementEndHandler(void *userData,
        const XML_Char *name);
    ///�ڵ��ڲ����ݵĽ��ܺ���
    static XMLCALL void characterDataHandler(void *userData,
        const XML_Char *s, int len);
    ///GBK��gb2312���ַ���ת��API
    static XMLCALL int convert(void* data, char const* s);
    ///GBK��gb2312�ַ�����ת�����¼�����
    static XMLCALL int encodingHandler(void* userData, XML_Char const* name, XML_Encoding* info);
private:
    XML_Parser  m_expatParser;///<expat������
    CwxCharPool m_memPool;///<�ַ��ڴ��
    CwxXmlTreeNode* m_root;///<���ڵ�
    CwxXmlTreeNode* m_pCur;///<���������еĵ�ǰ�ڵ�
    bool      m_bGbk;///<�Ƿ�ΪGBK����
    XML_Char*  m_szGbkBuf;///<GBK����ת������ʱBUF
    CWX_UINT32 m_uiGbkBufLen;///<m_szGbkBuf�Ŀռ��С
};

CWINUX_END_NAMESPACE

#include "CwxPost.h"

#endif


#ifndef __CWX_XML_FILE_CONFIG_PARSER_H__
#define __CWX_XML_FILE_CONFIG_PARSER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxXmlFileConfigParser.h
@brief ������CwxXmlFileConfigParser�࣬��XML���ļ�������CwxXmlTreeNode��֯�Ľڵ�����
@author cwinux@gmail.com
@version 0.1
@date 2009-10-10
@warning
@bug
*/

#include "CwxPre.h"
#include "CwxStl.h"
#include "CwxCommon.h"
#include "CwxParseMacro.h"

#include "CwxXmlConfigParser.h"

CWINUX_BEGIN_NAMESPACE
/**
@class CwxXmlFileConfigParser
@brief ��XML���ļ�������CwxXmlTreeNode��֯�Ľڵ���������֧��expatĬ��֧�ֵ��ַ�������֧��GBK��gb2312�ַ���
*/
class  CWX_API CwxXmlFileConfigParser
{
public:
    /**
    @brief ���캯����
    @param [in] uiAvgTokenLen XML�е����ݽڵ��ƽ������
    @param [in] uiAvgXmlSize Ҫ������XML��ƽ����С
    */
    CwxXmlFileConfigParser(CWX_UINT32 uiAvgTokenLen=1024, CWX_UINT32 uiAvgXmlSize=4096);
    ///��������
    virtual ~CwxXmlFileConfigParser(void);
public:
    /**
    @brief ��szXml�����XML�ı���������CwxXmlTreeNode�Ľڵ�����
    @param [in] strFileName XML�ļ���
    @return true�������ɹ���false������ʧ��
    */
    bool parse(string const& strFileName);
    /**
    @brief ��ȡһ��XML�ڵ�����ԡ�
    @param [in] szPath XML�Ľڵ㣬����key:key1:key2�ĸ�ʽ�������ڵ��ԡ�:���ָ�
    @param [in] szAttr �ڵ��������
    @return NULL�������ڣ�����Ϊ�ڵ����Ե���ֵ
    */
    char const* getElementAttr(char const* szPath, char const* szAttr) const 
    {
        return m_parser.getElementAttr(szPath, szAttr);
    }
    /**
    @brief ��ȡһ��XML�ڵ���������ԡ�
    @param [in] szPath XML�Ľڵ㣬����key:key1:key2�ĸ�ʽ�������ڵ��ԡ�:���ָ�
    @param [in] attrs �ڵ��������������pair��firstΪ��������secondΪ���Ե�ֵ
    @return false���ڵ㲻���ڣ����򷵻ؽڵ�������б�
    */
    bool getElementAttrs(char const* szPath, list<pair<char*, char*> >& attrs) const
    {
        return m_parser.getElementAttrs(szPath, attrs);
    }
    /**
    @brief ��ȡ[\<aa\>xxxx\</aa\>]����ʽ�Ľڵ������xxxx��
    @param [in] szPath XML�Ľڵ㣬����key:key1:key2�ĸ�ʽ�������ڵ��ԡ�:���ָ�
    @param [in] strData �ڵ������
    @return false���ڵ㲻���ڻ���\<aa\>xxxx\</aa\>�ĸ�ʽ���ڵ���ڶ���Ϊ�˸�ʽ
    */
    bool getElementData(char const* szPath, string& strData) const 
    {
        return m_parser.getElementData(szPath, strData);
    }
    /**
    @brief ��ȡ�ڵ��Tree Node��
    @param [in] szPath XML�Ľڵ㣬����key:key1:key2�ĸ�ʽ�������ڵ��ԡ�:���ָ�
    @return NULL���ڵ㲻���ڣ�·���Ľڵ�
    */
    CwxXmlTreeNode const* getElementNode(char const* szPath) const 
    {
        return m_parser.getElementNode(szPath);
    }
    ///��ȡ�ڵ�ĸ�
    CwxXmlTreeNode const * getRoot() const
    { 
        return m_parser.getRoot(); 
    }
    ///�ж�xml�ı����Ƿ�ΪGBK
    bool isGbk() const
    { 
        return m_parser.isGbk();
    }
private:
    FILE *  m_fd;///<xml�ļ���FD
    string  m_strFileName;///<xml�ļ�������
    char*   m_szBuf;///<XML�ļ���ȡBUF
    CwxXmlConfigParser  m_parser;///<CwxXmlConfigParser�࣬���XML �ڴ�Ľ���

};
#include "CwxPost.h"

CWINUX_END_NAMESPACE;

#endif /* _EXPATMM_EXPATXMLFILEPARSER_H */


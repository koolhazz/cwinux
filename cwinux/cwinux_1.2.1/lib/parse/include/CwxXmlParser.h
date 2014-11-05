#ifndef __CWX_XML_PARSER_H__
#define __CWX_XML_PARSER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxXmlParser.h
@brief ������CwxXmlParser�࣬�������expatʵ��XML����������
@author cwinux@gmail.com
@version 0.1
@date 2009-10-10
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxStl.h"
#include "CwxCommon.h"
#include "CwxGbkUnicodeMap.h"
#include "CwxParseMacro.h"
#include <expat.h>

CWINUX_BEGIN_NAMESPACE
/**
@class CwxXmlParser
@brief ����expatʵ�ֵ�XML���������󡣳���֧��expatĬ��֧�ֵ��ַ�������֧��GBK��gb2312�ַ���
*/
class CWX_API CwxXmlParser
{
public:
    enum{
        DEF_TRUCK_BUF_SIZE = 16 * 1024, ///<ȱʡ�����ݿ�Ĵ�С
        PATH_BUF_ALIGN = 1024 ///���ݿ�ı߽�����С
    };
public:
    /**
    @brief ���캯����
    @param [in] uiBufSize ���ݿ�Ĵ�С
    */
    CwxXmlParser(CWX_UINT32 uiBufSize=DEF_TRUCK_BUF_SIZE);
    ///��������
    virtual ~CwxXmlParser(void);
public:
    ///����XMLʵ�壬�û����ԶԴ�API�������ء�
    virtual bool parse();
    ///expat��XML���������Ƿ��ʼ��
    bool isReady(void) const
    {
        return m_isReady;
    }
    ///��ȡXML�Ľ���������Ϣ
    XML_Error getLastError(void) const
    {
        return m_lastError;
    }
    ///��ȡXML������״̬����
    XML_Status getStatus(void) const
    {
        return m_status; 
    }
    ///��ȡXML���������ݿ�
    XML_Char *getBuf(void) const
    {
        return m_szXmlBuf; 
    }
    ///��ȡ���ݿ�Ĵ�С
    CWX_UINT32 getBufSize(void) const
    {
        return m_uiBufSize; 
    }
    ///��ȡ��ǰ��������XML·��
    XML_Char const* getXmlPath() const
    {
        return m_szXmlPath;
    }
    ///�ж�XML�Ƿ�ΪGBK�ı���
    bool isGbk() const
    {
        return m_bGbk;
    }
    /**
    @brief ���ַ���ΪGBK��gb2312����expat��UTF-8�����ΪGBK��gb2312�ı����ʽ��
    @param [in] value expat�����UTF-8���ַ���
    @param [in] uiValueLen value�ĳ���
    @return ����GBK��gb2312������ַ���
    */
    char const* charsetValue(XML_Char const* value, CWX_UINT32 uiValueLen);
protected:
    ///����expat�������ready״̬
    void setReady(bool isReady)
    {
        m_isReady = isReady;
    }
    ///����xml������״̬��
    void setStatus(XML_Status status)
    {
        m_status = status; 
    }
    ///����XML�����Ĵ�����Ϣ
    void setLastError(XML_Error lastError)
    {
        m_lastError = lastError;
    }
    ///׼��xml�����Ļ������̳���������ش�API
    virtual bool prepare();
    ///��ȡXML��������һ�����ݿ飬��������Ҫ���ش�API��Ϊexpat�����ṩ������
    virtual ssize_t readBlock(void);
    /**
    @brief ֪ͨ����һ��XML�����ݽڵ㡣
    @param [in] name XML�ڵ������
    @param [in] atts XML�ڵ�����ԣ�atts[2n]Ϊ���Ե����֣�atts[2n+1]Ϊ���Ե�ֵ����atts[2n]ΪNULL����ʾ���Խ���
    @return void
    */
    virtual void startElement(const XML_Char *name, const XML_Char **atts);
    /**
    @brief ֪ͨ�뿪һ��XML�����ݽڵ㡣
    @param [in] name XML�ڵ������
    @return void
    */
    virtual void endElement(const XML_Char *name);
    /**
    @brief ֪ͨһ���ڵ��ڵ����ݡ�
    @param [in] s ���ݵ����ݣ������ΪUTF8�ı���
    @param [in] len ���ݵ����ݵĳ��ȡ�
    @return void
    */
    virtual void characterData(const XML_Char *s, int len);
    /**
    @brief ֪ͨXML��instructions.
    @param [in] target instruction�ĵ�һ��word.
    @param [in] data ��һ��word��ȥ�����пո���ַ�����
    @return void
    */
    virtual void processingInstruction(const XML_Char *target, const XML_Char *data);
    ///xml�е�ע��
    virtual void commentData(const XML_Char *data);
    ///xml��ȱʡ���ݴ�����
    virtual void defaultHandler(const XML_Char *s, int len);
    ///֪ͨ����XML��CDATA�﷨
    virtual void startCData(void);
    ///֪ͨ�뿪XML��CDATA�﷨
    virtual void endCData(void);

private:
    ///ע�����е�expat���¼�������
    void regDefHandlers();
    ///����һ��XML�ڵ���¼�������
    static XMLCALL void elementStartHandler(void *userData,
        const XML_Char *name, const XML_Char **atts);
    ///�뿪һ��XML�ڵ���¼�������
    static XMLCALL void elementEndHandler(void *userData,
        const XML_Char *name);
    ///�ڵ��ڲ����ݵĽ��ܺ���
    static XMLCALL void characterDataHandler(void *userData,
        const XML_Char *s, int len);
    ///XML instruction�Ľ��ܺ���
    static XMLCALL void processingInstrHandler(void *userData,
        const XML_Char *target, const XML_Char *data);
    ///ע�͵Ľ��ܺ���
    static XMLCALL void commentHandler(void *userData,
        const XML_Char *data);
    ///ȱʡ�¼��Ĵ�����
    static XMLCALL void defaultHandler(void *userData,
        const XML_Char *s, int len);
    ///����CDATA���¼�����
    static XMLCALL void startCDatahandler(void *userData);
    ///�뿪CDATA���¼�����
    static XMLCALL void endCDatahandler(void *userData);
    ///GBK��gb2312���ַ���ת��API
    static XMLCALL int convert(void* data, char const* s);
    ///GBK��gb2312�ַ�����ת�����¼�����
    static XMLCALL int encodingHandler(void* userData, XML_Char const* name, XML_Encoding* info);
private:
    XML_Parser  m_expatParser;///<expat������
    XML_Char *  m_szXmlBuf; ///<�ڲ���ʱBUF
    CWX_UINT32  m_uiBufSize;///<��ʱBUF�Ĵ�С
    bool    m_isReady;///<�����ʼ��״̬���
    XML_Status m_status;///<XML������״̬��
    XML_Error m_lastError;///<XML�����Ĵ�����Ϣ
    XML_Char*  m_szXmlPath;///<��ǰXML�ڵ��ȫ·��
    CWX_UINT32 m_uiPathBufLen;///<XML�ڵ�ȫ·����BUF�ĳ���
    CWX_UINT32 m_uiPathLen;///<m_szXmlPath�еĽڵ�·������
    bool      m_bGbk;///<�Ƿ������ı���
    XML_Char*  m_szGbkBuf;///<����GBK����ת�����ڴ�
    CWX_UINT32 m_uiGbkBufLen;///<m_szGbkBuf���ڴ泤��
};

CWINUX_END_NAMESPACE

#include "CwxPost.h"

#endif


#ifndef __CWX_HTML_TMPL_H__
#define __CWX_HTML_TMPL_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxHtmlTmpl.h
@brief �����ı�ģ���滻�ࡣ
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
#include "CwxReplMachine.h"
#include "CwxCharset.h"
#include "CwxMemLineReader.h"
#include "CwxTypePool.h"
#include "CwxCharPool.h"
#include "CwxXmlConfigParser.h"
#include "CwxHtmlTmplCmp.h"
#include "CwxHtmlTmplEscape.h"
#include "CwxHtmlTmplLoop.h"

CWINUX_BEGIN_NAMESPACE
/**
@class CwxHtmlTmplTagKind
@brief �ı�ģ���TAG���Ͷ��塣
*/
class CWX_API CwxHtmlTmplTagKind
{
public:
    enum{
        TAG_TEXT = 1,///<�ı�TAG
        TAG_VAL = 2,///<����TAG
        TAG_LOOP = 3,///<ѭ��TAG
        TAG_IF = 4,///<IF TAG
        TAG_ELIF = 5,///<ELIF TAG
        TAG_ELSE = 6,///<ELSE TAG
        TAG_JOIN = 7 ///<�﷨����TAG
    };
};

/**
@class CwxHtmlTmplValSysAttr
@brief �ı�ģ����������Զ��塣
*/
class CWX_API CwxHtmlTmplValSysAttr
{
public:
    enum{
        ATTR_REPLACE = 0X01,///<������������Ҫִ���ַ��滻
        ATTR_CHARSET_CONVERT = 0X02,///<������������Ҫ�����ַ����任
        ATTR_EXPLICT = 0X04///<�����������
    };
};

/**
@class CwxHtmlTmplTagNode
@brief �ı�ģ��TAG��ITEM���塣
*/
struct CwxHtmlTmplTagNode
{
    CWX_UINT8  m_kind;///<tag ����
    CwxHtmlTmplTagNode* m_next; ///<��һ��TAG
    union
    {
        struct 
        {
            char const * m_szText; ///<�ı�������
            int          m_iTextLen;///<�ı��ĳ���
        }m_text;///<�ı�TAG�ڵ�

        struct
        {
            char const * m_szName;///<����������
            char const * m_szObjName;///<�����Ķ�����
            CWX_UINT8    m_ucSysAttr;///<����������
            char const * m_szUserAttr;///<�������û�����
            int          m_iDataLen;///<�������ݳ������ƣ�<0���ַ����ܳ��������ֵ��0��û���ƣ�>0���ֽڲ��ܳ�����ֵ
            char const * m_szDefault;///<������ȱʡֵ
            char const * m_szEscape;///<�����ı任�������������
            char const * m_szArgument;///<�����ı任�����Ĳ���
            CwxHtmlTmplEscape* m_pEscapeObj;///<�����任��������
        }m_var;///<����TAG�ڵ�

        struct
        {
            char const * m_szName;///<IF�еı�����
            char const * m_szObjName;///<IF�еı����Ķ�����
            char const * m_szCompair;///<IF�бȽϺ������������
            char const * m_szData;///<�Ƚ��еĳ���
            char const * m_szArgument;///<�ȽϺ�������Ĳ���
            bool        m_bReverse; ///<ȡ��
            CwxHtmlTmplTagNode * m_pMain;///<IF�Ƚ�ΪTRUEʱ�ķ�֧
            CwxHtmlTmplTagNode * m_pBranch;///<IF�Ƚ�ΪFALSEʱ�ķ�֧
            CwxHtmlTmplCmp  * m_pCompareObj;///<�ȽϺ�������
        }m_if;///<IF TAG�ڵ�

        struct
        {
            char const * m_szName;///<elif�еı�����
            char const * m_szObjName;///<�����Ķ�����
            char const * m_szCompair;///<�ȽϺ������������
            char const * m_szData;///<�Ƚ��еĳ�������
            char const * m_szArgument;///<�ȽϺ�������Ĳ���
            bool        m_bReverse; ///<ȡ��
            CwxHtmlTmplTagNode * m_pMain;///<�ȽϽ��Ϊtrueʱ�ķ�֧
            CwxHtmlTmplTagNode * m_pBranch;///<�ȽϽ��Ϊfalseʱ�ķ�֧
            CwxHtmlTmplCmp * m_pCompareObj;///<�ȽϺ�������
        }m_elif;///<elif TAG�ڵ�

        struct
        {
            CwxHtmlTmplTagNode * m_pBody; ///<else�ķ�֧
        }m_else;///<else TAG�ڵ�


        struct 
        {
            char const *         m_szLoopName;///<loop�����֣�Ҳ�Ƕ��������
            list<pair<char*, char *> >* m_attrs;///<loop�����õĶ��������
            CwxHtmlTmplTagNode * m_pBody;///<loop������
        }m_loop;///<LOOP TAG�ڵ�
    }m_tag;
};

class CwxHtmlTmpl;

/**
@class CwxHtmlTmplEnv
@brief ģ���滻��������������ڱ����м���Ϣ��ʵ��CwxHtmlTmpl�Ķ��̰߳�ȫ��
*/
class CWX_API CwxHtmlTmplEnv
{
public:
    ///���캯��
    CwxHtmlTmplEnv():m_uiErrBufLen(1023)
    {
        m_uiOutTextPos = 0;
        m_uiOutTextLen = 0;
        m_szOutText = NULL;
        memset(m_szErr1K, 0x00, m_uiErrBufLen + 1);
    }
public:
    /**
    @brief ��ʼ��ģ�����������
    @param [in] root ��ģ�����
    @param [out] szOutText ģ�������BUFFER
    @param [in] uiOutTextBufLen Buffer�Ĵ�С
    @return void
    */
    void init(CwxHtmlTmplLoop* root, char* szOutText, CWX_UINT32 uiOutTextBufLen)
    {
        m_loopStackList.clear();
        m_loopStackList.push_front(pair<string,CwxHtmlTmplLoop*>("", root));
        m_loopMap.clear();
        m_szOutText = szOutText;
        m_uiOutTextLen = uiOutTextBufLen;
        m_uiOutTextPos = 0;
        memset(m_szErr1K, 0x00, 1024);
    }
    ///��ȡģ������滻�����еĴ�����Ϣ
    char const* getErrMsg() const
    {
        return m_szErr1K;
    }
    ///��ȡ�γɵ��ı��Ĵ�С
    CWX_UINT32 getBufLen()
    {
        return m_uiOutTextPos;
    }
public:
    friend  class CwxHtmlTmpl;
private:
    ///��ȡģ��bufʣ��Ŀռ䣬��ģ������滻�Ĺ�����ʹ��
    CWX_UINT32 getBufLeft()
    {
        return m_uiOutTextLen>=m_uiOutTextPos?m_uiOutTextLen -m_uiOutTextPos - 1:0;
    }
private:
    list<pair<string, CwxHtmlTmplLoop*> >    m_loopStackList;///<ģ������滻�����е�LOOP����Ƕ���б�
    map<string, CwxHtmlTmplLoop*> m_loopMap;///<ģ��LOOP����������ʵ����MAP
    char*                    m_szOutText;///<ģ�������BUF
    CWX_UINT32               m_uiOutTextPos;///<ģ�����BUF������ַ��ĵ�ǰλ��
    CWX_UINT32               m_uiOutTextLen;///<ģ�����BUF�Ĵ�С
    CWX_UINT32 const         m_uiErrBufLen;///<������ϢBUF�Ĵ�С
    char	                 m_szErr1K[1024];///<������ϢBUF
};

///ģ����������MAP��ӳ����������䶨�������ʽ��Ϣ
typedef map<char const*, CwxHtmlTmplTagNode*, CwxCharLess> CwxHtmlValMap;
///ģ�峣�������������ݵ�ӳ��MAP
typedef map<string, string> CwxHtmlConstMap;

/**
@class CwxHtmlTmpl
@brief ģ���滻�࣬ʵ�ֶ��̰߳�ȫ���ı�ģ��ı����滻��
*/
class CWX_API CwxHtmlTmpl
{
public:
    ///���캯��
    CwxHtmlTmpl()
    {
        m_repl = NULL;
        memset(&m_root, 0x00, sizeof(m_root));
        m_bCaseInsensitive = false;
        m_szTmpBuf = NULL;
    }
    ///��������
    ~CwxHtmlTmpl()
    {
        clear();
    }
public:
    ///��ʼ��ȫ�ֵ�ģ��ȽϺ���������ESCAPE�������󣬷Ƕ��̰߳�ȫ
    static void init();
    ///�ͷ�ȫ�ֵ�ģ��ȽϺ���������ESCAPE�������󣬷Ƕ��̰߳�ȫ
    static void destroy();
    /**
    @brief ���ȫ�ֵıȽϺ������󣬷Ƕ��̰߳�ȫ��
    @param [in] pCmpObj ��ӵıȽϺ�������
    @return false����ͬ���ֵĶ����Ѿ����ڣ�true����ӳɹ�
    */
    static bool addCmp(CwxHtmlTmplCmp* pCmpObj);
    /**
    @brief ��ȡȫ�ֵıȽϺ������󣬷Ƕ��̰߳�ȫ��
    @param [in] strName �ȽϺ������������
    @return NULL��ָ�����ֵĶ��󲻴��ڣ����򣬷��ؾ��д����ֵıȽϺ�������
    */
    static CwxHtmlTmplCmp* getCmp(string const& strName);
    /**
    @brief ɾ��ȫ�ֵıȽϺ������󣬷Ƕ��̰߳�ȫ��
    @param [in] strName Ҫɾ���ıȽϺ������������
    @return NULL��ָ�����ֵĶ��󲻴��ڣ����򣬷��ؾ��д����ֵıȽϺ�������
    */
    static CwxHtmlTmplCmp* eraseCmp(string const& strName);
    /**
    @brief �������ע��ıȽϺ�������
    @return void
    */
    static void clearCmp();
    /**
    @brief ���ȫ�ֵ�ESCACPE�������󣬷Ƕ��̰߳�ȫ��
    @param [in] pEscapeObj ��ӵ�ESCAPE��������
    @return false����ͬ���ֵĶ����Ѿ����ڣ�true����ӳɹ�
    */
    static bool addEscape(CwxHtmlTmplEscape* pEscapeObj);
    /**
    @brief ��ȡȫ�ֵ�ESCACPE�������󣬷Ƕ��̰߳�ȫ��
    @param [in] strName ESCAPE�������������
    @return NULL�����󲻴��ڣ����򣬷��ؾ��д����ֵ�ESCAPE��������
    */
    static CwxHtmlTmplEscape* getEscape(string const& strName);
    /**
    @brief ɾ��ȫ�ֵ�ESCACPE�������󣬷Ƕ��̰߳�ȫ��
    @param [in] strName Ҫɾ����ESCAPE�������������
    @return NULL�����󲻴��ڣ�����ɾ�����д����ֵ�ESCAPE�������󲢷���
    */
    static CwxHtmlTmplEscape* eraseEscape(string const& strName);
    ///�������ע���escape��������
    static void clearEscape();
public:
    /**
    @brief ���������滻�ı�ģ�塣
    @param [in] szTemplate �����滻�ı�ģ��Ķ���
    @param [in] uiTemplateLen �ı�ģ��Ķ���ĳ���
    @return false������ʧ�ܣ�ͨ��getErr()��ȡʧ�ܵ�ԭ��true�������ɹ�
    */
    bool parse(char const* szTemplate, CWX_UINT32 uiTemplateLen);
    /**
    @brief ִ��ģ��ı����滻��
    @param [in] env ģ������滻�Ļ���
    @return false��ִ��ʧ�ܣ�ͨ��CwxHtmlTmplEnv��getErrMsg()��ȡʧ�ܵ�ԭ��true���滻�ɹ�
    */
    bool output(CwxHtmlTmplEnv& env) const;
public:
    ///��ȡģ�������
    string const& getTemplateName() const
    {
        return m_strTmplName;
    }
    ///����ģ�������
    void setTemplateName(string const& strName)
    {
        m_strTmplName = strName;
    }
    ///��ȡģ����ļ�����
    string const& getTemplateFile() const
    {
        return m_strTmplFile;
    }
    ///����ģ����ļ�����
    void setTemplateFile(string const& strFile)
    {
        m_strTmplFile = strFile;
    }
    ///��ȡģ�����������
    string const& getTemplateAttr(string const& name)
    {
        static string strEmptyAttr;
        map<string, string>::iterator iter = m_attrTmplMap.find(name);
        return iter==m_attrTmplMap.end()?strEmptyAttr:iter->second;
    }
    ///����ģ�����������
    void setTemplateAttr(string const& name, string const& attr)
    {
        m_attrTmplMap[name] = attr; 
    }
    ///��ȡģ����ַ���
    string const& getCharset() const
    {
        return m_strCharset;
    }
    ///��ȡ�Ƿ�ģ��ı����ַ��滻��Ҫ��Сд������
    bool isCaseInsensitive() const
    {
        return m_bCaseInsensitive;
    }
    ///��ȡģ��ı����ַ��滻����
    CwxReplBase* getRepl()
    {
        return  m_repl;
    }
    ///��ȡģ����������еĴ���
    string const& getErr() const
    {
        return m_strErr;
    }
private:
    /**
    @brief �ڲ�ִ��ģ��ı����滻��
    @param [in] pNode ģ������滻�Ŀ�ʼλ��
    @param [in] env ģ������滻�Ļ���
    @return false��ִ��ʧ�ܣ�ͨ��CwxHtmlTmplEnv��getErrMsg()��ȡʧ�ܵ�ԭ��true���滻�ɹ�
    */
    bool output(CwxHtmlTmplTagNode* pNode, CwxHtmlTmplEnv& env) const;
    /**
    @brief ִ��ģ���һ���������滻��
    @param [in] pNode �����Ľڵ�
    @param [in] env ģ������滻�Ļ���
    @return false��ִ��ʧ�ܣ�ͨ��CwxHtmlTmplEnv��getErrMsg()��ȡʧ�ܵ�ԭ��true���滻�ɹ�
    */
    bool outputVal(CwxHtmlTmplTagNode* pNode, CwxHtmlTmplEnv& env) const;
    /**
    @brief ִ��ģ���һ��IF�ڵ���滻��
    @param [in] pNode IF�Ľڵ�
    @param [in] env ģ������滻�Ļ���
    @return false��ִ��ʧ�ܣ�ͨ��CwxHtmlTmplEnv��getErrMsg()��ȡʧ�ܵ�ԭ��true���滻�ɹ�
    */
    bool outputIf(CwxHtmlTmplTagNode* pNode, CwxHtmlTmplEnv& env) const;
    /**
    @brief ִ��ģ���һ��LOOP�ڵ���滻��
    @param [in] pNode LOOP�Ľڵ�
    @param [in] env ģ������滻�Ļ���
    @return false��ִ��ʧ�ܣ�ͨ��CwxHtmlTmplEnv��getErrMsg()��ȡʧ�ܵ�ԭ��true���滻�ɹ�
    */
    bool outputLoop(CwxHtmlTmplTagNode* pNode, CwxHtmlTmplEnv& env) const;
    /**
    @brief ��ȡһ���������ݡ�
    @param [in] pNode �����ڵ�
    @param [in] env ģ������滻�Ļ���
    @param [in] bVal �Ƿ�Ϊ����ȡֵ
    @return NULL�����������ڣ����򣺱�����ֵ
    */
    char const* getValValue(CwxHtmlTmplTagNode* pNode, CwxHtmlTmplEnv& env, bool bVal) const;
    /**
    @brief ���ݱ������壬��ʼ��һ�������ڵ㡣
    @param [out] node �����ڵ�
    @param [in] name ����������
    @param [in] szObjectName ���������Ķ�����
    @param [in] ucSysAttr ������ϵͳ����
    @return void
    */
    void initValNode(CwxHtmlTmplTagNode& node, char const* szName, char const* szObjectName, CWX_UINT8 ucSysAttr) const;
    ///���ģ�����
    void clear();
    ///����REPLACE���﷨��false��ʧ�ܣ�true���ɹ�
    bool parseReplace();
    ///����CONST���﷨��false��ʧ�ܣ�true���ɹ�
    bool parseConst();
    ///��������������﷨��false��ʧ�ܣ�true���ɹ�
    bool parseValFormat();
    /**
    @brief ����LOOP�﷨��
    @param [in] pPrev LOOP��ǰһ���ڵ�
    @return LOOP�ڵ㣬NULL��ʾʧ��
    */
    CwxHtmlTmplTagNode* parseLoopBegin(CwxHtmlTmplTagNode* pPrev);
    /**
    @brief ����IF�﷨��
    @param [in] pPrev IF��ǰһ���ڵ�
    @return IF�ڵ㣬NULL��ʾʧ��
    */
    CwxHtmlTmplTagNode* parseIfBegin(CwxHtmlTmplTagNode* pPrev);
    /**
    @brief ����ELIF�﷨��
    @param [in] pPrev ELIF��ǰһ���ڵ�
    @return ELIF�ڵ㣬NULL��ʾʧ��
    */
    CwxHtmlTmplTagNode* parseIfElif(CwxHtmlTmplTagNode* pPrev);
    /**
    @brief ����ELSE�﷨��
    @param [in] pPrev ELSE��ǰһ���ڵ�
    @return ELSE�ڵ㣬NULL��ʾʧ��
    */
    CwxHtmlTmplTagNode* parseIfElse(CwxHtmlTmplTagNode* pPrev);
    /**
    @brief ����ģ���е�һ���ı����������ж���ı�����
    @param [in] pPrev ���еĵ�ǰһ���ڵ�
    @return ���е�ĩ�ڵ㣬NULL��ʾʧ��
    */
    CwxHtmlTmplTagNode* parseLine(CwxHtmlTmplTagNode* pPrev);
    ///�ж�һ���﷨���Ƿ�ģ����ַ����﷨
    bool isCharsetDef();
    ///�ж�һ���﷨���Ƿ�ģ���REPLACE�﷨
    bool isReplaceDef();
    ///�ж�һ���﷨���Ƿ�ģ���CONST�﷨
    bool isConstDef();
    ///�ж�һ���﷨���Ƿ�ģ��ı�����ʽ�����﷨
    bool isValFormatDef();
    ///�ж�һ���﷨���Ƿ�ģ���LOOP��ʼ�﷨
    bool isLoopBeginDef();
    ///�ж�һ���﷨���Ƿ�ģ���LOOP�����﷨
    bool isLoopEndDef();
    ///�ж�һ���﷨���Ƿ�ģ���IF��ʼ�﷨
    bool isIfBeginDef();
    ///�ж�һ���﷨���Ƿ�ģ���ELIF��ʼ�﷨
    bool isIfElseIfDef();
    ///�ж�һ���﷨���Ƿ�ģ���ELSE��ʼ�﷨
    bool isIfElseDef();
    ///�ж�һ���﷨���Ƿ�ģ���IF�Ľ����﷨
    bool isIfEndDef();
    ///�ж�һ���Ƿ��ԡ����з�������
    bool isLineContinue(char const*& szLineEnd);
    ///�ж�ģ����ַ����Ƿ�ΪGBK��GB2312
    bool isGbkTmpl();
    ///��ģ�嶨�������ж�ȡһ�У������з��ָ����Ϊһ��
    bool readLine();
    /**
    @brief ����XML��ʽ���﷨��
    @param [in] szXml XML��ʽ���﷨
    @param [out] lsAttrs �﷨�е����Զ���
    @return false������ʧ�ܣ�true�������ɹ�
    */
    bool parseXml(char const* szXml, list<pair<char*, char*> >const *& lsAttrs);
    ///��ȡģ�嶨����ַ�����Ĭ��ΪUTF-8
    bool parseCharset();
    /**
    @brief ������ǰ�е�һ���﷨�����ȡ�﷨�ж�������ԡ�
    @param [out] lsAttrs �﷨�е����Զ���
    @return false������ʧ�ܣ�true�������ɹ�
    */
    bool prepareCmd(list<pair<char*, char*> >& lsAttrs);
    /**
    @brief ��ȡһ�����������Ķ�������
    @param [in] szValName ����������
    @param [out] szObjName ��������֣�NULL��ʾû���޶����������
    @return void
    */
    void parseValObject(char const* szValName, char const*& szObjName);
    ///�ж�ָ���Ķ������Ƿ����
    bool isExistObject(char const* szObjName);
    /**
    @brief ����һ�������ڵ㡣
    @param [in,out] pTag ������tag
    @param [in] szName ����������
    @param [in] szAttr ����������
    @param [in] szLength �����ĳ���
    @param [in] szDefault ������ȱʡֵ
    @param [in] szEscape ������ESCAPE�任������
    @param [in] szArgument ESCAPE�Ĳ���
    @return false��ʧ�ܣ�true���ɹ�
    */
    bool parseVal(CwxHtmlTmplTagNode* pTag, char const* szName, char const* szAttr, char const* szLength, char const* szDefault, char const* szEscape, char const* szArgument);
    /**
    @brief ��鵱ǰ�����BUF�Ŀռ��Ƿ��㹻��
    @param [in] env ģ������Ļ�������
    @param [in] uiSize ���������Ҫ��BUF�ռ��С
    @return false���ռ䲻�㣻true���ռ��㹻
    */
    inline bool checkBufSize(CwxHtmlTmplEnv& env, CWX_UINT32 uiSize) const
    {
        if (env.getBufLeft() < uiSize)
        {
            CwxCommon::snprintf(env.m_szErr1K, env.m_uiErrBufLen, "Output text's size too small, left:%u, need:%u.", env.getBufLeft(), uiSize);
            return false;
        }
        return true;
    }
    /**
    @brief ���If�������Ƿ�Ϊtrue��
    @param [in] szVal name������ֵ
    @param [in] pIfTag if tag
    @param [in] env ģ������Ļ�������
    @return false��������������true����������
    */
    inline bool checkIfCondition(char const* szVal, CwxHtmlTmplTagNode* pIfTag, CwxHtmlTmplEnv& env)  const
    {
        bool bRet = false;
        if (pIfTag->m_tag.m_if.m_pCompareObj)
        {
           bRet = pIfTag->m_tag.m_if.m_pCompareObj->compare(szVal, pIfTag->m_tag.m_if.m_szData, pIfTag->m_tag.m_if.m_szArgument, this, &env);
        }
        else
        {
            size_t len = szVal?strlen(szVal):0;
            if (!szVal || !len || ((1==len) && ('0'==szVal[0])))
            {
                bRet = false;
            }
            else
            {
                bRet = true;
            }
        }
        return pIfTag->m_tag.m_if.m_bReverse?!bRet:bRet;
    }
    /**
    @brief ���elif�������Ƿ�Ϊtrue��
    @param [in] szVal name������ֵ
    @param [in] pElifTag elif tag
    @param [in] env ģ������Ļ�������
    @return false��������������true����������
    */
    inline bool checkElifCondition(char const* szVal, CwxHtmlTmplTagNode* pElifTag, CwxHtmlTmplEnv& env) const
    {
        bool bRet = false;
        if (pElifTag->m_tag.m_elif.m_pCompareObj)
        {
            bRet = pElifTag->m_tag.m_elif.m_pCompareObj->compare(szVal, pElifTag->m_tag.m_elif.m_szData, pElifTag->m_tag.m_elif.m_szArgument, this, &env);
        }
        else
        {
            size_t len = szVal?strlen(szVal):0;
            if (!szVal || !len || ((1==len) && ('0'==szVal[0])))
            {
                bRet = false;
            }
            else
            {
                bRet = true;
            }
        }
        return pElifTag->m_tag.m_elif.m_bReverse?!bRet:bRet;
    }
private:
    ///��ִֹ�и�ֵ����
    CwxHtmlTmpl& operator=(CwxHtmlTmpl const& )
    {
        return *this;
    }
private:
    string                  m_strTmplName;///<ģ�������
    string                  m_strTmplFile;///<ģ���Ӧ�Ķ����ļ�����
    string                  m_strCharset;///<ģ�嶨����ַ���
    bool                    m_bCaseInsensitive;///<ֱ���ַ��滻��ʱ���Ƿ��Сд������
    map<string, string>      m_attrTmplMap;///<ģ�����������
    CwxReplBase*            m_repl;///<ģ����ַ��滻��
    CwxHtmlTmplTagNode      m_root;///<ģ���﷨���ĸ��ڵ�
    CwxHtmlValMap            m_valFormatMap;///<������ʽ����MAP
    CwxHtmlConstMap          m_constMap;///<������ʽ����MAP
    CwxTypePool<CwxHtmlTmplTagNode> m_tagPool;///<�ڵ��MEM POOL
    CwxCharPool              m_memPool;///<�ַ���MEM POOL
    string                  m_strErr;///<������Ϣ

    CwxMemLineReader        m_tmplLineReader;///<�м��ģ���ж�ȡ������
    CwxXmlConfigParser      m_cmdParse;///<ģ���﷨��XML��������
    string                  m_strLine;///<ģ���еı�������
    CWX_UINT32              m_uiLineBegin;///<��ǰ��������ģ��Ŀ�ʼ�кš�
    CWX_UINT32              m_uiLineEnd;///<��ǰ��������ģ��Ľ����кš�
    char*                   m_szTmpBuf;///<��ʱ�ռ䣬��XML����ʹ��
    CWX_UINT32              m_uiTmpBufLen;///<��ʱ�ռ�Ĵ�С
    CWX_UINT32              m_uiReplaceNum;///<ִ���ַ��滻���ַ���������
    list<string>            m_loopList;///<���������е�loopǶ�ײ��
    static CwxHtmlTmplCmpMap   m_cmpMap;///<�ȽϺ��������MAP
    static CwxHtmlTmplEscapeMap m_escapeMap;///<excape��������MAP
};
///ģ������MAP
typedef map<string const, CwxHtmlTmpl*> CwxFileTmplHash;


CWINUX_END_NAMESPACE


#include "CwxPost.h"

#endif

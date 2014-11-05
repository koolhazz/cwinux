#ifndef __CWF_FILTER_MGR_H__
#define __CWF_FILTER_MGR_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

#include "CwxFilterMachine.h"
#include "CwfFilterMacro.h"
#include "CwfFilterConfig.h"

///Filter�Ĺ�����
class CwfFilterMgr
{
public:
    enum
    {
        DEF_PER_FILTER_STOPWORD_NUM = 1000,
        DEF_PER_FILTER_KEYWORD_NUM = 10000
    };
public:
    ///���캯��
    CwfFilterMgr(CWX_UINT32 uiStopWord=DEF_PER_FILTER_STOPWORD_NUM,
        CWX_UINT32 uiWord=DEF_PER_FILTER_KEYWORD_NUM);
    ///��������
    ~CwfFilterMgr();
public:
    ///��ʼ��filter��������0���ɹ���-1��ʧ��
    int init(CwfFilterConfig const& config,
        char* szErr2K);
    ///����filter��id��filte content��-1��ʧ�ܣ�0���ɹ�
    int filter(CWX_UINT32 uiFilterId,
        char const* szContent,
        CWX_UINT32 uiLen,
        CWX_UINT8& ucLevel,
        CWX_UINT32& uiWordPos,
        CWX_UINT32& uiWordLen,
        char* szErr2K);
    ///����filter�����֣�filte content��-1��ʧ�ܣ�0���ɹ�
    int filter(string strName,
        char const* szContent,
        CWX_UINT32 uiLen, 
        CWX_UINT8& ucLevel,
        CWX_UINT32& uiWordPos,
        CWX_UINT32& uiWordLen,
        char* szErr2K);
private:
    ///��ն���
    void reset();
    CWX_UINT8 level(CWX_UINT8 ucLevel);
private:
    CWX_UINT32   m_uiStopWord;
    CWX_UINT32   m_uiKeyWord;
    hash_map<CWX_UINT32/*id*/, CwxFilterBase*>* m_idFilterMap;
    hash_map<string, CwxFilterBase*, CwxStringHash>*  m_nameFilterMap;
    bool  m_bCaseSensive;
};

#endif 

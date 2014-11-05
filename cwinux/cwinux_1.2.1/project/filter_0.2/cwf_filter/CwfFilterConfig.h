#ifndef __CWF_FILTER_CONFIG_H__
#define __CWF_FILTER_CONFIG_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

#include "CwxGlobalMacro.h"
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxXmlFileConfigParser.h"

CWINUX_USING_NAMESPACE

///һ������������ĸ���level��filter �ļ�����
class CwfFilterConfigFilter
{
public:
    ///���캯��
    CwfFilterConfigFilter()
    {
        m_uiId = 0;
    }

    ///��������
    ~CwfFilterConfigFilter()
    {
    }
    ///��ֵ����
    CwfFilterConfigFilter& operator=(CwfFilterConfigFilter const& obj)
    {
        if (this != &obj)
        {
            m_strName = obj.m_strName;
            m_uiId = obj.m_uiId;
            m_strStopwordFile = obj.m_strStopwordFile;
            m_levelFiles = obj.m_levelFiles;
        }
        return *this;
    }
    ///��������
    CwfFilterConfigFilter(CwfFilterConfigFilter const& obj)
    {
        m_strName = obj.m_strName;
        m_uiId = obj.m_uiId;
        m_strStopwordFile = obj.m_strStopwordFile;
        m_levelFiles = obj.m_levelFiles;
    }
public:
    string     m_strName; ///<������������
    CWX_UINT32  m_uiId; ///<��������id
    string     m_strStopwordFile;///<��������stopword�ļ�
    map<CWX_UINT8/*level*/, string/*file*/> m_levelFiles;  ///<������1~7��7�������ļ�
};

///�����ļ����ض���
class CwfFilterConfig
{
public:
    ///���캯��
    CwfFilterConfig()
    {
        m_unThreadNum = 4;
        m_bUtf8 = true;
        m_bCaseSensive = true;

    }
    ///��������
    ~CwfFilterConfig()
    {
        list<CwfFilterConfigFilter*>::iterator iter = m_fiters.begin();
        while(iter != m_fiters.end())
        {
            delete *iter;
            iter++;
        }
        m_fiters.clear();
    }
public:
    //���������ļ�.-1:failure, 0:success
    int loadConfig(string const & strConfFile);
    //������ص������ļ���Ϣ
    void outputConfig();
    //��ȡ�����ļ����ص�ʧ��ԭ��
    char const* getError() { return m_szError; };
public:
    string              m_strWorkDir;///<����Ŀ¼
    string              m_strUnixPathFile;///<unix domain�ļ��� path file
    CwxHostInfo          m_filterListen;///<���˵�tcp�ļ���ip/port
    bool                m_bUtf8; ///<���õĹ��˴ʼ����˵������Ƿ�utf-8���롣ȱʡΪUTF-8
    bool                m_bCaseSensive; ///<���õĹ��˴ʼ����˵������Ƿ��Сд���У�ȱʡΪ��Сд����
    CWX_UINT16           m_unThreadNum;///<echo�����echo�߳�����
    CwxHostInfo          m_mgrListen;///<�����tcp�ļ���ip/port
    list<CwfFilterConfigFilter*> m_fiters; ///<�����鶨���б�
    char                m_szError[2048];///<������Ϣ��buf
};

#endif

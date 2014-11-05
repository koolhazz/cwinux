#ifndef __CWX_ECHO_TB_CLIENT_CONFIG_H__
#define __CWX_ECHO_TB_CLIENT_CONFIG_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxXmlFileConfigParser.h"

CWINUX_USING_NAMESPACE

class CwxEchoTbClientGroup
{
public:
    CwxEchoTbClientGroup()
    {
    }
    CwxEchoTbClientGroup(CwxEchoTbClientGroup const& group)
    {
        m_hosts = group.m_hosts;
    }
    CwxEchoTbClientGroup& operator=(CwxEchoTbClientGroup const& group)
    {
        if (this != & group)
        {
            m_hosts = group.m_hosts;
        }
        return *this;
    }
public:
    list<CwxHostInfo> m_hosts;
};
///echoѹ�����Ե������ļ����ض���
class CwxEchoTbClientConfig
{
public:
    CwxEchoTbClientConfig()
    {
        m_uiDataSize = 0;
        m_unConnNum = 1;
        m_unThreadNum = 4;
        m_uiTimeout = 2000;
        m_uiTaskNum = 10;
        m_uiWaitMsgNum = 10;
        m_szError[0] = 0x00;
    }
    
    ~CwxEchoTbClientConfig()
    {
        list<CwxEchoTbClientGroup*>::iterator iter=m_svrGroup.begin();
        while(iter != m_svrGroup.end())
        {
            delete *iter;
            iter++;
        }
        m_svrGroup.clear();
    }
public:
    //���������ļ�.-1:failure, 0:success
    int loadConfig(string const & strConfFile);
    //��������ļ�
    void outputConfig(string & strConfig);
    //��ȡ���������ļ���ʧ�ܴ�����Ϣ
    char const* getError() { return m_szError; };
    
public:
    string              m_strWorkDir;///<����Ŀ¼
    CwxHostInfo          m_mgrListen; ///<����ļ����˿�
    CWX_UINT32           m_uiDataSize;///<echo�����ݰ��Ĵ�С
    CWX_UINT16           m_unConnNum; ///<ÿ��server����������
    CWX_UINT16           m_unThreadNum; ///<�̵߳�����
    CWX_UINT32           m_uiTaskNum; ///<���������
    CWX_UINT32           m_uiTimeout; ///<��ѯ��ʱʱ�䣬��λΪms
    CWX_UINT32           m_uiWaitMsgNum; ///<�����ϵȴ�������Ϣ������
    list<CwxEchoTbClientGroup*> m_svrGroup; ///<��������map
    char                m_szError[2048];///<������Ϣbuf
};

#endif

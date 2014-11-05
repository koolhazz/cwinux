#ifndef __CWX_ECHO_CONFIG_H__
#define __CWX_ECHO_CONFIG_H__

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

///�����ļ����ض���
class CwxEchoConfig
{
public:
    CwxEchoConfig(){
        m_unThreadNum = 0;
    }
    
    ~CwxEchoConfig(){}
public:
    //���������ļ�.-1:failure, 0:success
    int loadConfig(string const & strConfFile);
    //������ص������ļ���Ϣ
    void outputConfig(string & strConfig);
    //��ȡ�����ļ����ص�ʧ��ԭ��
    char const* getError() { return m_szError; };
public:
    string              m_strWorkDir;///<����Ŀ¼
    string              m_strUnixPathFile;///<unix domain�ļ��� path file
    CWX_UINT16           m_unThreadNum;///<echo�����echo�߳�����
    CwxHostInfo       m_listen;///<tcp�ļ���ip/port
    CwxHostInfo          m_mgrListen; ///<����ļ����˿�
    char                m_szError[2048];///<������Ϣ��buf
};

#endif

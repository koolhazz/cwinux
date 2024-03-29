#ifndef __CWX_ECHO_CONFIG_H__
#define __CWX_ECHO_CONFIG_H__

/*
版权声明：
    本软件为个人所有，遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html），
但有以下例外：
    腾讯公司及与腾讯公司有直接业务与合作关系的公司不得使用此软件。原因可参考：
http://it.sohu.com/20100903/n274684530.shtml
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/
#include "CwxGlobalMacro.h"
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxXmlFileConfigParser.h"

CWINUX_USING_NAMESPACE

///配置文件加载对象
class CwxEchoConfig
{
public:
    CwxEchoConfig(){
        m_unThreadNum = 0;
    }
    
    ~CwxEchoConfig(){}
public:
    //加载配置文件.-1:failure, 0:success
    int loadConfig(string const & strConfFile);
    //输出加载的配置文件信息
    void outputConfig(string & strConfig);
    //获取配置文件加载的失败原因
    char const* getError() { return m_szError; };
public:
    string              m_strWorkDir;///<工作目录
    string              m_strUnixPathFile;///<unix domain的监听 path file
    CWX_UINT16           m_unThreadNum;///<echo服务的echo线程数量
    CwxHostInfo       m_listen;///<tcp的监听ip/port
    CwxHostInfo          m_mgrListen; ///<管理的监听端口
    char                m_szError[2048];///<错误消息的buf
};

#endif

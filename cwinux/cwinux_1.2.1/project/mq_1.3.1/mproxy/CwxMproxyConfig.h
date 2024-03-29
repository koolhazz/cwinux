#ifndef __CWX_MQ_PROXY_CONFIG_H__
#define __CWX_MQ_PROXY_CONFIG_H__
/*
版权声明：
    本软件为个人所有，遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html），
但有以下例外：
    腾讯公司及与腾讯公司有直接业务与合作关系的公司不得使用此软件。原因可参考：
http://it.sohu.com/20100903/n274684530.shtml
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/


#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxXmlFileConfigParser.h"
#include "CwxMqDef.h"

CWINUX_USING_NAMESPACE

///echo压力测试的配置文件加载对象
class CwxMproxyConfig
{
public:
    CwxMproxyConfig()
    {
        m_unThreadNum = 4;
        m_uiTimeout = 5000;
        m_uiConnNum = 1;
        m_szErrMsg[0] = 0x00;
    }
    
    ~CwxMproxyConfig()
    {
    }
public:
    //加载配置文件.-1:failure, 0:success
    int loadConfig(string const & strConfFile);
    //输出配置文件
    void outputConfig();
    //获取加载配置文件的失败错误信息
    char const* getError() { return m_szErrMsg; };
private:
    bool fetchHost(CwxXmlFileConfigParser& parser,
        string const& path,
        CwxHostInfo& host);
    bool loadGroup(string const& path, CwxXmlTreeNode const* pGroup, CwxMqConfigQueue& group);
    bool parseIds(string const& group, list<pair<CWX_UINT32, CWX_UINT32> >& ids);

public:
    string               m_strWorkDir;///<工作目录
    CwxHostInfo          m_mgrListen; ///<管理的监听端口
    CWX_UINT16           m_unThreadNum; ///<线程的数量
    CWX_UINT32           m_uiTimeout; ///<查询超时时间，单位为ms
    CwxHostInfo          m_recv;      ///<代理消息接受的监听地址
    CWX_UINT32           m_uiConnNum; ///<连接的数量
    map<CwxMqIdRange, CwxMqConfigQueue>  m_groupPasswd; ///<口令
    map<CwxMqIdRange, string>    m_allowGroup; ///<允许的group，若不为空，则group必须在allow中存在，否则查deny
    map<CwxMqIdRange, string>    m_denyGroup; ///<禁止的group，若allow为空，则查deny。若在deny中存在，则禁止。
    CwxHostInfo          m_mq; ///<mq的服务器
    char                 m_szErrMsg[2048];///<错误消息buf
};

#endif

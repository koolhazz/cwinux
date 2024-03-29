#ifndef __CWX_MQ_CONFIG_H__
#define __CWX_MQ_CONFIG_H__
/*
版权声明：
    本软件为个人所有，遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html），
但有以下例外：
    腾讯公司及与腾讯公司有直接业务与合作关系的公司不得使用此软件。原因可参考：
http://it.sohu.com/20100903/n274684530.shtml
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/

#include "CwxMqMacro.h"
#include "CwxGlobalMacro.h"
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxXmlFileConfigParser.h"
#include "CwxBinLogMgr.h"
#include "CwxStl.h"
#include "CwxStlFunc.h"
#include "CwxMqDef.h"

CWINUX_USING_NAMESPACE

///配置文件的common参数对象
class CwxMqConfigCmn
{
public:
    enum
    {
        MIN_ASYNC_WINDOW_SIZE = 1, ///<最小的异步分发的窗口大小
        MAX_ASYNC_WINDOW_SIZE = 1024, ///<最大的异步分发的窗口大小
        DEF_ASYNC_WINDOW_SIZE = 128 ///<缺省的异步分发的窗口大小
    };
public:
    CwxMqConfigCmn()
    {
        m_bMaster = false;
        m_uiDispatchWindowSize = DEF_ASYNC_WINDOW_SIZE;
        m_uiFromMasterWindowSize = DEF_ASYNC_WINDOW_SIZE;
    };
public:
    string              m_strWorkDir;///<工作目录
    bool                m_bMaster; ///<是否是master dispatch
    CwxHostInfo         m_mgrListen;///<管理的tcp的监听ip/port
    CWX_UINT32          m_uiDispatchWindowSize; ///<发送的窗口大小
    CWX_UINT32          m_uiFromMasterWindowSize; ///<从master接收的窗口大小
};

///配置文件的binlog参数对象
class CwxMqConfigBinLog
{
public:
    enum
    {
        DEF_BINLOG_MSIZE = 2048, ///<缺省的binlog大小
        MIN_BINLOG_MSIZE = 64, ///<最小的binlog大小
        MAX_BINLOG_MSIZE = 8192 ///<最大的binlog大小
    };
public:
    CwxMqConfigBinLog()
    {
        m_uiBinLogMSize = DEF_BINLOG_MSIZE;
        m_uiMgrMaxDay = CwxBinLogMgr::DEF_MANAGE_MAX_DAY;
        m_uiFlushNum = 100;
        m_uiFlushSecond = 30;
        m_uiMqFetchFlushNum = 1;
        m_uiMqFetchFlushSecond = 30;
    }
public:
    string              m_strBinlogPath; ///<binlog的目录
    string              m_strBinlogPrex; ///<binlog的文件的前缀
    CWX_UINT32          m_uiBinLogMSize; ///<binlog文件的最大大小，单位为M
    CWX_UINT32          m_uiMgrMaxDay; ///<管理的binglog的最小天数
    CWX_UINT32          m_uiFlushNum; ///<接收多少条记录后，flush binlog文件
    CWX_UINT32          m_uiFlushSecond; ///<间隔多少秒，必须flush binlog文件
    CWX_UINT32          m_uiMqFetchFlushNum; ///<fetch多少条日志，必须flush获取点
    CWX_UINT32          m_uiMqFetchFlushSecond; ///<多少秒必须flush获取点
};

///配置文件的master参数对象
class CwxMqConfigMaster
{
public:
    CwxMqConfigMaster()
    {
    }
public:
    CwxHostInfo     m_recv; ///<master的信息接口端口信息
    CwxHostInfo     m_async; ///<master异步分发的分发端口信息
};

///配置文件的slave参数对象
class CwxMqConfigSlave
{
public:
    CwxMqConfigSlave()
    {
    }
public:
    CwxHostInfo     m_master; ///<slave的master的连接信息
    string          m_strSubScribe;///<消息订阅表达式
    CwxHostInfo     m_async; ///<slave异步分发的分发端口信息
};

///配置文件的mq参数对象
class CwxMqConfigMq
{
public:
    CwxMqConfigMq()
    {
    }
public:
    CwxMqConfigQueue const* getQueue(string const& strQueue) const
    {
        map<string, CwxMqConfigQueue>::const_iterator iter = m_queues.find(strQueue);
        return iter == m_queues.end()?NULL:&iter->second;
    }
public:
    CwxHostInfo     m_listen; ///<mq的listen的连接信息
    map<string, CwxMqConfigQueue>  m_queues; ///<消息分发的队列
};

///配置文件加载对象
class CwxMqConfig
{
public:
    ///构造函数
    CwxMqConfig()
    {
        m_szErrMsg[0] = 0x00;
    }
    ///析构函数
    ~CwxMqConfig()
    {
    }
public:
    //加载配置文件.-1:failure, 0:success
    int loadConfig(string const & strConfFile);
    //输出加载的配置文件信息
    void outputConfig() const;
public:
    ///获取common配置信息
    inline CwxMqConfigCmn const& getCommon() const
    {
        return  m_common;
    }
    ///获取binlog配置信息
    inline CwxMqConfigBinLog const& getBinLog() const
    {
        return m_binlog;
    }
    ///获取master配置信息
    inline CwxMqConfigMaster const& getMaster() const
    {
        return m_master;
    }
    ///获取slave配置信息
    inline CwxMqConfigSlave const& getSlave() const 
    {
        return m_slave;
    }
    inline CwxMqConfigMq const& getMq() const
    {
        return m_mq;
    }
    ///获取配置文件加载的失败原因
    inline char const* getErrMsg() const 
    {
        return m_szErrMsg;
    };
private:
    bool fetchHost(CwxXmlFileConfigParser& parser,
        string const& path,
        CwxHostInfo& host);
private:
    CwxMqConfigCmn  m_common; ///<common的配置信息
    CwxMqConfigBinLog m_binlog; ///<binlog的配置信息
    CwxMqConfigMaster m_master; ///<master的配置信息
    CwxMqConfigSlave  m_slave; ///<slave的配置信息
    CwxMqConfigMq     m_mq; ///<mq的fetch的配置信息
    char                m_szErrMsg[2048];///<错误消息的buf
};

#endif

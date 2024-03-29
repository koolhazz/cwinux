#ifndef __CWX_MQ_RECV_HANDLER_H__
#define __CWX_MQ_RECV_HANDLER_H__
/*
版权声明：
    本软件为个人所有，遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html），
但有以下例外：
    腾讯公司及与腾讯公司有直接业务与合作关系的公司不得使用此软件。原因可参考：
http://it.sohu.com/20100903/n274684530.shtml
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/
#include "CwxAppCommander.h"
#include "CwxMqMacro.h"
#include "CwxMqTss.h"
class CwxMqApp;


///Dispatch master处理收到的binlog handler
class CwxMqRecvHandler: public CwxAppCmdOp
{
public:
    ///构造函数
    CwxMqRecvHandler(CwxMqApp* pApp):m_pApp(pApp)
    {
        m_uiUnSyncLogNum = 0; ///<上次形成sync记录以来的新记录数
        m_ttLastSyncTime = 0; ///<上一次形成sync记录的时间
    }
    ///析构函数
    virtual ~CwxMqRecvHandler()
    {

    }
public:
    ///连接建立后，需要维护连接上数据的分发
    virtual int onConnCreated(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    ///连接关闭后，需要清理环境
    virtual int onConnClosed(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    ///处理收到binlog的事件
    virtual int onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    ///对于同步dispatch，需要检查同步的超时
    virtual int onTimeoutCheck(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
private:
    ///-1:失败；0：成功
    int commit(char* szErr2K);
    ///-1:失败；0：无需形成log；1：形成一个log
    int checkSyncLog(bool bNew, char* szErr2K);
private:
    CWX_UINT32      m_uiUnSyncLogNum; ///<上次形成sync记录以来的新记录数
    time_t          m_ttLastSyncTime; ///<上一次形成sync记录的时间
    map<CWX_UINT32, bool>   m_clientMap; ///<连接认证的map
    CwxMqApp*       m_pApp;  ///<app对象
};

#endif 

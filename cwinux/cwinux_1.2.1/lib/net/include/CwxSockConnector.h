#ifndef __CWX_SOCK_CONNECTOR_H__
#define __CWX_SOCK_CONNECTOR_H__
/*
版权声明：
    本软件为个人所有，遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html），
但有以下例外：
    腾讯公司及与腾讯公司有直接业务与合作关系的公司不得使用此软件。原因可参考：
http://it.sohu.com/20100903/n274684530.shtml
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/
/**
@file CwxSockConnector.h
@brief TCP主动连接的连接器对象的定义。
@author cwinux@gmail.com
@version 0.1
@date 2009-10-11
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxType.h"
#include "CwxErrGuard.h"
#include "CwxNetMacro.h"
#include "CwxINetAddr.h"
#include "CwxSockStream.h"
#include "CwxSockBase.h"

CWINUX_BEGIN_NAMESPACE
/**
@class CwxSockConnector
@brief TCP主动连接的连接器对象。
*/
class CWX_API CwxSockConnector
{
public:
    ///默认构造函数
    CwxSockConnector();
    ///析构函数.
    ~CwxSockConnector(void);
public:
    /**
    @brief 建立TCP主动连接。
    @param [out] stream 主动连接。
    @param [in] remoteAddr 连接的远程地址。
    @param [in] localAddr 连接的本地地址，若为空，则有connect自己分配。
    @param [in] timeout 连接的超时时间，若NULL，表示没有超时限制。若值为0，则表示若没有连接上，立即返回。
    @param [in] protocol 连接的协议，就是socket()的protocol参数，由于一个协议家族的socket 类型，其protocol也是唯一的，为0就可以了。
    @param [in] reuse_addr 是否重用本地地址。
    @return -1：错误，errno记录错误的原因；0：成功。
    */
    int connect (CwxSockStream& stream,
        CwxAddr const& remoteAddr,
        CwxAddr const& localAddr=CwxAddr::sap_any,
        CwxTimeouter* timeout=0,
        int protocol = 0,
        bool reuse_addr = false);
    /**
    @brief 设置连接完成后的连接标志。
    @param [out] stream 主动连接。
    @param [in] remoteAddr 连接的远程地址，若不为空则获取远端地址。
    @param [in] timeout 连接的超时时间，若NULL，表示没有超时限制。若值为0，则表示若没有连接上，立即返回。
    @return -1：错误，errno记录错误的原因；0：成功。
    */
    int complete (CwxSockStream &stream,
        CwxAddr *remoteAddr = 0,
        CwxTimeouter* timeout=0);

private:
};

CWINUX_END_NAMESPACE

#include "CwxSockConnector.inl"
#include "CwxPost.h"

#endif

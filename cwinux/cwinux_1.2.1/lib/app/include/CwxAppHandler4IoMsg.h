#ifndef __CWX_APP_HANDLER_4_IO_MSG_H__
#define __CWX_APP_HANDLER_4_IO_MSG_H__
/*
版权声明：
    本软件为个人所有，遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html），
但有以下例外：
    腾讯公司及与腾讯公司有直接业务与合作关系的公司不得使用此软件。原因可参考：
http://it.sohu.com/20100903/n274684530.shtml
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppHandler4IoMsg.h
@brief 定义基于msg收发的IO通信、管理的Handle对象CwxAppHandler4IoMsg。
@author cwinux@gmail.com
@version 0.1
@date 2009-07-20
@warning
@bug
*/

#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxMsgBlock.h"
#include "CwxMsgHead.h"
#include "CwxAppConfig.h"
#include "CwxAppMacro.h"
#include "CwxAppLogger.h"
#include "CwxAppHandler4Msg.h"

CWINUX_BEGIN_NAMESPACE
/**
@class CwxAppHandler4IoMsg
@brief PIPE、及其他IO通信、状态管理的Handle对象
*/
class CwxAppFramework;

class CWX_API CwxAppHandler4IoMsg:public CwxAppHandler4Msg
{
public:
    ///构造函数
    CwxAppHandler4IoMsg(CwxAppFramework* pApp,
        CwxAppReactor *reactor);
    ///析构函数
    ~CwxAppHandler4IoMsg();
public:
    ///handle close
    virtual int close(CWX_HANDLE handle=CWX_INVALID_HANDLE);
public:
    CwxAppHandler4IoMsg*     m_next;
};
CWINUX_END_NAMESPACE

#include "CwxPost.h"

#endif

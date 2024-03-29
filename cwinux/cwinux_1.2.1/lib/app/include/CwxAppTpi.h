#ifndef __CWX_APP_TPI_H__
#define __CWX_APP_TPI_H__
/*
版权声明：
    本软件为个人所有，遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html），
但有以下例外：
    腾讯公司及与腾讯公司有直接业务与合作关系的公司不得使用此软件。原因可参考：
http://it.sohu.com/20100903/n274684530.shtml
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppTpi.h
@brief 线程池接口定义
@author cwinux@gmail.com
@version 0.1
@date 2009-07-20
@warning
@bug
*/

#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxAppMacro.h"
#include "CwxAppTss.h"

CWINUX_BEGIN_NAMESPACE

class CwxAppFramework;
/**
@class CwxAppTpi
@brief 线程池的接口对象。
*/

class CWX_API CwxAppTpi
{
public :
    ///构造函数
    CwxAppTpi(CWX_UINT16 unGroup, CWX_UINT16 unThreadNum)
        :m_unGroup(unGroup), m_unThreadNum(unThreadNum)
    {
    }
    ///析构函数
    virtual ~CwxAppTpi()
    {

    }
public:
    /**
    @brief 启动线程池，为纯虚接口
    @param [in] pThrEnv 线程池的线程Tss的数组，若不指定，可通过onThreadCreated创建。
    @param [in] stack_size 线程堆栈的大小，若为0，则采用系统默认大小。
    @return -1：失败； 0：成功
    */
    virtual int start(CwxAppTss** pThrEnv=NULL, size_t stack_size= 0) = 0;
    ///停止线程池
    virtual void stop() = 0;
    ///check thread 是否死锁。若需要改变检查的规则，则重载此API
    virtual bool isDeath() = 0;
    ///check thread 是否停止。若需要改变检查的规则，则重载此API
    virtual bool isStop() = 0;
    ///获取线程的TSS，及Thread env
    virtual CwxAppTss* getTss(CWX_UINT16 unThreadIndex)=0;
    ///锁住整个线程池。返回值0：成功；-1：失败
    virtual int lock()=0;
    ///解锁这个线程池。返回值0：成功；-1：失败
    virtual int unlock()=0;
public:
    ///获取线程池中线程的数量
    inline CWX_UINT16 getThreadNum() const
    {
        return m_unThreadNum;
    }
    ///获取线程池的线程组ID
    inline CWX_UINT16 getGroupId() const 
    {
        return m_unGroup;
    }
private:
    CWX_UINT16             m_unGroup;///<线程组id
    CWX_UINT16             m_unThreadNum;///<线程池中线程的数量
};

CWINUX_END_NAMESPACE

#include "CwxPost.h"
#endif


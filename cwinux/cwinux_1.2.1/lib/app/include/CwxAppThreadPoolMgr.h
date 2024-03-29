#ifndef __CWX_APP_THREAD_POOL_MGR_H__
#define __CWX_APP_THREAD_POOL_MGR_H__
/*
版权声明：
    本软件为个人所有，遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html），
但有以下例外：
    腾讯公司及与腾讯公司有直接业务与合作关系的公司不得使用此软件。原因可参考：
http://it.sohu.com/20100903/n274684530.shtml
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppThreadPoolMgr.h
@brief 线程池及其线程的TSS的管理对象的实现
@author cwinux@gmail.com
@version 0.1
@date 2009-07-20
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxStl.h"
#include "CwxType.h"
#include "CwxLockGuard.h"
#include "CwxMutexLock.h"
#include "CwxAppMacro.h"
#include "CwxAppTss.h"
#include "CwxAppTpi.h"
#include "CwxAppTss.h"

CWINUX_BEGIN_NAMESPACE
/**
@class CwxAppThreadPoolMgr
@brief 线程池及其线程的TSS的管理对象
*/
class CWX_API CwxAppThreadPoolMgr
{
public:
    ///构造函数
    CwxAppThreadPoolMgr();
    ///析构函数
    ~CwxAppThreadPoolMgr();
public:
    /**
    @brief 往管理器添加一个线程池
    @param [in] unGroupId 线程池的线程组ID
    @param [in] pThreadPool 线程池对象
    @return false：unGroupId指定的线程池已经存在； true：成功
    */
    bool add(CWX_UINT16 unGroupId, CwxAppTpi* pThreadPool);
    /**
    @brief 从管理器中删除一个线程池
    @param [in] unGroupId 删除线程池的线程组ID
    @return false：不存在； true：成功删除
    */
    bool remove(CWX_UINT16 unGroupId);
    /**
    @brief 检查管理的线程池的线程状态是否正常
    @return false：不正常； true：正常
    */
    bool isValid();
    /**
    @brief 检查指定的unGroupId的线程组在管理器中是否存在
    @return false：不存在； true：成功删除
    */
    bool isExist(CWX_UINT16 unGroupId);
    ///获取管理的线程池的数量
    CWX_UINT16 getNum();
    /**
    @brief 往线程池管理器中添加一个线程的TSS
    @param [in] pTss 线程的TSS
    @return false：与此TSS的GroupId与ThreadId相同的Tss已经存在； true：成功
    */
    bool addTss(CwxAppTss* pTss);
    /**
    @brief 返回所管理的所有线程的TSS
    @param [in] arrTss 所有线程的TSS。arrTss[i]为一个线程组的线程的TSS。第一级数组的元素按GroupId升序，第二级按ThreadId升序。
    @return void
    */
    void getTss(vector<vector<CwxAppTss*> >& arrTss);
    /**
    @brief 返回指定Thread GroupId的TSS
    @param [in] unGroup 线程的GroupId
    @param [in] arrTss 此线程组的线程的TSS，数组按照线程的ThreadId升序。
    @return void
    */
    void getTss(CWX_UINT16 unGroup, vector<CwxAppTss*>& arrTss);
    /**
    @brief 返回一个线程的Tss
    @param [in] unGroup 线程的GroupId
    @param [in] unThreadId 线程的ThreadId。
    @return NULL：不存在；否则为线程的TSS
    */
    CwxAppTss* getTss(CWX_UINT16 unGroup, CWX_UINT16 unThreadId);
private:
    CwxMutexLock        m_lock;///<thread lock for sync.
    map<CWX_UINT16, CwxAppTpi*>  m_threadPoolMap; ///<线程池的MAP
    map<CWX_UINT16, map<CWX_UINT16, CwxAppTss*> >  m_threadPoolTss;///线程Tss的map
};

CWINUX_END_NAMESPACE

#include "CwxPost.h"


#endif

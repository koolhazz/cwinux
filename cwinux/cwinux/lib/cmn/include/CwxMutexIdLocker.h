#ifndef __CWX_MUTEX_ID_LOCKER_H__
#define __CWX_MUTEX_ID_LOCKER_H__
/*
版权声明：
    本软件遵循GNU GPL V3（http://www.gnu.org/licenses/gpl.html），
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/

/**
*@file  CwxMutexIdLocker.h
*@brief 实现基于Id的排他锁对象，完成对一个64位数字的加锁
*@author cwinux@gmail.com
*@version 0.1
*@date  2009-05-30
*@warning  无.
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxStl.h"
#include "CwxStlFunc.h"
#include "CwxMutexLock.h"
#include "CwxLockGuard.h"
#include "CwxSingleton.h"

CWINUX_BEGIN_NAMESPACE

/**
* @class CwxMutexIdLockMgr
*
* @brief 64位数字的排他ID锁管理器对象。
*/
class CWX_API CwxMutexIdLockMgr : public CwxSingleton
{
public:
    enum{
        MAX_FREE_MUTEX_NUM = 32,///<最多空闲锁的数量
        HASH_BUCKET_SIZE = 2048///<锁HASH的大小
    };
    ///ID读写锁对象
    class CwxMutexObj
    {
    public:
        CwxMutexObj():m_unNum(0)
        {

        }
        ~CwxMutexObj()
        {

        }
    public:
        CwxMutexLock        m_lock;///<读写锁
        CWX_UINT16       m_unNum;///<等待读写锁的线程数量
    };
public:
public:
    ///创建signleton CwxRwIdLockMgr 对象
    static CwxMutexIdLockMgr* instance();
public:
    ///对ID加排他锁, 0：成功； -1：失败
    int lock(CWX_UINT64  id);
    ///对ID解锁, 0：成功； -1：失败
    int unlock(CWX_UINT64 id);
private:
    ///ID排他锁的初始化
    void  init();
    ///禁止外部创建对象实例
    CwxMutexIdLockMgr();
    ///禁止外部删除对象
    virtual ~CwxMutexIdLockMgr();

private:
    static CwxMutexIdLockMgr* m_pInstance; ///<单实例句柄
    static CwxMutexLock   m_lock;///<单实例的保护锁
    CWX_UINT16        m_unFreeMutexNum;///<空闲锁的数量
    list<CwxMutexObj*>*  m_pListLocks;///<空闲锁的列表
    CwxMutexLock      m_mutex;///<全局信息操作的同步锁
    hash_map<CWX_UINT64, CwxMutexObj* /*lock*/, CwxNumHash<CWX_UINT64> >*   m_pLockMap;///<锁的hash
};


/**
* @class CwxMutexIdLocker
*
* @brief 对一个64位数字，加排他锁。
*/
class CWX_API CwxMutexIdLocker
{
public:
public:
    ///对id加排他锁
    CwxMutexIdLocker(CWX_UINT64 id)
    {
        m_ullLockID = id;
        CwxMutexIdLockMgr::instance()->lock(m_ullLockID);
    }
    ///通过析构函数，完成对ID排他锁的释放.
    ~CwxMutexIdLocker()
    {
        CwxMutexIdLockMgr::instance()->unlock(m_ullLockID);
    }
private:
    CWX_UINT64              m_ullLockID;///<被锁的ID
};

CWINUX_END_NAMESPACE

#include "CwxPost.h"

#endif

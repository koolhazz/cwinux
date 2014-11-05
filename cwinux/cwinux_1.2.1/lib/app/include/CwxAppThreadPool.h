#ifndef __CWX_APP_THREAD_POOL_H__
#define __CWX_APP_THREAD_POOL_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppThreadPool.h
@brief �޷����Ƶ����̵߳���ͨ�̳߳ض���ʵ��
@author cwinux@gmail.com
@version 0.1
@date 2009-07-20
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxLockGuard.h"
#include "CwxMutexLock.h"
#include "CwxMsgBlock.h"
#include "CwxAppMacro.h"
#include "CwxAppConfig.h"
#include "CwxAppTss.h"
#include "CwxAppTpi.h"
#include "CwxAppThread.h"

CWINUX_BEGIN_NAMESPACE

class CwxAppFramework;
/**
@class CwxAppThreadPool
@brief ��ͨ���̳߳أ��̳߳��е������߳���Ϊһ��������֣��޷��������ء�
       ���̳߳ر������һ�������������߶��С�
*/
class CWX_API CwxAppThreadPool:public CwxAppTpi
{
public:
    enum{
        DEATH_CHECK_MSG_WATER_MASK = 5, ///<�̵߳�״̬�����Ŷ���Ϣ����
        DEATH_CHECK_UPDATE_WATER_MASK = 30 ///<�߳�ʧЧ����״̬���µ�ʱ������
    };
public :
    ///���캯��
    CwxAppThreadPool(CwxAppFramework* pApp,///<app����
        CWX_UINT16 unGroupId,///<�̳߳ص�thread-group
        CWX_UINT16 unThreadNum,///<�̳߳����̵߳�����
        CWX_UINT32 uiDeathCheckMsgWaterMask=DEATH_CHECK_MSG_WATER_MASK,///<�̵߳�״̬�����Ŷ���Ϣ����
        CWX_UINT32 uiDeathCheckUpdateWaterMask=DEATH_CHECK_UPDATE_WATER_MASK///<�߳�ʧЧ����״̬���µ�ʱ������
        );
    ///��������
    ~CwxAppThreadPool();
public:
    /**
    @brief �����̳߳�
    @param [in] pThrEnv �̳߳ص��߳�Tss�����飬����ָ������ͨ��onThreadCreated������
    @param [in] stack_size �̶߳�ջ�Ĵ�С����Ϊ0�������ϵͳĬ�ϴ�С��
    @return -1��ʧ�ܣ� 0���ɹ�
    */
    virtual int start(CwxAppTss** pThrEnv=NULL, size_t stack_size= 0);
    ///ֹͣ�̳߳�
    virtual void stop();
    ///check thread �Ƿ�����������Ҫ�ı���Ĺ��������ش�API
    virtual bool isDeath();
    ///check thread �Ƿ�ֹͣ������Ҫ�ı���Ĺ��������ش�API
    virtual bool isStop();
    ///��ȡ�̵߳�TSS����Thread env
    virtual CwxAppTss* getTss(CWX_UINT16 unThreadIndex);
    ///��ס�����̳߳ء�����ֵ0���ɹ���-1��ʧ��
    virtual int lock();
    ///��������̳߳ء�����ֵ0���ɹ���-1��ʧ��
    virtual int unlock();
public:
    /**
    @brief ֪ͨ�̴߳�������Ҫ�����Լ���Thread-Env�������ش�API
    @param [in] unGroup �̵߳��߳��顣
    @param [in] unThreadId �߳����߳����е���š�
    @param [out] pThrEnv ������Thread��Thread Env��
    @return -1��ʧ�ܣ� 0���ɹ�
    */
    virtual int onThreadCreated(CWX_UINT16 unGroup, CWX_UINT16 unThreadId, CwxAppTss*& pThrEnv);
    /**
    @brief ֪ͨ�߳��˳�
    @param [out] pThrEnv Thread��Thread Env��
    @return void
    */
    virtual void onThreadClosed(CwxAppTss*& pThrEnv);
    /**
    @brief �̵߳�body������Ҫ�ı��̵߳�������Ϊ�������ش�API
    @param [out] pThrEnv Thread��Thread Env��
    @return void
    */
    virtual void threadMain(CwxAppTss* pThrEnv);
public:
    ///��ȡ�̵߳���Ϣ�����Ŷ���Ϣ��
    inline size_t getQueuedMsgNum();
    /**
    @brief ���̵߳���Ϣ�������һ������Ϣ��
    @param [in] pMsg append����Ϣ
    @return -1��ʧ�ܣ�>=0�������Ŷӵ���Ϣ����
    */
    inline int  append(CwxMsgBlock* pMsg);
    /**
    @brief ���̵߳���Ϣ���л�ȡһ���Ŷ���Ϣ��������Ϊ�գ���������
    @param [out] pMsg pop����Ϣ��
    @return -1��ʧ�ܣ�>=0�������Ŷӵ���Ϣ����
    */
    inline int  pop(CwxMsgBlock*& pMsg);
private:
    ///ֹͣ�̳߳�
    void _stop();
    ///��ȡ��һ��thread�����
    static void* threadFunc(void *);

private:
    CwxAppFramework*        m_pApp;///<�ܹ���APP
    CwxMutexLock            m_lock;
    CwxAppTss**             m_arrTssEnv;///<�̵߳�tss
    CWX_UINT32              m_uiTheadDeathMsgWaterMask;///<�߳�death���Ķ�����Ϣ�Ŷӷ�ֵ
    CWX_UINT32              m_uiThreadDeathUpdateWaterMask;///<�߳�death�����߳���״̬���µ�ʱ�䷧ֵ
    CwxMsgQueue*         m_msgQueue; ///<��Ϣ����
    pthread_t*              m_tidArr;  ///<thead id������
};

CWINUX_END_NAMESPACE

#include "CwxAppThreadPool.inl"
#include "CwxPost.h"
#endif


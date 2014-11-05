#ifndef __CWX_APP_THREAD_POOL_MGR_H__
#define __CWX_APP_THREAD_POOL_MGR_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppThreadPoolMgr.h
@brief �̳߳ؼ����̵߳�TSS�Ĺ�������ʵ��
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
@brief �̳߳ؼ����̵߳�TSS�Ĺ������
*/
class CWX_API CwxAppThreadPoolMgr
{
public:
    ///���캯��
    CwxAppThreadPoolMgr();
    ///��������
    ~CwxAppThreadPoolMgr();
public:
    /**
    @brief �����������һ���̳߳�
    @param [in] unGroupId �̳߳ص��߳���ID
    @param [in] pThreadPool �̳߳ض���
    @return false��unGroupIdָ�����̳߳��Ѿ����ڣ� true���ɹ�
    */
    bool add(CWX_UINT16 unGroupId, CwxAppTpi* pThreadPool);
    /**
    @brief �ӹ�������ɾ��һ���̳߳�
    @param [in] unGroupId ɾ���̳߳ص��߳���ID
    @return false�������ڣ� true���ɹ�ɾ��
    */
    bool remove(CWX_UINT16 unGroupId);
    /**
    @brief ��������̳߳ص��߳�״̬�Ƿ�����
    @return false���������� true������
    */
    bool isValid();
    /**
    @brief ���ָ����unGroupId���߳����ڹ��������Ƿ����
    @return false�������ڣ� true���ɹ�ɾ��
    */
    bool isExist(CWX_UINT16 unGroupId);
    ///��ȡ������̳߳ص�����
    CWX_UINT16 getNum();
    /**
    @brief ���̳߳ع����������һ���̵߳�TSS
    @param [in] pTss �̵߳�TSS
    @return false�����TSS��GroupId��ThreadId��ͬ��Tss�Ѿ����ڣ� true���ɹ�
    */
    bool addTss(CwxAppTss* pTss);
    /**
    @brief ����������������̵߳�TSS
    @param [in] arrTss �����̵߳�TSS��arrTss[i]Ϊһ���߳�����̵߳�TSS����һ�������Ԫ�ذ�GroupId���򣬵ڶ�����ThreadId����
    @return void
    */
    void getTss(vector<vector<CwxAppTss*> >& arrTss);
    /**
    @brief ����ָ��Thread GroupId��TSS
    @param [in] unGroup �̵߳�GroupId
    @param [in] arrTss ���߳�����̵߳�TSS�����鰴���̵߳�ThreadId����
    @return void
    */
    void getTss(CWX_UINT16 unGroup, vector<CwxAppTss*>& arrTss);
    /**
    @brief ����һ���̵߳�Tss
    @param [in] unGroup �̵߳�GroupId
    @param [in] unThreadId �̵߳�ThreadId��
    @return NULL�������ڣ�����Ϊ�̵߳�TSS
    */
    CwxAppTss* getTss(CWX_UINT16 unGroup, CWX_UINT16 unThreadId);
private:
    CwxMutexLock        m_lock;///<thread lock for sync.
    map<CWX_UINT16, CwxAppTpi*>  m_threadPoolMap; ///<�̳߳ص�MAP
    map<CWX_UINT16, map<CWX_UINT16, CwxAppTss*> >  m_threadPoolTss;///�߳�Tss��map
};

CWINUX_END_NAMESPACE

#include "CwxPost.h"


#endif

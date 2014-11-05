#ifndef __CWX_APP_THREAD_POOL_EX_H__
#define __CWX_APP_THREAD_POOL_EX_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppThreadPoolEx.h
@brief ���Կ��Ƶ����̵߳��̳߳ض���ʵ��
@author cwinux@gmail.com
@version 0.1
@date 2009-07-20
@warning
@bug
*/

#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxMsgBlock.h"
#include "CwxAppMacro.h"
#include "CwxAppConfig.h"
#include "CwxAppTpi.h"
#include "CwxAppThread.h"
#include "CwxAppTss.h"


CWINUX_BEGIN_NAMESPACE

class CwxAppFramework;
/**
@class CwxAppThreadPoolEx
@brief ���Կ����̳߳�ÿ���̵߳��̳߳ء�
       ���̳߳ر������һ�������������߶��С�
*/
class CWX_API CwxAppThreadPoolEx:public CwxAppTpi
{
public:
    enum{
        DEATH_CHECK_MSG_WATER_MASK = 5, ///<�̵߳�״̬�����Ŷ���Ϣ����
        DEATH_CHECK_UPDATE_WATER_MASK = 30 ///<�߳�ʧЧ����״̬���µ�ʱ������
    };
public :
    ///���캯��
    CwxAppThreadPoolEx(CwxAppFramework* pApp,///<app����
        CWX_UINT16 unGroupId,///<�̳߳ص�thread-group
        CWX_UINT16 unThreadNum,///<�̳߳����̵߳�����
        CWX_UINT32 uiDeathCheckMsgWaterMask=DEATH_CHECK_MSG_WATER_MASK,///<�̵߳�״̬�����Ŷ���Ϣ����
        CWX_UINT32 uiDeathCheckUpdateWaterMask=DEATH_CHECK_UPDATE_WATER_MASK///<�߳�ʧЧ����״̬���µ�ʱ������
        );
    ///��������
    ~CwxAppThreadPoolEx();
public:
    /**
    @brief �����̳߳�
    @param [in] pThrEnv �̳߳ص��߳�Tss�����飬����ָ������ͨ���̵߳�onThreadCreated������
    @param [in] stack_size �̶߳�ջ�Ĵ�С����Ϊ0�������ϵͳĬ�ϴ�С��
    @return -1��ʧ�ܣ� 0���ɹ�
    */
    virtual int start(CwxAppTss** pThrEnv=NULL, size_t stack_size = 0);
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
    @brief ֪ͨ�̴߳���������Ҫ�����̶߳���
    @param [in] pApp �̵߳�APP��
    @param [in] unGroup �̵߳��߳��顣
    @param [in] unThreadId �߳����߳����е���š�
    @param [in] uiMsgWaterMask �߳������ļ����Ŷ���Ϣ�����ķ�ֵ��
    @param [in] uiUpdateWaterMask �߳������ļ����߳�״̬û����ʱ��ķ�ֵ��
    @return NULL��ʧ�ܣ� ����Ϊ�������̶߳���
    */
    virtual CwxAppThread* onCreateThread(CwxAppFramework* pApp, CWX_UINT16 unGroup, CWX_UINT16 unThreadId, CWX_UINT32 uiMsgWaterMask, CWX_UINT32 uiUpdateWaterMask);
public:
    ///��ȡ�̵߳���Ϣ�����Ŷ���Ϣ��
    inline size_t getQueuedMsgNum();
    ///��ȡ�̵߳���Ϣ�����Ŷ���Ϣ��
    inline size_t getQueuedMsgNum(CWX_UINT16 unThreadIndex);
    /**
    @brief ���̵߳���Ϣ�������һ������Ϣ��
    @param [in] pMsg append����Ϣ
    @param [in] uiThread ��Ϣ���̶߳��У��ڲ������Thread��������������������̡߳�
    @return -1��ʧ�ܣ�>=0Ϊ��Ӧ�̵߳Ķ������Ŷӵ���Ϣ����
    */
    inline int append(CwxMsgBlock* pMsg, CWX_UINT32 uiThread);
private:
    CwxAppFramework*        m_pApp;///<�ܹ���APP
    CwxAppThread**          m_arrThreadPool;///<�̵߳�����
    CWX_UINT32              m_uiTheadDeathMsgWaterMask;///<�߳�death���Ķ�����Ϣ�Ŷӷ�ֵ
    CWX_UINT32              m_uiThreadDeathUpdateWaterMask;///<�߳�death�����߳���״̬���µ�ʱ�䷧ֵ
};


CWINUX_END_NAMESPACE

#include "CwxAppThreadPoolEx.inl"
#include "CwxPost.h"

#endif


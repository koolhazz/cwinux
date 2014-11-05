#ifndef __CWX_CONDITION_H__
#define __CWX_CONDITION_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxCondition.h
@brief ʵ����Condition�Ľӿڡ�
@author cwinux@gmail.com
@version 0.1
@date 2010-07-10
@warning
@bug
*/

#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxMutexLock.h"
#include "CwxTimeValue.h"
CWINUX_BEGIN_NAMESPACE
/**
@class Condition
@brief Condition����
*/
class CWX_API CwxCondition
{
public:
    ///���캯��������һ���߳�������
    CwxCondition(CwxMutexLock &lock, pthread_condattr_t * attr=NULL);
    ///��������
    ~CwxCondition();
public:
    /**
    @brief ����ֱ����condition���ػ��߳�ʱ��
    @param [in] timeout ��ʱ��ʱ�䣬��ΪNULL��ʾ�־õĵȴ���
    @return -1��ʧ�ܣ����ǳ�ʱ����errnoΪETIMEDOUT�� 0���ɹ�
    */
    int wait (CwxTimeValue const *timeout = 0);
    /**
    @brief ֪ͨһ��thread��
    @return -1��ʧ�ܣ� 0���ɹ�
    */
    int signal (void);
    /**
    @brief ֪ͨ����thread��
    @return -1��ʧ�ܣ� 0���ɹ�
    */
    int broadcast(void);
    ///��ȡ��
    CwxMutexLock  &lock();
    ///��ȡ�ײ��condition
    pthread_cond_t* cond();
private:
    pthread_cond_t*  m_cond;///<condition����
    CwxMutexLock&    m_lock;
};


CWINUX_END_NAMESPACE
#include "CwxCondition.inl"
#include "CwxPost.h"
#endif


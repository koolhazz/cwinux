
CWINUX_BEGIN_NAMESPACE

///��ȡ�̵߳���Ϣ�����Ŷ���Ϣ��
inline size_t CwxAppThread::getQueuedMsgNum()
{
    return m_msgQueue->getMsgCount();
}
/**
@brief ���̵߳���Ϣ�������һ������Ϣ��
@param [in] pMsg append����Ϣ
@return -1��ʧ�ܣ�>=0�������Ŷӵ���Ϣ����
*/
inline int  CwxAppThread::append(CwxMsgBlock* pMsg)
{
    return this->m_msgQueue->enqueue_tail(pMsg);
}
/**
@brief ���̵߳���Ϣ���л�ȡһ���Ŷ���Ϣ��������Ϊ�գ���������
@param [out] pMsg pop����Ϣ��
@return -1��ʧ�ܣ�>=0�������Ŷӵ���Ϣ����
*/
inline int CwxAppThread::pop(CwxMsgBlock*& pMsg)
{
    return this->m_msgQueue->dequeue(pMsg);
}


///��ȡ�̵߳�group id
inline CWX_UINT16 CwxAppThread::getThreadId() const
{
    return m_unThreadId;
}
///��ȡ�������߳����е����
inline CWX_UINT16 CwxAppThread::getGroupId() const 
{ 
    return m_unGroupId;
}


inline int CwxAppThread::join(pthread_t thread, void **value_ptr)
{
    int result = ::pthread_join(thread, value_ptr);
    if (0 != result)
    {
        errno = result;
        result = -1;
        CWX_ERROR(("Failure to invoke pthread_join(), err-code=%d", errno));
    }
    return result;
}

inline int CwxAppThread::kill(pthread_t thread, int sig)
{
    int result = ::pthread_kill(thread, sig);
    if (0 != result)
    {
        errno = result;
        result = -1;
        CWX_ERROR(("Failure to invoke pthread_kill(), err-code=%d", errno));
    }
    return result;
}

inline pthread_t CwxAppThread::self()
{
    return pthread_self();
}

inline void CwxAppThread::exit(void *value_ptr)
{
    return pthread_exit(value_ptr);
}

inline bool CwxAppThread::equal(pthread_t t1, pthread_t t2)
{
    return pthread_equal(t1, t2) != 0;
}


inline int CwxAppThread::cancel(pthread_t thread)
{
    int result = ::pthread_cancel(thread);
    if (0 != result)
    {
        errno = result;
        result = -1;
        CWX_ERROR(("Failure to invoke pthread_cancel(), err-code=%d", errno));
    }
    return result;
}


CWINUX_END_NAMESPACE


#ifdef WITH_CWINUX_THRIFT
CWINUX_BEGIN_NAMESPACE

///�رն��У�ͬʱ�ͷ�������Ϣ��-1��ʧ�ܣ�>=0�������е���Ϣ����
inline int CwxMsgQueueThrift::close()
{
  CwxMutexGuard<CwxMutexLock> guard(&this->m_lock);
  _deactivate();
  return _flush();
}
///ֻ�ͷŶ����е�������Ϣ��-1��ʧ�ܣ�>=0�������е���Ϣ����
inline int CwxMsgQueueThrift::flush (void)
{
  CwxMutexGuard<CwxMutexLock> guard(&this->m_lock);
  return _flush();
}

///�������Ƿ�full
inline bool CwxMsgQueueThrift::isFull (void)
{
  CwxMutexGuard<CwxMutexLock> guard(&this->m_lock);
  return _isFull();
}
///�������Ƿ��.
inline bool CwxMsgQueueThrift::isEmpty(void)
{
  CwxMutexGuard<CwxMutexLock> guard(&this->m_lock);
  return _isEmpty();
}

///��ȡ��Ϣ������.
inline size_t CwxMsgQueueThrift::getMsgCount(void)
{
  return m_curCount;
}


inline int CwxMsgQueueThrift::deactivate (void)
{
  CwxMutexGuard<CwxMutexLock> guard(&this->m_lock);
  return _deactivate();
}

inline int CwxMsgQueueThrift::activate (void)
{
  CwxMutexGuard<CwxMutexLock> guard(&this->m_lock);
  return _activate();
}

inline int CwxMsgQueueThrift::getState (void)
{
  return m_state;
}

inline bool CwxMsgQueueThrift::isDeactived(void)
{
  return m_state == DEACTIVATED;
}

inline bool CwxMsgQueueThrift::isActivate(void)
{
  return m_state == ACTIVATED;
}

/// ��ȡ��.
inline CwxMutexLock& CwxMsgQueueThrift::lock()
{
  return m_lock;
}


inline int CwxMsgQueueThrift::_deactivate(void)
{
  int const previous_state = this->m_state;
  if (this->m_state != DEACTIVATED)
  {
    // Wakeup all waiters.
    this->m_notEmptyCond.broadcast();
    this->m_notFullCond.broadcast();
    this->m_state = DEACTIVATED;
  }
  return previous_state;
}

inline int CwxMsgQueueThrift::_activate(void)
{
  int const previous_state = this->m_state;
  this->m_state = ACTIVATED;
  return previous_state;

}

inline int CwxMsgQueueThrift::_flush(void)
{
  int number_flushed = m_curCount;
  m_tasks.clear();
  m_curCount = 0;
  return number_flushed;
}

///�������Ƿ�full
inline bool CwxMsgQueueThrift::_isFull (void)
{
  return m_curCount >= m_maxCount;
}
///�������Ƿ��.
inline bool CwxMsgQueueThrift::_isEmpty(void)
{
  return m_tasks.begin() == m_tasks.end();
}

inline int CwxMsgQueueThrift::_waitNotFullCond(CwxTimeValue *timeout)
{
  // Wait while the queue is full.
  while (this->_isFull())
  {
    if (this->m_notFullCond.wait(timeout) == -1)
    {
      return -1;
    }
    if (this->m_state != ACTIVATED)
    {
      return -1;
    }
  }
  return 0;

}

///�ȴ�������Ϣ
inline int CwxMsgQueueThrift::_waitNotEmptyCond(CwxTimeValue *timeout)
{
  // Wait while the queue is full.
  while (this->_isEmpty())
  {
    if (this->m_notEmptyCond.wait(timeout) == -1)
    {
      return -1;
    }
    if (this->m_state != ACTIVATED)
    {
      return -1;
    }
  }
  return 0;
}


// = Disallow copying and assignment.
inline CwxMsgQueueThrift::CwxMsgQueueThrift (const CwxMsgQueueThrift &)
  :m_notEmptyCond(m_lock),m_notFullCond(m_lock)
{
}

inline CwxMsgQueueThrift& CwxMsgQueueThrift::operator= (const CwxMsgQueueThrift &)
{
  return *this;
}


///��ȡ�̵߳���Ϣ�����Ŷ���Ϣ��
inline size_t CwxThreadThrift::getQueuedMsgNum()
{
  return m_msgQueue->getMsgCount();
}
/**
@brief ���̵߳���Ϣ�������һ������Ϣ��
@param [in] pMsg append����Ϣ
@return -1��ʧ�ܣ�>=0�������Ŷӵ���Ϣ����
*/
inline int  CwxThreadThrift::append(boost::shared_ptr<Runnable> task)
{
  return this->m_msgQueue->enqueue_tail(task);
}

inline int  CwxThreadThrift::appendHead(boost::shared_ptr<Runnable> task)
{
  return this->m_msgQueue->enqueue(task);
}

/**
@brief ���̵߳���Ϣ���л�ȡһ���Ŷ���Ϣ��������Ϊ�գ���������
@param [out] pMsg pop����Ϣ��
@return -1��ʧ�ܣ�>=0�������Ŷӵ���Ϣ����
*/
inline int CwxThreadThrift::pop(boost::shared_ptr<Runnable>& task)
{
  return this->m_msgQueue->dequeue(task);
}

///��ȡ�̵߳�group id
inline CWX_UINT16 CwxThreadThrift::getThreadId() const
{
  return m_unThreadId;
}


inline size_t CwxThreadPoolThrift::getQueuedMsgNum()
{ 
    return m_msgQueue->getMsgCount();
}

inline int CwxThreadPoolThrift::append(boost::shared_ptr<Runnable> task)
{
    return m_msgQueue->enqueue_tail(task);
}

inline int CwxThreadPoolThrift::appendHead(boost::shared_ptr<Runnable> task)
{
    return m_msgQueue->enqueue(task);
}

inline int CwxThreadPoolThrift::pop(boost::shared_ptr<Runnable> &task)
{
    return m_msgQueue->dequeue(task);
}

CWINUX_END_NAMESPACE

#endif


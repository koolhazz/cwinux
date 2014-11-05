
CWINUX_BEGIN_NAMESPACE

inline size_t CwxAppThreadPoolEx::getQueuedMsgNum()
{
    size_t num = 0;
    for (CWX_UINT16 i=0; i<getThreadNum(); i++){
        if (m_arrThreadPool && m_arrThreadPool[i]) {
            num += m_arrThreadPool[i]->getQueuedMsgNum();
        }
    }
    return num;
}
///��ȡ�̵߳���Ϣ�����Ŷ���Ϣ��
inline size_t CwxAppThreadPoolEx::getQueuedMsgNum(CWX_UINT16 unThreadIndex)
{
    if (!m_arrThreadPool || (unThreadIndex >= getThreadNum())) return 0;
    return m_arrThreadPool[unThreadIndex]->getQueuedMsgNum();
}

/**
@brief ���̵߳���Ϣ�������һ������Ϣ��
@param [in] pMsg append����Ϣ
@param [in] uiThread ��Ϣ���̶߳��У��ڲ������Thread��������������������̡߳�
@return -1��ʧ�ܣ�>=0Ϊ��Ӧ�̵߳Ķ������Ŷӵ���Ϣ����
*/
inline int CwxAppThreadPoolEx::append(CwxMsgBlock* pMsg, CWX_UINT32 uiThread)
{
    CWX_UINT16 uiIndex = uiThread%getThreadNum();
    return m_arrThreadPool[uiIndex]->append(pMsg);
}


CWINUX_END_NAMESPACE


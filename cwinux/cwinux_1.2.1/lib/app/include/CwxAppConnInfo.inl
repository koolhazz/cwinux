
CWINUX_BEGIN_NAMESPACE

inline CWX_UINT32 CwxAppConnInfo::getSvrId() const 
{
    return m_uiSvrId;
}

inline void CwxAppConnInfo::setSvrId(CWX_UINT32 uiSvrId)
{
    m_uiSvrId = uiSvrId;
}

///��ȡ���ӵ�HOST-ID
inline CWX_UINT32 CwxAppConnInfo::getHostId() const 
{
    return m_uiHostId;
}

inline void CwxAppConnInfo::setHostId(CWX_UINT32 uiHostId)
{
    m_uiHostId = uiHostId;
}
///��ȡ���ӵ�����ID
inline CWX_UINT32 CwxAppConnInfo::getConnId() const 
{
    return m_uiConnId;
}
///�������ӵ�����ID
inline void CwxAppConnInfo::setConnId(CWX_UINT32 uiConnId)
{
    m_uiConnId = uiConnId;
}
///���ñ������ӵ�Listen ID
inline CWX_UINT32 CwxAppConnInfo::getListenId() const 
{
    return m_uiListenId;
}
inline void CwxAppConnInfo::setListenId(CWX_UINT32 uiListenId)
{
    m_uiListenId = uiListenId;
}


///��ȡ���ӵ�״̬
inline CWX_UINT16 CwxAppConnInfo::getState() const
{
    return m_unState;
}
inline void CwxAppConnInfo::setState(CWX_UINT16 unState)
{
    m_unState = unState;
}

///��ȡ���ӵĴ���ʱ��
inline time_t CwxAppConnInfo::getCreateTime() const 
{
    return m_ttCreateTime;
}
inline void CwxAppConnInfo::setCreateTime(time_t ttTime)
{
    m_ttCreateTime = ttTime;
}

///��ȡ��������ʧ�ܵĴ���
inline CWX_UINT32 CwxAppConnInfo::getFailConnNum() const
{
    return m_uiFailConnNum;
}
///��������ʧ�����Ӵ���
inline void CwxAppConnInfo::setFailConnNum(CWX_UINT32 uiNum)
{
    m_uiFailConnNum = uiNum;
}
///��������ʧ�����Ӵ���
inline CWX_UINT32 CwxAppConnInfo::incFailConnNum()
{
    m_uiFailConnNum++;
    return m_uiFailConnNum;
}

///��ȡʧЧ����������С������ʱ����
inline CWX_UINT16 CwxAppConnInfo::getMinRetryInternal() const 
{
    return m_unMinRetryInternal;
}
inline void CwxAppConnInfo::setMinRetryInternal(CWX_UINT16 unInternal)
{
    m_unMinRetryInternal = unInternal;
}

///��ȡʧЧ�����������������ʱ����
inline CWX_UINT16 CwxAppConnInfo::getMaxRetryInternal() const 
{
    return m_unMaxRetryInternal;
}
inline void CwxAppConnInfo::setMaxRetryInternal(CWX_UINT16 unInternal)
{
    m_unMaxRetryInternal = unInternal;
}

///��ȡ�����Ƿ�Ϊ��������
inline bool CwxAppConnInfo::isActiveConn() const 
{
    return m_bActiveConn;
}
inline void CwxAppConnInfo::setActiveConn(bool bActive)
{
    m_bActiveConn = bActive;
}

///��ȡ�����Ƿ������ر�
inline bool CwxAppConnInfo::isActiveClose() const 
{
    return m_bActiveClose;
}
inline void CwxAppConnInfo::setActiveClose(bool bActive)
{
    m_bActiveClose = bActive;
}


///��ȡ���ӵ����ݰ��Ƿ��а�ͷ
inline bool CwxAppConnInfo::isRawData() const 
{
    return m_bRawData;
}
inline void CwxAppConnInfo::setRawData(bool bRaw)
{
    m_bRawData = bRaw;
}

///��ȡ�ް�ͷ���ӵ����ݽ���BUF
inline CWX_UINT32  CwxAppConnInfo::getRawRecvLen() const
{
    return m_uiRawRecvLen;
}
inline void CwxAppConnInfo::setRawRecvLen(CWX_UINT32 uiLen)
{
    m_uiRawRecvLen = uiLen;
}

///��ȡ�����Ƿ���Ҫ�������KEEP-ALIVE
inline bool CwxAppConnInfo::isKeepalive() const 
{
    return m_bKeepAlive;
}
inline void CwxAppConnInfo::setKeepalive(bool bKeepAlive)
{
    m_bKeepAlive = bKeepAlive;
}

///��ȡ���������յ���Ϣ��ʱ��
inline time_t  CwxAppConnInfo::getLastRecvMsgTime() const 
{
    return m_ttLastRecvMsgTime;
}
inline void CwxAppConnInfo::setLastRecvMsgTime(time_t ttTime)
{
    m_ttLastRecvMsgTime = ttTime;
}

///��ȡ�������·�����Ϣ��ʱ��
inline time_t  CwxAppConnInfo::getLastSendMsgTime() const 
{
    return m_ttLastSendMsgTime;
}
inline void CwxAppConnInfo::setLastSendMsgTime(time_t ttTime)
{
    m_ttLastSendMsgTime = ttTime;
}

///��ȡKEEP-ALIVE�������·���KEEP-ALIVE��ʱ��
inline time_t  CwxAppConnInfo::getKeepAliveSendTime() const
{
    return m_ttKeepAliveSendTime;
}
inline void CwxAppConnInfo::setKeepAliveSendTime(time_t ttTime)
{
    m_ttKeepAliveSendTime = ttTime;
}

///��ȡ�Ƿ��յ������ӵ�KEEP-ALIVE�ظ�
inline bool CwxAppConnInfo::isKeepAliveReply() const
{
    return m_bKeepAliveReply;
}
inline void CwxAppConnInfo::setKeepAliveReply(bool bReply)
{
    m_bKeepAliveReply = bReply;
}

///��ȡ���ӵ��û�����
inline void*  CwxAppConnInfo::getUserData() const
{
    return  m_pUserData;
}
///�������ӵ��û�����
inline void CwxAppConnInfo::setUserData(void* userData)
{
    m_pUserData = userData;
}
///��ȡ���ӵ�Э���������
inline CwxAppPai* CwxAppConnInfo::getPai()
{
    return m_pPai;
}
///�������ӵ�Э���������
inline void CwxAppConnInfo::setPai(CwxAppPai* pAdapter)
{
    m_pPai = pAdapter;
}

///��ȡ���ӵȴ����͵������Ϣ��������0��ʾû������
inline CWX_UINT32 CwxAppConnInfo::getMaxWaitingMsgNum() const
{
    return m_uiMaxWaitingMsgNum;
}
///�����������ĵȴ����͵���Ϣ������Ĭ��0��ʾû������
inline void CwxAppConnInfo::setMaxWaitingMsgNum(CWX_UINT32 uiNum)
{
    m_uiMaxWaitingMsgNum = uiNum;
}
///�ж��Ƿ����Ӵ����Ͷ�������
inline bool CwxAppConnInfo::isWaitingMsgQueueFull() const
{
    return m_uiMaxWaitingMsgNum && (m_uiMaxWaitingMsgNum <= m_uiWaitingMsgNum);
}


///��ȡ���ӵȴ����͵���Ϣ������
inline CWX_UINT32 CwxAppConnInfo::getWaitingMsgNum() const
{
    return m_uiWaitingMsgNum;
}
///�������ӵȴ����͵���Ϣ������
inline void CwxAppConnInfo::setWaitingMsgNum(CWX_UINT32 uiNum)
{
    m_uiWaitingMsgNum = uiNum;
}
///�������ӵȴ����͵���Ϣ������
inline CWX_UINT32 CwxAppConnInfo::incWaitingMsgNum()
{
    m_uiWaitingMsgNum++;
    return m_uiWaitingMsgNum;
}
///�������ӵȴ����͵���Ϣ������
inline CWX_UINT32 CwxAppConnInfo::decWaitingMsgNum()
{
    if (m_uiWaitingMsgNum) m_uiWaitingMsgNum--;
    return m_uiWaitingMsgNum;
}

///��ȡ�����Ѿ��������յ�����Ϣ��������
inline CWX_UINT32 CwxAppConnInfo::getContinueRecvNum() const
{
    return m_uiContinueRecvNum;
}
inline void CwxAppConnInfo::setContinueRecvNum(CWX_UINT32 uiNum)
{
    m_uiContinueRecvNum = uiNum;
}
///��ȡ�������͵���Ϣ����
inline CWX_UINT32 CwxAppConnInfo::getContinueSendNum() const
{
    return m_uiContinueSendNum;
}
///�����������͵���Ϣ����
inline void CwxAppConnInfo::setContinueSendNum(CWX_UINT32 uiNum)
{
    m_uiContinueSendNum = uiNum;
}


///�ж϶Ͽ��������Ƿ���Ҫ����
inline bool CwxAppConnInfo::isNeedReconnect() const 
{
    return !m_bActiveClose && m_bActiveConn;
}


///�Ƿ����CwxAppFramework::onCreate
inline bool CwxAppConnInfo::isInvokeCreate() const
{
    return m_bInvokeCreate;
}
///�����Ƿ����CwxAppFramework::onCreate
inline void CwxAppConnInfo::setInvokeCreate(bool bInvoke)
{
    m_bInvokeCreate = bInvoke;
}

///�Ƿ���������
inline bool CwxAppConnInfo::isReconn() const
{
    return m_bReconn;
}
///�����Ƿ�����
inline void CwxAppConnInfo::setReconn(bool bReconnect)
{
    m_bReconn = bReconnect;
}
///��ȡ����������ʱ�ĺ�����
inline CWX_UINT32 CwxAppConnInfo::getReconnDelay() const
{
    return m_uiReconnDelay;
}
///��������������ʱ�ĺ�����
inline void CwxAppConnInfo::setReconnDelay(CWX_UINT32 uiDelay)
{
    m_uiReconnDelay = uiDelay;
}


///��ȡ���Ӷ�Ӧ��handler
inline CwxAppHandler4Msg* CwxAppConnInfo::getHandler()
{
    return m_pHandler;
}
///�������Ӷ�Ӧ��handler
inline void CwxAppConnInfo::setHandler(CwxAppHandler4Msg*  pHandler)
{
    m_pHandler = pHandler;
}


inline void CwxAppConnInfo::reset()
{
    m_bActiveClose = false;
    m_uiWaitingMsgNum = 0;
    m_uiMaxWaitingMsgNum = 0;
    m_uiContinueRecvNum = 0;
    m_uiContinueSendNum = 0;
    m_bInvokeCreate = true;
    m_bReconn = false;
    m_uiReconnDelay = 0;
}

///��ȡparent
inline CwxAppHostInfo* CwxAppConnInfo::getParent()
{
    return m_parent;
}
///����parent
inline void CwxAppConnInfo::setParent(CwxAppHostInfo* parent)
{
    m_parent = parent;
}




///Get Svr id
inline CWX_UINT32 CwxAppHostInfo::getSvrId() const
{
    return m_uiSvrId;
}
///Get host id
inline CWX_UINT32 CwxAppHostInfo::getHostId() const
{
    return m_uiHostId;
}
///Get conn nun
inline CWX_UINT32 CwxAppHostInfo::getConnNum() const
{
    return m_hostConn.size();
}
///��ȡ�Ƿ��ܹ�������Ϣ
inline bool CwxAppHostInfo::isEnableSendMsg() const
{
    CWX_UINT32 uiSize = m_hostConn.size();
    for (CWX_UINT32 i=0; i<uiSize; i++)
    {
        if (!m_hostConn[i]->isWaitingMsgQueueFull()) return true;
        CWX_DEBUG(("Connection is full, svr_id=%u, host_id=%u, conn_id=%u, msg_num=%u", 
            m_hostConn[i]->getSvrId(),
            m_hostConn[i]->getHostId(),
            m_hostConn[i]->getConnId(),
            m_hostConn[i]->getWaitingMsgNum()));

    }
    return false;
}

///Get WaitMsgNum() 
inline CWX_UINT32 CwxAppHostInfo::getWaitingMsgNum() const
{
    return m_uiWaitingMsgNum;
}
///Get SndMsgNum
inline CWX_UINT64 CwxAppHostInfo::getSndMsgNum() const
{
    return m_ullSndMsgNum;
}
///Get RecvMsgNum
inline CWX_UINT64 CwxAppHostInfo::getRecvMsgNum() const
{
    return m_ullRecvMsgNum;
}
///get RecentSndMsgNum
inline CWX_UINT32 CwxAppHostInfo::getRecentSndMsgNum() const
{
    return m_uiRecentSndMsgNum;
}
///get RecentRecvMsgNum
inline CWX_UINT32 CwxAppHostInfo::getRecentRecvMsgNum() const
{
    return m_uiRecentRecvMsgNum;
}
///get RecentClosedCount
inline CWX_UINT32 CwxAppHostInfo::getRecentClosedCount() const
{
    return m_uiRecentClosedCount;
}
///select connection for send msg
inline CwxAppConnInfo* CwxAppHostInfo::selectConn()
{
    CWX_UINT32 uiSize = m_hostConn.size();
    if (uiSize)
    {
        m_uiRand ++;
        CWX_UINT32 uiStart = m_uiRand % uiSize;
        CWX_UINT32 uiPos = uiStart;
        do
        {
            if (!m_hostConn[uiPos]->isWaitingMsgQueueFull()) return m_hostConn[uiPos];
            CWX_DEBUG(("Connection is full, svr_id=%u, host_id=%u, conn_id=%u, msg_num=%u", 
                m_hostConn[uiPos]->getSvrId(),
                m_hostConn[uiPos]->getHostId(),
                m_hostConn[uiPos]->getConnId(),
                m_hostConn[uiPos]->getWaitingMsgNum()));
            uiPos++;
            if (uiPos == uiSize) uiPos = 0;
        }while(uiPos != uiStart);
    }
    return NULL;
}
///Get parent
inline CwxAppSvrInfo * CwxAppHostInfo::getParent()
{
    return   m_parent;
}
///Get host's valid connection
inline vector<CwxAppConnInfo*>* CwxAppHostInfo::GetHostConn()
{
    return &m_hostConn;
}

///���һ����Ч����������
inline void CwxAppHostInfo::addConn(CwxAppConnInfo* conn)
{
    m_hostConn.push_back(conn);
}
///�Ƴ�һ����������
inline void CwxAppHostInfo::removeConn(CwxAppConnInfo* conn)
{
    m_hostConn.erase(find(m_hostConn.begin(), m_hostConn.end(), conn));
}
///֪ͨ����������һ����Ϣ
inline void CwxAppHostInfo::sendOneMsg()
{
    m_ullSndMsgNum++;
    m_uiRecentSndMsgNum++;
    if (m_uiWaitingMsgNum) m_uiWaitingMsgNum--;
}
///֪ͨ�������յ�һ��Ҫ���͵���Ϣ
inline void CwxAppHostInfo::recvOneMsg()
{
    m_ullRecvMsgNum++;
    m_uiRecentRecvMsgNum++;
}
///֪ͨ��������һ���Ŷӷ��͵���Ϣ
inline void CwxAppHostInfo::waitingOneMsg()
{
    m_uiWaitingMsgNum++;
}
///���������ĸ���
inline void CwxAppHostInfo::calcHostLoad()
{
    CWX_UINT32 i=0;
    m_uiWaitingMsgNum = 0;
    for (i=0; i<m_hostConn.size(); i++){
        m_uiWaitingMsgNum += m_hostConn[i]->getWaitingMsgNum();
    }
    m_uiRecentSndMsgNum /= 6;
    m_uiRecentRecvMsgNum /=6;
    if (m_uiRecentRecvMsgNum > m_uiRecentSndMsgNum)
    {
        m_uiRecentRecvMsgNum = m_uiRecentSndMsgNum;
    }
    m_uiRecentClosedCount /= 6;
}


///Get svr id
inline CWX_UINT32 CwxAppSvrInfo::getSvrId() const
{
    return m_uiSvrId;
}
///Get HostNum
inline CWX_UINT32 CwxAppSvrInfo::getHostNum() const
{
    return m_svrHost.size();
}
///ѡ��һ̨������������Ϣ�ķ���
inline CwxAppHostInfo* CwxAppSvrInfo::selectHost()
{
    CWX_UINT32 uiSize = m_svrHost.size();
    if (uiSize)
    {
        CWX_UINT32 start = m_uiRand%uiSize;
        CWX_UINT32 pos = start;
        m_uiRand++;
        do 
        {
            if (m_svrHost[pos]->isEnableSendMsg()) return m_svrHost[pos];
            pos++;
            if (pos>=uiSize) pos=0;
        } while(pos != start);
    }
    return NULL;
}
///��ȡsvr�µ������б�
inline vector<CwxAppHostInfo*>& CwxAppSvrInfo::getHosts()
{
    return m_svrHost;
}

///����һ̨������
inline void CwxAppSvrInfo::addHost(CwxAppHostInfo* host)
{
    m_svrHost.push_back(host);
}
///���¼���svr�²�ͬ�����ĸ���
inline void CwxAppSvrInfo::calcHostLoad()
{
    for (CWX_UINT32 i=0; i<m_svrHost.size(); i++)
        m_svrHost[i]->calcHostLoad();
}



CWINUX_END_NAMESPACE


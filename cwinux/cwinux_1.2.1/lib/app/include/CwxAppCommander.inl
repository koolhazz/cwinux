
CWINUX_BEGIN_NAMESPACE

//0:success, -1: not unique
inline int CwxAppCommander::regHandle(CWX_UINT32 uiSvrID, CwxAppCmdOp* pHandle)
{
    CWX_ASSERT(pHandle != NULL);
    if (this->getEventOp(uiSvrID)) return -1;
    this->m_msgHash[uiSvrID] = pHandle;
    return 0;

}
//true: has object to accept the msg,
//false: no object to accept the msg
inline bool CwxAppCommander::dispatch(CwxMsgBlock*& msg, CwxAppTss* pThrEnv, int& iRet)
{
    CwxAppCmdOp* pHandle = getEventOp(msg->event().getSvrId());
    if (!pHandle) return false;
    if (msg->event().getEvent() < CwxEventInfo::SYS_EVENT_NUM)
    {
        if (m_arrEvent[msg->event().getEvent()])
        {
            iRet = (*m_arrEvent[msg->event().getEvent()])(pHandle, msg, pThrEnv);
        }
        else
        {
            iRet = 0;
        }
    }
    else
    {
        iRet = (*m_arrEvent[CwxEventInfo::SYS_EVENT_NUM])(pHandle, msg, pThrEnv);
    }
    return true;
}


inline CwxAppCmdOp* CwxAppCommander::getEventOp(CWX_UINT32 uiSvrID)
{
    CwxEventCommandHash::iterator iter = this->m_msgHash.find(uiSvrID);
    if (iter != this->m_msgHash.end())
    {
        return iter->second;
    }
    return NULL;
}


CWINUX_END_NAMESPACE



#include "CwxMproxyRecvHandler.h"
#include "CwxMproxyApp.h"
#include "CwxMqPoco.h"

///echo请求的处理函数
int CwxMproxyRecvHandler::onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
{
    CwxMproxyTask* pTask = NULL;
    CwxMqTss* pTss = (CwxMqTss*)pThrEnv;
    bool* bAuth = (bool*)msg->event().getConnUserData();
    int iRet = CWX_MQ_SUCCESS;
    char const* user=NULL;
    char const* passwd=NULL;
    CWX_UINT32 uiTaskId = 0;
    do{
        ///binlog数据接收消息
        if (CwxMqPoco::MSG_TYPE_RECV_DATA == msg->event().getMsgHeader().getMsgType())
        {
            CWX_UINT32 uiGroup;
            CWX_UINT32 uiType;
            CWX_UINT32 uiAttr;
            CwxKeyValueItem const* pData;
            if (CWX_MQ_SUCCESS != (iRet = CwxMqPoco::parseRecvData(pTss,
                msg,
                pData,
                uiGroup,
                uiType,
                uiAttr,
                user,
                passwd,
                pTss->m_szBuf2K)))
            {
                //如果是无效数据，返回
                CWX_DEBUG(("Failure to parse the recieve msg, err=%s", pTss->m_szBuf2K));
                break;
            }
            iRet = isAuth(pTss, uiGroup, user, passwd);
            if (CWX_MQ_SUCCESS != iRet) break;
            *bAuth = true;
            CwxMsgBlock* sndMsg = NULL;
            uiTaskId = m_pApp->getNextTaskId();
            if (CWX_MQ_SUCCESS != CwxMqPoco::packRecvData(pTss,
                sndMsg,
                uiTaskId,
                *pData,
                uiGroup,
                uiType,
                uiAttr,
                m_pApp->getConfig().m_mq.getUser().c_str(),
                m_pApp->getConfig().m_mq.getPasswd().c_str(),
                pTss->m_szBuf2K))
            {
                CWX_ERROR((pTss->m_szBuf2K));
                break;
            }
            pTask = new CwxMproxyTask(m_pApp, &m_pApp->getTaskBoard());
            pTask->m_sndMsg = sndMsg;
            pTask->setTaskId(uiTaskId);
            pTask->m_uiMsgTaskId = msg->event().getMsgHeader().getTaskId();
            pTask->m_uiReplyConnId = msg->event().getConnId();
            pTask->execute(pTss);
            return 1;
        }
        else if(CwxMqPoco::MSG_TYPE_RECV_COMMIT == msg->event().getMsgHeader().getMsgType())
        {
            if (CWX_MQ_SUCCESS != CwxMqPoco::parseCommit(pTss,
                msg,
                user,
                passwd,
                pTss->m_szBuf2K))
            {
                //如果是无效数据，返回
                CWX_DEBUG(("Failure to parse the commit msg, err=%s", pTss->m_szBuf2K));
                iRet = CWX_MQ_INVALID_MSG;
                break;
            }
            if (!*bAuth)
            {
                CwxCommon::snprintf(pTss->m_szBuf2K, 2048, "Failure to auth user[%s] passwd[%s]", user, passwd);
                iRet = CWX_MQ_PROXY_NO_AUTH;
                break;
            }
            CwxMsgBlock* sndMsg = NULL;
            uiTaskId = m_pApp->getNextTaskId();
            if (CWX_MQ_SUCCESS != (iRet = CwxMqPoco::packCommit(pTss,
                sndMsg,
                uiTaskId,
                m_pApp->getConfig().m_mq.getUser().c_str(),
                m_pApp->getConfig().m_mq.getPasswd().c_str(),
                pTss->m_szBuf2K)))
            {
                CWX_ERROR((pTss->m_szBuf2K));
                break;
            }
            pTask = new CwxMproxyTask(m_pApp, &m_pApp->getTaskBoard());
            pTask->setTaskId(uiTaskId);
            pTask->m_sndMsg = sndMsg;
            pTask->m_uiMsgTaskId = msg->event().getMsgHeader().getTaskId();
            pTask->m_uiReplyConnId = msg->event().getConnId();
            pTask->execute(pTss);
            return 1;
        }
        else
        {
            CwxCommon::snprintf(pTss->m_szBuf2K, 2047, "Invalid msg type:%u", msg->event().getMsgHeader().getMsgType());
            CWX_ERROR((pTss->m_szBuf2K));
            iRet = CWX_MQ_INVALID_MSG_TYPE;
            break;
        }
    }while(0);

    CwxMsgBlock* pBlock = NULL;
    if (CwxMqPoco::MSG_TYPE_RECV_COMMIT==msg->event().getMsgHeader().getMsgType())
    {
        if (CWX_MQ_SUCCESS != CwxMqPoco::packCommitReply(pTss,
            pBlock,
            msg->event().getMsgHeader().getTaskId(),
            iRet,
            pTss->m_szBuf2K,
            pTss->m_szBuf2K))
        {
            CWX_ERROR(("Failure to pack commit reply msg, err=%s", pTss->m_szBuf2K));
            m_pApp->noticeCloseConn(msg->event().getConnId());
            return 1;
        }
    }
    else
    {
        if (CWX_MQ_SUCCESS != CwxMqPoco::packRecvDataReply(pTss,
            pBlock,
            msg->event().getMsgHeader().getTaskId(),
            iRet,
            0,
            pTss->m_szBuf2K,
            pTss->m_szBuf2K))
        {
            CWX_ERROR(("Failure to pack mq reply msg, err=%s", pTss->m_szBuf2K));
            m_pApp->noticeCloseConn(msg->event().getConnId());
            return 1;
        }
    }
    reply(m_pApp, pBlock, msg->event().getConnId());
    return 1;
}

void CwxMproxyRecvHandler::reply(CwxMproxyApp* app, CwxMsgBlock* msg, CWX_UINT32 uiConnId)
{
    msg->send_ctrl().setConnId(uiConnId);
    msg->send_ctrl().setSvrId(CwxMproxyApp::SVR_TYPE_RECV);
    msg->send_ctrl().setHostId(0);
    msg->send_ctrl().setMsgAttr(CwxMsgSendCtrl::NONE);
    if (0 != app->sendMsgByConn(msg))
    {
        CWX_ERROR(("Failure to reply error msg"));
        CwxMsgBlockAlloc::free(msg);
        app->noticeCloseConn(uiConnId);
    }
}

int CwxMproxyRecvHandler::onConnClosed(CwxMsgBlock*& msg, CwxAppTss*)
{
    delete ((bool*)(msg->event().getConnUserData()));
    return 1;
}

int CwxMproxyRecvHandler::onTimeoutCheck(CwxMsgBlock*& , CwxAppTss* pThrEnv)
{
    list<CwxAppTaskBoardTask*> tasks;
    m_pApp->getTaskBoard().noticeCheckTimeout(pThrEnv, tasks);
    if (!tasks.empty())
    {
        list<CwxAppTaskBoardTask*>::iterator iter=tasks.begin();
        (*iter)->execute(pThrEnv);
        iter++;
    }
    return 1;
}

CWX_UINT32 CwxMproxyRecvHandler::isAuth(CwxMqTss* pTss, CWX_UINT32 uiGroup, char const* user, char const* passwd)
{
    CwxMqIdRange id(uiGroup, uiGroup);
    if (m_pApp->getConfig().m_allowGroup.size())
    {///group必须在允许的group范围内
        if (m_pApp->getConfig().m_allowGroup.find(id) == m_pApp->getConfig().m_allowGroup.end())
        {
            CwxCommon::snprintf(pTss->m_szBuf2K, 2047, "group[%u] is not allowed.", uiGroup);
            return CWX_MQ_PROXY_NO_AUTH_GROUP;
        }
    }
    else if (m_pApp->getConfig().m_denyGroup.size())
    {///是否在被禁止的group范围内
        if (m_pApp->getConfig().m_denyGroup.find(id) != m_pApp->getConfig().m_denyGroup.end())
        {
            CwxCommon::snprintf(pTss->m_szBuf2K, 2047, "group[%u] is forbiden.", uiGroup);
            return CWX_MQ_PROXY_FORBID_GROUP;
        }
    }
    map<CwxMqIdRange, CwxMqConfigQueue>::const_iterator iter_pass = m_pApp->getConfig().m_groupPasswd.find(id);
    if (iter_pass != m_pApp->getConfig().m_groupPasswd.end())
    {
        if (iter_pass->second.m_strUser.length())
        {
            if ((iter_pass->second.m_strUser != user) ||
                (iter_pass->second.m_strPasswd != passwd))
            {
                CwxCommon::snprintf(pTss->m_szBuf2K, 2048, "Failure to auth user[%s] passwd[%s]", user, passwd);
                return CWX_MQ_PROXY_NO_AUTH;
            }
        }
    }
    else
    {
        if (m_pApp->getConfig().m_recv.getUser().length())
        {
            if ((m_pApp->getConfig().m_recv.getUser() != user) ||
                (m_pApp->getConfig().m_recv.getPasswd() != passwd))
            {
                CwxCommon::snprintf(pTss->m_szBuf2K, 2048, "Failure to auth user[%s] passwd[%s]", user, passwd);
                return CWX_MQ_PROXY_NO_AUTH;
            }
        }
    }
    return CWX_MQ_SUCCESS;
}

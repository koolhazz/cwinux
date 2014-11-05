#include "CwxAppConnInfo.h"
#include "CwxAppPai.h"
CWINUX_BEGIN_NAMESPACE
CwxAppConnInfo::CwxAppConnInfo()
{
    m_uiSvrId = 0;
    m_uiHostId = 0;
    m_uiConnId = 0;
    m_uiListenId = 0;
    m_unState = IDLE;
    m_ttCreateTime = time(NULL);
    m_uiFailConnNum = 0;
    m_unMinRetryInternal = 1;
    m_unMaxRetryInternal = 60;
    m_bActiveConn = false;
    m_bActiveClose = false;
    m_bRawData = false;
    m_uiRawRecvLen = 2048;
    m_bKeepAlive = true;
    m_ttLastRecvMsgTime = 0;
    m_ttLastSendMsgTime = 0;
    m_ttKeepAliveSendTime = 0;
    m_bKeepAliveReply = true;
    m_pUserData = NULL;
    m_uiContinueRecvNum = 0;
    m_uiContinueSendNum = 0;
    m_uiMaxWaitingMsgNum = 0;
    m_uiWaitingMsgNum = 0;
    m_pPai = NULL;
    m_bInvokeCreate = true;
    m_bReconn = false;
    m_uiReconnDelay = 0;
    m_pHandler = NULL;
    m_parent = NULL;
}

CwxAppConnInfo::~CwxAppConnInfo()
{
    if (m_pPai) delete m_pPai;
}


CwxAppHostInfo::CwxAppHostInfo(CWX_UINT32 uiSvrId,
                               CWX_UINT32 uiHostId,
                               CwxAppSvrInfo* parent)
                               :m_uiSvrId(uiSvrId), m_uiHostId(uiHostId), m_parent(parent)
{
    m_ullSndMsgNum = 0 ;
    m_ullRecvMsgNum = 0;
    m_uiWaitingMsgNum = 0;
    m_uiRecentSndMsgNum = 0;
    m_uiRecentRecvMsgNum = 0;
    m_uiRecentClosedCount = 0;
    m_uiRand = 0;
}


///���캯��
CwxAppSvrInfo::CwxAppSvrInfo(CWX_UINT32 uiSvrId)
:m_uiSvrId(uiSvrId)
{
    m_uiRand = 0;
}



CWINUX_END_NAMESPACE


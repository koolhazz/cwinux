#include "CwmNerveApp.h"
#include <sys/wait.h>
///���캯��
CwmNerveApp::CwmNerveApp()
{
    m_uiAlarmConnId = 0;
    m_uiTaskId = 0;
    m_pAlarmHandler = NULL;
    m_pCgiHandler = NULL;
    m_pServerHandler = NULL;
    m_pQueryHandler = NULL;
    m_pDataMgr = NULL;

}

///��������
CwmNerveApp::~CwmNerveApp()
{

}

///��ʼ��APP�����������ļ�
int CwmNerveApp::init(int argc, char** argv)
{
    ///���ȵ��üܹ���init
    if (CwxAppFramework::init(argc, argv) == -1) return -1;
    ///��û��ͨ��-fָ�������ļ��������Ĭ�ϵ������ļ�
    if ((NULL == this->getConfFile()) || (strlen(this->getConfFile()) == 0))
    {
        this->setConfFile("svr_conf.xml");
    }
    ///���������ļ�
    if (!m_config.loadConfig(getConfFile()))
    {
        CWX_ERROR((m_config.getErrMsg()));
        return -1;
    }
    ///�������������־��level
    setLogLevel(CwxAppLogger::LEVEL_ALL);
    return 0;
}

//init the Enviroment before run.0:success, -1:failure.
int CwmNerveApp::initRunEnv()
{
    ///����ʱ�ӵĿ̶ȣ���СΪ1ms����Ϊ0.1s��
    this->setClick(100);//0.1s
    //set work dir
    this->setWorkDir(this->m_config.getWorkDir().c_str());
    //Set log file
    this->setLogFileNum(LOG_FILE_NUM);
    this->setLogFileSize(LOG_FILE_SIZE*1024*1024);
    ///���üܹ���initRunEnv��ʹ���õĲ�����Ч
    if (CwxAppFramework::initRunEnv() == -1 ) return -1;
    //set version
    this->setAppVersion(CWM_APP_VERSION);
    //set last modify date
    this->setLastModifyDatetime(CWM_NERVE_MODIFY_DATE);
    //set compile date
    this->setLastCompileDatetime(CWX_COMPILE_DATE(_BUILD_DATE));
    //output config
    m_config.outputConfig();
    //�򿪼����˿�
    if (-1 == this->noticeMgrListen(m_config.getMgrListen().getHostName().c_str(), m_config.getMgrListen().getPort(), true))
    {
       CWX_ERROR(("Failure to open mgr listen, ip=*, port=9010"));
       return -1;
    }
    //init data driver
    m_pDataMgr = new CwmCmnDataMgr();
    if (!m_pDataMgr->init(m_config.getDataPath() + CWM_NERVE_DB_FILE))
    {
        CWX_ERROR(("Failure to init Data file, err=%s, file=%s/%s", m_pDataMgr->getErrMsg(), m_config.getDataPath().c_str(),CWM_NERVE_DB_FILE));
        return -1;
    }
    ///������Ϣ�Ĵ���handler������ע�ᣬÿ��SVR-TYPEһ������handle
    m_pQueryHandler = new CwmNerveQueryHandler(this);
    getCommander().regHandle(SVR_TYPE_QUERY, m_pQueryHandler);
    m_pAlarmHandler = new CwmNerveAlarmHandler(this);
    getCommander().regHandle(SVR_TYPE_ALARM, m_pAlarmHandler);
    m_pCgiHandler = new CwmNerveCgiHandler(this);
    getCommander().regHandle(SVR_TYPE_CGI_ACTION, m_pCgiHandler);
    m_pServerHandler = new CwmNerveServerHandler(this);
    getCommander().regHandle(SVR_TYPE_SERVER_ACTION, m_pServerHandler);

    //����query
    int ret = 0;
    if (0 > (ret=this->noticeTcpListen(SVR_TYPE_QUERY,
        m_config.getQueryListen().getHostName().c_str(),
        m_config.getQueryListen().getPort(),
        false,
        0,
        true)))
    {
        CWX_ERROR(("Failure to listen query tcp, host=%s, port=%u", m_config.getQueryListen().getHostName().c_str(), m_config.getQueryListen().getPort()));
        return -1;
    }
    ///�����������service��״̬����
    list<CwmNerveActionInfo>::const_iterator act_iter ;
    map<pair<string,string>, CwmNerveServiceInfo>::const_iterator iter = m_config.getServices().begin();
    CwmNerveServiceStatus* pServerStatus;
    CwmNerveActionStatus* pActStatus;
    while(iter != m_config.getServices().end())
    {
        pServerStatus = new CwmNerveServiceStatus();
        pServerStatus->setServiceInfo(&iter->second);
        ///����server���͵�service�������������server��TCP����
        if (!pServerStatus->getServiceInfo()->isCgi())
        {///connect server
            if (0 > (ret = noticeTcpConnect(SVR_TYPE_SERVER_ACTION, 0, iter->second.getServerIp().c_str(), iter->second.getPort(), false, 0, true, 1, 4)))
            {
                CWX_ERROR(("Failure to connect monitor server, host=%s, port=%u", iter->second.getServerIp().c_str(), iter->second.getPort()));
                return -1;
            }
            pServerStatus->getSelfStatus().setAlarmRule(&iter->second.getAlarmRule());
            pServerStatus->setConnId(ret);
            pServerStatus->setConnected(false);
        }
        ///add action
        act_iter = pServerStatus->getServiceInfo()->getActions().begin();
        while(act_iter != pServerStatus->getServiceInfo()->getActions().end())
        {
            pActStatus = new CwmNerveActionStatus();
            pActStatus->setActionInfo(&(*act_iter));
            pActStatus->setServiceStatus( pServerStatus);
            pServerStatus->addActionStatus(pActStatus);
            act_iter++;
        }
        m_lsService.push_back(pServerStatus);
        iter++;
    }

    //����center�ĸ澯���ն˿�
    if (0 > (ret=this->noticeTcpConnect(SVR_TYPE_ALARM,
        0,
        m_config.getAlarmListen().getHostName().c_str(),
        m_config.getAlarmListen().getPort(),
        false,
        0,
        true,
        1,
        4
        )))
    {
        CWX_ERROR(("Failure to connect alarm listen, host=%s, port=%u", m_config.getAlarmListen().getHostName().c_str(), m_config.getAlarmListen().getPort())); 
        return -1;
    }
    m_uiAlarmConnId = ret;


    return 0;
}

///����tss�Ķ���
CwxAppTss* CwmNerveApp::onTssEnv()
{
    CwmNerveTss* pTss = new CwmNerveTss();
    if (0 != pTss->init())
    {
        CWX_ERROR(("Failure to init CwmNerveTss"));
        exit(0);
    }
    return pTss;
}

void CwmNerveApp::onTime(CwxTimeValue const& current)
{
    static CWX_UINT64 ullLastTime = CwxDate::getTimestamp();
    CwxAppFramework::onTime(current);
    if (current.to_usec() > ullLastTime + 200000)
    {//0.2s
        ///�γ�timeout check���¼�����CwmNerverQueryHandler��onTimeoutCheck������
        ullLastTime = current.to_usec();
        CwxMsgBlock* pBlock = CwxMsgBlockAlloc::malloc(0);
        pBlock->event().setSvrId(SVR_TYPE_QUERY);
        pBlock->event().setHostId(0);
        pBlock->event().setConnId(0);
        pBlock->event().setEvent(CwxEventInfo::TIMEOUT_CHECK);
        dispatch(pBlock);
    }
}

///�źŴ�����
void CwmNerveApp::onSignal(int signum)
{
    int statues=0;
    switch(signum)
    {
    case SIGQUIT: 
        CWX_INFO(("Recv exit signal, exit right now."));
        this->stop();
        break;
    case SIGCHLD:
        ///cgi�Ľ����˳������н���״̬��Ϣ�Ļ��գ������γɽ�ʬ����
        wait(&statues);
        break;
    default:
        ///�����źţ�����
        CWX_INFO(("Recv signal=%d, ignore it.", signum));
        break;
    }
}

///���ӽ�����Ӧ����
int CwmNerveApp::onConnCreated(CwxAppHandler4Msg& conn, bool& , bool& )
{
    if ((SVR_TYPE_ALARM == conn.getConnInfo().getSvrId()) ||  ///���澯��������ӽ�������Ҫ���������澯���ύ
        (SVR_TYPE_SERVER_ACTION == conn.getConnInfo().getSvrId())) ///���Ǹ�������server�����ӽ���������Ҫ�޸�������״̬
    {
        CwxMsgBlock* pBlock = CwxMsgBlockAlloc::malloc(0);
        ///�����ӵ���Ϣ���õ�events������
        pBlock->event().setSvrId(conn.getConnInfo().getSvrId());
        pBlock->event().setHostId(conn.getConnInfo().getHostId());
        pBlock->event().setConnId(conn.getConnInfo().getConnId());
        ///�����¼�������
        pBlock->event().setEvent(CwxEventInfo::CONN_CREATED);
        ///�ַ��¼�
        dispatch(pBlock);
    }
    return 0;
}

///���ӹر�
int CwmNerveApp::onConnClosed(CwxAppHandler4Msg const& conn)
{
    ///����query�����ӹرգ�����Ҫ�������ӹرյ��¼������зַ�
    if (SVR_TYPE_QUERY != conn.getConnInfo().getSvrId())
    {
        CwxMsgBlock* pBlock = CwxMsgBlockAlloc::malloc(0);
        pBlock->event().setSvrId(conn.getConnInfo().getSvrId());
        pBlock->event().setHostId(conn.getConnInfo().getHostId());
        pBlock->event().setConnId(conn.getConnInfo().getConnId());
        pBlock->event().setConnUserData(conn.getConnInfo().getUserData());
        pBlock->event().setEvent(CwxEventInfo::CONN_CLOSED);
        dispatch(pBlock);
    }
    return 0;
}


///��Ӧ����
int CwmNerveApp::onRecvMsg(CwxMsgBlock* msg, CwxAppHandler4Msg const& conn, CwxMsgHead const& header, bool& )
{

    msg->event().setSvrId(conn.getConnInfo().getSvrId());
    msg->event().setHostId(conn.getConnInfo().getHostId());
    msg->event().setConnId(conn.getConnInfo().getConnId());
    msg->event().setConnUserData(conn.getConnInfo().getUserData());
    msg->event().setMsgHeader(header);
    msg->event().setEvent(CwxEventInfo::RECV_MSG);
    msg->event().setTimestamp(CwxDate::getTimestamp());
    msg->event().setTaskId(msg->event().getMsgHeader().getTaskId());
    this->dispatch(msg);
    return 0;
}

CWX_UINT32 CwmNerveApp::onEndSendMsg(CwxMsgBlock*& msg, CwxAppHandler4Msg const& conn)
{
    if (SVR_TYPE_QUERY != conn.getConnInfo().getSvrId())
    {
        msg->event().setSvrId(conn.getConnInfo().getSvrId());
        msg->event().setHostId(conn.getConnInfo().getHostId());
        msg->event().setConnId(conn.getConnInfo().getConnId());
        msg->event().setConnUserData(conn.getConnInfo().getUserData());
        msg->event().setEvent(CwxEventInfo::END_SEND_MSG);
        dispatch(msg);
        ///��msg��Ϊ�գ���ֹ�ײ��ͷ�
        msg = NULL;
    }
    return CwxMsgSendCtrl::UNDO_CONN;
}

///��������ʧ��
void CwmNerveApp::onFailSendMsg(CwxMsgBlock*& msg)
{
    if (SVR_TYPE_QUERY != msg->send_ctrl().getSvrId())
    {
        msg->event().setSvrId(msg->send_ctrl().getSvrId());
        msg->event().setHostId(msg->send_ctrl().getHostId());
        msg->event().setConnId(msg->send_ctrl().getConnId());
        msg->event().setEvent(CwxEventInfo::FAIL_SEND_MSG);
        dispatch(msg);
        ///��msg��Ϊ�գ���ֹ�ײ��ͷ�
        msg = NULL;
    }
}

///�Ƿ������Դ
void CwmNerveApp::destroy()
{
    m_config.reset();
    m_uiAlarmConnId = 0;
    m_uiTaskId = 0;
    list<CwmNerveServiceStatus*>::iterator iter = m_lsService.begin();
    while(iter != m_lsService.end())
    {
        delete *iter;
        iter++;
    }
    m_lsService.clear();
    if (m_pAlarmHandler)
    {
        delete m_pAlarmHandler;
        m_pAlarmHandler = NULL;
    }
    if (m_pCgiHandler)
    {
        delete m_pCgiHandler;
        m_pCgiHandler = NULL;
    }
    if (m_pServerHandler)
    {
        delete m_pServerHandler;
        m_pServerHandler = NULL;
    }
    if (m_pQueryHandler)
    {
        delete m_pQueryHandler;
        m_pQueryHandler = NULL;
    }
    if (m_pDataMgr) delete m_pDataMgr;
    m_pDataMgr = NULL;
    ///��������ø����destroy api�����ͷŸ������Դ
    CwxAppFramework::destroy();
}

///ʵ����Ϣ�ķַ�
void CwmNerveApp::dispatch(CwxMsgBlock* msg)
{
    int iRet = 0;
    ///��ȡ�¼�������
    CWX_UINT32 uiEventType = msg->event().getEvent();
    CWX_UINT32 uiSvrId = msg->event().getSvrId();
    ///����msg�е�SVR-IDѡ����handler������event-typeȷ�����õ�handler����Ӧ����
    if (!this->getCommander().dispatch(msg, getAppTss(), iRet))
    {
        CWX_DEBUG(("No handle to deal with event: event_type=%u, svr_id=%u", uiEventType, uiSvrId));
    }
    if (1 != iRet)
    {
        if (0 == iRet)
        {///����Ϣ��Ӧ��handler������
            CWX_DEBUG(("No care the event for  event_type=%u, svr_id=%u", uiEventType, uiSvrId));
        }
        else
        {///��Ϣ����ʧ��
            CWX_DEBUG(("Failure to act the event for  event_type=%u, svr_id=%u", uiEventType, uiSvrId));
        }
    }
    ///����¼��������û���ͷŻ���msg�����ڴ˴�ͳһ�ͷ�
    if (msg) CwxMsgBlockAlloc::free(msg);
}



#include "CwmCenterApp.h"

CwmCenterApp::CwmCenterApp()
{
    m_uiTaskId = 1;
    m_pDataMgr = NULL;
    m_pAlarmAcceptor = NULL;
    m_pAlarmReportor = NULL;
    m_pNerveQuery = NULL;
    m_pUiQuery = NULL;
    m_pThreadPool = NULL;

}

CwmCenterApp::~CwmCenterApp()
{
}

///��ʼ��APP�����������ļ�
int CwmCenterApp::init(int argc, char** argv)
{
    ///���ȵ��üܹ���init
    if (CwxAppFramework::init(argc, argv) == -1) return -1;
    ///��û��ͨ��-fָ�������ļ��������Ĭ�ϵ������ļ�
    if ((NULL == this->getConfFile()) || (strlen(this->getConfFile()) == 0))
    {
        this->setConfFile("svr_conf.xml");
    }
    ///��ʼ��HtmlTmpl
    CwxHtmlTmpl::init();
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
int CwmCenterApp::initRunEnv()
{
    //���������
    //���default alarm email
    if (!m_config.getAlarmMail(CWM_CMN_DEFAULT))
    {
        CWX_ERROR(("Must config the center's default email rule"));
        return -1;
    }
    //���systemsģ��
    if (!m_config.getTemplate(CWM_CMN_TMPL_SYSTEMS))
    {
        CWX_ERROR(("Must config the systems's template:%s", CWM_CMN_TMPL_SYSTEMS));
        return -1;
    }
    if (!m_config.getTemplate(CWM_CMN_TMPL_SYSTEM))
    {
        CWX_ERROR(("Must config the systems's template:%s", CWM_CMN_TMPL_SYSTEM));
        return -1;
    }
    if (!m_config.getTemplate(CWM_CMN_TMPL_SERVICE))
    {
        CWX_ERROR(("Must config the systems's template:%s", CWM_CMN_TMPL_SERVICE));
        return -1;
    }

    ///����ʱ�ӵĿ̶ȣ���СΪ10ms����Ϊ1s��
    this->setClick(10);//0.1s
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
    this->setLastModifyDatetime(CWM_CENTER_MODIFY_DATE);
    //set compile date
    this->setLastCompileDatetime(CWX_COMPILE_DATE(_BUILD_DATE));

    ///���������
    m_config.outputConfig();
    //�򿪼����˿�
    if (-1 == this->noticeMgrListen(m_config.getMgrListen().getHostName().c_str(),
        m_config.getMgrListen().getPort(),
        true))
    {
        CWX_ERROR(("Failure to open mgr listen, ip=*, port=9010"));
        return -1;
    }

    //init data driver
    m_pDataMgr = new CwmCmnDataMgr();
    if (!m_pDataMgr->init(m_config.getDbFilePath() + CWM_CENTER_DB_FILE))
    {
        CWX_ERROR(("Failure to init Data file, err=%s, file=%s/%s", m_pDataMgr->getErrMsg(), m_config.getDbFilePath().c_str(), CWM_CENTER_DB_FILE));
        return -1;
    }
    ///reg handle
    m_pAlarmAcceptor = new CwmCenterAlarmAcceptor(this);
    getCommander().regHandle(SVR_TYPE_ALARM_ACCEPT, m_pAlarmAcceptor);
    m_pAlarmReportor = new CwmCenterAlarmReportor(this);
    getCommander().regHandle(SVR_TYPE_ALARM_REPORT, m_pAlarmReportor);
    m_pNerveQuery = new CwmCenterNerveQuery(this);
    getCommander().regHandle(SVR_TYPE_NERVE_QUERY, m_pNerveQuery);
    m_pUiQuery = new CwmCenterUiQuery(this);
    getCommander().regHandle(SVR_TYPE_UI_QUERY, m_pUiQuery);
    //�����澯���ն˿�
    int ret = 0;
    if (0 > (ret=this->noticeTcpListen(SVR_TYPE_ALARM_ACCEPT,
        m_config.getAlarmAccept().getHostName().c_str(),
        m_config.getAlarmAccept().getPort(),
        false,
        0,
        true)))
    {
        CWX_ERROR(("Failure to listen alarm accept, host=%s, port=%u", m_config.getAlarmAccept().getHostName().c_str(), m_config.getAlarmAccept().getPort()));
        return -1;
    }
    //�����澯����˿�
    if (0 > (ret=this->noticeTcpListen(SVR_TYPE_ALARM_REPORT,
        m_config.getAlarmReport().getHostName().c_str(),
        m_config.getAlarmReport().getPort(),
        false,
        0,
        true)))
    {
        CWX_ERROR(("Failure to listen alarm report, host=%s, port=%u", m_config.getAlarmReport().getHostName().c_str(), m_config.getAlarmReport().getPort()));
        return -1;
    }
    //����UI��ѯ�Ķ˿�
    if (0 > (ret=this->noticeTcpListen(SVR_TYPE_UI_QUERY,
        m_config.getQueryListen().getHostName().c_str(),
        m_config.getQueryListen().getPort(),
        false,
        0,
        false)))
    {
        CWX_ERROR(("Failure to listen query, host=%s, port=%u", m_config.getQueryListen().getHostName().c_str(), m_config.getQueryListen().getPort()));
        return -1;
    }
    ///����nerve����
    map<string/*ip*/, CwmCenterHost*>::const_iterator iter_host = m_config.getHosts().begin();
    CwmCenterNerveStatus* pHost=NULL;
    while(iter_host != m_config.getHosts().end())
    {
        pHost = new CwmCenterNerveStatus();
        pHost->setHostInfo(iter_host->second);
        pHost->setConnected(false);
        if (0 > (ret = noticeTcpConnect(SVR_TYPE_NERVE_QUERY,
            0,
            iter_host->second->getIp().c_str(),
            iter_host->second->getPort(),
            false,
            0,
            true,
            1,
            4)))
        {
            CWX_ERROR(("Failure to connect nerver host, host=%s, port=%u", iter_host->second->getIp().c_str(), iter_host->second->getPort()));
            return -1;
        }
        pHost->setConnId(ret);
        m_nerves[pHost->getConnId()] = pHost;
        m_nervesIndex[iter_host->second->getIp()] = pHost;
        iter_host++;
    }

    //create thread pool
    m_pThreadPool = new CwxAppThreadPoolEx(this, CwxAppFramework::THREAD_GROUP_USER_START, m_config.getThreadNum());
    CwxAppTss** pTss = new CwxAppTss*[m_config.getThreadNum()];
    for (CWX_UINT32 uiThreadIndex=0; uiThreadIndex<m_config.getThreadNum(); uiThreadIndex++)
    {
        pTss[uiThreadIndex] = new CwmCenterTss();
        if (0 != ((CwmCenterTss*)pTss[uiThreadIndex])->init())
        {
            CWX_ERROR(("Failure to init center's tss."));
            return -1;
        }
    }
    ///�����̳߳�
    if (0 != m_pThreadPool->start(pTss))
    {
        CWX_ERROR(("Failure to start thread pool"));
        return -1;
    }
    return 0;
}

///����ͨ���߳����TSS
CwxAppTss* CwmCenterApp::onTssEnv()
{
    CwmCenterTss* pTss = new CwmCenterTss();
    if (0 != pTss->init())
    {
        CWX_ERROR(("Failure to init CwmCenterTss"));
        exit(0);
    }
    return pTss;
}
///ʱ��
void CwmCenterApp::onTime(CwxTimeValue const& current)
{
    static CWX_UINT64 ullLastTime = CwxDate::getTimestamp();
    CwxAppFramework::onTime(current);
    if (current.to_usec() > ullLastTime + 200000)
    {//0.2s
        ///�γɳ�ʱ����¼�����CwmCenterUiQuery��onTimeoutCheck����Ӧ
        ullLastTime = current.to_usec();
        CwxMsgBlock* pBlock = CwxMsgBlockAlloc::malloc(0);
        pBlock->event().setSvrId(SVR_TYPE_UI_QUERY);
        pBlock->event().setHostId(0);
        pBlock->event().setConnId(0);
        pBlock->event().setEvent(CwxEventInfo::TIMEOUT_CHECK);
        m_pThreadPool->append(pBlock, 0);
    }
}

///�źŴ�����
void CwmCenterApp::onSignal(int signum)
{
    switch(signum)
    {
    case SIGQUIT: 
        CWX_INFO(("Recv exit signal, exit right now."));
        this->stop();
        break;
    default:
        ///�����źţ�����
        CWX_INFO(("Recv signal=%d, ignore it.", signum));
        break;
    }
}

///���ӽ�����Ӧ����
int CwmCenterApp::onConnCreated(CwxAppHandler4Msg& conn, bool& , bool& )
{
    ///ֻ����Alarm report��Nerve query�����ӽ����¼�
    if ((SVR_TYPE_NERVE_QUERY == conn.getConnInfo().getSvrId()) || 
        (SVR_TYPE_ALARM_REPORT == conn.getConnInfo().getSvrId()))
    {
        CwxMsgBlock* pBlock = CwxMsgBlockAlloc::malloc(0);
        pBlock->event().setSvrId(conn.getConnInfo().getSvrId());
        pBlock->event().setHostId(conn.getConnInfo().getHostId());
        pBlock->event().setConnId(conn.getConnInfo().getConnId());
        pBlock->event().setEvent(CwxEventInfo::CONN_CREATED);
        m_pThreadPool->append(pBlock, conn.getConnInfo().getConnId());
    }
    return 0;
}

///���ӹر�
int CwmCenterApp::onConnClosed(CwxAppHandler4Msg const& conn)
{
    ///ֻ����Alarm report��Nerve query�����ӹر��¼�
    if ((SVR_TYPE_NERVE_QUERY == conn.getConnInfo().getSvrId()) || 
        (SVR_TYPE_ALARM_REPORT == conn.getConnInfo().getSvrId()))
    {
        CwxMsgBlock* pBlock = CwxMsgBlockAlloc::malloc(0);
        pBlock->event().setSvrId(conn.getConnInfo().getSvrId());
        pBlock->event().setHostId(conn.getConnInfo().getHostId());
        pBlock->event().setConnId(conn.getConnInfo().getConnId());
        pBlock->event().setEvent(CwxEventInfo::CONN_CLOSED);
        m_pThreadPool->append(pBlock, conn.getConnInfo().getConnId());
    }
    return 0;
}


///��Ӧ����
int CwmCenterApp::onRecvMsg(CwxMsgBlock* msg, CwxAppHandler4Msg const& conn, CwxMsgHead const& header, bool& )
{
    ///�յ���Ϣ
    ///����conn����Ϣ����SVR-IDʱcommander  dispatch������
    msg->event().setSvrId(conn.getConnInfo().getSvrId());
    msg->event().setHostId(conn.getConnInfo().getHostId());
    msg->event().setConnId(conn.getConnInfo().getConnId());
    ///�����յ���Ϣ����Ϣͷ
    msg->event().setMsgHeader(header);
    ///����event������
    msg->event().setEvent(CwxEventInfo::RECV_MSG);
    ///�յ���Ϣ��ʱ���
    msg->event().setTimestamp(CwxDate::getTimestamp());
    ///����task id����ΪTaskBoard������Ϣ��task���ȵ�����
    msg->event().setTaskId(msg->event().getMsgHeader().getTaskId());
    ///����Ϣ�ŵ��̳߳أ���֤һ�����ӵ���Ϣֻ��һ���̴߳���
    m_pThreadPool->append(msg, conn.getConnInfo().getConnId());
    return 0;
}

CWX_UINT32 CwmCenterApp::onEndSendMsg(CwxMsgBlock*& msg, CwxAppHandler4Msg const& conn)
{
    ///ֻ��Alarm report��Nerve query��handle��Ҫ������Ϣ������ϵ��¼�
    if ((SVR_TYPE_NERVE_QUERY == conn.getConnInfo().getSvrId()) || 
        (SVR_TYPE_ALARM_REPORT == conn.getConnInfo().getSvrId()))
    {
        msg->event().setSvrId(conn.getConnInfo().getSvrId());
        msg->event().setHostId(conn.getConnInfo().getHostId());
        msg->event().setConnId(conn.getConnInfo().getConnId());
        msg->event().setEvent(CwxEventInfo::END_SEND_MSG);
        m_pThreadPool->append(msg, conn.getConnInfo().getConnId());
        msg = NULL;
    }
    return CwxMsgSendCtrl::UNDO_CONN;
}

///��������ʧ��
void CwmCenterApp::onFailSendMsg(CwxMsgBlock*& msg)
{
    ///ֻ��Alarm report��Nerve query��handle��Ҫ������Ϣ����ʧ�ܵ��¼�
    if ((SVR_TYPE_NERVE_QUERY == msg->send_ctrl().getSvrId()) || 
        (SVR_TYPE_ALARM_REPORT == msg->send_ctrl().getSvrId()))
    {
        msg->event().setSvrId(msg->send_ctrl().getSvrId());
        msg->event().setHostId(msg->send_ctrl().getHostId());
        msg->event().setConnId(msg->send_ctrl().getConnId());
        msg->event().setEvent(CwxEventInfo::FAIL_SEND_MSG);
        m_pThreadPool->append(msg, msg->send_ctrl().getConnId());
        msg = NULL;
    }
}
///�ͷ�app����Դ
void CwmCenterApp::destroy()
{
    if (m_pThreadPool)
    {
        m_pThreadPool->stop();
        delete m_pThreadPool;
        m_pThreadPool = NULL;
    }
    m_uiTaskId = 1;
    m_config.reset();
    if (m_pDataMgr)
    {
        delete m_pDataMgr;
        m_pDataMgr = NULL;
    }
    if (m_pAlarmAcceptor)
    {
        delete m_pAlarmAcceptor;
        m_pAlarmAcceptor = NULL;
    }
    if (m_pAlarmReportor)
    {
        delete m_pAlarmReportor;
        m_pAlarmReportor = NULL;
    }
    if (m_pNerveQuery)
    {
        delete m_pNerveQuery;
        m_pNerveQuery = NULL;
    }
    if (m_pUiQuery)
    {
        delete m_pUiQuery;
        m_pUiQuery = NULL;
    }
    map<CWX_UINT32, CwmCenterNerveStatus*>::iterator iter = m_nerves.begin();
    while(iter != m_nerves.end())
    {
        delete iter->second;
        iter++;
    }
    m_nerves.clear();
    m_nervesIndex.clear();
    CwxAppFramework::destroy();
}

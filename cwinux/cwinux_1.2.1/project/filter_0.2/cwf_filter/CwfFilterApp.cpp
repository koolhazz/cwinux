#include "CwfFilterApp.h"
#include "CwxDate.h"

///���캯��
CwfFilterApp::CwfFilterApp(){
    m_pFilterHandler = NULL;
    m_pThreadPool = NULL;
    m_pFilterMgr = NULL;
}

///��������
CwfFilterApp::~CwfFilterApp(){
}

///��ʼ��
int CwfFilterApp::init(int argc, char** argv){
    string strErrMsg;
    ///���ȵ��üܹ���init api
    if (CwxAppFramework::init(argc, argv) == -1) return -1;
    ///����Ƿ�ͨ��-fָ���������ļ�����û�У������Ĭ�ϵ������ļ�
    if ((NULL == this->getConfFile()) || (strlen(this->getConfFile()) == 0)){
        this->setConfFile("svr_conf.xml");
    }
    ///���������ļ�����ʧ�����˳�
    if (0 != m_config.loadConfig(getConfFile())){
        CWX_ERROR((m_config.getError()));
        return -1;
    }
    ///����������־�����level
    setLogLevel(CwxAppLogger::LEVEL_ERROR|CwxAppLogger::LEVEL_INFO|CwxAppLogger::LEVEL_WARNING);
    return 0;
}

///�������л�����Ϣ
int CwfFilterApp::initRunEnv(){
    ///����ϵͳ��ʱ�Ӽ������С�̶�Ϊ1ms����Ϊ1s��
    this->setClick(1000);//1s
    ///���ù���Ŀ¼
    this->setWorkDir(this->m_config.m_strWorkDir.c_str());
    ///����ѭ��������־������
    this->setLogFileNum(LOG_FILE_NUM);
    ///����ÿ����־�ļ��Ĵ�С
    this->setLogFileSize(LOG_FILE_SIZE*1024*1024);
    ///���üܹ���initRunEnv��ʹ�������õĲ�����Ч
    if (CwxAppFramework::initRunEnv() == -1 ) return -1;
    ///�����ص������ļ���Ϣ�������־�ļ��У��Թ��鿴���
    m_config.outputConfig();
    //set version
    this->setAppVersion(FILTER_APP_VERSION);
    //set last modify date
    this->setLastModifyDatetime(FILTER_MODIFY_DATE);
    //set compile date
    this->setLastCompileDatetime(CWX_COMPILE_DATE(_BUILD_DATE));

    //�򿪼����˿�
    if (-1 == this->noticeMgrListen(m_config.m_mgrListen.getHostName().c_str(),
        m_config.m_mgrListen.getPort(),
        true))
    {
        CWX_ERROR(("Failure to open mgr listen, ip=%s, port=%u", m_config.m_mgrListen.getHostName().c_str(), m_config.m_mgrListen.getPort()));
        return -1;
    }

    ///��ʼ������������������
    m_pFilterMgr = new CwfFilterMgr();
    if (0 != m_pFilterMgr->init(m_config, getAppTss()->m_szBuf2K))
    {
        CWX_ERROR(("Failure to init Filter mgr, err=%s", getAppTss()->m_szBuf2K));
        return -1;
    }
    ///����filter handler
    m_pFilterHandler = new CwfFilterHandler(this);
    ///ע��echo����Ĵ���handle��echo�����svr-idΪSVR_TYPE_ECHO
    this->getCommander().regHandle(SVR_TYPE_FILTER, m_pFilterHandler);
    ///����TCP���ӣ��佨�������ӵ�svr-id��ΪSVR_TYPE_FILTER�����յ���Ϣ��svr-id��ΪSVR_TYPE_FILTER��
    ///ȫ����m_pFilterHandler����������, no-keep-alive
    if (m_config.m_filterListen.getHostName().length())
    {
        if (0 > this->noticeTcpListen(SVR_TYPE_FILTER, 
            this->m_config.m_filterListen.getHostName().c_str(),
            this->m_config.m_filterListen.getPort()))
        {
            CWX_ERROR(("Can't register the filter acceptor port: addr=%s, port=%d",
                this->m_config.m_filterListen.getHostName().c_str(),
                this->m_config.m_filterListen.getPort()));
            return -1;
        }
    }
    ///����UNIX DOMAIN���ӣ��佨�������ӵ�svr-id��ΪSVR_TYPE_FILTER�����յ���Ϣ��svr-id��ΪSVR_TYPE_FILTER��
    ///ȫ����m_pFilterHandler����������, no-keep-alive
    if (m_config.m_strUnixPathFile.length())
    {
        if (0 > this->noticeLsockListen(SVR_TYPE_FILTER, 
            this->m_config.m_strUnixPathFile.c_str()))
        {
            CWX_ERROR(("Can't register the filter unix acceptor port: path=%s",
                m_config.m_strUnixPathFile.c_str()));
            return -1;
        }
    }
    ///�����̳߳ض��󣬴��̳߳����̵߳�group-idΪTHREAD_GROUP_USER_START��
    ///�̳߳ص��߳�����Ϊm_config.m_unThreadNum��
    m_pThreadPool = new CwxAppThreadPool(this,
        CwxAppFramework::THREAD_GROUP_USER_START,
        m_config.m_unThreadNum);
    ///�����̵߳�tss����
    CwxAppTss** pTss = new CwxAppTss*[m_config.m_unThreadNum];
    for (CWX_UINT32 i=0; i<m_config.m_unThreadNum; i++){
        pTss[i] = new CwfFilterTss();
        ((CwfFilterTss*)pTss[i])->init();
    }
    ///�����̣߳��̳߳����̵߳��߳�ջ��СΪ64k��
    if ( 0 != m_pThreadPool->start(pTss, 64 * 1024))
    {
        CWX_ERROR(("Failure to start thread pool"));
        return -1;
    }
    return 0;

}

///ʱ�Ӻ�����ʲôҲû����
void CwfFilterApp::onTime(CwxTimeValue const& current)
{
    CwxAppFramework::onTime(current);
}

///�źŴ�����
void CwfFilterApp::onSignal(int signum)
{
    switch(signum){
    case SIGQUIT: 
        CWX_INFO(("Recv exit signal , exit right now."));
        this->stop();
        break;
    default:
        ///�����źţ�ȫ������
        CWX_INFO(("Recv signal=%d , ignore it.", signum));
        break;
    }

}

///echo�����������Ϣ
int CwfFilterApp::onRecvMsg(CwxMsgBlock* msg,
                            CwxAppHandler4Msg const& conn,
                            CwxMsgHead const& header,
                            bool& )
{
    msg->event().setSvrId(conn.getConnInfo().getSvrId());
    msg->event().setHostId(conn.getConnInfo().getHostId());
    msg->event().setConnId(conn.getConnInfo().getConnId());
    msg->event().setMsgHeader(header);
    msg->event().setEvent(CwxEventInfo::RECV_MSG);
    msg->event().setTimestamp(CwxDate::getTimestamp());
    ///����Ϣ�ŵ��̳߳ض����У����ڲ����̵߳����䴦��handle������
    m_pThreadPool->append(msg);
    return 0;
}

void CwfFilterApp::destroy()
{
    if (m_pThreadPool)
    {
        m_pThreadPool->stop();
        delete m_pThreadPool;
        m_pThreadPool = NULL;
    }
    if (m_pFilterMgr)
    {
        delete m_pFilterMgr;
        m_pFilterMgr = NULL;
    }
    if (m_pFilterHandler)
    {
        delete m_pFilterHandler;
        m_pFilterHandler = NULL;
    }
    CwxAppFramework::destroy();
}



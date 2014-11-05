#include "CwxAppFramework.h"
#include "CwxAppReactor.h"

CWINUX_BEGIN_NAMESPACE

CwxAppReactor::CwxAppReactor()
:m_connMap(CWX_APP_MAX_IO_NUM * 2)
{
    m_owner = CwxAppThread::self();
    m_bStop = true;
    m_eventBase = NULL;
    ///��ʼ��IO handler������
    for (int i=0; i<CWX_APP_MAX_IO_NUM; i++)
    {
        m_ioHandler[i].m_pHandler = NULL;
        m_ioHandler[i].m_uiConnId = CWX_APP_INVALID_CONN_ID;
    }
    ///��ʼ��signal������
    memset(m_arrSignals, 0x00, sizeof(m_arrSignals));
    ///����notice pipe����
    m_pNoticePipe = NULL;
}


CwxAppReactor::~CwxAppReactor()
{
    close();
}

///fork��re-init����������ֵ��0���ɹ���-1��ʧ��
int CwxAppReactor::forkReinit()
{
    m_owner = CwxAppThread::self();
    int ret = event_reinit(m_eventBase);
    if (-1 == ret)
    {
        CWX_ERROR(("Failure to invoke libevent::event_reinit"));
        return -1;
    }
    return 0;
}

///��reactor��return -1��ʧ�ܣ�0���ɹ�
int CwxAppReactor::open()
{
    if (!m_bStop)
    {
        CWX_ERROR(("Can't re-open the openning reactor"));
        return -1;
    }
    ///����reactor��owner
    m_owner = CwxAppThread::self();
    ///����reactor
    this->close();
    ///����notice pipe����
    m_pNoticePipe = new CwxAppNoticePipe();
    ///����event-base
    if (m_eventBase)
    {///�ͷ�libevent base
        event_base_free(m_eventBase);
        m_eventBase = NULL;
    }

    ///����event base
/*    if (m_type == REACTOR_EPOLL)
    {
        m_eventBase = event_base_new_type("epoll");
    }
    else
    {
        m_eventBase = event_base_new_type("select");
    }*/
    m_eventBase = event_base_new();
    if (!m_eventBase)
    {
        CWX_ERROR(("Failure to create event base"));
        return -1;        
    }
    if (m_pNoticePipe->init() != 0)
    {
        CWX_ERROR(("Failure to invoke CwxAppNoticePipe::init()"));
        return -1;
    }
    CWX_DEBUG(("Success to open CwxAppReactor"));
    return 0;
}

///�ر�reactor��return -1��ʧ�ܣ�0���ɹ�
int CwxAppReactor::close()
{
    if (!CwxAppThread::equal(m_owner, CwxAppThread::self()))
    {
        CWX_ERROR(("CwxAppReactor::close must be invoked by owner thread"));
        return -1;
    }
    m_bStop = true;
    if (m_eventBase)
    {
        event_base_free(m_eventBase);
        m_eventBase = NULL;
    }
    if (m_pNoticePipe)
    {
        delete m_pNoticePipe;
        m_pNoticePipe = NULL;
    }
    int i =0;
    m_uiCurConnId = 0;
    m_connMap.clear();
    for (i=0; i<CWX_APP_MAX_IO_NUM; i++)
    {
        if (m_ioHandler[i].m_pHandler) delete m_ioHandler[i].m_pHandler;
        m_ioHandler[i].m_pHandler = NULL;
        m_ioHandler[i].m_uiConnId = CWX_APP_INVALID_CONN_ID;
    }
    for (i=0; i<CWX_APP_MAX_SIGNAL_ID + 1; i++)
    {
        if (m_arrSignals[i]) delete m_arrSignals[i];
        m_arrSignals[i] = NULL;
    }
    set<CwxAppHandler4Base*>::iterator iter = m_timeouts.begin();
    while(iter != m_timeouts.end())
    {
        delete *iter;
        iter++;
    }
    m_timeouts.clear();
    return 0;
}

/**
@brief �ܹ��¼���ѭ������API��ʵ����Ϣ�ķַ���
@return -1��ʧ�ܣ�0�������˳�
*/
int CwxAppReactor::run(CwxAppHandler4Base* noticeHandler,
                       REACTOR_EVENT_HOOK hook,
                       void* arg)
{
    int ret = 0;
    if (!m_bStop || !m_eventBase)
    {
        CWX_ERROR(("CwxAppReactor::open() must be invoke before CwxAppReactor::run()"));
        return -1;
    }
    ///����reactor��owner
    m_owner = CwxAppThread::self();
    ///ע��notice handler
    noticeHandler->setHandle(m_pNoticePipe->getPipeReader());
    if (0 != this->registerHandler(m_pNoticePipe->getPipeReader(),
        noticeHandler,
        CwxAppHandler4Base::PREAD_MASK))
    {
        CWX_ERROR(("Failure to register CwxAppHandler4Notice notice handler"));
        return -1;
    }
    m_bStop = false;

    while(!m_bStop)
    {
        {
            ///����ִ��event-loop
            CwxMutexGuard<CwxMutexLock> lock(&m_lock);
            ret = event_base_loop(m_eventBase, EVLOOP_ONCE);
        }
        if (m_bStop)
        {
            CWX_DEBUG(("Stop running for stop"));
            break;
        }
        if (0 != ret)
        {
            if ((-1 == ret) && (EINTR != errno))
            {
                CWX_ERROR(("Failure to running event_base_loop with -1, errno=%d", errno));
                break;
            }
            else if (1 == ret)
            {
                CWX_ASSERT(0); ///������notice handler�����һ����event
                sleep(1);
                ret = 0;
            }
        }
        ///����hook
        if (hook)
        {
            if (0 != hook(arg))
            {
                CWX_DEBUG(("Stop running for hook() without 0"));
                break;
            }
        }
        ///�ȴ��������߳�ִ�и��ֲ�����
        m_rwLock.acquire_write();
        m_rwLock.release();
    }
    return ret;
}

/**
@brief ֹͣ�ܹ��¼���ѭ������
@return -1��ʧ�ܣ�0�������˳�
*/
int CwxAppReactor::stop()
{
    if (!CwxAppThread::equal(m_owner, CwxAppThread::self()))
    {
        m_rwLock.acquire_read();
        this->notice(NULL);
        {
            CwxMutexGuard<CwxMutexLock> lock(&m_lock);
            return _stop();
        }
        m_rwLock.release();
    }
    return _stop();
}


void CwxAppReactor::callback(int fd, short event, void *arg)
{
    CwxAppHandler4Base* handler = (CwxAppHandler4Base*)arg;
    CwxAppReactor* reactor=handler->reactor();
    if (!handler->isPersistMask())
    {
        switch(handler->getRegType())
        {
        case REG_TYPE_IO:
            reactor->m_ioHandler[handler->getHandle()].m_pHandler = NULL;
            reactor->m_ioHandler[handler->getHandle()].m_uiConnId = CWX_APP_INVALID_CONN_ID;
            break;
        case REG_TYPE_TIMEOUT:
            reactor->m_timeouts.erase(handler);
            break;
        case REG_TYPE_SIG:
            reactor->m_arrSignals[handler->getHandle()] = NULL;
            break;
        default:
            CWX_ASSERT(0);
        }
        handler->setReg(false);
    }
    int ret = handler->handle_event(event, fd);
    if (-1 == ret)
    {
        handler->close(fd);
    }
}

CWINUX_END_NAMESPACE

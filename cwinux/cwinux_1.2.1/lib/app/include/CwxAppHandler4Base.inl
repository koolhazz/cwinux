CWINUX_BEGIN_NAMESPACE

inline void CwxAppHandler4Base::setApp(CwxAppFramework* app)
{
    m_pApp = app;
}
///��ȡapp
inline CwxAppFramework* CwxAppHandler4Base::getApp()
{
    return m_pApp;
}
///��ȡapp
///����handle��reactor
inline void CwxAppHandler4Base::reactor (CwxAppReactor *reactor)
{
    m_reactor = reactor;
}
///��ȡhandle��reactor.
inline CwxAppReactor *CwxAppHandler4Base::reactor(void)
{
    return m_reactor;
}
inline bool CwxAppHandler4Base::isReg() const
{
    return m_bReg;
}
///����ע��״̬
inline void CwxAppHandler4Base::setReg(bool bReg)
{
    m_bReg = bReg;
}

///��ȡreg mask
inline int CwxAppHandler4Base::getRegMask() const
{
    return m_regMask;
}
///����reg mask
inline void CwxAppHandler4Base::setRegMask(int mask)
{
    m_regMask = mask;
}

///��ȡIo handle
inline CWX_HANDLE CwxAppHandler4Base::getHandle(void) const
{
    return m_handler;
}
///����IO handle
inline void CwxAppHandler4Base::setHandle (CWX_HANDLE handle)
{
    m_handler = handle;
}

///����handle type
inline void CwxAppHandler4Base::setType(int type)
{
    m_type = type;
}
///��ȡhandle type
inline int CwxAppHandler4Base::getType() const
{
    return m_type;
}

///��ȡע������
inline int CwxAppHandler4Base::getRegType() const
{
    return m_regType;
}
///����ע������
inline void CwxAppHandler4Base::setRegType(int type)
{
    m_regType = type;
}

///��ȡ�Ƿ�Ϊpersist�¼�
inline bool CwxAppHandler4Base::isPersistMask() const
{
    return (m_regMask&PERSIST_MASK) !=0;
}

///�Ƿ�������read mask
inline bool CwxAppHandler4Base::isReadMask() const
{
    return (m_regMask&READ_MASK) !=0;
}
///�Ƿ�������write mask
inline bool CwxAppHandler4Base::isWriteMask() const
{
    return (m_regMask&WRITE_MASK) !=0;
}
///�Ƿ�������timeout mask
inline bool CwxAppHandler4Base::isTimeoutMask() const
{
    return (m_regMask&TIMEOUT_MASK) !=0;
}
///�Ƿ�������signal mask
inline bool CwxAppHandler4Base::isSignalMask() const
{
    return (m_regMask&SIGNAL_MASK) !=0;
}



CWINUX_END_NAMESPACE


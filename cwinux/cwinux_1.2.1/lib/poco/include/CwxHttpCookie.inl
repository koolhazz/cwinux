CWINUX_BEGIN_NAMESPACE
///����cookie�İ汾�ţ�ȱʡΪ0
inline void CwxHttpCookie::setVersion(int version)
{
    m_iVersion = version;
}
///��ȡcookie�İ汾��
inline int CwxHttpCookie::getVersion() const
{
    return m_iVersion;
}
///����cookie������		
inline void CwxHttpCookie::setName(char const* name)
{
    if (name)
    {
        m_strName = name;
    }
    else
    {
        m_strName.erase();
    }
}
///��ȡcookie������		
inline string const& CwxHttpCookie::getName() const
{
    return m_strName;
}
///����cookie����ֵ���䳤�Ȳ��ܳ���4K
inline void CwxHttpCookie::setValue(char const* value)
{
    if (value)
    {
        m_strValue = value;
    }
    else
    {
        m_strValue.erase();
    }
}
///��ȡcookie����ֵ		
inline string const& CwxHttpCookie::getValue() const
{
    return m_strValue;
}
///����cookie��comment,ֻ��v1֧��comment
inline void CwxHttpCookie::setComment(char const* comment)
{
    if (comment)
    {
        m_strComment = comment;
    }
    else
    {
        m_strComment.erase();
    }
}
///��ȡcookie��comment
inline string const& CwxHttpCookie::getComment() const
{
    return m_strComment;
}
///����cookie��domain
inline void CwxHttpCookie::setDomain(char const* domain)
{
    if (domain)
    {
        m_strDomain = domain;
    }
    else
    {
        m_strDomain.erase();
    }
}
///��ȡcookie��domain		
inline string const& CwxHttpCookie::getDomain() const
{
    return m_strDomain;
}
///����cookie��·��
inline void CwxHttpCookie::setPath(char const* path)
{
    if (path)
    {
        m_strPath = path;
    }
    else
    {
        m_strPath.erase();
    }
}
///��ȡcookie��·��		
inline string const& CwxHttpCookie::getPath() const
{
    return m_strPath;
}
///����cookie�İ�ȫflag
inline void CwxHttpCookie::setSecure(bool secure)
{
    m_bSecure =secure;
}
///��ȡ�Ƿ������˰�ȫflag
inline bool CwxHttpCookie::getSecure() const
{
    return m_bSecure;
}
///����ʧЧʱ�䡣ttTimeΪʧЧ��ʱ��㡣
inline void CwxHttpCookie::setExpire(time_t ttTime)
{
    m_ttExpire = ttTime;
}
///��ȡ�������ʧЧ��
inline time_t CwxHttpCookie::getExpire() const
{
    return m_ttExpire;
}
///����ʧЧʱ�䣬Ϊyyyy-mm-dd hh:mm:ss��ʽ��
inline void CwxHttpCookie::setExpire(char const* daytime)
{
    if (daytime)
    {
        m_ttExpire = CwxDate::getDate(daytime);
    }
    else
    {
        m_ttExpire = -1;
    }
}
///��ȡʧЧ��ʱ�䡣���صĸ�ʽΪyyyy-mm-dd hh:mm:ss��ʽ��
inline string& CwxHttpCookie::getExpire(string& daytime) const
{
    CwxDate::getDate(m_ttExpire, daytime);
    return daytime;
}
///����cookie��HttpOnly���
inline void CwxHttpCookie::setHttpOnly(bool flag)
{
    m_bHttpOnly = flag;
}
///��ȡcookie��HttpOnly���		
inline bool CwxHttpCookie::getHttpOnly() const
{
    return m_bHttpOnly;
}

CWINUX_END_NAMESPACE

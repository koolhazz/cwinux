#include "CwxHttpCookie.h"

CWINUX_BEGIN_NAMESPACE

///ȱʡ���캯��
CwxHttpCookie::CwxHttpCookie()
{
    m_iVersion = 0;
    m_bSecure = false;
    m_ttExpire = -1;
    m_bHttpOnly = false;
}
///ͨ��ָ�������֣�����һ��cookie����Ч��Ϊ��Զ��
CwxHttpCookie::CwxHttpCookie(const std::string& name)
{
    m_iVersion = 0;
    m_bSecure = false;
    m_ttExpire = -1;
    m_bHttpOnly = false;
    m_strName = name;
}
///ͨ��ָ�������ּ���ֵ������һ��cookie����Ч��Ϊ��Զ��
CwxHttpCookie::CwxHttpCookie(const std::string& name, const std::string& value)
{
    m_iVersion = 0;
    m_bSecure = false;
    m_ttExpire = -1;
    m_bHttpOnly = false;
    m_strName = name;
    m_strValue = value;
}
///�������캯��
CwxHttpCookie::CwxHttpCookie(CwxHttpCookie const& cookie)
{
    m_iVersion = cookie.m_iVersion;
    m_strName = cookie.m_strName;
    m_strValue = cookie.m_strValue;
    m_strComment = cookie.m_strComment;
    m_strDomain = cookie.m_strDomain;
    m_strPath = cookie.m_strPath;
    m_bSecure = cookie.m_bSecure;
    m_ttExpire = cookie.m_ttExpire;
    m_bHttpOnly = cookie.m_bHttpOnly;
}
///��������
CwxHttpCookie::~CwxHttpCookie()
{

}
///��ֵ����	
CwxHttpCookie& CwxHttpCookie::operator = (const CwxHttpCookie& cookie)
{
    if (this != &cookie)
    {
        m_iVersion = cookie.m_iVersion;
        m_strName = cookie.m_strName;
        m_strValue = cookie.m_strValue;
        m_strComment = cookie.m_strComment;
        m_strDomain = cookie.m_strDomain;
        m_strPath = cookie.m_strPath;
        m_bSecure = cookie.m_bSecure;
        m_ttExpire = cookie.m_ttExpire;
        m_bHttpOnly = cookie.m_bHttpOnly;
    }
    return *this;
}

///����cookie���ַ���		
string& CwxHttpCookie::toCookie(string& cookie) const
{
    cookie.reserve(256);
    cookie.append(m_strName);
    cookie.append("=");
    if (0 == m_iVersion)
    {
        cookie.append(m_strValue);
        if (!m_strDomain.empty())
        {
            cookie.append("; domain=");
            cookie.append(m_strDomain);
        }
        if (!m_strPath.empty())
        {
            cookie.append("; path=");
            cookie.append(m_strPath);
        }
        if (m_ttExpire != -1)
        {
            string datetime;
            cookie.append("; expires=");
            cookie.append(CwxDate::format(m_ttExpire, CwxDate::HTTP_FORMAT.c_str(), datetime));
        }
        if (m_bSecure)
        {
            cookie.append("; secure");
        }
        if (m_bHttpOnly)
        {
            cookie.append("; HttpOnly");
        }
    }
    else
    {
        // RFC 2109 cookie
        cookie.append("\"");
        cookie.append(m_strValue);
        cookie.append("\"");
        if (!m_strComment.empty())
        {
            cookie.append("; Comment=\"");
            cookie.append(m_strComment);
            cookie.append("\"");
        }
        if (!m_strDomain.empty())
        {
            cookie.append("; Domain=\"");
            cookie.append(m_strDomain);
            cookie.append("\"");
        }
        if (!m_strPath.empty())
        {
            cookie.append("; Path=\"");
            cookie.append(m_strPath);
            cookie.append("\"");
        }
        if (m_ttExpire != -1)
        {
            char szBuf[16];
            time_t now;
            time(&now);
            cookie.append("; Max-Age=\"");
            if (now >= m_ttExpire)
            {
                cookie.append("0");
            }
            else
            {
                sprintf(szBuf, "%d", (int)(m_ttExpire - now));
                cookie.append(szBuf);
            }
            cookie.append("\"");
        }
        if (m_bSecure)  cookie.append("; secure");
        if (m_bHttpOnly) cookie.append("; HttpOnly");
        cookie.append("; Version=\"1\"");
    }
    return cookie;
}

CWINUX_END_NAMESPACE

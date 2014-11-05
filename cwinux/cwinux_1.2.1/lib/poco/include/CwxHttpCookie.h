#ifndef __CWX_HTTP_COOKIE_H__
#define __CWX_HTTP_COOKIE_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxHttpCookie.h
@brief ������HTTP��cookie����֧��V0��V1��ȱʡΪV0
@author cwinux@gmail.com
@version 0.1
@date 2009-10-16
@warning
@bug
*/

#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxStl.h"
#include "CwxCommon.h"
#include "CwxDate.h"

CWINUX_BEGIN_NAMESPACE

/**
@class CwxHttpCookie
@brief HTTPЭ���Cookie����Ķ��壬֧��V0��V1��
*/
class CWX_API CwxHttpCookie
{
public:
    ///ȱʡ���캯��
	CwxHttpCookie();
    ///ͨ��ָ�������֣�����һ��cookie����Ч��Ϊ��Զ��
	explicit CwxHttpCookie(string const& name);
    ///ͨ��ָ�������ּ���ֵ������һ��cookie����Ч��Ϊ��Զ��
	CwxHttpCookie(string const& name, string const& value);
    ///�������캯��
    CwxHttpCookie(CwxHttpCookie const& cookie);
    ///��������
    ~CwxHttpCookie();
    ///��ֵ����	
    CwxHttpCookie& operator = (const CwxHttpCookie& cookie);
public:
    ///����cookie�İ汾�ţ�ȱʡΪ0
	void setVersion(int version=0);
    ///��ȡcookie�İ汾��
	int getVersion() const;
    ///����cookie������		
	void setName(char const* name);
    ///��ȡcookie������		
	string const& getName() const;
    ///����cookie����ֵ���䳤�Ȳ��ܳ���4K
	void setValue(char const* value);
    ///��ȡcookie����ֵ		
	string const& getValue() const;
    ///����cookie��comment,ֻ��v1֧��comment
	void setComment(char const* comment);
    ///��ȡcookie��comment
	string const& getComment() const;
    ///����cookie��domain
	void setDomain(char const* domain);
    ///��ȡcookie��domain		
	string const& getDomain() const;
    ///����cookie��·��
	void setPath(char const* path);
    ///��ȡcookie��·��		
	string const& getPath() const;
    ///����cookie�İ�ȫflag
	void setSecure(bool secure);
    ///��ȡ�Ƿ������˰�ȫflag
	bool getSecure() const;
    ///����ʧЧʱ�䡣ttTimeΪʧЧ��ʱ��㡣
    void setExpire(time_t ttTime);
    ///��ȡ�������ʧЧ��
	time_t getExpire() const;
    ///����ʧЧʱ�䣬Ϊyyyy-mm-dd hh:mm:ss��ʽ��
    void setExpire(char const* daytime);
    ///��ȡʧЧ��ʱ�䡣���صĸ�ʽΪyyyy-mm-dd hh:mm:ss��ʽ��
    string& getExpire(string& daytime) const;
    ///����cookie��HttpOnly���
    void setHttpOnly(bool flag);
    ///��ȡcookie��HttpOnly���		
	bool getHttpOnly() const;
    ///����cookie���ַ���		
	string& toCookie(string& cookie) const;
    ///�ڳ����ʱ�򣬷��ش�����Ϣ
    string const& getErrMsg() const
    {
        return m_strErr;
    }
private:
	int         m_iVersion; ///<version
	string      m_strName; ///<cookie's name
	string      m_strValue; ///<cookie's value
	string      m_strComment; ///<cookie's comment, only for v1
	string      m_strDomain; ///<cookie's domain
	string      m_strPath; ///<cookie's path
	bool        m_bSecure; ///<cookie's secure sign
    time_t      m_ttExpire; ///<cookie's expire time
	bool        m_bHttpOnly; ///<http-only sign
    string      m_strErr; ///<error msg for failure
};

CWINUX_END_NAMESPACE
#include "CwxHttpCookie.inl"
#include "CwxPost.h"

#endif

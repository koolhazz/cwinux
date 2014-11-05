#ifndef __CWX_URI_H__
#define __CWX_URI_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxURI.h
@brief ������URI�࣬ʵ��URI��Դ�Ľ����봦��
@author cwinux@gmail.com
@version 0.1
@date 2009-10-15
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxStl.h"
#include "CwxStlFunc.h"

CWINUX_BEGIN_NAMESPACE
/**
@class CwxURI
@brief Uniform Resource Identifier, ʵ��RFC 3986��specification��
       ���ֲ������Ǵ�Сд���еġ�������scheme��host��path��arg������fragment��
       ���û��ȡ��Ӧ���Ǿ�������ġ�URI���󲻸������Ĵ���
*/

class CWX_API CwxURI
{
public:
    ///Ĭ�Ϲ��캯��
	CwxURI();
    ///ָ��URI�Ĺ��캯��
	explicit CwxURI(char const* uri);
    ///��������
	CwxURI(CwxURI const& uri);
    ///��������
	~CwxURI();
public:	
    ///��ֵ����
	CwxURI& operator = (CwxURI const& uri);
    ///ͨ���ַ����ĸ�ֵ����
	CwxURI& operator = (char const* uri);
    ///��ͬ�Ƚϲ���
    bool operator == (CwxURI const& uri) const;
    ///��ͬ�Ƚϲ���
    bool operator == (char const* uri) const;
    ///����ͬ�Ƚϲ���
    bool operator != (CwxURI const& uri) const;
    ///����ͬ�Ƚϲ���
    bool operator != (char const* uri) const;
public:
    ///����uri������ֵ��true���ɹ���false����Ч
    bool setUri(char const* uri);
    ///��ȡURI��scheme����http��ftp��
    string const& getScheme() const;
    ///����URI��scheme
    void setScheme(char const* scheme);
    ///��ȡURI�е��û�info
    string const& getUserInfo() const;
    ///����URI�е��û�info
    void setUserInfo(char const* userInfo);
    ///��ȡURI������
    string const& getHost() const;
    ///����URI������
    void setHost(char const* host);
    ///��ȡ�˿ں�
    CWX_UINT16 getPort() const;
    ///���ö˿ں�
    void setPort(CWX_UINT16 port);
    ///����uri�е�Ȩ�޲��֣�Ϊuserinfo\@host�򵱶˿ڲ�Ϊ��׼�˿ڵ�ʱ�򣬷���userinfo\@host:port
    string const& getAuthority(string& strAuth) const;
    ///����URI��Ȩ�޲��֣���ʽΪuserinfo\@host�򵱶˿ڲ�Ϊ��׼�˿ڵ�ʱ��userinfo\@host:port
    bool setAuthority(char const* authority);
    ///��ȡURI��·��
    string const& getPath() const;
    ///����URI��·��
    void setPath(char const* path);
    ///��ȡURI�Ĳ�������
    string const& getArg() const;
    ///����url�Ĳ�������
    void setArg(char const* arg);	
    ///��ȡURI��fragment����
    string const& getFragment() const;
    ///����URI��fragment����
    void setFragment(char const* fragment);
    ///��ȡpath��arg����
    string & getPathArg(string & pathArg) const;
    ///�ж϶����Ƿ�Ϊ��
    bool empty() const;
    ///�ж�uri�Ƿ�Ϊ���Ŀ¼����schemeΪ��
    bool isRelative() const;
    ///���س���ʱ�Ĵ�����Ϣ
    string const& getErrMsg() const
    {
        return m_strErrMsg;
    }
public:
    ///���URI
    string& toUri(string& uri) const;
    ///��ն���
	void clear();
		
protected:
    ///�ж�uri�뱾�����Ƿ����
	bool equals(CwxURI const& uri) const;
    ///�ж����õĶ˿ں��Ƿ���scheme�ı�׼�˿ں�
	bool isDefPort() const;
    ///��ȡscheme�ı�׼�˿ں�
	CWX_UINT16 getDefPort(char const* szScheme) const;
    ///����URI������URI��ʼ�����󣬷���ֵ��false����Ч��URI��true���ɹ���
	bool parse(char const* uri);
    ///����URI��userinfo\@host:port���֣�����ֵ��false����Ч��URI��true���ɹ���
    bool parseAuth(char const*& auth);
    ///����URI��Path arg��fragment���֣�����ֵ��false����Ч��URI��true���ɹ���
    bool parsePathArgFragment(char const*& pathArgFrag);
    ///����URI��host:port����
    bool parseHostAndPort(char const* host_port);
    ///����path
    bool parsePath(char const*& path);
    ///����path
    bool parseArg(char const*& arg);
    ///����fragment
    bool parseFragment(char const*& fragment);

private:
    string         m_strScheme; ///<uri's scheme
    string         m_strUserInfo;///<uri's user 
    string         m_strHost; ///<uri's host
    CWX_UINT16     m_unPort; ///<uri's host port
    string         m_strPath;///<uri's path
    string         m_strArg; ///<uri's argument
    string         m_strFragment; ///<uri's fragment
    string         m_strErrMsg; ///<failure message
};

CWINUX_END_NAMESPACE
#include "CwxURI.inl"
#include "CwxPost.h"

#endif

#ifndef __CWX_UNIX_ACCEPTOR_H__
#define __CWX_UNIX_ACCEPTOR_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxUnixAcceptor.h
@brief UNIX Domain�������ӽ��ն���Ķ��塣
@author cwinux@gmail.com
@version 0.1
@date 2009-10-12
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxType.h"
#include "CwxNetMacro.h"
#include "CwxUnixAddr.h"
#include "CwxUnixStream.h"
#include "CwxSockAcceptor.h"

CWINUX_BEGIN_NAMESPACE
/**
@class CwxUnixAcceptor
@brief Unix domain�������ӽ��ն���
*/
class CWX_API CwxUnixAcceptor:public CwxSockAcceptor
{
public:
    ///Ĭ�Ϲ��캯��
    CwxUnixAcceptor();
    ///�򿪼����˿ڵĹ��캯��
    CwxUnixAcceptor(CwxAddr const& addr,
        bool reuse= 0,
        int backlog = DEF_BACK_LOG,
        int domain = PF_UNIX,
        int protocol = 0);

    ///��������.
    ~CwxUnixAcceptor(void);
public:
    /**
    @brief ����TCP�������ӡ�
    @param [in] addr Accept�ı��ص�ַ��
    @param [in] reuse ��������ַû���ͷŵĻ����Ƿ�re-use��true���ǣ�false�����ǡ�
    @param [in] backlog listen����Ŷӵ�������
    @param [in] domain Э���壬����socket()�е�domain������PF_UNIX��
    @param [in] protocol ���ӵ�Э�飬����socket()��protocol����������һ��Э������socket ���ͣ���protocolҲ��Ψһ�ģ�Ϊ0�Ϳ����ˡ�
    @return -1������errno��¼�����ԭ��0���ɹ���
    */
    int listen(CwxAddr const& addr,
        bool reuse= 0,
        int backlog = DEF_BACK_LOG,
        int domain = PF_UNIX,
        int protocol = 0);
    /**
    @brief ����һ������TCP���ӡ�
    @param [in] stream ���ؽ��յ��ı������ӡ�
    @param [in] remote_addr ����Ϊ�գ��򷵻ؽ��յ��ĶԶ�host�ĵ�ַ��
    @param [in] timeout accept�ĳ�ʱʱ�䣬��ΪNULL�������޵ȴ���
    @param [in] bRestart ���ڵȴ������б��ź��жϣ��Ƿ�����ȴ���1�������ȴ���0�����ȴ���
    @return -1������errno��¼�����ԭ��0���ɹ���
    */
    int accept (CwxUnixStream &stream,
        CwxAddr* remote_addr = 0,
        CwxTimeouter* timeout = NULL,
        bool bRestart = 1) const;
public:
    /// Close down the CwxUnixStream and remove the rendezvous point from the
    /// file system.
    int remove (void);
    /// Return the local endpoint address.
    int getLocalAddr (CwxAddr &) const;
private:
    int getRemoteAddr(CwxAddr &) const;
private:
    CwxUnixAddr   local_addr_;

};

CWINUX_END_NAMESPACE

#include "CwxUnixAcceptor.inl"
#include "CwxPost.h"

#endif

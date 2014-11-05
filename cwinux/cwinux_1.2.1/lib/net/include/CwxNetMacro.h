#ifndef __CWX_NET_MACRO_H__
#define __CWX_NET_MACRO_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwxNetMacro.h
@brief Netģ��Ĺ����궨���ļ���
@author cwinux@gmail.com
@version 0.1
@date 2009-10-10
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"

#include <netinet/in.h>
#include <arpa/inet.h>

# if !defined (INADDR_ANY)
#   define INADDR_ANY (CWX_UINT32)0x00000000
# endif /* INADDR_ANY */

#if !defined (INADDR_LOOPBACK)
#  define INADDR_LOOPBACK ((CWX_UINT32) 0x7f000001)
#endif /* INADDR_LOOPBACK */

#if !defined (AF_ANY)
#  define AF_ANY (-1)
#endif /* AF_ANY */

#define  CWX_HAS_IPV6  0
#define  CWX_IPV4_IPV6_MIGRATION 0

#define CWX_HAS_SOCKADDR_IN6_SIN6_LEN 0
#define CWX_HAS_SOCKADDR_IN_SIN_LEN 0


#define CWX_MAX_DEFAULT_PORT 65535

#define CWX_MAX_HOST_NAME_LEN  256

#include "CwxPost.h"

#endif

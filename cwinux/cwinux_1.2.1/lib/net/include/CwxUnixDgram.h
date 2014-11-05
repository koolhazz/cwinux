#ifndef __CWX_UNIX_DGRAM_H__
#define __CWX_UNIX_DGRAM_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxUnixDgram.h
@brief unix domain Э�����UDP������ͨ�Ŷ���Ķ��塣
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
#include "CwxSockDgram.h"

CWINUX_BEGIN_NAMESPACE
/**
@class CwxUnixDgram
@brief Unix domainЭ������������UDPͨ�Ŷ���
*/
class CWX_API CwxUnixDgram:public CwxSockDgram
{
public:
    ///Ĭ�Ϲ��캯��
    CwxUnixDgram();
    ///���캯�������������趨����handle
    CwxUnixDgram(CWX_HANDLE handle);
    ///��������.
    ~CwxUnixDgram(void);
public:
private:
    /**
    * Return the address of the remotely connected peer (if there is
    * one), in the referenced CwxAddr. Returns 0 if successful, else
    * -1.
    */
    int getRemoteAddr (CwxAddr &) const;

};

CWINUX_END_NAMESPACE

#include "CwxUnixDgram.inl"
#include "CwxPost.h"

#endif

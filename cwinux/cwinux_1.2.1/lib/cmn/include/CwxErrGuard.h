#ifndef __CWX_ERR_GUARD_H__
#define __CWX_ERR_GUARD_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxErrGuard.h
@brief ������CwxErrGuard�࣬ȷ��errno�������ǡ�
@author cwinux@gmail.com
@version 0.1
@date 2010-07-10
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxType.h"

CWINUX_BEGIN_NAMESPACE

/**
@class CwxErrGuard
@brief ȷ��errno�������ǡ�
*/
class CWX_API CwxErrGuard
{
public:
    CwxErrGuard();
    ~CwxErrGuard();
private:
    int    m_errno;
};

CWINUX_END_NAMESPACE

#include "CwxErrGuard.inl"
#include "CwxPost.h"

#endif


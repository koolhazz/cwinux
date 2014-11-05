#ifndef __CWX_ESCAPE_H__
#define __CWX_ESCAPE_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxEscape.h
@brief escape�ӿڵĶ��壬ʵ�ָ����ַ��任��
@author cwinux@gmail.com
@version 0.1
@date 2009-11-10
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxChrType.h"
#include "CwxEscapeUtil.h"
#include "CwxCommon.h"
CWINUX_BEGIN_NAMESPACE
/**
@class CwxEscape
@brief �����ַ��ı��롢���������Ĭ��ʲô������
*/
class CWX_API CwxEscape
{
public:
    ///���캯��
    CwxEscape(){}
    ///��������
    virtual ~CwxEscape(){}
public:
    /**
    @brief ��szSrc���ַ������б��룬�������ַ������szOut�С�
    @param [in] szSrc ��Ҫ���б�����ַ���
    @param [in] uiSrcLen Դ�ַ����ĳ���
    @param [out] szOut �������ַ������γ��ַ�����\\0������
    @param [in,out] uiOutLen ����szOut�Ŀռ��С����������ĳ���
    @return true���ɹ���false:szOut�Ŀռ䲻�㡣
    */
    virtual bool encode(char const* szSrc, CWX_UINT32 uiSrcLen, char* szOut, CWX_UINT32& uiOutLen) const
    {
        if (uiSrcLen >= uiOutLen) return false;
        memcpy(szOut, szSrc, uiSrcLen);
        szOut[uiSrcLen] = 0x00;
        uiOutLen = uiSrcLen;
        return true;
    }
    /**
    @brief ��szSrc���ַ������н��룬�������ַ������szOut�С�
    @param [in] szSrc ��Ҫ���н�����ַ���
    @param [in] uiSrcLen Դ�ַ����ĳ���
    @param [out] szOut �������ַ������γ��ַ�����\\0������
    @param [in,out] uiOutLen ����szOut�Ŀռ��С����������ĳ���
    @return true���ɹ���false:szOut�Ŀռ䲻�㡣
    */
    virtual bool decode(char const* szSrc, CWX_UINT32 uiSrcLen, char* szOut, CWX_UINT32& uiOutLen) const
    {
        if (uiSrcLen >= uiOutLen) return false;
        memcpy(szOut, szSrc, uiSrcLen);
        szOut[uiSrcLen] = 0x00;
        uiOutLen = uiSrcLen;
        return true;
    }
};

CWINUX_END_NAMESPACE

#include "CwxPost.h"

#endif

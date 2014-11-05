#ifndef __CWX_MD5_H__
#define __CWX_MD5_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/* MD5DEEP - md5.h
 *
 * By Jesse Kornblum
 *
 * This is a work of the US Government. In accordance with 17 USC 105,
 * copyright protection is not available for any work of the US Government.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/**
*@file  CwxMd5.h
*@brief  ��������Դ��MD5DEEP����CWINUX��C����Ϊ��C++��������CWINUX�Ľӿ�
         ���ļ�������CwxMd5���࣬ʵ��MD5��ǩ��
*@author cwinux@gmail.com
*@version 0.1
*@date    2009-11-28
*@warning ��
*@bug   
*/

#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxUtilMacro.h"

CWINUX_BEGIN_NAMESPACE
/**
*@class  CwxMd5
*@brief  Md5��ǩ�����󡣴˶�����̲߳���ȫ���ڶ��̻߳����£�
        ÿ���߳���Ҫ�Լ���һ������ʵ����
*/
class CwxMd5
{
public:
    ///���캯��
    CwxMd5();
    ///��������
    ~CwxMd5();
public:
    /**
    *@brief  ����buf�����ݣ���MD5ǩ�����и���
    *@param [in] szBuf ǩ��������.
    *@param [in] uiLen ���ݵĳ���.
    *@return void.
    */
    void update(unsigned char *szBuf, CWX_UINT32 uiLen);
    /**
    *@brief  ���16�ֽڵ�ǩ������
    *@param [out] digest ������ݵ�ǩ��.
    *@return void.
    */
    void final(unsigned char digest[16]);
private:
    void transform(CWX_UINT32 buf[4], CWX_UINT32 const in[16]);
    void byteReverse(unsigned char *buf, CWX_UINT32 uiLen);
    void init();
private:
    CWX_UINT32     m_buf[4]; 
    CWX_UINT32     m_bits[2];
    unsigned char  m_in[64];
};

CWINUX_END_NAMESPACE

#include "CwxPost.h"

#endif

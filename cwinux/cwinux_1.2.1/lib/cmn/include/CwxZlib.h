#ifndef __CWX_ZLIB_H__
#define __CWX_ZLIB_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
*@file CwxZlib.h
*@brief ZLIB�ļ򵥷�װ������ʵ��CWINUXƽ̨��ѹ��
*@author cwinux@gmail.com
*@version 1.0
*@date  2009-10-25
*@warning  nothing
*@bug    
*/

#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include <zlib.h>
CWINUX_BEGIN_NAMESPACE
/**
*@class  CwxZlib
*@brief  zlib��ļ򻯷�װ��ʵ��CWXINUX������ѹ������ѹ���ܡ�
*
*/
class CwxZlib
{
public:
    /**
    *@brief ��szSrc����ѹ��������ѹ��������ݱ�����szDest��
    *@param [out] szDest ѹ���������.
    *@param [in, out] ulDestLen ����szDest�ĳ��ȣ�����ѹ�������ݵĳ���.
    *@param [in] szSrc ѹ��ǰ������.
    *@param [in] ulSrcLen ѹ��ǰ���ݵĳ���.
    *@param [in] ucLevel ѹ���ļ���0~9��0��ʾ��ѹ��,����ԽС��ѹ����Խ�ͣ��ٶ�Խ�죬Z_DEFAULT_COMPRESSIONΪȱʡ��
    *@return true:success; false:failure.
    */
    static inline bool zip(unsigned char* szDest,
        unsigned long& ulDestLen,
        const unsigned char* szSrc,
        unsigned long ulSrcLen,
        CWX_UINT8 ucLevel=Z_DEFAULT_COMPRESSION)
    {
        return Z_OK == compress2(szDest, &ulDestLen, szSrc, ulSrcLen, ucLevel);
    }
    /**
    *@brief ��ѹ�������ݽ�ѹ
    *@param [out] szDest ��ѹ�������.
    *@param [in, out] ulDestLen ����szDest�ĳ��ȣ����ؽ�ѹ�����ݵĳ���.
    *@param [in] szSrc ��ѹǰ������.
    *@param [in] ulSrcLen ��ѹǰ���ݵĳ���.
    *@return true:success; false:failure.
    */
    static inline bool unzip(unsigned char* szDest,
        unsigned long& ulDestLen,
        const unsigned char* szSrc,
        unsigned long ulSrcLen)
    {
        return Z_OK == uncompress(szDest,&ulDestLen,szSrc,ulSrcLen);
    }
};

CWINUX_END_NAMESPACE

#include "CwxPost.h"

#endif

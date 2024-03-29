#ifndef __CWX_ZLIB_H__
#define __CWX_ZLIB_H__
/*
版权声明：
    本软件为个人所有，遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html），
但有以下例外：
    腾讯公司及与腾讯公司有直接业务与合作关系的公司不得使用此软件。原因可参考：
http://it.sohu.com/20100903/n274684530.shtml
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/

/**
*@file CwxZlib.h
*@brief ZLIB的简单封装，用于实现CWINUX平台的压缩
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
*@brief  zlib库的简化封装，实现CWXINUX的数据压缩、解压功能。
*
*/
class CwxZlib
{
public:
    /**
    *@brief 对szSrc进行压缩，并将压缩后的数据保存于szDest。
    *@param [out] szDest 压缩后的数据.
    *@param [in, out] ulDestLen 传入szDest的长度，传出压缩后数据的长度.
    *@param [in] szSrc 压缩前的数据.
    *@param [in] ulSrcLen 压缩前数据的长度.
    *@param [in] ucLevel 压缩的级别，0~9，0表示不压缩,数字越小，压缩率越低，速度越快，Z_DEFAULT_COMPRESSION为缺省。
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
    *@brief 对压缩的数据解压
    *@param [out] szDest 解压后的数据.
    *@param [in, out] ulDestLen 传入szDest的长度，返回解压后数据的长度.
    *@param [in] szSrc 解压前的数据.
    *@param [in] ulSrcLen 解压前数据的长度.
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

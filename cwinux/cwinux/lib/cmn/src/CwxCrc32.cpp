#include "CwxCrc32.h"

CWINUX_BEGIN_NAMESPACE



#include <stdint.h>



CWX_UINT32 CwxCrc32::extend(CWX_UINT32 crc, const char* buf, size_t size)
{
    return crc32( crc, (unsigned char*)buf, size );
}

CWINUX_END_NAMESPACE

#ifndef __CWM_CENTER_TSS_H__
#define __CWM_CENTER_TSS_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmCenterTss.h
@brief ���ϵͳ�е�Center�����TSS�����ļ���
@author cwinux@gmail.com
@version 0.1
@date 2009-11-05
@warning
@bug
*/

#include "CwxGlobalMacro.h"
#include "CwxStl.h"
#include "CwxStlFunc.h"
#include "CwxCommon.h"
#include "CwxPackageWriter.h"
#include "CwxAppLogger.h"
#include "CwxAppTss.h"
#include "CwxXmlPackageConv.h"
#include "CwmCmnMacro.h"

class CwmCenterActionLoop;
class CwmCenterServiceLoop;
class CwmCenterSystemLoop;
class CwmCenterActionNameLoop;
//center��tss
class CwmCenterTss:public CwxAppTss
{
public:
    enum
    {
        MAX_PACKAGE_SIZE = 2 * 1024 * 1024 ///<UI��ѯ�������ݰ�����󳤶�
    };
public:
    ///���캯��
    CwmCenterTss():CwxAppTss(new CwxAppTssInfo)
    {
        m_pSndPackage = NULL;
        m_szOutputBuf = NULL;
        m_uiOutputDataLen = 0;
        m_pActionNameLoop = NULL;
        m_pActionLoop = NULL;
        m_pServiceLoop = NULL;
        m_pSystemLoop = NULL;
    }
    ///��������
    ~CwmCenterTss();
public:
    ///tss�ĳ�ʼ��
    int init();
public:
    CwxPackageWriter*   m_pSndPackage; ///<reply query's package writer
    char*              m_szOutputBuf; ///<template's output buf
    CWX_UINT32         m_uiOutputDataLen; ///<ģ����������ݳ���
    char               m_szKeyValue64K[60 * 1024]; ///<ģ�����key��data����ʱ�ռ�
    CwmCenterActionNameLoop* m_pActionNameLoop; ///<service��action���ֵ�loop
    CwmCenterActionLoop*  m_pActionLoop; ///<service��action��loop����
    CwmCenterServiceLoop*  m_pServiceLoop;  ///<system��service��loop����
    CwmCenterSystemLoop* m_pSystemLoop; ///<system��loop����
};





#endif

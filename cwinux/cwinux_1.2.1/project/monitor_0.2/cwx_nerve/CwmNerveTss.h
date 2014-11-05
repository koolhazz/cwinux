#ifndef __CWM_NERVE_TSS_H__
#define __CWM_NERVE_TSS_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwmNerveTss.h
@brief ���ϵͳ�е�Nerve�����TSS�����ļ���
@author cwinux@gmail.com
@version 0.1
@date 2009-10-25
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

//nerve��tss
class CwmNerveTss:public CwxAppTss
{
public:
    enum
    {
        MAX_PACKAGE_SIZE = 128 * 1024 ///<��ѯ���ݰ�����󳤶�
    };
public:
    ///���캯��
    CwmNerveTss():CwxAppTss(new CwxAppTssInfo)
    {
        m_pSndPackage = NULL;
        m_szBuf = NULL;
        m_uiBufDataLen = 0;
        m_pXmlEncode = NULL;
        m_pXmlConv = NULL;
    }
    ///��������
    ~CwmNerveTss()
    {
        if (m_pSndPackage) delete m_pSndPackage;
        if (m_szBuf) delete [] m_szBuf;
        if (m_pXmlEncode) delete m_pXmlEncode;
        if (m_pXmlConv) delete m_pXmlConv;
    }
public:
    ///��ʼ��tss�ĳ�Ա��-1��ʧ�ܣ�0���ɹ�
    int init()
    {
        m_pSndPackage = new CwxPackageWriter(MAX_PACKAGE_SIZE);
        m_szBuf = new char[MAX_PACKAGE_SIZE];
        m_pXmlEncode = new CwxEncodeXml(false, true);
        if (!m_pXmlEncode->init())
        {
            CWX_ERROR(("Failure to init xml-encode"));
            return -1;
        }
        m_pXmlConv = new CwxXmlPackageConv(m_pXmlEncode);
        return 0;
    }
public:
    ///��ȡ���͵�package writer
    CwxPackageWriter* getSndPackage()
    {
        return m_pSndPackage;
    }
    ///package��buf����package writer��С��ͬ������XML��package��ת��
    char* getBuf()
    {
        return m_szBuf;
    }
    ///��ȡpackage��XMLת����
    CwxXmlPackageConv*   getXmlPackageConv()
    {
        return m_pXmlConv;
    }
    ///����buf�����ݵĳ���
    void setBufDataLen(CWX_UINT32 uiLen)
    {
        m_uiBufDataLen = uiLen;
    }
    ///��ȡbuf�����ݵĳ���
    CWX_UINT32 getBufDataLen() const
    {
        return m_uiBufDataLen;
    }
private:
    CwxPackageWriter*   m_pSndPackage; ///<reply query's package writer
    char*              m_szBuf;     ///<XML��PACKAGEת����buf
    CWX_UINT32         m_uiBufDataLen; ///<buf�����ݵĳ���
    CwxEncodeXml*       m_pXmlEncode;   ///<xml�����ַ�ת��
    CwxXmlPackageConv*   m_pXmlConv;  ///<xml��package��ת����
};





#endif

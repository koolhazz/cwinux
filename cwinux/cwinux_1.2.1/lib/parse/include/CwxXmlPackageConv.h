#ifndef __CWX_XML_PACKAGE_CONV_H__
#define __CWX_XML_PACKAGE_CONV_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxXmlPackageConv.h
@brief ����XML��Package�໥ת���Ķ���CwxXmlPackageConv��
@author cwinux@gmail.com
@version 0.1
@date 2009-10-10
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxType.h"
#include "CwxStl.h"
#include "CwxStlFunc.h"
#include "CwxReplMachine.h"
#include "CwxPackageReader.h"
#include "CwxPackageWriter.h"
#include "CwxEncodeXml.h"
#include "CwxXmlConfigParser.h"

CWINUX_BEGIN_NAMESPACE
/**
@class CwxXmlPackageConv
@brief ʵ��XML��Package���໥ת����
*/
class CWX_API CwxXmlPackageConv
{
public:
    ///���캯��������ΪXML��encode�滻�������ⲿ���й���
    CwxXmlPackageConv(CwxEncodeXml const* encode)
        :m_xmlEncode(encode)
    {
        memset(m_szErrMsg, 0x00, 512);
    }
    ///��������
    ~CwxXmlPackageConv()
    {

    }
public:
    /**
    *@brief  ��XMLת��ΪPackage.
    *@param [in] szSrc XML��
    *@param [out] szOut �����PACKAGE��
    *@param [in,out] uiOutLen ����szDesc������������γɵ�Package�Ĵ�С��
    *@return false��ʧ�ܣ�true���ɹ�.
    */ 
    bool xmlToPackage(char const * szSrc,
        char* szOut,
        CWX_UINT32& uiOutLen);
    /**
    *@brief  ��Packageת��Ϊ������XML��Ĭ�ϲ���UTF8����
    *@param [in] szRootName �γɵ�XML���ڵ������,���Ϊ�գ����ʾû�и��ڵ㡣
    *@param [in] szSrc package��buf��
    *@param [in] uiSrcLen Package�Ĵ�С��
    *@param [out] szOut �����XML��
    *@param [in,out] uiOutLen ����XML��BUF��С������γɵ�XML�ĳ��ȡ�
    *@param [in] szXmlTitile XML�ı��⣬����ָ������Ϊ��<?xml version='1.0' encoding=\"utf-8\" ?>��
    *@return false��ʧ�ܣ�true���ɹ�.
    */ 
    bool packageToXml(char const* szRootName,
        char const * szSrc,
        CWX_UINT32 uiSrcLen,
        char* szOut,
        CWX_UINT32& uiOutLen,
        char const* szXmlTitile=NULL);
    /**
    *@brief  ��Packageת��Ϊ������XML��Ĭ�ϲ���UTF8����
    *@param [in] szRootName �γɵ�XML���ڵ������,���Ϊ�գ����ʾû�и��ڵ㡣
    *@param [in] package package��
    *@param [out] szOut �����XML��
    *@param [in,out] uiOutLen ����XML��BUF��С������γɵ�XML�ĳ��ȡ�
    *@param [in] szXmlTitile XML�ı��⣬����ָ������Ϊ��<?xml version='1.0' encoding=\"utf-8\" ?>��
    *@return false��ʧ�ܣ�true���ɹ�.
    */ 
    bool packageToXml(char const* szRootName,
        CwxPackageReader& package,
        char* szOut,
        CWX_UINT32& uiOutLen,
        char const* szXmlTitile=NULL);
    /**
    *@brief  ��packageת��Ϊ��szNodeNameΪ�ڵ��XMLƬ��.
    *@param [in] szNodeName �γɵ�XML�Ľڵ������,���Ϊ�գ����ʾû�и��ڵ㡣
    *@param [in] szSrc package��buf��
    *@param [in] uiSrcLen PACKAGE�ĳ��ȡ�
    *@param [out] szOut �����XML��
    *@param [in,out] uiOutLen ����XML��BUF��С������γɵ�XML�ĳ��ȡ�
    *@return false��ʧ�ܣ�true���ɹ�.
    */ 
    bool packageToXmlNode(char const* szNodeName,
        char const * szSrc,
        CWX_UINT32 uiSrcLen,
        char* szOut,
        CWX_UINT32& uiOutLen);
    /**
    *@brief  ��packageת��Ϊ��szNodeNameΪ�ڵ��XMLƬ��.
    *@param [in] szNodeName �γɵ�XML�Ľڵ������,���Ϊ�գ����ʾû�и��ڵ㡣
    *@param [in] package package��
    *@param [out] szOut �����XML��
    *@param [in,out] uiOutLen ����XML��BUF��С������γɵ�XML�ĳ��ȡ�
    *@return false��ʧ�ܣ�true���ɹ�.
    */ 
    bool packageToXmlNode(char const* szNodeName,
        CwxPackageReader& package,
        char* szOut,
        CWX_UINT32& uiOutLen);
    ///���ش�����Ϣ
    char const* getErrMsg() const{ return m_szErrMsg;}
private:
    ///xmlת��Ϊpackage
    bool xmlToPackage(CwxXmlTreeNode const * treeNode, char* szOut, CWX_UINT32& uiOutLen);
    ///packageת��Ϊxml
    bool packageToXml(CwxKeyValueItem const& item, char* szOut, CWX_UINT32& uiOutLen);
    ///append <key>
    bool appendXmlKeyBegin(char const* szKey, CWX_UINT16 unKeyLen, char* szOut, CWX_UINT32& uiOutLen);
    ///append </key>
    bool appendXmlKeyEnd(char const* szKey, CWX_UINT16 unKeyLen, char* szOut, CWX_UINT32& uiOutLen);
private:
    CwxEncodeXml const*  m_xmlEncode;///<xml�������ַ��滻��
    char m_szErrMsg[512];///<����buf
};

CWINUX_END_NAMESPACE
#include "CwxPost.h"

#endif

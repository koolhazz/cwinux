#ifndef __CWX_XML_TREE_NODE_H__
#define __CWX_XML_TREE_NODE_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxXmlTreeNode.h
@brief XML�����ݽڵ㶨�塣
@author cwinux@gmail.com
@version 0.1
@date 2009-10-10
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxStl.h"
#include "CwxCommon.h"
#include "CwxCharPool.h"


#include "CwxParseMacro.h"

CWINUX_BEGIN_NAMESPACE

/**
@class CwxXmlTreeNode
@brief ��״�����ݽڵ�������ڱ�ʾXML��JSON�����ݽڵ㡣
*/
class CWX_API CwxXmlTreeNode
{
public:
    ///���캯��
    CwxXmlTreeNode()
    {
        m_pChildHead = NULL;
        m_pChildTail = NULL;
        m_prev = NULL;
        m_next = NULL;
        m_pParent = NULL;
    }
    ///��������
    ~CwxXmlTreeNode()
    {
        if (m_pChildHead) delete m_pChildHead;
        if (m_next) delete m_next;
    }
public:
    char*   m_szElement;///<�ڵ������
    list<char*>   m_listData; ///<XML��\<aaa\>aaaaa\</aaa\>���ͽڵ������
    list<pair<char*, char*> > m_lsAttrs;///<�ڵ����Ե�key,value��
    CwxXmlTreeNode* m_pChildHead;///<�ڵ�ĺ��ӽ���ͷ
    CwxXmlTreeNode* m_pChildTail;///<�ڵ�ĺ��ӽ���β
    CwxXmlTreeNode* m_prev;///<�ڵ��ǰһ���ֵܽڵ�
    CwxXmlTreeNode* m_next;///<�ڵ����һ���ֵܽڵ�
    CwxXmlTreeNode* m_pParent;///<�ڵ�ĸ��ڵ�
};

CWINUX_END_NAMESPACE

#include "CwxPost.h"

#endif


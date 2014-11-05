#ifndef __CWX_APP_PAI_H__
#define __CWX_APP_PAI_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppPai.h
@brief ͨ��Э���������ӿڶ���
@author cwinux@gmail.com
@version 0.1
@date 2009-07-20
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxMsgBlock.h"
#include "CwxAppConfig.h"
#include "CwxAppMacro.h"
#include "CwxAppHandler4Msg.h"


CWINUX_BEGIN_NAMESPACE
/**
@class CwxAppPai
@brief ͨ�����ݰ�Э������ӿڶ���Pai��protocol Adapter interface����д
*/
class CWX_API CwxAppPai
{
public:
    ///���캯��������Ϊ��������Ӷ���
    CwxAppPai(CwxAppHandler4Msg const* conn);
    ///��������
    virtual ~CwxAppPai();
public:
    /**
    @brief ֪ͨ�������յ�������
    @param [in] msg �յ������ݰ�������Ϣ��Э������������ͷ�
    @param [in] conn �յ���Ϣ�����ӡ�
    @param [in] header �յ���Ϣ����Ϣͷ��
    @param [in] bSuspendConn �Ƿ�suspend�����ϵ����ݽ���
    @return -1����Ϣ��Ч���ر����ӡ� 0��������������Ϣ�� >0�������Ӵ������Ͻ�����Ϣ��
    */
    virtual int noticeRecvMsg(CwxMsgBlock* msg,
        CwxAppHandler4Msg const& conn,
        CwxMsgHead const& header,
        bool& bSuspendConn) = 0;
    ///��鷢��KEEP-ALIVE����Ϣ������ֵ��-1���ر����ӣ�0,����
    virtual int checkKeepAlive()
    {
        return 0;
    }
    ///����Ƿ�������ҪKEEP-ALIVE
    bool isKeepAlive() const
    {
        return m_bKeepAlive;
    }
    ///�����Ƿ�������ҪKEEP-ALIVE
    void setKeepAlive(bool bKeepAlive)
    {
        m_bKeepAlive = bKeepAlive;
    }
private:
    CwxAppHandler4Msg const*   m_pConn;///<���Ӷ���
    bool          m_bKeepAlive;///<�Ƿ���ҪKEEP-ALIVE�ı�־
};


CWINUX_END_NAMESPACE

#include "CwxPost.h"

#endif 

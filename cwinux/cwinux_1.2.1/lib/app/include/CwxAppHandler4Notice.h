#ifndef __CWX_APP_HANDLER_4_NOTICE_H__
#define __CWX_APP_HANDLER_4_NOTICE_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
*@file  CwxAppHandler4Notice.h
*@brief �ܹ�Notice�¼����źš�ʱ�ӵĴ���Hanlde������
*@author cwinux@gmail.com
*@version 0.1
*@date  2009-05-30
*@warning  ��.
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxAppConfig.h"
#include "CwxAppMacro.h"
#include "CwxAppHandler4Base.h"
#include "CwxAppReactor.h"

CWINUX_BEGIN_NAMESPACE

class CwxAppFramework;
/**
*@class  CwxAppHandler4Notice
*@brief  ����Notice�¼����źš�ʱ��
*/
class CWX_API CwxAppHandler4Notice : public CwxAppHandler4Base
{
public:
    ///���캯��
    CwxAppHandler4Notice(CwxAppFramework* app, CwxAppReactor *reactor);
    ///��������
    ~CwxAppHandler4Notice();
public:
    /**
    @brief handler open����reactor��ע�ᡣ
    @param [in] arg  ��Ч����
    @return -1��ʧ�ܣ� 0���ɹ�
    */
    virtual int open (void * arg= 0);
    /**
    @brief ���������¼�������
    @param [in] event �����ϵ��¼�
    @param [in] handle  �������¼���handle��
    @return -1������ʧ�ܣ� 0������ɹ�
    */
    virtual int handle_event(int event, CWX_HANDLE handle=CWX_INVALID_HANDLE);
    ///handle close
    virtual int close(CWX_HANDLE handle=CWX_INVALID_HANDLE);
private:
};

CWINUX_END_NAMESPACE
#include "CwxPost.h"

#endif

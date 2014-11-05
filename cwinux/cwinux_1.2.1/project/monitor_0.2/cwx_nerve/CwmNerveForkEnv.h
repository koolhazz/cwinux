#ifndef __CWM_NERVE_FORK_ENV_H__
#define __CWM_NERVE_FORK_ENV_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwmNerveForkEnv.h
@brief cgi fork ����Ķ���
@author cwinux@gmail.com
@version 0.1
@date 2009-11-25
@warning
@bug
*/

#include "CwxAppForkMgr.h"
#include "CwmCmnMacro.h"
#include "CwmNerveCgiTask.h"

class CwmNerveApp;
/**
@class CwmNerveForkEnv
@brief Cgi fork���첽�¼���ִ��fork������
*/
class CWX_API CwmNerveForkEnv : public CwxAppForkEnv
{
public:
    ///���캯��
    CwmNerveForkEnv(CwmNerveApp* pApp);
    ///��������
    virtual ~CwmNerveForkEnv();
public:
    /**
    @brief ִ��CGI��fork��
    @return   ���ڸ����̣��ɹ��򷵻��ӽ��̵�pid��ʧ�ܵ�ʱ�򷵻�-1��ʧ��ʱ�ӽ���û�д�����
    ����child���̣��򷵻�0��
    */
    virtual int onFork();
    /**
    @brief child���̵����壬���child�Ĺ�����
    @return void
    */
    virtual void onChildMain();
public:
    ///�ͷŶ������Դ
    void reset();
public:
    int        m_cgiPipe[2]; ///<��������child���̵�ͨ�Źܵ�
    string     m_strCgiScript; ///<child���̵�cgi�ű�����
    CwmNerveCgiTask*   m_pCgiTask; ///<cgi�ű���Ӧ�������̵�task����
private:
    CwmNerveApp*    m_pApp;
};


#endif

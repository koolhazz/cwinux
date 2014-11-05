#ifndef __CWX_ECHO_APP_H__
#define __CWX_ECHO_APP_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
#include "CwxAppFramework.h"
#include "CwxEchoConfig.h"
#include "CwxEchoEventHandler.h"

#define ECHO_APP_VERSION "1.0"
#define ECHO_MODIFY_DATE "2010-08-29"


///���̵߳�echo����֧��TCP��UNIX-DOMAIN����Э��
class CwxEchoApp : public CwxAppFramework{
public:
    enum{
        LOG_FILE_SIZE = 30, ///<ÿ����ѭ��ʹ����־�ļ���MByte
        LOG_FILE_NUM = 7, ///<��ѭ��ʹ����־�ļ�������
        SVR_TYPE_ECHO = CwxAppFramework::SVR_TYPE_USER_START ///<echo����ķ������ͣ���SVR-ID����ֵ
    };
    ///���캯��
	CwxEchoApp();
    ///��������
	virtual ~CwxEchoApp();
    ///���س�ʼ������
    virtual int init(int argc, char** argv);
public:
    ///ʱ����Ӧ����
    virtual void onTime(CwxTimeValue const& current);
    ///signal��Ӧ����
    virtual void onSignal(int signum);
    ///�յ�echo��Ϣ����Ӧ����
    virtual int onRecvMsg(CwxMsgBlock* msg,///<�յ���echo�������ݰ�
                        CwxAppHandler4Msg const& conn,///<�յ�echo��������Ӷ���
                        CwxMsgHead const& header, ///<�յ�echo�������Ϣͷ
                        bool& bSuspendConn///<true��ֹͣ�����Ӽ���������Ϣ��false�������ӿ��Լ���������Ϣ
                        );
protected:
    ///�������л�������API
	virtual int initRunEnv();
    virtual void destroy();
private:
    CwxEchoEventHandler*         m_eventHandler;///<echo�������commander handle
    CwxAppThreadPool*            m_threadPool;///<�̳߳ض���
    CwxEchoConfig               m_config;///<�����ļ�����
};
#endif


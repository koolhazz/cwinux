#ifndef __CWF_FILTER_APP_H__
#define __CWF_FILTER_APP_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
#include "CwxAppFramework.h"
#include "CwfFilterConfig.h"
#include "CwfFilterHandler.h"
#include "CwfFilterMgr.h"
#include "CwfFilterTss.h"

#define FILTER_APP_VERSION "1.0"
#define FILTER_MODIFY_DATE "2010-09-08 22:10:66 "

///���̵߳�echo����֧��TCP��UNIX-DOMAIN����Э��
class CwfFilterApp : public CwxAppFramework{
public:
    enum{
        LOG_FILE_SIZE = 30, ///<ÿ����ѭ��ʹ����־�ļ���MByte
        LOG_FILE_NUM = 7, ///<��ѭ��ʹ����־�ļ�������
        SVR_TYPE_FILTER = CwxAppFramework::SVR_TYPE_USER_START ///<echo����ķ������ͣ���SVR-ID����ֵ
    };
    ///���캯��
	CwfFilterApp();
    ///��������
	virtual ~CwfFilterApp();
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
public:
    CwfFilterMgr* getFilterMgr() { return m_pFilterMgr;}
protected:
    ///�������л�������API
	virtual int initRunEnv();
    virtual void destroy();
private:
    CwfFilterHandler*            m_pFilterHandler;///<echo�������commander handle
    CwxAppThreadPool*            m_pThreadPool;///<�̳߳ض���
    CwfFilterMgr*                m_pFilterMgr; ///<����������������
    CwfFilterConfig              m_config;///<�����ļ�����
};
#endif


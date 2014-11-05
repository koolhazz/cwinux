#ifndef __CWX_APP_HANDLER_4_BASE_H__
#define __CWX_APP_HANDLER_4_BASE_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppHandler4Base.h
@brief Event handler�Ļ���
@author cwinux@gmail.com
@version 0.1
@date 2010-08-01
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxLockGuard.h"
#include "CwxMutexLock.h"
#include "CwxMsgBlock.h"
#include "CwxAppMacro.h"
#include "CwxAppConfig.h"
#include <event.h>

CWINUX_BEGIN_NAMESPACE

class CwxAppFramework;
class CwxAppReactor;


class CWX_API CwxAppHandler4Base{
public:
    ///�����¼�����
    enum{
        TIMEOUT_MASK = EV_TIMEOUT,
        READ_MASK = EV_READ,
        WRITE_MASK = EV_WRITE,
        SIGNAL_MASK = EV_SIGNAL,
        PERSIST_MASK = EV_PERSIST,
        PREAD_MASK = READ_MASK|PERSIST_MASK,
        RW_MASK = READ_MASK|WRITE_MASK,
        IO_MASK = RW_MASK|PERSIST_MASK,
        ALL_EVENTS_MASK =  TIMEOUT_MASK|
                          READ_MASK|
                          WRITE_MASK|
                          SIGNAL_MASK|
                          PERSIST_MASK
    };
public :
    ///��������.
    virtual ~CwxAppHandler4Base (void);
    /**
    @brief handler open����handler�ĳ�ʼ����reactor��ע�������
    @param [in] arg  Handler�ĳ�ʼ�����������������Լ�����
    @return -1��ʧ�ܣ� 0���ɹ�
    */
    virtual int open (void * arg= 0)=0;
    /**
    @brief Handler���¼�֪ͨ�ص���
    @param [in] event  �������¼����ͣ�ΪTIMEOUT_MASK��READ_MASK��WRITE_MASK��<br>
            SIGNAL_MASK����ϡ�
    @param [in] handle  �������¼���handle��
    @return -1��ʧ�ܣ�reactor����������close��
            0���ɹ���
    */
    virtual int handle_event(int event, CWX_HANDLE handle=CWX_INVALID_HANDLE)=0;
    ///handle close
    virtual int close(CWX_HANDLE handle=CWX_INVALID_HANDLE)=0;
public:
    ///����app
    void setApp(CwxAppFramework* app);
    ///��ȡapp
    CwxAppFramework* getApp();
    ///��ȡapp
    ///����handle��reactor
    void reactor (CwxAppReactor *reactor);
    ///��ȡhandle��reactor.
    CwxAppReactor *reactor(void);
    ///�Ƿ�ע��
    bool isReg() const;
    ///��ȡreg mask
    int  getRegMask() const;
    ///��ȡIo handle
    CWX_HANDLE getHandle(void) const;
    ///����IO handle
    void setHandle (CWX_HANDLE);
    ///����handle type
    void setType(int type);
    ///��ȡhandle type
    int getType() const;
    ///��ȡע������
    int getRegType() const;
    ///��ȡ�Ƿ�Ϊpersist�¼�
    bool isPersistMask() const;
    ///�Ƿ�������read mask
    bool isReadMask() const;
    ///�Ƿ�������write mask
    bool isWriteMask() const;
    ///�Ƿ�������timeout mask
    bool isTimeoutMask() const;
    ///�Ƿ�������signal mask
    bool isSignalMask() const;
protected:
    /// Force CwxAppHandler4Base to be an abstract base class.
    CwxAppHandler4Base (CwxAppFramework* pApp, CwxAppReactor *reactor);
    friend class CwxAppReactor;
    ///����reg mask
    void setRegMask(int mask);
    ///����ע��״̬
    void setReg(bool bReg);
    ///����ע������
    void setRegType(int type);
private:
    CwxAppFramework*       m_pApp; ///<app�����ָ��
    CwxAppReactor *        m_reactor; ///<reactor�����ָ��
    bool                  m_bReg; ///<handler�Ƿ��Ѿ�ע��
    int                   m_regMask; ///<handlerע�������
    int                   m_regType; ///<handler��reactorע������
    CWX_HANDLE             m_handler; ///<�¼���io handle
    int                   m_type; ///<event handle type;
    struct event           m_event; ///<handler��event����
};

CWINUX_END_NAMESPACE

#include "CwxAppHandler4Base.inl"
#include "CwxPost.h"
#endif

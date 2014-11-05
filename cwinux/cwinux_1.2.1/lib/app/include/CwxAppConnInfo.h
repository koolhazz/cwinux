#ifndef __CWX_APP_CONN_INFO_H__
#define __CWX_APP_CONN_INFO_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
*@file  CwxAppConnInfo.h
*@brief ������CwxAppConnInfo
*@author cwinux@gmail.com
*@version 0.1
*@date  2010-07-30
*@warning  ��.
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxMsgHead.h"
#include "CwxAppMacro.h"
#include "CwxAppConfig.h"
#include "CwxStl.h"
#include "CwxStlFunc.h"
#include "CwxAppLogger.h"

CWINUX_BEGIN_NAMESPACE
class CwxAppHandler4Msg;
class CwxAppPai;
class CwxAppHostInfo;
class CwxAppSvrInfo;
/**
@class CwxAppConnInfo
@brief ���Ӷ��󣬱������ӵ�״̬�����ͼ������շ�����Ϣ��
*/
class CWX_API CwxAppConnInfo{
public:
    ///����״̬����
    enum{
        IDLE = 0,      ///<��ʼ����״̬
        CONNECTING,    ///<�����е�״̬������connector���ã���ת��ΪESTABLISHING��FAILED
        TIMEOUT,       ///<�ȴ���ʱ״̬��Ҳ���ǵȴ���һ���������ӡ���ת��ΪESTABLISHING��FAILED
        ESTABLISHING,  ///<�ȴ���������ת��ΪESTABLISHED��FAILED��
        ESTABLISHED,   ///<�����Ѿ�������״̬����ת��ΪFAILED
        FAILED         ///<����ʧ�ܵ�״̬����ת��ΪCONNECTING��TIMEOUT
    };
public:
    /**
    @brief ���캯��
    */
    CwxAppConnInfo();
    ///��������
    ~CwxAppConnInfo();
public:
    ///��ȡ���ӵ�SVR-ID
    CWX_UINT32 getSvrId() const; 
    ///�������ӵ�SVR-ID
    void setSvrId(CWX_UINT32 uiSvrId);

    ///��ȡ���ӵ�HOST-ID
    CWX_UINT32 getHostId() const;
    ///�������ӵ�HOST-ID
    void setHostId(CWX_UINT32 uiHostId);

    ///��ȡ���ӵ�����ID
    CWX_UINT32 getConnId() const; 
    ///�������ӵ�����ID
    void setConnId(CWX_UINT32 uiConnId);

    ///��ȡ�������ӵ�Listen ID
    CWX_UINT32 getListenId() const;
    ///���ñ������ӵ�Listen ID
    void setListenId(CWX_UINT32 uiListenId);

    ///��ȡ���ӵ�״̬
    CWX_UINT16 getState() const;
    ///�������ӵ�״̬
    void setState(CWX_UINT16 unState);

    ///��ȡ���ӵĴ���ʱ��
    time_t getCreateTime() const;
    ///�������ӵĴ���ʱ��
    void setCreateTime(time_t ttTime);
    ///��ȡ����ʧ�����ӵĴ���
    CWX_UINT32 getFailConnNum() const;
    ///��������ʧ�����Ӵ���
    void setFailConnNum(CWX_UINT32 uiNum);
    ///��������ʧ�����Ӵ���
    CWX_UINT32 incFailConnNum();
    ///��ȡʧЧ����������С������ʱ����
    CWX_UINT16 getMinRetryInternal() const;
    ///����ʧЧ����������С������ʱ����
    void setMinRetryInternal(CWX_UINT16 unInternal);
    ///��ȡʧЧ�����������������ʱ����
    CWX_UINT16 getMaxRetryInternal() const;
    ///����ʧЧ�����������������ʱ����
    void setMaxRetryInternal(CWX_UINT16 unInternal);
    ///��ȡ�����Ƿ�Ϊ��������
    bool isActiveConn() const;
    ///����Ϊ��������
    void setActiveConn(bool bActive);
    ///��ȡ�����Ƿ������ر�
    bool isActiveClose() const;
    ///��������ʱ�����ر�
    void setActiveClose(bool bActive);
    ///��ȡ���ӵ����ݰ��Ƿ��а�ͷ
    bool isRawData() const ;
    ///�������ӵ����ݰ���raw��ʽ
    void setRawData(bool bRaw);
    ///��ȡ�ް�ͷ���ӵ����ݽ���BUF
    CWX_UINT32  getRawRecvLen() const;
    ///��ȡ�ް�ͷ���ӵ����ݽ���buf
    void setRawRecvLen(CWX_UINT32 uiLen);
    ///��ȡ�����Ƿ���Ҫ�������KEEP-ALIVE
    bool isKeepalive() const;
    ///���������Ƿ���Ҫ�������KEEP-ALIVE
    void setKeepalive(bool bKeepAlive);
    ///��ȡ���������յ���Ϣ��ʱ��
    time_t  getLastRecvMsgTime() const;
    ///�������������յ���Ϣ��ʱ��
    void setLastRecvMsgTime(time_t ttTime);
    ///��ȡ�������·�����Ϣ��ʱ��
    time_t  getLastSendMsgTime() const;
    ///�����������·�����Ϣ��ʱ��
    void setLastSendMsgTime(time_t ttTime);
    ///��ȡKEEP-ALIVE�������·���KEEP-ALIVE��ʱ��
    time_t  getKeepAliveSendTime() const;
    ///����KEEP-ALIVE�������·���KEEP-ALIVE��ʱ��
    void setKeepAliveSendTime(time_t ttTime);
    ///��ȡ�Ƿ��յ������ӵ�KEEP-ALIVE�ظ�
    bool isKeepAliveReply() const;
    ///�����Ƿ��յ������ӵ�KEEP-ALIVE�ظ�
    void setKeepAliveReply(bool bReply);
    ///��ȡ���ӵ��û�����
    void*  getUserData() const;
    ///�������ӵ��û�����
    void setUserData(void* userData);
    ///��ȡ���ӵ�Э���������
    CwxAppPai* getPai();
    ///�������ӵ�Э���������
    void setPai(CwxAppPai* pAdapter);
    ///��ȡ���ӵȴ����͵������Ϣ��������0��ʾû������
    CWX_UINT32 getMaxWaitingMsgNum() const;
    ///�����������ĵȴ����͵���Ϣ������Ĭ��0��ʾû������
    void setMaxWaitingMsgNum(CWX_UINT32 uiNum=0);
    ///�ж��Ƿ����Ӵ����Ͷ�������
    bool isWaitingMsgQueueFull() const;
    ///��ȡ���ӵȴ����͵���Ϣ������
    CWX_UINT32 getWaitingMsgNum() const;
    ///�������ӵȴ����͵���Ϣ������
    void setWaitingMsgNum(CWX_UINT32 uiNum);
    ///�������ӵȴ����͵���Ϣ������
    CWX_UINT32 incWaitingMsgNum();
    ///�������ӵȴ����͵���Ϣ������
    CWX_UINT32 decWaitingMsgNum();
    ///��ȡ�����Ѿ��������յ�����Ϣ��������
    CWX_UINT32 getContinueRecvNum() const;
    ///���������Ѿ������յ�����Ϣ��������
    void setContinueRecvNum(CWX_UINT32 uiNum);
    ///��ȡ�������͵���Ϣ����
    CWX_UINT32 getContinueSendNum() const;
    ///�����������͵���Ϣ����
    void setContinueSendNum(CWX_UINT32 uiNum);
    ///�ж϶Ͽ��������Ƿ���Ҫ����
    bool isNeedReconnect() const;
    ///�Ƿ����CwxAppFramework::onCreate
    bool isInvokeCreate() const;
    ///�����Ƿ����CwxAppFramework::onCreate
    void setInvokeCreate(bool bInvoke);
    ///�Ƿ���������
    bool isReconn() const;
    ///�����Ƿ�����
    void setReconn(bool bReconnect);
    ///��ȡ����������ʱ�ĺ�����
    CWX_UINT32 getReconnDelay() const;
    ///��������������ʱ�ĺ�����
    void setReconnDelay(CWX_UINT32 uiDelay);
    ///��ȡ���Ӷ�Ӧ��handler
    CwxAppHandler4Msg* getHandler();
    ///�������Ӷ�Ӧ��handler
    void setHandler(CwxAppHandler4Msg*  pHandler);
    ///��ȡparent
    CwxAppHostInfo* getParent();
    ///����parent
    void setParent(CwxAppHostInfo* parent);

public:
    ///�����Ӷ����״̬��Ϣ��λ
    void reset();
private:
    CWX_UINT32         m_uiSvrId;  ///<svr id
    CWX_UINT32         m_uiHostId; ///<host id
    CWX_UINT32         m_uiConnId;  ///<connection id
    CWX_UINT32         m_uiListenId; ///<accept connection's  acceptor ID. for passive conn.
    CWX_UINT16         m_unState; ///<connection state.
    time_t             m_ttCreateTime;///<connection's create time
    CWX_UINT16          m_unMinRetryInternal; ///<min re-connect internal
    CWX_UINT16         m_unMaxRetryInternal; ///<max re-connect internal
    CWX_UINT32          m_uiFailConnNum; ///<count for failure connect
    bool               m_bActiveConn; ///< sign for active connection.
    bool               m_bActiveClose; ///< sign for close connection by user.
    bool               m_bRawData; ///< sign for raw data connection
    CWX_UINT32          m_uiRawRecvLen; ///<max len for per-recieve
    bool               m_bKeepAlive; ///<sign for keep alive
    time_t             m_ttLastRecvMsgTime;///<last recv msg time
    time_t             m_ttLastSendMsgTime;///<last send msg time
    time_t             m_ttKeepAliveSendTime;///<keep-alive send time
    bool               m_bKeepAliveReply; ///<sign for waiting keep-alive reply
    CwxAppPai*         m_pPai; ///<Э���������
    void*              m_pUserData; ///<user dat for connection
    CWX_UINT32         m_uiContinueRecvNum; ///<conintue recv msg num
    CWX_UINT32         m_uiContinueSendNum; ///<�������͵��������
    CWX_UINT32         m_uiMaxWaitingMsgNum;
    CWX_UINT32         m_uiWaitingMsgNum;///<waiting msg num
    bool               m_bInvokeCreate; ///<�Ƿ���open��ʱ�򣬵���CwxAppFramework::onCreate��Ĭ�ϵ���
    bool               m_bReconn; ///<�Ƿ�������
    CWX_UINT32         m_uiReconnDelay; ///<������ʱ�ĺ�����
    CwxAppHandler4Msg*  m_pHandler; ///<���Ӷ�Ӧ��Handler
    CwxAppHostInfo*    m_parent; ///<���ӵ�parent
};


/**
@class CwxAppHostInfo
@brief Framework����������
*/
class CWX_API CwxAppHostInfo{
public:
    /**
    @brief ���캯��
    @param [in] uiSvrId ������svr id
    @param [in] uiHostId ������host id
    @param [in] parent ������SVR ����
    */
    CwxAppHostInfo(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId,
        CwxAppSvrInfo* parent);
public:
    ///Get Svr id
    inline CWX_UINT32 getSvrId() const;
    ///Get host id
    inline CWX_UINT32 getHostId() const;
    ///Get conn nun
    inline CWX_UINT32 getConnNum() const;
    ///��ȡ�Ƿ��ܹ�������Ϣ
    inline bool isEnableSendMsg() const;
    ///Get WaitMsgNum() 
    inline CWX_UINT32 getWaitingMsgNum() const;
    ///Get SndMsgNum
    inline CWX_UINT64 getSndMsgNum() const;
    ///Get RecvMsgNum
    inline CWX_UINT64 getRecvMsgNum() const;
    ///get RecentSndMsgNum
    inline CWX_UINT32 getRecentSndMsgNum() const;
    ///get RecentRecvMsgNum
    inline CWX_UINT32 getRecentRecvMsgNum() const;
    ///get RecentClosedCount
    inline CWX_UINT32 getRecentClosedCount() const;
    ///select connection for send msg
    inline CwxAppConnInfo* selectConn();
    ///Get parent
    inline CwxAppSvrInfo * getParent();
    ///Get host's valid connection
    inline vector<CwxAppConnInfo*>* GetHostConn();
public:
    ///���һ����Ч����������
    inline void addConn(CwxAppConnInfo* conn);
    ///�Ƴ�һ����������
    inline void removeConn(CwxAppConnInfo* conn);
    ///֪ͨ����������һ����Ϣ
    inline void sendOneMsg();
    ///֪ͨ�������յ�һ��Ҫ���͵���Ϣ
    inline void recvOneMsg();
    ///֪ͨ��������һ���Ŷӷ��͵���Ϣ
    inline void waitingOneMsg();
    ///���������ĸ���
    inline void calcHostLoad();
private:
    vector<CwxAppConnInfo*>   m_hostConn;///<host's connection
    CWX_UINT32                m_uiSvrId; ///<service id;
    CWX_UINT32                m_uiHostId; ///<host id
    CWX_UINT64                m_ullSndMsgNum; ///<send msg number
    CWX_UINT64                m_ullRecvMsgNum; ///<recv msg number
    CWX_UINT32                m_uiWaitingMsgNum; ///<msg num for waiting sending
    CWX_UINT32                m_uiRecentSndMsgNum;//recent one minute's sent msg num
    CWX_UINT32                m_uiRecentRecvMsgNum;//recent one minute's recv msg num
    CWX_UINT32                m_uiRecentClosedCount;//recent one minute's closed connection
    CWX_UINT32                m_uiRand;///<����ѡ��������
    CwxAppSvrInfo*            m_parent; //parent
};

/**
@class CwxAppSvrInfo
@brief Framework��SVR����
*/
class CWX_API CwxAppSvrInfo
{
public:
    ///���캯��
    CwxAppSvrInfo(CWX_UINT32 uiSvrId);
public:
    ///Get svr id
    inline CWX_UINT32 getSvrId() const;
    ///Get HostNum
    inline CWX_UINT32 getHostNum() const;
    ///ѡ��һ̨������������Ϣ�ķ���
    inline CwxAppHostInfo* selectHost();
    ///��ȡsvr�µ������б�
    inline vector<CwxAppHostInfo*>& getHosts();
public:
    ///����һ̨������
    inline void addHost(CwxAppHostInfo* host);
    ///���¼���svr�²�ͬ�����ĸ���
    inline void calcHostLoad();
private:
    vector<CwxAppHostInfo*>     m_svrHost;///<SVR�µ�������Ϣ
    CWX_UINT32                 m_uiSvrId; ///<svr id
    CWX_UINT32                 m_uiRand;///<����ѡ����������
};

CWINUX_END_NAMESPACE
#include "CwxAppConnInfo.inl"
#include "CwxPost.h"
#endif


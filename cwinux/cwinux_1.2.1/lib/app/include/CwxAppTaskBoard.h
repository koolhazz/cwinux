#ifndef __CWX_APP_TASK_BOARD_H__
#define __CWX_APP_TASK_BOARD_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
@file CwxAppTaskBoard.h
@brief �첽������Ϣ���������
@author cwinux@gmail.com
@version 0.1
@date 2009-07-20
@warning
@bug
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxMutexLock.h"
#include "CwxLockGuard.h"
#include "CwxTypePoolEx.h"
#include "CwxMsgBlock.h"
#include "CwxAppTss.h"
#include "CwxAppConfig.h"
#include "CwxAppMacro.h"

CWINUX_BEGIN_NAMESPACE

class CwxAppTaskBoard;
/**
@class CwxAppTaskBoardConnInfo
@brief Task�����ӹرռ���Ϣ��������¼��ķ�װ����ʵ������������Ϣ�Ļ��档
*/
class CWX_API CwxAppTaskBoardConnInfo
{
public:
    ///���캯��
    CwxAppTaskBoardConnInfo(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId,
        CWX_UINT32 uiConnId,
        CwxMsgBlock* msg);
    ///��������
    ~CwxAppTaskBoardConnInfo();
public:
    ///��ȡ��װ�¼���svr-id
    inline CWX_UINT32 getSvrId() const;
    ///��ȡ��װ�¼���host-id
    inline CWX_UINT32 getHostId() const;
    ///��ȡ��װ�¼���conn-id
    inline CWX_UINT32 getConnId() const;
    ///��ȡ��װ�¼���msg
    inline CwxMsgBlock* getMsg();
    ///���÷�װ�¼���msg
    inline void setMsg(CwxMsgBlock* msg);
private:
    CWX_UINT32     m_uiSvrId;///<�¼���svr-id
    CWX_UINT32     m_uiHostId;///<�¼���host-id
    CWX_UINT32     m_uiConnId;///<�¼���conn-id
    CwxMsgBlock*   m_msg;///<�¼���msg

};

/**
@class CwxAppTaskBoardTask
@brief �첽�����Task����Ļ��࣬ʵ��Task�����ݼ��¼��Ĵ���,����Task��״̬ת��
*/
class CWX_API CwxAppTaskBoardTask
{
public:
    ///�����״̬��������״̬�û��Լ�����
    enum{
        TASK_STATE_INIT = 0,///<��ʼ��״̬
        TASK_STATE_FINISH = 1,///<���״̬
        TASK_STATE_USER = 2 ///<�û���Task״̬�Ŀ�ʼֵ
    };
public:
    ///���캯��
    CwxAppTaskBoardTask(CwxAppTaskBoard* pTaskBoard);
    ///��������
    virtual ~CwxAppTaskBoardTask();
public:
    /**
    @brief ֪ͨTask�Ѿ���ʱ
    @param [in] pThrEnv �����̵߳�Thread-env
    @return void
    */
    virtual void noticeTimeout(CwxAppTss* pThrEnv) = 0;
    /**
    @brief ֪ͨTask���յ�һ�����ݰ���
    @param [in] msg �յ�����Ϣ
    @param [in] pThrEnv �����̵߳�Thread-env
    @param [out] bConnAppendMsg �յ���Ϣ�������ϣ��Ƿ��д����յ�������Ϣ��true���ǣ�false��û��,Ĭ��Ϊfalse��
    @return void
    */
    virtual void noticeRecvMsg(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        bool& bConnAppendMsg) = 0;
    /**
    @brief ֪ͨTask���ⷢ�͵�һ�����ݰ�����ʧ�ܡ�
    @param [in] msg �յ�����Ϣ
    @param [in] pThrEnv �����̵߳�Thread-env
    @return void
    */
    virtual void noticeFailSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv) = 0;
    /**
    @brief ֪ͨTaskͨ��ĳ�����ӣ�������һ�����ݰ���
    @param [in] msg ���͵����ݰ�����Ϣ
    @param [in] pThrEnv �����̵߳�Thread-env
    @param [out] bConnAppendMsg ������Ϣ�������ϣ��Ƿ��еȴ��ظ�����Ϣ��true���ǣ�false��û�У�Ĭ��Ϊtrue��
    @return void
    */
    virtual void noticeEndSendMsg(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        bool& bConnAppendMsg) = 0;
    /**
    @brief ֪ͨTask�ȴ��ظ���Ϣ��һ�����ӹرա�
    @param [in] uiSvrId �ر����ӵ�SVR-ID
    @param [in] uiHostId �ر����ӵ�HOST-ID
    @param [in] uiConnId �ر����ӵ�CONN-ID
    @param [in] pThrEnv �����̵߳�Thread-env
    @return void
    */
    virtual void noticeConnClosed(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId,
        CWX_UINT32 uiConnId,
        CwxAppTss* pThrEnv) = 0;
    /**
    @brief ����Task����Task����ǰ��Task��Task�Ĵ����߳���ӵ�С�
           ������ǰ��Task���Խ����Լ����첽��Ϣ�������ܴ���
           ��ʱ��Taskboard��noticeActiveTask()�ӿڵ��õġ�
    @param [in] pThrEnv �����̵߳�Thread-env
    @return 0:�ɹ���-1��ʧ�ܣ���ʧ�ܵ�ʱ��Task��Taskboard���Ƴ�������Ϊ���״̬��
    */
    virtual int noticeActive(CwxAppTss* pThrEnv)=0;
    /**
    @brief ִ��Task���ڵ��ô�APIǰ��Task��Taskboard�в����ڣ�Ҳ����˵�Ա���̲߳��ɼ���
           TaskҪô�Ǹմ���״̬��Ҫô�������ǰһ���׶εĴ����������״̬��
           ͨ���˽ӿڣ���Task�Լ������Լ���step����ת����������ϵTask�����ͼ�������̡�
    @param [in] pThrEnv �����̵߳�Thread-env
    @return void
    */
    virtual void execute(CwxAppTss* pThrEnv)
    {
        pThrEnv = NULL;
    }
public:
    ///��ȡTask��Taskboard
    inline CwxAppTaskBoard* getTaskBoard()
    {
        return m_pTaskBoard;
    }
    ///��ȡTask��task id
    inline CWX_UINT32 getTaskId() const;
    ///����Task��task id
    inline void setTaskId(CWX_UINT32 id);
    ///��ȡTask��ʱ��ʱ���
    inline CWX_UINT64 const& getTimeoutValue() const;
    ///����Task��ʱ��ʱ���
    inline void setTimeoutValue(CWX_UINT64 ullTimestamp);
    ///��ȡTask��״̬
    inline CWX_UINT8 getTaskState() const;
    ///����Task��״̬
    inline void setTaskState(CWX_UINT8 state);
    ///Check Task�Ƿ���ɣ�����ɣ�����Ҫ����Taskboard�Ĺ���
    inline bool isFinish() const;
    ///Check Task�Ƿ�ʱ����ʱҲ��ζ����ɡ�����ʱ������Ҫ����Taskboard�Ĺ���
    inline bool isTimeout() const;
    ///��� Task�Ƿ����Ƴ�״̬��������Taskboard��remove API���õġ��������Ƴ�״̬������Ҫ����Taskboard�Ĺ���
    inline bool isWaitingRemove() const;
private:
    ///����ullNow��ʱ��㣬��������Ƿ�ʱ���糬ʱ�������ó�ʱ״̬������ʱ״̬�Ѿ����ã�������ullNow,���ǳ�ʱ��
    inline bool checkTimeout(CWX_UINT64 const& ullNow);
    ///Task�Ƿ�lock������lock�Ļ���˵���б���߳����ڴ����Task��
    inline bool isLocked() const;
    ///���Task״̬��������¼�����Ϣ
    inline void clearBase();
    ///��ȡTask������¼�
    inline void fetchWaitingMsg(bool& bTimeout,
        list<CwxMsgBlock*>& failSendMsgs,
        list<CwxMsgBlock*>& recvMsgs,
        list<CwxAppTaskBoardConnInfo*>& endclosedConnList);
    ///����һ�����͵����ݰ�ͨ�����ӷ�����ϵ��¼�
    inline void addEndSendMsgEvent(CwxMsgBlock* msg);
    ///����һ�����ݰ�����ʧ�ܵ��¼�
    inline void addFailSendMsgEvent(CwxMsgBlock* msg);
    ///�����յ�һ�����ݰ����¼�
    inline void addRecvMsgEvent(CwxMsgBlock* msg);
    ///����ȴ��������ݵ�һ�����ӹرյĵ��¼�
    inline void addClosedConnEvent(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId,
        CWX_UINT32 uiConnId);
    friend class CwxAppTaskBoard;
private:
    CWX_UINT32            m_uiTaskId; ///<Task��ID
    CWX_UINT64            m_ullTimeoutStamp;///<Task��ʱ��ʱ���
    CWX_UINT8             m_ucTaskState;///<Task��״̬
    CwxAppTaskBoardTask*   m_next;///<Task����һ��Task
    CwxAppTaskBoardTask*   m_prev;///<Task��ǰһ��Task
    bool                  m_bLooked;///<Task�Ƿ�����״̬����ֹ����
    bool                  m_bWaitingRemove;///<Task�Ƿ��ڴ�Taskboard�Ƴ�״̬
    bool                  m_bTimeout;///<Task�Ƿ��Ѿ���ʱ
    list<CwxMsgBlock*>      m_failSendMsgList;///<��Ϣͨ�����ӷ��͡�����ʧ�ܵ��¼��������
    list<CwxMsgBlock*>      m_recvMsgList;///<���յ������ݵĻ������
    list<CwxAppTaskBoardConnInfo*> m_sendCloseConnList;///<���ӹرյĻ������
    CwxAppTaskBoard*       m_pTaskBoard;
};


/**
@class CwxAppTaskBoardConnTasks
@brief һ��������Task��ϵ�Ķ�������ʵ�ֹ���һ����������ЩTask��ء�
       �����ӹرյ�ʱ�򣬻�Ӱ����ЩTask
*/
class CwxAppTaskBoardConnTasks
{
public:
    ///���캯��
    CwxAppTaskBoardConnTasks(CWX_UINT32 uiConnId, CWX_UINT32 uiTaskId);
    ///��������
    ~CwxAppTaskBoardConnTasks();
    ///��������
    CwxAppTaskBoardConnTasks(CwxAppTaskBoardConnTasks const& item);
    ///��ֵ����
    CwxAppTaskBoardConnTasks& operator=(CwxAppTaskBoardConnTasks const& item);
    ///�����С�ڱȽϲ�����
    inline bool operator<(CwxAppTaskBoardConnTasks const& item) const;
    ///����ĵ��ڲ�����
    inline bool operator==(CwxAppTaskBoardConnTasks const& item) const;
private:
    friend class CwxAppTaskBoard;
private:
    CWX_UINT32      m_uiConnId;///<����ID
    CWX_UINT32      m_uiTaskId;///<��������ص�Task ID
};

/**
@class CwxAppTaskBoardTaskConns
@brief һ��Task�����ӹ�ϵ�Ķ�������ʵ�ֹ���һ��Task����Щ������ء�
��һ��Task��ɵ�ʱ�򣬻�������Щ�����ϵ�Task
*/
class CwxAppTaskBoardTaskConns
{
public:
    ///���캯��
    CwxAppTaskBoardTaskConns(CWX_UINT32 uiTaskId, CWX_UINT32 uiConnId);
    ///��������
    ~CwxAppTaskBoardTaskConns();
    ///��������
    CwxAppTaskBoardTaskConns(CwxAppTaskBoardTaskConns const& item);
    ///��ֵ����
    CwxAppTaskBoardTaskConns& operator=(CwxAppTaskBoardTaskConns const& item);
    ///С�ڲ�����
    inline bool operator<(CwxAppTaskBoardTaskConns const& item) const;
    ///���ڲ�����
    inline bool operator==(CwxAppTaskBoardTaskConns const& item) const;
private:
    friend class CwxAppTaskBoard;
private:
    CWX_UINT32      m_uiTaskId; ///<Task id
    CWX_UINT32      m_uiConnId; ///<��Task��ص�����ID
};

/**
@class CwxAppTaskBoard
@brief Task�Ĺ������ʵ��Task��������ȴ�����Ϣ�Ĺ���������Task���״̬ת�塣
       Task��ͨ��noticeActiveTask()�ӿڼ��뵽Taskboard�еġ���Task���ʱ��
       ���Զ�����Taskboard��
*/
class CWX_API CwxAppTaskBoard
{
public:
    ///Task��hash-map���Ͷ���
    typedef hash_map<CWX_UINT32/*taskid*/, CwxAppTaskBoardTask*, CwxNumHash<CWX_UINT32> > CWX_APP_TASK_MAP;
public:
    /**
    @brief ���캯����
    @param [in] uiMaxTaskNum Taskboard��������Task�������û�����Task hash�Ĵ�С
    */
    CwxAppTaskBoard(CWX_UINT32 uiMaxTaskNum=1024);
    ///��������
    ~CwxAppTaskBoard();

public:
    /**
    @brief Taskboard�ĳ�ʼ����
    @return -1��ʧ�ܣ�0���ɹ�
    */
    int  init();
    /**
    @brief ���ָ��Taskid��task�Ƿ���ڡ�
    @param [in] uiTaskId Task id
    @return true�����ڣ�false��������
    */
    bool isExist(CWX_UINT32 uiTaskId);
    /**
    @brief ��һ��Task��Taskoard�Ƴ���
    @param [in] uiTaskId Ҫ�Ƴ���Task��Task id
    @param [out] pFinishTask �Ƴ�Task�ķ���ָ�롣
    @return -1��Task�����ڣ�pFinishTask����NULL��
            0��Task������������̲߳���������lock״̬��ֻ�������Ƴ���־���޷��Ƴ���pFinishTask����NULL��
            1���ɹ��Ƴ����Ƴ���Taskͨ��pFinishTask���ء�
    */
    int remove(CWX_UINT32 uiTaskId, CwxAppTaskBoardTask*& pFinishTask);
    /**
    @brief ��Taskboard�����һ��Task����Task���
    @param [in] pTask Ҫ��Ӳ������Task����
    @param [in] pThrEnv �����̵߳�Thread-Env��
    @return -1��Taskboard�У����������Task id��ͬ��task��
    0��Task�Ѿ���Taskboard�ӹܴ��������̲߳����ٶ�Task�����κδ���
    1��Task�Ѿ���ɣ�������Taskboard�������ڵ����̵߳Ŀ���֮�¡�
    */
    int noticeActiveTask(CwxAppTaskBoardTask* pTask, CwxAppTss* pThrEnv);
    /**
    @brief ���Taskboard�еĳ�ʱTask��
    @param [in] pThrEnv �����̵߳�Thread-Env��
    @param [out] finishTasks �Ѿ���ʱ��Task���б�
    @return void��
    */
    void noticeCheckTimeout(CwxAppTss* pThrEnv, list<CwxAppTaskBoardTask*>& finishTasks);
    /**
    @brief ֪ͨTaskboard��uiTaskId�������յ�һ��ͨ�����ݰ����˿��ܽ��Ǵ�Task��ɡ�
    @param [in] uiTaskId �յ���Ϣ��Task��Task Id��
    @param [in] msg �յ�����Ϣ��
    @param [in] pThrEnv �����̵߳�Thread-Env��
    @param [out] pFinishTask ����յ���Ϣ��Task��Ϊ����Ϣ����ɣ��򷵻ء�
    @return -1��Task�����ڣ�
            0��Task�Ѿ����ܴ���Ϣ����Taskû����ɣ����ڵȴ������Ϣ��
            1��Task�Ѿ���ɣ�������Taskboard�������ڵ����̵߳Ŀ���֮�¡�
    */
    int noticeRecvMsg(CWX_UINT32 uiTaskId,
        CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        CwxAppTaskBoardTask*& pFinishTask);
    /**
    @brief ֪ͨTaskboard��uiTaskId��Task��һ����Ϣ����ʧ�ܡ��˿��ܽ��Ǵ�Task��ɡ�
    @param [in] uiTaskId ������Ϣʧ�ܵ�Task��Task Id��
    @param [in] msg ����ʧ�ܵ���Ϣ����Ϣ��
    @param [in] pThrEnv �����̵߳�Thread-Env��
    @param [out] pFinishTask ���Task��Ϊ����ʧ�ܶ���ɣ��򷵻ء�
    @return -1��Task�����ڣ�
            0��Task�Ѿ����ܴ���Ϣ����Taskû����ɣ����ڵȴ������Ϣ��
            1��Task�Ѿ���ɣ�������Taskboard�������ڵ����̵߳Ŀ���֮�¡�
    */
    int noticeFailSendMsg(CWX_UINT32 uiTaskId,
        CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv,
        CwxAppTaskBoardTask*& pFinishTask);
    /**
    @brief ֪ͨTaskboard��uiTaskId��Task��һ����Ϣ��һ�����ӷ�����ϡ�
    @param [in] uiTaskId Task��Task Id��
    @param [in] msg ����������ص���Ϣ��
    @param [in] pThrEnv �����̵߳�Thread-Env��
    @param [out] pFinishTask ���Task��ɣ��򷵻ء�
    @return -1��Task�����ڣ�
            0��Task�Ѿ����ܴ���Ϣ����Taskû����ɣ����ڵȴ������Ϣ��
            1��Task�Ѿ���ɣ�������Taskboard�������ڵ����̵߳Ŀ���֮�¡�
    */
    int noticeEndSendMsg(CWX_UINT32 uiTaskId,
        CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv, 
        CwxAppTaskBoardTask*& pFinishTask);
    /**
    @brief ֪ͨTaskboard��һ�����ӹرա�
    @param [in] msg �ر�������ص���Ϣ��
    @param [in] pThrEnv �����̵߳�Thread-Env��
    @param [out] finishTasks ��Ϊ���ӹرն���ɵ�����
    @return void
    */
    void noticeConnClosed(CwxMsgBlock*& msg,
        CwxAppTss* pThrEnv, 
        list<CwxAppTaskBoardTask*>& finishTasks);
    ///��ȡTaskboard�������������
    inline CWX_UINT32 getTaskNum() const ;
    ///��ȡtaskboard��conn-tasks��map��Ԫ����Ŀ��Ϊ�˵���
    inline int getConnTasksMapSize() const;
    ///��ȡtaskboard��task-conns��set��Ԫ����Ŀ��Ϊ�˵���
    inline int getTaskConnsMapSize() const;
    ///���Taskboard
    void reset();
private:
    ///���������ж�һ�������Ƿ����
    inline bool _isExist(CWX_UINT32 uiTaskId);
    ///��������Taskboard���һ��Task
    bool _addTask(CwxAppTaskBoardTask* pTask);
    ///����������TaskId��ȡ��Ӧ��Task
    inline CwxAppTaskBoardTask* _getTask(CWX_UINT32 uiTaskId);
    ///��������Taskboardɾ��һ��task;
    CwxAppTaskBoardTask* _remove(CWX_UINT32 uiTaskId);
    ///�ַ�Task�ϻ������Ϣ
    CWX_UINT8 dispatchEvent(CwxAppTaskBoardTask* pTask, CwxAppTss* pThrEnv);
    ///��������������ӵ�һ��Task
    inline void _addConnTask(CWX_UINT32 uiConnId, CwxAppTaskBoardTask* pTask);
    ///��������ɾ�����ӵ�һ��Task
    inline void _removeConnTask(CWX_UINT32 uiConnId, CWX_UINT32 uiTaskId);
    ///��������ɾ��һ�������ϵ�����Task
    inline void _removeConnTask(CWX_UINT32 uiConnId);
private:
    CwxAppTaskBoardTask*      m_pTaskHead;///<�����Task�������ͷ
    CwxAppTaskBoardTask*      m_pTaskTail;///<�����Task�������β
    CWX_APP_TASK_MAP*         m_pTaskMap;///<Task��Map����
    map<CwxAppTaskBoardConnTasks, CwxAppTaskBoardTask*> m_connTaskMap;///<������Task�Ķ�ӦMap
    set<CwxAppTaskBoardTaskConns> m_taskConnSet;///<Task��Conn�Ķ�ӦMap
	CwxMutexLock        m_lock;///<Taskboard��ͬ����
    CWX_UINT32         m_uiMaxTaskNum;///<����Task���������
};

CWINUX_END_NAMESPACE
#include "CwxAppTaskBoard.inl"

#include "CwxPost.h"


#endif

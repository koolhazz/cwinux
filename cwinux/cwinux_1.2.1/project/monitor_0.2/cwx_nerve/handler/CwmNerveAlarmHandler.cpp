#include "CwmNerveAlarmHandler.h"
#include "CwmNerveApp.h"
#include "CwmNerveAlarmTask.h"
int CwmNerveAlarmHandler::onConnCreated(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
{
    CWX_DEBUG(("Alarm report's connection is created"));
    ///���澯��������ӽ���ʱ������澯������ID
    m_uiAlarmConnId = msg->event().getConnId();
    ///��鲢����������δ���͸澯
    reportNextAlarm(m_pApp, pThrEnv);
    return 1;
}

int CwmNerveAlarmHandler::onConnClosed(CwxMsgBlock*& msg, CwxAppTss* pThrEnv) 
{
    CWX_DEBUG(("Alarm report's connection is closed"));
    list<CwxAppTaskBoardTask*> tasks;
    ///���ø澯��������Ч
    m_uiAlarmConnId = CWX_APP_INVALID_CONN_ID;
    ///֪ͨtaskboard������澯�������Ѿ��ر�
    m_pApp->getTaskBoard().noticeConnClosed(msg, pThrEnv, tasks);
    ///���д��ظ��ĸ澯����Ӧ�÷��ظ澯�����task
    if (!tasks.empty())
    {
        list<CwxAppTaskBoardTask*>::iterator iter = tasks.begin();
        while(iter != tasks.end())
        {
            CWX_DEBUG(("Alarm task is finished for conn-closed."));
            ///���ڸ澯�Ǵ��б��棬������ֻ��һ��task
            (*iter)->execute(pThrEnv);
            iter++;
        }
        tasks.clear();
    }
    return 1;
}

int CwmNerveAlarmHandler::onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
{
    CwxAppTaskBoardTask* pTask = NULL;
    ///֪ͨtaskboard�յ��澯�Ļظ�
    CWX_DEBUG(("Recv alarm report's reply, task-id=%u", msg->event().getTaskId()));
    int ret = m_pApp->getTaskBoard().noticeRecvMsg(msg->event().getTaskId(), msg, pThrEnv, pTask);
    if (-1 == ret)
    {
        CWX_DEBUG(("Alarm report's task doesn't exist, task-id=%u", msg->event().getTaskId()));
    }
    else if (0 == ret)
    {
        CWX_DEBUG(("Alarm report's task doesn't finish, task-id=%u", msg->event().getTaskId()));
    }
    else
    {
        CWX_ASSERT(pTask);
        CWX_DEBUG(("Alarm report's task has finished.task-id=%u", msg->event().getTaskId()));
        pTask->execute(pThrEnv);
    }
    return 1;
}

int CwmNerveAlarmHandler::onEndSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
{
    CwxAppTaskBoardTask* pTask = NULL;
    CWX_DEBUG(("Alarm repot's msg is sent, task-id=%u", msg->event().getTaskId()));
    m_pApp->getTaskBoard().noticeEndSendMsg(msg->event().getTaskId(), msg, pThrEnv, pTask);
    if (pTask)
    {
        CWX_DEBUG(("Task has finished for msg-end-sent, it's strange. task-id=%u", msg->event().getTaskId()));
        pTask->execute(pThrEnv);
    }
    return 1;
}

int CwmNerveAlarmHandler::onFailSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv)
{
    CwxAppTaskBoardTask* pTask = NULL;
    CWX_DEBUG(("Alarm repot's msg is failure to be sent, task-id=%u", msg->event().getTaskId()));
    m_pApp->getTaskBoard().noticeFailSendMsg(msg->event().getTaskId(), msg, pThrEnv, pTask);
    if (pTask) pTask->execute(pThrEnv);
    return 1;
}

void CwmNerveAlarmHandler::reportNextAlarm(CwmNerveApp* pApp, CwxAppTss* pThrEnv)
{
    ///��������Ч����һ������ĸ澯û�лظ����򲻷�����һ���澯
    if (pApp->getAlarmHandler()->isReportReply() &&
        (CWX_APP_INVALID_CONN_ID != pApp->getAlarmHandler()->getAlarmConnId()))
    {
        CwmCmnAlarm alarm;
        ///���д��ڵ������澯������뷢��
        if (1 == pApp->getDataMgr()->nextReportAlarm(alarm))
        {
            CwmNerveAlarmTask* pTask = new CwmNerveAlarmTask(pApp, &pApp->getTaskBoard());
            pTask->m_alarm = alarm;
            ///����task��id
            pTask->setTaskId(pApp->nextTaskId());
            ///����task�ĳ�ʱʱ���
            pTask->setTimeoutValue(CwxDate::getTimestamp() + pApp->getConfig().getTimeout() * 1000000);
            CWX_DEBUG(("Report the next alarm, task's task-id=%u", pTask->getTaskId()));
            pTask->execute(pThrEnv);
        }
    }
}

bool CwmNerveAlarmHandler::sendAlarm(CwmNerveApp* pApp, CwxAppTss* pThrEnv, CwmCmnAlarm const& alarm)
{
    CwmNerveTss* pTss = (CwmNerveTss*)pThrEnv;
    CwxPackageWriter* pWriter = pTss->getSndPackage();
    CWX_DEBUG(("Begin report alarm, service=%s, action=%s, wid=%d, pid=%d, datetime=%s, level=%u",
        alarm.getService().c_str(),
        alarm.getAction().c_str(),
        alarm.getWid(),
        alarm.getPid(),
        alarm.getDatetime().c_str(),
        alarm.getLevel()));
    ///���澯����Ϣ���γ�һ��key/value��package����Ϊmsg��data����
    pWriter->beginPack();
    ///add host
    pWriter->addKeyValue(CWM_CMN_HOST, alarm.getHost());
    ///add wid
    pWriter->addKeyValue(CWM_CMN_WID, alarm.getWid());
    ///add pid
    pWriter->addKeyValue(CWM_CMN_PID, alarm.getPid());
    ///add datetime
    pWriter->addKeyValue(CWM_CMN_DATETIME, alarm.getDatetime());
    ///add level
    pWriter->addKeyValue(CWM_CMN_LEVEL, alarm.getLevel());
    ///add system
    pWriter->addKeyValue(CWM_CMN_SYSTEM, alarm.getSystem());
    ///add service
    pWriter->addKeyValue(CWM_CMN_SERVICE, alarm.getService());
    ///add action
    pWriter->addKeyValue(CWM_CMN_ACTION, alarm.getAction());
    ///add type
    pWriter->addKeyValue(CWM_CMN_TYPE, alarm.getType());
    ///add pwid
    pWriter->addKeyValue(CWM_CMN_PWID, alarm.getPWid());
    ///add plevel
    pWriter->addKeyValue(CWM_CMN_PLEVEL, alarm.getPLevel());
    ///add error
    pWriter->addKeyValue(CWM_CMN_ERROR, alarm.getError());
    pWriter->pack();

    ///�γɷ��͵�msg block
    CwxMsgHead header(0, 0, MSG_TYPE_ALARM_REPORT, pApp->nextTaskId(), pWriter->getMsgSize());
    CwxMsgBlock* pBlock = CwxMsgBlockAlloc::pack(header, pWriter->getMsg(), pWriter->getMsgSize());
    ///���÷��͵Ŀ�����Ϣ
    //���÷��͵�����
    pBlock->send_ctrl().setConnId(pApp->getAlarmHandler()->getAlarmConnId());
    //���÷��͵����ӵ�svr-id
    pBlock->send_ctrl().setSvrId(CwmNerveApp::SVR_TYPE_ALARM);
    //����host id
    pBlock->send_ctrl().setHostId(0);
    //���÷��͹��̵Ļص�
    pBlock->send_ctrl().setMsgAttr(CwxMsgSendCtrl::FAIL_FINISH_NOTICE);
    //���÷��Ͱ���Task ID��������ʧ�ܻ����ʱ�����Ի�ȡ��
    pBlock->event().setTaskId(header.getTaskId());
    if (0 != pApp->sendMsgByConn(pBlock))
    {
        CWX_ERROR(("Failure to report alarm msg, task-id=%u", header.getTaskId()));
        CwxMsgBlockAlloc::free(pBlock);
        return false;
    }
    CWX_DEBUG(("Alarm is reported,wid=%u", alarm.getWid()));
    return true;
}

#ifndef __CWX_DAY_LOGGER_H__
#define __CWX_DAY_LOGGER_H__
/*
��Ȩ������
    �����Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
*@file  CwxDayLogger.h
*@brief  ������CwxDayLogger�࣬ʵ����־�������ΧΪ1�죬��СΪ1���ӵķ��ļ���¼
*@author cwinux@gmail.com
*@version 0.1
*@date    2009-10-19
*@warning ��
*@bug   
*/

#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxStl.h"
#include "CwxCommon.h"
#include "CwxMutexLock.h"
#include "CwxLockGuard.h"
#include "CwxDate.h"
#include "CwxUtilMacro.h"

CWINUX_BEGIN_NAMESPACE
/**
*@class  CwxDayLogger
*@brief  ������־�������ΧΪ1�죬��СΪ1���ӵķ��ļ���¼��
*        ÿ��ָ����ʱ�̣�ϵͳ���Զ��л���־�ļ�����־�ļ�������Ϊ���ļ���_yyyymmddH24MMSS.suffix��
*        �˶����Ƕ��̰߳�ȫ�ġ�
*/
class CwxDayLogger
{
public:
    enum{
        DEF_LOG_INTERNAL = 1440///<ȱʡһ��һ����־�ļ�
    };
    ///���캯��
    CwxDayLogger()
    {
        m_switchInternal = DEF_LOG_INTERNAL * 60;
        m_ttCurLogTimeBegin = 0;
        m_ttCurLogTimeEnd = 0;
        m_curFd = NULL;
        m_prevFd = NULL;
        memset(m_szErrMsg, 0x00, 511);
    }
    ///��������
    ~CwxDayLogger()
    {
        if (m_curFd) fclose(m_curFd);
        if (m_prevFd) fclose(m_prevFd);
    }
public:
    /**
    *@brief  �����ʼ��.
    *@param [in] strPath ��־�ļ���·��+���ļ���.
    *@param [in] strFilePrex ��־�ļ��ĺ�׺���γɵ��ļ���Ϊ[strPath_yyyymmddH24MMSS.strFilePrex].
    *@param [in] uiSwitchInternal ��־�ļ����л�ʱ��������λΪ����.
    *@return 0:success; -1:failure.
    */
    int init(string const& strPath, string const& strFilePrex, CWX_UINT32 uiSwitchInternal=DEF_LOG_INTERNAL);
    /**
    *@brief  ����־д����־�ļ��У�����ǰʱ��Ϊ��ǰlog�ķ�Χ����ʹ�õ�ǰ��־�ļ��������л���һ��.
             ֧�ֵ���־��¼�Ϊ4K��
             ��֧�ֱ�Σ����ʽ�����ͬprintf()����API��Ϊÿ����¼�Զ��ӻس���
             ͬʱ��API��Ϊÿ����¼����һ��[yyyy-mm-dd h24:mm:ss]��ʱ���
    *@param [in] format ��־�ļ��ĸ�ʽ���ַ���.
    *@param [in] ... ��β���.
    *@return 0:success; -1:failure.
    */
    int log(char const* format, ...);
    /**
    *@brief  ͬlog(char const* format, ...)��������buf���ⲿ�趨
    *@param [in] buf ��־��buf.
    *@param [in] uiBufLen buf�Ŀռ�.
    *@param [in] format ��־�ļ��ĸ�ʽ���ַ���.
    *@param [in] ... ��β���.
    *@return 0:success; -1:failure.
    */
    int log(char* buf, CWX_UINT32 uiBufLen, char const* format, ...);

    /**
    *@brief  ����־д����־�ļ��У�����ǰʱ��Ϊ��ǰlog�ķ�Χ����ʹ�õ�ǰ��־�ļ��������л���һ��.
    ֧�ֵ���־��¼�Ϊ4K��
    ��֧�ֱ�Σ����ʽ�����ͬprintf()����API��Ϊÿ����¼�Զ��ӻس���
    ��log�Ĳ���ǲ����Զ�����ʱ�����
    *@param [in] format ��־�ļ��ĸ�ʽ���ַ���.
    *@param [in] ... ��β���.
    *@return 0:success; -1:failure.
    */
    int rawLog(char const* format, ...);
    /**
    *@brief  ͬrawLog(char const* format, ...)��������buf���ⲿ�趨
    *@param [in] buf ��־��buf.
    *@param [in] uiBufLen buf�Ŀռ�.
    *@param [in] format ��־�ļ��ĸ�ʽ���ַ���.
    *@param [in] ... ��β���.
    *@return 0:success; -1:failure.
    */
    int rawLog(char* buf, CWX_UINT32 uiBufLen, char const* format, ...);

    ///��ʼ�������ʱ�򣬻�ȡ�����ԭ��
    char const* getErrMsg() const
    {
        return m_szErrMsg;
    }
private:
    ///�л���־�ļ���ttDayΪ����־�ļ�����������
    int switchLog();
private:
    string              m_strPath;  ///<��־�ļ���·��+���ļ���
    string              m_strFilePrex;///<��־�ļ��ĺ�׺
    CWX_UINT32          m_switchInternal; ///<��־�ļ����л�ʱ��������λΪs
    time_t              m_ttCurLogTimeBegin; ///<��ǰ��־�ļ�������
    time_t              m_ttCurLogTimeEnd; ///<��ǰ��־�ļ�������
    CwxMutexLock         m_lock; ///<�����ļ��л�ʱ��ı�����
    FILE *              m_curFd;    ///<��ǰ����־�ļ�fd
    FILE *              m_prevFd; ///<ǰһ������־�ļ�fd
    char                m_szErrMsg[512];///<����init�Ĵ�����־
};


CWINUX_END_NAMESPACE

#include "CwxPost.h"

#endif

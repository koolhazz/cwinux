#ifndef __CWX_BINLOG_OP_H__
#define __CWX_BINLOG_OP_H__
/*
版权声明：
    本软件为个人所有，遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html），
但有以下例外：
    腾讯公司及与腾讯公司有直接业务与合作关系的公司不得使用此软件。原因可参考：
http://it.sohu.com/20100903/n274684530.shtml
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/
/**
@file CwxBinlogOp.h
@brief binlog 文件的浏览对象
@author cwinux@gmail.com
@version 0.1
@date 2009-10-10
@warning
@bug
*/
#include "CwxPackageReader.h"
#include "CwxBinLogMgr.h"
#include "CwxXmlPackageConv.h"

CWINUX_USING_NAMESPACE

class CwxBinlogOp{
public:
    enum{
        BINLOG_INDEX_INTERNAL = 100, ///<binlog建立索引的粒度，N,2N,3N......
        BINLOG_COMPRESS_RATE  = 10   ///<若是压缩数据，则默认压缩率为10倍
    };
public:
    CwxBinlogOp();
    ~CwxBinlogOp();
    int init(string const& strBinLogFileName);
    void run();
private:
    void clear();
    void prompt();
    //0：exit，1：continue
    int doCommand(char* szCmd);
    void doHelp();
    void doInfo();
    void doNext(CWX_UINT32 uiNum);
    void doPrev(CWX_UINT32 uiNum);
    void doSid(CWX_UINT64 ullSid);
    void doRecord(CWX_UINT32 uiRecord);
    void doAttr(CWX_UINT32 uiMask, CWX_UINT32 uiAttr);
    void doGroup(CWX_UINT32 uiGroup);
    void doType(CWX_UINT32 uiType);
    void doKey(char const* szKey, char const* szValue);
    void doHead();
    void doData();
    void doSave(string const& strFileName);
//    void doDump(bool bHead, string const& strFileName);
    void doZip(int bit);

    bool prepareBuf(CWX_UINT32 uiLen);
    bool prepareUnBuf(CWX_UINT32 uiLen);
    bool prepareDumpBuf(CWX_UINT32 uiLen);
    char* getData(CWX_UINT32& uiLen);

private:
    map<CWX_UINT64/*sid*/, CWX_UINT64/*offset*/>  m_sidIndex; ///<每BINLOG_INDEX_INTERNAL条记录建立一条索引
    map<CWX_UINT32/*rec_no*/, CWX_UINT64/*offset*/> m_recIndex; ///<每BINLOG_INDEX_INTERNAL条记录建立索引
    CwxBinLogCursor*     m_pCursor; ///<binlog的读取cursor
    char*               m_pBuf; ///<data读取的buf
    CWX_UINT32          m_uiBufLen; ///<data读取buf的空间大小
    char*               m_pUnBuf; ///<data解压buf
    CWX_UINT32          m_uiUnBufLen; ///<data解压buf的空间大小
    char*               m_pDumpBuf; ///<data dump buf
    CWX_UINT32           m_uiDumpBufLen; ///<data dump buf的空间大小
    CWX_UINT64          m_ullMinSid; ///<最小的sid值
    CWX_UINT64          m_ullMaxSid; ///<最大的sid值
    CWX_UINT32          m_uiRecNum; ///<binlog的数量
    int                m_iZipBit; ///<head attr中的压缩位
    string              m_strLogFileName; ///<binlog文件的名字
    char                m_szErr2K[2048]; ///<错误时的错误消息
};

#endif

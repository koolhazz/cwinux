#include "CwxAppProcessMgr.h"
#include "CwfFilterApp.h"

int main(int argc, char** argv)
{
    //����ECHO��app����ʵ��
    CwfFilterApp* pApp = new CwfFilterApp();
    //��ʼ��˫���̹�����
    if (0 != CwxAppProcessMgr::init(pApp)) return 1;
    //����˫���̣�һ��Ϊ���echo���̵ļ�ؽ��̣�һ��Ϊ�ṩecho����Ĺ������̡�
    CwxAppProcessMgr::start(argc, argv, 100, 300);
    return 0;
}

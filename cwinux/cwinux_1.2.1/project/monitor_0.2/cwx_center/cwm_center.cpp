#include "CwxAppProcessMgr.h"
#include "CwmCenterApp.h"

int main(int argc, char** argv)
{
    ///����app����
    CwmCenterApp* pApp = new CwmCenterApp();
    ///��ʼ�����̹�����
    if (0 != CwxAppProcessMgr::init(pApp)) return 1;
    ///����˫���̣�10Ϊ�������������300��ʾ����ʱ��ǰ300�����û��������
    CwxAppProcessMgr::start(argc, argv, 10, 300);
    return 0;
}

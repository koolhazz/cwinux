#include "CwxAppProcessMgr.h"
#include "CwmNerveApp.h"

int main(int argc, char** argv)
{
    ///����Nerve App ����
    CwmNerveApp* pApp = new CwmNerveApp();
    ///��ʼ�����̹�����
    if (0 != CwxAppProcessMgr::init(pApp)) return 1;
    ///����Nerve App��10Ϊ�����������Ϊ10s��
    ///300Ϊ����������ʱ��ǰ300����Բ����͸澯
    CwxAppProcessMgr::start(argc, argv, 10, 300);
    return 0;
}

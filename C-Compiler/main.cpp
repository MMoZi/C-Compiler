#include "Common.h"
#include "IOManager.h" 

int main(int argc, char** argv)
{
    // ��ȡλ��
    string path;
    // ����λ��
    string savePath; 

    IOManager& iomgr = IOManager::get_instance();
    string contents = iomgr.open(path);


    return 0;
}
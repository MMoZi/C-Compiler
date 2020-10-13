#include "Common.h"
#include "IOManager.h" 

int main(int argc, char** argv)
{
    // 读取位置
    string path;
    // 保存位置
    string savePath; 

    IOManager& iomgr = IOManager::get_instance();
    string contents = iomgr.open(path);


    return 0;
}
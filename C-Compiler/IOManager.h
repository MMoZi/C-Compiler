#pragma once 
#include "Common.h"
 
class IOManager
{
public: 
	string open(string& path); 
    IOManager(const IOManager&) = delete;
    IOManager& operator=(const IOManager&) = delete; 
    static IOManager& get_instance() { 
        static IOManager instance; // µ¥Àý»ñÈ¡
        return instance;

    } 
    void save(string& path, vector<string>& contents);
	void save(string& path, string& contents);
private:
    IOManager();
};
  

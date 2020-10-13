#include "IOManager.h"

void IOManager::save(string& path,vector<string>& contents) {
  
    ofstream outFile;
    //打开文件
    outFile.open(path,ios::in | ios::trunc);
    for (string c : contents) {
        outFile << c << "\n";
    } 
    //关闭文件
    outFile.close(); 
}

void IOManager::save(string& path, string& contents) {

    ofstream outFile;
    //打开文件
    outFile.open(path, ios::in | ios::trunc);
 
    outFile << contents << "\n";
 
    //关闭文件
    outFile.close();
}

string IOManager::open(string& path) {
    ifstream inFile; 
    inFile.open(path);      
    
    stringstream buffer;
    buffer << inFile.rdbuf();
    string contents(buffer.str());

    buffer.clear();
    inFile.close();
    
    return contents; 
}

IOManager::IOManager() {}
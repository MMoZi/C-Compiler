#include "LexicalAnalysis.h"

// 将 2的h次方进制 转换 为十进制  
string LexicalAnalysis::convert2decimal(string w, int h) {

    int len = w.size();
    int val = 0; 
    for (int i = 0; i < len; i++) {
        val <<= h;
        if (w[i] >= 'A' && w[i] <= 'F') {
            val = val + (w[i] - 'A' + 10);
        }
        else if (w[i] >= 'a' && w[i] <= 'f') {
            val = val + (w[i] - 'a' + 10);
        }
        else {
            val = val + (w[i] - '0');
        }
    }
    return to_string(val);
}

// 解析标识符
int LexicalAnalysis::parseId(string& str, int index)
{ 
    int state = 0; 
    string words = "";
    while (state != 2) {
        switch (state)
        {
        case 0:
            if (isalpha(str[index]) || str[index] == '_') {
                words += str[index];
                state = 1;
            } break;
        case 1:
            if (isalpha(str[index]) || str[index] == '_' || isdigit(str[index])) {
                words += str[index];
                state = 1;
            }
            else {
                state = 2; 
            }break;
        }
        index++; col++;
    }
    index--; col--; // 回退坐标
  
    if (keyWordSet.count(words)) {
        tokenVec.push_back({ words,TokenCode::OTHER,row,col - 1 }); // 关键字直接归类为 OTHER
    }
    else {
        tokenVec.push_back({ words,TokenCode::ID ,row,col - 1 });   // 标识符
    } 
    return index;
}

// 解析数字
int LexicalAnalysis::parseDigit(string& str, int index)
{
    int state = 0;
    int i = 0;
    string words = ""; 

    // state == 2 十进制结束
    // state == 5 八进制结束
    // state == 8 十六进制结束
    // state == 9 整数 0
    while (state != 2 && state != 5 && state != 8 && state != 9) {
        switch (state)
        {
        case 0:
            if (str[index] == '0'){
                words += str[index];
                state = 3;
            }
            else {
                state = 1;
                words += str[index];
            }
            break;
        case 1:
            if (isdigit(str[index])) {
                words += str[index];
                state = 1;
            }
            else {
                state = 2;// 十进制结束
            }
            break;
        case 3:
            if (str[index] >= '0'  && str[index] <= '7'){
                state = 4;
                words += str[index]; 
            }
            else if (str[index] == 'X' || str[index] == 'x'){
                state = 6;
                words += str[index];
            }
            else {
                state = 9;  // 整数 0 
            }
            break;
        case 4:
            if (str[index] >= '0' && str[index] <= '7') {
                state = 4;
                words += str[index]; 
            }
            else {
                state = 5; // 八进制结束 
            }
            break;
        case 6:
            if ( (str[index] >= 'a' && str[index] <= 'f' )|| (str[index] >= 'A' && str[index] <= 'F') || isdigit(str[index]) ){
                state = 7;
                words += str[index];
            }
            else { 
                cout << "error" << endl;
            }
              break;
        case 7:	
            if ( (str[index] >= 'a' && str[index] <= 'f') || (str[index] >= 'A' && str[index] <= 'F') || isdigit(str[index])){
                state = 7;
                words += str[index]; 
            } 
            else {
                state = 8; //十六进制结束，返回整型 
            }
            break; 
        }
        index++;
        col++;
    }
    index--;
    col--; 
    if (state == 5) {
        words = convert2decimal(words,3);
    }else if(state == 8){
        words = convert2decimal(words.substr(2),4);
    }  
    tokenVec.push_back({ words,TokenCode::NUM,row,col - 1 });

    return index;
}

// 解析比较符号，如：>= <= == 
int LexicalAnalysis::parseCmp(string& str, int index)//< <= > >=
{ 
    char target = str[index];
    string words = "" + target;
    ++index; ++col; 
    if (str[index] == '=') { 
        words += str[index];
        ++index; ++col;
    } 
    tokenVec.push_back({ words,TokenCode::OTHER,row,col - 1 }); 
    return index;
}

// 解析逻辑符号，如 && 和 ||
int LexicalAnalysis::parseLogic(string& str, int index)//&&
{ 
    char target = str[index];
    string words = "" + target;
    ++index; ++col;
    if (str[index] == target) {
        words += str[index];
        ++index; ++col;
    }
    else {
        cout << "error" << endl;
    }
    tokenVec.push_back({ words,TokenCode::OTHER,row,col - 1 }); 
    return index;
} 

// 解析 除号 和 注释  
int LexicalAnalysis::parseDivAndAnnot(string& str, int index) 
{
    int flag = 0;   // flag = 0 代表解析内容为注释 ，否则为运算符
    int state = 0;  // 状态
    string words = "";  

    while (state != 5) {
        switch (state)
        {
            case 0:
                if (str[index] == '/') {
                    state = 1;
                    words += str[index];
                }  break;
            case 1: // 依次对应 a) 多行注释  b)单行注释  c) 除号等于  d) 除号 
                if (str[index] == '*'){ state = 2; }
                else if (str[index] == '/') { state = 3;}
                else if (str[index] == '=') {
                    words += str[index]; 
                    state = 5; flag = 1;
                }
                else{ 
                    index--;
                    state = 5; flag = 1;  
                } break;
            case 2://  多行注释 /**
                if (str[index] == '*') { state = 4;} 
                break;
            case 3://  单行注释 //
                if (str[index] != '\n') { state = 5;}
                else { 
                    cout << "ERROR" << endl;
                } break;
            case 4://  多行注释 /**/
                if (str[index] == '/') { state = 5; }
                break;
        }
        index++; col++;
    } 
    if (flag) { 
        tokenVec.push_back({ words,TokenCode::OTHER,row,col - 1 });
    }
    return index;
}

// 解析 加号 和 减号
int LexicalAnalysis::parsePlusAndMinus(string& str, int index)
{ 
    char target = str[index];
    string words = "" + target;
    ++index; ++col;
    if (str[index] == '=' || str[index] == target){ 
        words += str[index];   // ++  -- -= +=
    }   
    tokenVec.push_back({ words,TokenCode::OTHER,row,col - 1 });
    return index;
} 

// 解析 乘法
int LexicalAnalysis::parseMul(string& str, int index)
{
    char target = str[index];
    string words = "" + target;
    ++index; ++col;
    if (str[index] == '=') {
        words += str[index];   // *=
    }
    tokenVec.push_back({ words,TokenCode::OTHER,row,col - 1 }); 
    return index;
}

vector<Token> LexicalAnalysis::analysis(string& contents)
{ 
    char ch = ' ';
    int idx = 0; //文本下标  
    set<char> others = { '(' , ')' , '{' , '}' , '[' , ']' , ',' , ';', '\"', '\'', '.'};
    //block["%"] = 205;  
    //扫描文本
    while (idx < contents.size())
    {  
        if (contents[idx] == '\n') {
            ++row; col = 1;
            ++idx;
        }
        else if (contents[idx] == ' ' || contents[idx] == '\t') { 
            ++idx; 
        }
        else if (contents[idx] == '/') {
            idx = parseDivAndAnnot(contents, idx);
        }
        else if (isalpha(contents[idx]) || contents[idx] == '_') {
            idx = parseId(contents, idx); 
        }
        else if (isdigit(contents[idx])) {
            idx = parseDigit(contents, idx);
        }
        else if (contents[idx] == '<' || contents[idx] == '>' || contents[idx] == '=' || contents[idx] == '!'){
            idx = parseCmp(contents, idx); 
        } 
        else if (contents[idx] == '&' || contents[idx] == '|'){
            idx = parseLogic(contents, idx); 
        } 
        else if (contents[idx] == '+' || contents[idx] == '-') {
            idx = parsePlusAndMinus(contents, idx);
        } 
        else if (contents[idx] == '*') {
            idx = parseMul(contents, idx); 
        }
        else if (others.count(contents[idx])) {
            string word = "" + contents[idx]; 
            tokenVec.push_back({ word ,TokenCode::OTHER,row,col });
            idx++; col++;         
        }
        else {
            cout << "无法识别该字符:" << contents[idx] << ";";
            idx++; col++; 
        }
    }
    //cout << "TOKEN串" << endl;
    //cout << "单词 种别码 行 列" << endl;
    //for (int i = 0; i < token_list.size(); i++)
    //{
    //    cout << token_list[i].word << " " << token_list[i].code << " " << token_list[i].row << " " << token_list[i].col << endl;//单词后面的\0输出的是乱码
    //}
    return tokenVec;
}

 

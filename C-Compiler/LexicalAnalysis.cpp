#include "LexicalAnalysis.h"

// �� 2��h�η����� ת�� Ϊʮ����  
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

// ������ʶ��
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
    index--; col--; // ��������
  
    if (keyWordSet.count(words)) {
        tokenVec.push_back({ words,TokenCode::OTHER,row,col - 1 }); // �ؼ���ֱ�ӹ���Ϊ OTHER
    }
    else {
        tokenVec.push_back({ words,TokenCode::ID ,row,col - 1 });   // ��ʶ��
    } 
    return index;
}

// ��������
int LexicalAnalysis::parseDigit(string& str, int index)
{
    int state = 0;
    int i = 0;
    string words = ""; 

    // state == 2 ʮ���ƽ���
    // state == 5 �˽��ƽ���
    // state == 8 ʮ�����ƽ���
    // state == 9 ���� 0
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
                state = 2;// ʮ���ƽ���
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
                state = 9;  // ���� 0 
            }
            break;
        case 4:
            if (str[index] >= '0' && str[index] <= '7') {
                state = 4;
                words += str[index]; 
            }
            else {
                state = 5; // �˽��ƽ��� 
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
                state = 8; //ʮ�����ƽ������������� 
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

// �����ȽϷ��ţ��磺>= <= == 
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

// �����߼����ţ��� && �� ||
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

// ���� ���� �� ע��  
int LexicalAnalysis::parseDivAndAnnot(string& str, int index) 
{
    int flag = 0;   // flag = 0 �����������Ϊע�� ������Ϊ�����
    int state = 0;  // ״̬
    string words = "";  

    while (state != 5) {
        switch (state)
        {
            case 0:
                if (str[index] == '/') {
                    state = 1;
                    words += str[index];
                }  break;
            case 1: // ���ζ�Ӧ a) ����ע��  b)����ע��  c) ���ŵ���  d) ���� 
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
            case 2://  ����ע�� /**
                if (str[index] == '*') { state = 4;} 
                break;
            case 3://  ����ע�� //
                if (str[index] != '\n') { state = 5;}
                else { 
                    cout << "ERROR" << endl;
                } break;
            case 4://  ����ע�� /**/
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

// ���� �Ӻ� �� ����
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

// ���� �˷�
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
    int idx = 0; //�ı��±�  
    set<char> others = { '(' , ')' , '{' , '}' , '[' , ']' , ',' , ';', '\"', '\'', '.'};
    //block["%"] = 205;  
    //ɨ���ı�
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
            cout << "�޷�ʶ����ַ�:" << contents[idx] << ";";
            idx++; col++; 
        }
    }
    //cout << "TOKEN��" << endl;
    //cout << "���� �ֱ��� �� ��" << endl;
    //for (int i = 0; i < token_list.size(); i++)
    //{
    //    cout << token_list[i].word << " " << token_list[i].code << " " << token_list[i].row << " " << token_list[i].col << endl;//���ʺ����\0�����������
    //}
    return tokenVec;
}

 

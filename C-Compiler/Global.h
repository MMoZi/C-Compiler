#pragma once 

#include "Common.h"

unordered_set<string> keyWordSet = { "int","const","void","if", "for", "switch", "while", "do", "return", "break", "continue" };


// �ֱ���
enum class TokenCode : int{
	ID,			// ��ʶ��
	NUM,		// ����
	OTHER		// ����
};

// Token �ṹ��
struct Token
{
    string word;
    TokenCode code;
    int row;
    int col;
	Token(string _word, TokenCode _code, int _row, int _col) :word(_word), code(_code), row(_row), col(_col) {}
};

// �м���� ���� ��Ԫʽ
struct Quadruple
{
	int type;  //��Ԫʽ����
    string op;
    string arg1;
    string arg2;
    string result;

    Quadruple(string op, string arg1, string arg2, string result):op(op),arg1(arg1),arg2(arg2),result(result),type(0) {  } 
	Quadruple(int type,string op, string arg1, string arg2, string result) :op(op), arg1(arg1), arg2(arg2), result(result), type(type) {  }

	bool isMethod() { return op[0] != '@' && arg1 == "" && arg2 == "" && result == ""; }
	bool isNotMethod() { return  op[0] == '@' || arg1 != "" || arg2 != "" || result != ""; }

};

struct BasicBlock {

	// �������
	int name ;
	//��ڱ��
	int start ;
	//���ڱ��
	int end ;

	// ֻ����Ծ֮��ĵ�һ��λ����label
	string label;
	// ����Ŀ��
	string jumpto;
	// ��һ����
	vector<int> next;
	// ��һ����
	vector<int> last;
	  
	// ������Ļ�Ծ����
	set<string> activeSet;
	// �����������еı��� ���ܻ��п�ֵ����
	unordered_set<string> allSymbol;

	BasicBlock():name(-1),start(-1),end(-1),label(""){}
};

 
//���������ķ��ű�
struct ChangBianTable {
	//����
	string name = "";

	//������
	int Area = 0;

	//0:���� 1:����
	int isChang = 1;

	//0:��������  1������
	int isarray = 0;

	// �Ƿ���ȫ�ֱ���(1:ȫ�ֱ���  0����ȫ�ֱ���)
	int isGlobal = -1;
	// ����Ƿ��ʼ����(1:��ʼ��  0���ǳ�ʼ��)
	int isInit = -1;
	// ����ֵ int��ҪΪ��Զ�ά����
	map<int, int> value;
	// ÿ��ά�ȵ����� ,dnum[0] Ϊ�ܸ���
	vector<int> dnum;
};

// �������ű�
struct FunTable {

	string name = "";//������
	string type = "";//����ֵ����
	vector<ChangBianTable> para;//ÿ��������Ϣ
};
 
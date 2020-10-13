#pragma once 

#include "Common.h"

unordered_set<string> keyWordSet = { "int","const","void","if", "for", "switch", "while", "do", "return", "break", "continue" };


// 种别码
enum class TokenCode : int{
	ID,			// 标识符
	NUM,		// 数字
	OTHER		// 其他
};

// Token 结构体
struct Token
{
    string word;
    TokenCode code;
    int row;
    int col;
	Token(string _word, TokenCode _code, int _row, int _col) :word(_word), code(_code), row(_row), col(_col) {}
};

// 中间代码 —— 四元式
struct Quadruple
{
	int type;  //四元式类型
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

	// 基本块号
	int name ;
	//入口编号
	int start ;
	//出口编号
	int end ;

	// 只有跳跃之后的第一个位置有label
	string label;
	// 跳向目标
	string jumpto;
	// 下一块编号
	vector<int> next;
	// 上一块编号
	vector<int> last;
	  
	// 基本块的活跃变量
	set<string> activeSet;
	// 基本块内所有的变量 可能会有空值“”
	unordered_set<string> allSymbol;

	BasicBlock():name(-1),start(-1),end(-1),label(""){}
};

 
//变量常量的符号表
struct ChangBianTable {
	//名字
	string name = "";

	//作用域
	int Area = 0;

	//0:常量 1:变量
	int isChang = 1;

	//0:单个变量  1：数组
	int isarray = 0;

	// 是否是全局变量(1:全局变量  0：非全局变量)
	int isGlobal = -1;
	// 标记是否初始化过(1:初始化  0：非初始化)
	int isInit = -1;
	// 变量值 int主要为针对二维数组
	map<int, int> value;
	// 每个维度的数量 ,dnum[0] 为总个数
	vector<int> dnum;
};

// 函数符号表
struct FunTable {

	string name = "";//函数名
	string type = "";//返回值类型
	vector<ChangBianTable> para;//每个参数信息
};
 
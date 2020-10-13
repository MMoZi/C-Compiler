#pragma once 

#include "Common.h"
#include "Global.h" 

class LexicalAnalysis {

private:
	
	vector<Token> tokenVec;//token´®
	int row = 1;//ÐÐÊý
	int col = 1;
	  
	string convert2decimal(string w, int h); 

	int parseCmp(string& str, int index); 

	int parseLogic(string& str, int index);   

	int parsePlusAndMinus(string& str, int index);  

	int parseDivAndAnnot(string& str, int index);
	
	int parseId(string& str, int index);

	int parseDigit(string& str, int index);
	
	int parseMul(string& str, int index); 

public:
	vector<Token> analysis(string& path); 

};
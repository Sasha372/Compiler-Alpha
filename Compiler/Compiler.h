#pragma once
#ifndef COMPILER_H
#define COMPILER_H

#define Glob 0 //����� � ���������� ������������
#define Var 1 //��� ����������
#define Var_eq 2 //������������ ���������� ��������
#define Func 3 //��� �������
#define Func_arg 4 //��������� �������
#define Func_cl 5 //����� �������
#define Func_API 6
#define Ret 7 //��� return
#define While 8 //��� ����� while
#define Whl_arg 9 //��������� ����� while
#define For 10 // ��� ����� for
#define For_arg 11 //��������� ����� for
#define If 12 //��� �������
#define If_arg  13 //��������� �������
#define User 14

#include <vector>
using namespace std;

namespace Compiler {
	extern struct word;
	extern word Global;

	//================================//

	void processCode(Code & TextCode); //������� ������� �����������
	void processBlock(Code & TextCode, word & vct, int parent); //��������� ����� ����

	void spGlobal(Code & TextCode, word & vct, int parent); //����� ���� � ����� ����
	bool readWordVar(string & istr, int & id, word & vct); //������ ����� var
	bool readWordFunc(string & istr, int & id, word & vct); //������ ����� func
	bool readWordWhile(string & istr, int & id, word & vct); //������ ����� while
	bool readWordReturn(string & istr, int & id, word & vct); //������ ����� return
	bool readWordIf(string & istr, int & id, word & vct); //������ ����� if
	bool readWordDLL(string & istr, int & id, word & vct);

	//================================//

	bool EquallyVar(string name, string & istr, int & id, word & vct); //��������� ����������� ���������� ��������
	bool CallFunc(string name, string & istr, int & id, word & vct); //��������� ������ �������
	
	//================================//

	void unpackBlock(word & vct);
	void glueCode(word vct,vector<string> & str);
}

#endif
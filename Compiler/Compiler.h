#pragma once
#ifndef COMPILER_H
#define COMPILER_H

#define Glob 0 //Слово в глобальном пространстве
#define Var 1 //Тип переменной
#define Var_eq 2 //Присваевание переменной значения
#define Func 3 //Тип функции
#define Func_arg 4 //Агрументы функции
#define Func_cl 5 //Вызов функции
#define Func_API 6
#define Ret 7 //Тип return
#define While 8 //Тип цикла while
#define Whl_arg 9 //Аргументы цикла while
#define For 10 // Тип цикла for
#define For_arg 11 //Аргументы цикла for
#define If 12 //Тип условия
#define If_arg  13 //Аргументы условия
#define User 14

#include <vector>
using namespace std;

namespace Compiler {
	extern struct word;
	extern word Global;

	//================================//

	void processCode(Code & TextCode); //Входная функция компилятора
	void processBlock(Code & TextCode, word & vct, int parent); //Обработка блока кода

	void spGlobal(Code & TextCode, word & vct, int parent); //Посик слов в блоке кода
	bool readWordVar(string & istr, int & id, word & vct); //Чтение слова var
	bool readWordFunc(string & istr, int & id, word & vct); //Чтение слова func
	bool readWordWhile(string & istr, int & id, word & vct); //Чтение слова while
	bool readWordReturn(string & istr, int & id, word & vct); //Чтение слова return
	bool readWordIf(string & istr, int & id, word & vct); //Чтение слова if
	bool readWordDLL(string & istr, int & id, word & vct);

	//================================//

	bool EquallyVar(string name, string & istr, int & id, word & vct); //Обработка присаивания переменной значения
	bool CallFunc(string name, string & istr, int & id, word & vct); //Обработка вызова функции
	
	//================================//

	void unpackBlock(word & vct);
	void glueCode(word vct,vector<string> & str);
}

#endif
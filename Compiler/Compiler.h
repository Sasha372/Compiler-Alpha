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
	void spGlobal		(Code & TextCode, word & vct); //Поиск слов в блоке кода
	void wordInGlobal	(Code & TextCode, vector<word> & vct);
	void readWordVar	(Code & TextCode, vector<word> & vct); //Чтение слова var
	void readWordFunc	(Code & TextCode, vector<word> & vct); //Чтение слова func
	void readWordWhile	(Code & TextCode, vector<word> & vct); //Чтение слова while
	void readWordReturn	(Code & TextCode, vector<word> & vct); //Чтение слова return
	void readWordIf		(Code & TextCode, vector<word> & vct); //Чтение слова if
	void readWordDLL	(Code & TextCode, vector<word> & vct);

	//================================//

	int VarOrFunc	(Code & TextCode, word & vct, string n); //Обработка присаивания переменной значения
	bool setValVar	(Code & TextCode, word & vct); //Обработка присаивания переменной значения
	bool CallFunc	(Code & TextCode, word & vct); //Обработка вызова функции
	
	//================================//

	void unpackBlock(word & vct);
	void glueCode(word vct,vector<string> & str);
}

#endif
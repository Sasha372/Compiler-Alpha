#include "stdafx.h"
#include "Compiler.h"
using namespace std;

namespace Compiler {
	struct word {
		string name; //Имя функции, переменной
		int type; //Тип слова
		//string str; //Не распакованная сторка
		string adr;
		int parent;
		vector<word> arg; //Аргумент после распаковки из str. Содержит 
		vector<word> body; //Слова после распаковки из str
	};
	word Global;
	vector<word> listFunc;
	vector<vector<word>> listVar;

	string currFunc;
}

void Compiler::processCode(Code & C)
{
	cout << "Processing..." << endl;
	word wrd;
	wrd.type = Func_API;
	wrd.name = "status";
	listFunc.push_back(wrd);

	//==============================//

	spGlobal(C, Global); //Запуск обработки кода и запись слов п вектор listWord
	//glueCode(Global, out);
}

void Compiler::spGlobal			(Code & C, word & vct)
{
	while(!C.isEnd()) {
		string nWord;
		if (C.nextSymbol(true) == 0)break;
		switch (C.nextSymbol(true))
		{
		case '@':{
			C.nextSymbol();
			nWord = C.nextWord();
			if (nWord == "def") {
				cout << "define " << C.nextWord() << " -> ";
				cout << C.nextWord() << endl;
			}
			else if (nWord == "req") {
				string sss = C.nextWord();
				cout << "included file " << sss << endl;
				//Code New(C.getPath() + sss, "//", "/*", "*/");
				//spGlobal(New, vct);
			}
			else {
				C.error(0, nWord);
			}
			break; }
		default:
			if (str::isChrBeStr(C.nextSymbol(true), str::letters + "_")) {
				string tmp_wrd = C.nextWord();
					 if (tmp_wrd == "var")		readWordVar(C, vct.body);
				else if (tmp_wrd == "func")		readWordFunc(C, vct.body);
				else if (tmp_wrd == "while")	readWordWhile(C, vct.body);
				else if (tmp_wrd == "return")	readWordReturn(C, vct.body);
				else if (tmp_wrd == "if")		readWordIf(C, vct.body);
				//else if (EquallyVar(tmp_wrd, istr, id, vct.body)) {}
				//else if (CallFunc(tmp_wrd, istr, id, vct.body)) {}
				else cout << "Unknow identifier: " << tmp_wrd << endl;
			}
			else {
				C.error(1, C.nextSymbol(true) + "");
				C.nextSymbol();
			}
		}
	}
}
void Compiler::readWordVar		(Code & C, vector<word> & vct)
{
	string value;
	word tmp, arg;
	tmp.type = Var;
	tmp.name = C.nextWord();
	if (C.nextSymbol(true) == '=') {
		value = C.nextWord();
	}
	if (currFunc != "") { //Если находимся в теле функции
		tmp.name = currFunc + "." + tmp.name; //Добавляем к имени имя функции
	}

	if (value != "") arg.name = value;
	else arg.name = "0"; // Value of var is zero
	cout << "var " << tmp.name << " = " << arg.name << endl;
	tmp.arg.push_back(arg); //Добавлени в конец вектора аргуменов слова значения переменной
	vct.push_back(tmp); //Добавление к главному дереву слов
}
void Compiler::readWordFunc		(Code & C, vector<word> & vct)
{
	word tmp;
	tmp.type = Func;
	tmp.name = C.nextWord();
	tmp.adr = str::CharRand();
	cout << "function " << tmp.name << " begin" << endl;

	if (C.nextSymbol(true) == '(') {
		C.nextSymbol();
		while (C.nextSymbol(true) != ')') {
			readWordVar(C, tmp.arg);
		}
		C.nextSymbol();
	}
	cout << "begining body of func" << endl;
	while (C.nextWord(true) != "end") {
		/*char fggggg = C.nextSymbol(true);
		//cout << fggggg << ":" << (int)fggggg <<* endl;*/
		string tmp_wrd = C.nextWord();
			 if (tmp_wrd == "var")		readWordVar(C, tmp.body);
		else if (tmp_wrd == "while")	readWordWhile(C, tmp.body);
		else if (tmp_wrd == "return")	readWordReturn(C, tmp.body);
		else if (tmp_wrd == "if")		readWordIf(C, tmp.body);
		//else if (EquallyVar(tmp_wrd, istr, id, tmp.body)) {}
		//else if (CallFunc(tmp_wrd, istr, id, tmp.body)) {}
		else C.error(3, tmp_wrd);
	}
	C.nextWord();
	cout << "function " << tmp.name << " ended" << endl;
	vct.push_back(tmp);
}
void Compiler::readWordWhile	(Code & C, vector<word> & vct)
{
	word tmp;
	tmp.type = While;
	tmp.adr = str::CharRand();
	cout << "while begin" << endl;

	if (C.nextWord(true) != "do") {
		C.nextWord();
		C.nextWord();
	}
	while (C.nextWord(true) != "end") {
		string tmp_wrd = C.nextWord();
		if (tmp_wrd == "var") readWordVar(C, tmp.body);
		else if (tmp_wrd == "while") readWordWhile(C, tmp.body);
		//else if (tmp_wrd == "return") readWordReturn(C, tmp.body);
		else if (tmp_wrd == "if") readWordIf(C, tmp.body);
		//else if (EquallyVar(tmp_wrd, istr, id, tmp.body)) {}
		//else if (CallFunc(tmp_wrd, istr, id, tmp.body)) {}
		else C.error(3, tmp_wrd);
	}
	C.nextWord();
	cout << "while ended" << endl;
	vct.push_back(tmp);
}
void Compiler::readWordReturn	(Code & C, vector<word> & vct)
{
	/*
	string tmp_str;
	string val;
	word tmp;
	tmp.type = Ret;
	while (!(istr[id] == ';')) {
		if (!(istr[id] == ' ')) {
			tmp_str += istr[id];
		}
		id++;
	}
	//id++;
	if (tmp_str.size() != 0) {
		tmp.name = tmp_str;
	}
	//cout << istr[id] << endl;
	vct.body.push_back(tmp);
	*/
}
void Compiler::readWordIf		(Code & C, vector<word> & vct)
{
	word tmp;
	tmp.type = If;
	cout << "if " << tmp.name << " begin" << endl;

	if (C.nextWord(true) != "then") {
		
	}
	C.nextWord();

	if (C.nextSymbol(true) == '{') {
		C.nextSymbol();
		while (C.nextSymbol(true) != '}') {
			char fggggg = C.nextSymbol(true);
			cout << fggggg << ":" << (int)fggggg << endl;
			string tmp_wrd = C.nextWord();
			if (tmp_wrd == "var") readWordVar(C, tmp.body);
			else if (tmp_wrd == "while") readWordWhile(C, tmp.body);
			//else if (tmp_wrd == "return") readWordReturn(C, tmp.body);
			//else if (tmp_wrd == "if") readWordIf(C, tmp.body);
			//else if (EquallyVar(tmp_wrd, istr, id, tmp.body)) {}
			//else if (CallFunc(tmp_wrd, istr, id, tmp.body)) {}
			else C.error(3, tmp_wrd);
		}
		C.nextSymbol();
	}
	else C.error(2, "");
	cout << "if " << tmp.name << " ended" << endl;
	vct.push_back(tmp);
}
void Compiler::readWordDLL		(Code & C, vector<word> & vct)
{
	/*string func_name;
	word func_arg;
	{
		id += 2;
		while (istr[id] != '(' && istr[id] != ' ') {
			func_name += istr[id];
			id++;
		}
		id++;
		int quotes = 1;
		bool argOpen = false;
		while (!(quotes == 0)) {
			if (istr[id] == '(')quotes++;
			if (istr[id] == ')')quotes--;
			if (quotes == 0)break;
			func_arg.str += istr[id];
			id++;
		}
		id++;
	}

	word usr;
	usr.type = Func_cl;
	usr.name = func_name;
	listFunc.push_back(usr);

	word tmp;
	tmp.type = Func_API;
	tmp.name = func_name;
	tmp.arg.push_back(func_arg);

	vct.body.push_back(tmp);*/
}

int Compiler::VarOrFunc(Code & C, word & vct, string n)
{
	for (auto i = vct.body.begin(); i < vct.body.end(); i++) {
		if (i->type == Var) return Var;
		if(i == vct.body.end() - 1){
			if (i->type== Func) VarOrFunc(C, *i, n);
			if (i->type == While) VarOrFunc(C, *i, n);
		}
	}
	return 0;
}
bool Compiler::CallFunc		(Code & C, word & vct)
{
	/*word arg;
	word tmp;
	int isEql = -1;

	int size = listFunc.size();
	
	for (int i = 0; i < size; i++) {
		if (listFunc[i].name == name) {
			isEql = i;
			break;
		}
		else isEql = -1; 
	}
	
	if (isEql >= 0)
	{
		if(listFunc[isEql].type == Func_cl)
			tmp.name = listFunc[isEql].arg[0].str;
		else if (listFunc[isEql].type == Func_API)
			tmp.name = name;
		id += 2;
		int quotes = 1;
		bool Bquotes = false;
		while (istr[id] != ';') {
			if (istr[id] == '(')quotes++;
			if (istr[id] == ')')quotes--;
			if (quotes == 0)break;
			if (istr[id] == '\"' || istr[id] == '\'')Bquotes = !Bquotes; //Если знак кавычки то инверстия их соостояния
			if (!(istr[id] == ' ') || quotes)arg.str += istr[id]; //Если не пробел то добавление к строке
			id++;
		}

		tmp.type = listFunc[isEql].type;
		tmp.arg.push_back(arg);
		vct.body.push_back(tmp);
	}*/
	return false;
}

//Нахождение в слове других слов
void Compiler::unpackBlock(word & vct)
{	
	/*cout << "uB: " << vct.body.size() << endl;
	for (int i = 0; i < vct.body.size(); i++) {
		int type = vct.body[i].type;
		switch (type) {
		case Func:
			currFunc = vct.body[i].name;
			processBlock(vct.body[i].arg[1].str, vct.body[i].arg[1], Func_arg);
			processBlock(vct.body[i].body[0].str, vct.body[i].body[0], Func);
			currFunc = "";
			break;
		case While:
			processBlock(vct.body[i].arg[0].str, vct.body[i].arg[0], Whl_arg);
			processBlock(vct.body[i].body[0].str, vct.body[i].body[0], While);
			break;
		case If:
			processBlock(vct.body[i].arg[0].str, vct.body[i].arg[0], If_arg);
			processBlock(vct.body[i].body[0].str, vct.body[i].body[0], If);
			processBlock(vct.body[i].body[1].str, vct.body[i].body[1], If);
			break;
		default:break;
		}
	}*/
}
void Compiler::glueCode(word vct, vector<string>& str)
{
	for (int i = 0; i < vct.body.size();i++) {
		string tmp;
		if (vct.body[i].type == Var) {
			tmp += vct.body[i].name + "=" + vct.body[i].arg[0].name; //Создание переменной с её значением
			str.push_back(tmp); //Добавление в вектор
		}
		if (vct.body[i].type == Func) {
			string func_bgn = vct.body[i].adr; //CharRand();
			tmp = "$" + func_bgn + "$";
			str.push_back(tmp);

			tmp = vct.body[i].name + "={}";
			str.push_back(tmp);
			tmp = "";

			//Если ургументов функии больше нуля
			if (vct.body[i].arg[1].body.size() > 0) {
				
				//Создание строки с именами переменных в аргрументе функции
				for (int j = 0; j < vct.body[i].arg[1].body.size(); j++) {
					tmp += vct.body[i].arg[1].body[j].name; //Запись переменной

					//Если не последняя переменная то добавляем запятую
					if (!(j == vct.body[i].arg[1].body.size() - 1))tmp += ",";
				}

				tmp += "=GetArg()"; //Динамическое получение аргументов функции
				str.push_back(tmp); //Добавление строки в вектор
			}

			glueCode(vct.body[i].body[0], str); //Обработка тела функции

			tmp = "ret()";
			str.push_back(tmp);
		}
		if (vct.body[i].type == Func_cl) {
			tmp = "SetArg(";
			if (vct.body[i].arg.size() > 0) {
				tmp += vct.body[i].arg[0].name + ")";
			}
			str.push_back(tmp);

			tmp = "SetDotRet()";
			str.push_back(tmp);

			tmp = "jmp(@" + vct.body[i].name + "@)";
			str.push_back(tmp);

			tmp = "GetRet()";
			str.push_back(tmp);
		}
		if (vct.body[i].type == Func_API) {
			tmp = vct.body[i].name + "(";
			if (vct.body[i].arg.size() > 0) {
				tmp += vct.body[i].arg[0].name + ")";
			}
			str.push_back(tmp);
		}
		if (vct.body[i].type == While) {
			//cout << "===================" << endl;
			string Whl_end = str::CharRand(); //Указатель линкера на конец цикла. Создание ранодомного набора символов
			string Whl_bgn = str::CharRand(); //Указатель линкера на начало цикла. Создание ранодомного набора символов

			tmp = "$" + Whl_bgn + "$ "; //Установка метки начала цикла
			str.push_back(tmp); //Добавление в вектор

			// Условие при котором цикл будет выполняться и кокой код исполять
			tmp = "if " + vct.body[i].arg[0].name + " then else jmp(@" + Whl_end + "@) end"; 
			str.push_back(tmp); //Добавление в вектор

			glueCode(vct.body[i].body[0], str); //Запись тела цикла

			tmp = "jmp(@" + Whl_bgn + "@)"; //Отправка указателя исполнения на начало цикла
			str.push_back(tmp); //Добавление в вектор

			tmp = "$" + Whl_end + "$"; //Установка метки окончания цикла
			str.push_back(tmp); //Добавление в вектор
		}
		if (vct.body[i].type == Ret) {
			tmp = "ret(" + vct.body[i].name + ")"; //Возврашение 
			str.push_back(tmp); //Добавление в вектор
		}
		if (vct.body[i].type == If) {
			string if_end = str::CharRand(); //Указатель линкера на конец тела условия. Создание ранодомного набора символов
			string else_end = str::CharRand(); //Указатель линкера на конец else условия. Создание ранодомного набора символов

			// Условие при котором код будет выполняться и кокой код исполять
			tmp = "if " + vct.body[i].arg[0].name + " then else jmp(@" + if_end + "@) end";
			str.push_back(tmp); //Добавление в вектор

			glueCode(vct.body[i].body[0], str); //Запись тела условия

			tmp = "jmp(@" + else_end + "@)";
			str.push_back(tmp); //Добавление в вектор

			tmp = "$" + if_end + "$"; //Установка метки окончания условия
			str.push_back(tmp); //Добавление в вектор

			glueCode(vct.body[i].body[1], str); //Запись тела условия

			tmp = "$" + else_end + "$"; //Установка метки окончания условия
			str.push_back(tmp); //Добавление в вектор
		}
	}
}

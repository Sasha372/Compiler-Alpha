#include "stdafx.h"
#include "Compiler.h"
#include "Random.h"
using namespace std;

namespace Compiler {
	int listWordSize = 0;
	struct word {
		string name; //��� �������, ����������
		int type; //��� �����
		string str; //�� ������������� ������
		int parent;
		vector<word> arg; //�������� ����� ���������� �� str. �������� 
		vector<word> body; //����� ����� ���������� �� str
	};
	word Global;
	vector<word> listFunc;
	vector<word> listVarGlob;
	vector<word> listVarLocal;

	string chrRG = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"}; //54 �������
	string CharRand() {
		string st;
		int ti = chrRG.size() - 1;
		for (int i = 0; i < 10; i++) 
			st += chrRG[random(0, ti)];
		return st;
	}
	string currFunc;

	//������ false ���� ������ ���� � ������
	bool isChrBeStr(char str, string chr) { 
		int strS = 1;// str.size();
		int chrS = chr.size();

		for (int i = 0; i < strS; i++) {
			for (int j = 0; j < chrS; j++)
				if (str == chr[j])return false;
		}
		return true;
	}

	void split(string line, char split, vector<string> & part) {
		string buffer = ""; //��������� ������
		for (int i = 0; i < line.size(); i++) {
			if (line[i] != split) 
				buffer += line[i];
			else {
				part.push_back(buffer);
				buffer = "";
			}
		}
		part.push_back(buffer);
	}
}

void Compiler::processCode(string & str, vector<string> & out)
{
	//cout << str << endl;
	word wrd;
	wrd.type = Func_API;
	wrd.name = "status";
	listFunc.push_back(wrd);

	//==============================//

	processBlock(str, Global, Glob); //������ ��������� ���� � ������ ���� � ������ listWord
	glueCode(Global, out);
}
void Compiler::processBlock(string & istr, word & vct, int parent)
{
	searchWord(istr, vct, parent); //����� ������ ���� � ������ istr  ������ �� � ������ vct
	unpackBlock(vct); //��������� ���� � ������ �� � ������ vct
}

bool Compiler::searchWord(string & istr, word & vct, int parent)
{
	int id = 0;
	string tmp_wrd; //��������� ���������� �� ������
	while (!(istr[id] == 0)) {
		if (isChrBeStr(istr[id], " []{}()<>;\\/''\"=+-*&|")) {
			//cout << "IStr: " << istr[id] << endl;
			tmp_wrd += istr[id];
		}
		else tmp_wrd = ""; //���� ���������� ������ �� ������� ��������� ����������
		
		if ((isChrBeStr(istr[id + 1], chrRG)) && (tmp_wrd.size() != 0)) {
			//cout << "%" << tmp_wrd.size() << endl;
			/*int type_wrd = User;
				 if (tmp_wrd == "var")type_wrd = Var; 
			else if (tmp_wrd == "func")type_wrd = Func;
			else if (tmp_wrd == "return")type_wrd = Ret;
			else if (tmp_wrd == "while")type_wrd = While;
			else if (tmp_wrd == "for")type_wrd = For;
			else if (tmp_wrd == "if")type_wrd = If;

			switch (type_wrd)
			{
			case Var:
				switch (parent)
				{
				case Glob: //������� � ������� ��������� �������� ����������
				case Func:
				case Func_arg:
				case For:
				case For_arg:
				case While:
				case If:
					if (!readWordVar(istr, id, vct)) { //������ ���������� ����������
						cout << "incorrect variable declaration." << endl; //���� ������ �� ������� ����� ������
						return false; //���������� ����������
					}
					break;
				default:
					cout << "Variable outside " << endl; //���������� ��������� �� ��������� �����������
					return false;
				}
			case Func:
				switch (parent)
				{
				case Glob:
					//������ ���������� �������
					if(!readWordFunc(istr, id, vct)) {
						cout << "incorrect function declaration" << endl;
						return false;
					}
					break;
				default:
					cout << "function outside declaration" << endl;
					return false;
				}
			case Ret:
				switch (parent)
				{
				case Func:
				case Func_arg:
				case For:
				case For_arg:
				case While:
				case If:
					if (!readWordReturn(istr, id, vct)) {
						cout << "" << endl;
						return false;
					}
				default:
					cout << "function outside declaration" << endl;
					return 
				}
			case While:
				switch (parent)
				{
				case Func:
				case While:
				case For:
				case If:
					if (!readWordWhile(istr, id, vct)) {
						cout << "" << endl;
						return false;
					}
				default:
					cout << "" << endl;
					return false;
				}
			case If:
				switch (parent)
				{
				case Func:
				case While:
				case For:
				case If:
					if (!readWordIf(istr, id, vct)) {
						cout << "" << endl;
						return false;
					}
				default:
					cout << "" << endl;
					return false;
				}
			case User:
				switch (parent)
				{
				case Func:
				case While:
				case For:
				case If:
					if (!EquallyVar(tmp_wrd, istr, id, vct)) 
						if (!CallFunc(tmp_wrd, istr, id, vct)) {
							cout << "" << endl;
							return false;
						}
					break;
				default:
					cout << "" << endl;
					return false;
				}
				
			}*/
			//cout << tmp_wrd << endl;
			switch (parent) {
			case Glob: 
				if (tmp_wrd == "var") readWordVar(istr, id, vct); //������ ���������� ����������
				else if (tmp_wrd == "func") readWordFunc(istr, id, vct); //������ ���������� �������
				else if (tmp_wrd == "DLL") readWordDLL(istr, id, vct);
				else if (CallFunc(tmp_wrd, istr, id, vct)) {}
				else { cout << "1 Unknow identifier: " << tmp_wrd << endl; tmp_wrd = ""; return false; }
				break;
			case If: 
				if (tmp_wrd == "var") readWordVar(istr, id, vct); //���� �����
				else if (tmp_wrd == "while") readWordWhile(istr, id, vct);
				else if (tmp_wrd == "return") readWordReturn(istr, id, vct); 
				else if (tmp_wrd == "if") readWordIf(istr, id, vct);
				else if (EquallyVar(tmp_wrd, istr, id, vct)) {}
				else if (CallFunc(tmp_wrd, istr, id, vct)) {}
				else { cout << "4 Unknow identifier: " << tmp_wrd << endl; return false; }
				break;
			case While:
				if (tmp_wrd == "var") { readWordVar(istr, id, vct); tmp_wrd = ""; } //���� �����
				else if (tmp_wrd == "while") { readWordWhile(istr, id, vct); tmp_wrd = ""; }
				else if (tmp_wrd == "return") { readWordReturn(istr, id, vct); tmp_wrd = ""; }
				else if (tmp_wrd == "if") { readWordIf(istr, id, vct); tmp_wrd = ""; }
				else if (EquallyVar(tmp_wrd, istr, id, vct)) { tmp_wrd = ""; }
				else if (CallFunc(tmp_wrd, istr, id, vct)) {}
				else { cout << "5 Unknow identifier: " << tmp_wrd << endl; tmp_wrd = ""; return false; }
				break;
			case Func:
				if (tmp_wrd == "var") { readWordVar(istr, id, vct); tmp_wrd = ""; } //���� ����� 
				else if (tmp_wrd == "while") { readWordWhile(istr, id, vct); tmp_wrd = ""; }
				else if (tmp_wrd == "return") { readWordReturn(istr, id, vct); tmp_wrd = ""; }
				else if (tmp_wrd == "if") { readWordIf(istr, id, vct); tmp_wrd = ""; }
				else if (EquallyVar(tmp_wrd, istr, id, vct)) {}
				else if (CallFunc(tmp_wrd, istr, id, vct)) {}
				else { cout << "2 Unknow identifier: " << tmp_wrd << endl; tmp_wrd = ""; return false; }
				break;
			case If_arg:
			case Whl_arg:break;
			case Func_arg: 
				if (tmp_wrd == "var") { readWordVar(istr, id, vct); tmp_wrd = ""; } //���� ����� 
				else { cout << "3 Unknow identifier: " << tmp_wrd << endl; tmp_wrd = ""; return false; }
				break;
			case Func_cl:
			case Func_API:
				break;
			//default:
				//break;
			}
		}
		id++;
	}
}
bool Compiler::readWordVar(string & istr, int & id, word & vct)
{
	id++;
	string str_var; //������ � ���������� � ���������
	bool quotes = false; //true ���� ������� �������, false ���� ������� �������
	while (istr[id] != ';' && istr[id] != 0) { //���� �� ����������� ���� ';' ��� ���� ',' ��� 0
		if (currFunc != "" && istr[id] == ',')break;
		if (istr[id] == '\"' || istr[id] == '\'')quotes = !quotes; //���� ���� ������� �� ��������� �� ����������
		if (!(istr[id] == ' ') || quotes)str_var += istr[id]; //���� �� ������ �� ���������� � ������
		id++;
	}
	if (quotes) { //���� ������� �� ���� ������� ����� ������
		cout << "Quotes in innitialize variable unclose: " << str_var << endl; 
		return false; //���������� ����������
	}
	
	vector<string> tmp_str_var; //������ � �������� ���������� ����� �������
	split(str_var, ',', tmp_str_var); //��������� ����� ������ �� �����

	for (int i = 0; i < tmp_str_var.size(); i++) {
		word tmp; //��������� �����
		word arg; //��������� ������ � ��������� ����������
		vector<string> str; //������ �� �������� [0] - ��� ���������� [1] - ��������
		tmp.str = tmp_str_var[i]; //�����������
		tmp.type = Var; //������ ���� �����

		split(str_var, '=', str); //���������� ����� ���������� � � ��������

		tmp.name = str[0]; //������������ ����� ����������
		if (currFunc != "") { //���� ��������� � ���� �������
			tmp.name = currFunc + "." + tmp.name; //��������� � ����� ��� �������
		}

		if (str.size() == 2) { //���� ���� 2� �����
			arg.str = str[1]; //������ � ��������
		}
		else //���� 2� ����� �� �������
			if (str.size() == 1) { //���� ����� ����� 1
				arg.str = "0"; //�������� ���������� ����� "0"
			}
			else return false; //���� ������ �� 1 �� ������ 

		word usr; //����� ��� ��������� ������������ ��������
		usr.type = Var; //��� ����� - ����������
		usr.name = tmp.name; //���� ����������
		if (currFunc != "") //���� ���������� ��������� � �������
			listVarLocal.push_back(usr); //��������� � ������ ��������� � ����������������� ������������
		else //���� � ���������� ������������
			listVarGlob.push_back(usr); //��������� � ������ ���������� � ����������������� ������������

		tmp.arg.push_back(arg); //��������� � ����� ������� ��������� ����� �������� ����������
		vct.body.push_back(tmp); //���������� � �������� ������ ����
	}
	return true; //�������
}
bool Compiler::readWordFunc(string & istr, int & id, word & vct)
{
	string func_name;
	word func_arg;
	word func_body;
	{
		id += 2;
		while (!(istr[id] == '(')) {
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
		quotes = 1;
		while (!(istr[id] == '{')) { //��������� �� ������ �������� ������
			id++;
		}
		id++;
		while (!(quotes == 0)) {
			if (istr[id] == '{')quotes++;				
			if (istr[id] == '}')quotes--;
			if (quotes == 0)break;
			func_body.str += istr[id];
			id++;
		}
	}
	
	word adr_call;
	adr_call.str = CharRand();

	word usr;
	usr.type = Func_cl;
	usr.name = func_name;
	usr.arg.push_back(adr_call);
	listFunc.push_back(usr);

	word tmp;
	tmp.type = Func;
	tmp.name = func_name;
	tmp.arg.push_back(adr_call);
	tmp.arg.push_back(func_arg);
	tmp.body.push_back(func_body);

	vct.body.push_back(tmp);
	return true;
}
bool Compiler::readWordWhile(string & istr, int & id, word & vct)
{
	word while_arg; //������� ��� ������� ���� ����� �����������
	word while_body; //���� �����
	{
		while (!(istr[id] == '(')) { //��������� �� ������ ������� ������
			id++;
		}
		id++;
		int quotes = 1;
		while (!(quotes == 0)) {
			if (istr[id] == '(')quotes++;
			if (istr[id] == ')')quotes--;
			if (quotes == 0)break;
			while_arg.str += istr[id];
			id++;
		}
		quotes = 1;
		while (!(istr[id] == '{')) { //��������� �� ������ �������� ������
			id++;
		}
		id++;
		while (!(quotes == 0)) {
			//cout << istr[id] << endl;
			if (istr[id] == '{')quotes++;
			if (istr[id] == '}')quotes--;
			if (quotes == 0)break;
			while_body.str += istr[id];
			id++;
		}
	}

	word tmp;
	tmp.type = While;
	tmp.arg.push_back(while_arg);
	tmp.body.push_back(while_body);

	vct.body.push_back(tmp);
	return true;
}
bool Compiler::readWordReturn(string & istr, int & id, word & vct)
{
	id++;
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
	return true;
}
bool Compiler::readWordIf(string & istr, int & id, word & vct)
{
	word if_arg; //������� ��� ������� ��� ����� �����������
	word if_body; //���� �������
	word if_else; //���� else
	{
		while (!(istr[id] == '(')) { //��������� �� ������ ������� ������
			id++;
		}
		id++;
		int quotes = 1;
		while (!(quotes == 0)) {
			if (istr[id] == '(')quotes++;
			if (istr[id] == ')')quotes--;
			if (quotes == 0)break;
			if_arg.str += istr[id];
			id++;
		}
		quotes = 1;
		while (!(istr[id] == '{')) { //��������� �� ������ �������� ������
			id++;
		}
		id++;
		while (!(quotes == 0)) {
			if (istr[id] == '{')quotes++;
			if (istr[id] == '}')quotes--;
			if (quotes == 0)break;
			if_body.str += istr[id];
			id++;
		}
		id++;
		int back_id = id;
		string tmp_else;
		quotes = 1;
		while (!(istr[id] == 0)) {
			if (!(istr[id] == ' '))tmp_else += istr[id]; else { if (tmp_else.size() == 0)break; }
			if (tmp_else == "else") {
				while (!(istr[id] == '{')) { //��������� �� ������ �������� ������
					id++;
				}
				id++;
				while (!(quotes == 0)) {
					if (istr[id] == '{')quotes++;
					if (istr[id] == '}')quotes--;
					if (quotes == 0)break;
					if_else.str += istr[id];
					id++;
				}
				break;
			}
			else if (tmp_else.size() > 3)break;
			id++;
		}
	}

	word tmp;
	tmp.type = If;
	tmp.arg.push_back(if_arg);
	tmp.body.push_back(if_body);
	tmp.body.push_back(if_else);

	//cout << "Arg: " << tmp.arg[0].str << endl;
	//cout << "Body: " << tmp.body[0].str << endl;
	//cout << "Else: " << tmp.body[1].str << endl;

	vct.body.push_back(tmp);
	return true;
}
bool Compiler::readWordDLL(string & istr, int & id, word & vct)
{
	string func_name;
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

	vct.body.push_back(tmp);
	return true;
}

bool Compiler::EquallyVar(string name, string & istr, int & id, word & vct)
{
	bool isUsr = false;
	if (currFunc != "") {
		name = currFunc + "." + name;
		int sizeL = listVarLocal.size();
		for (int i = 0; i < sizeL; i++) {
			if (listVarLocal[i].name == name) isUsr = true;
		}
	}

	if (!isUsr) {
		int size = listVarGlob.size();
		for (int i = 0; i < size; i++) {
			if (listVarGlob[i].name == name) isUsr = true;
		}
	}
	if (!isUsr)return false;

	id++;
	string str_var; //������ � ���������� � ���������
	bool quotes = false; //true ���� ������� �������, false ���� ������� �������
	while (istr[id] != ';' && istr[id] != 0) { //���� �� ����������� ���� ';' ��� ���� ',' ��� 0
		if (istr[id] == '\"' || istr[id] == '\'')quotes = !quotes; //���� ���� ������� �� ��������� �� ����������
		if (!(istr[id] == ' ') || quotes)str_var += istr[id]; //���� �� ������ �� ���������� � ������
		id++;
	}
	if (quotes) { //���� ������� �� ���� ������� ����� ������
		cout << "Quotes in innitialize variable unclose: " << str_var << endl;
		return false; //���������� ����������
	}

	vector<string> tmp_str; //������ � �������� ���������� ����� �������
	split(str_var, '=', tmp_str); //��������� ����� ������ �� �����

	if (tmp_str.size() > 1) {
		word tmp; //��������� �����
		word arg; //��������� ������ � ��������� ����������
		tmp.str = name + "=" + tmp_str[1]; //�����������
		tmp.type = Var; //������ ���� �����

		if (currFunc != "") { //���� ��������� � ���� �������
			tmp.name = name; //��������� � ����� ��� �������
		}
		else return false;

		if (tmp_str.size() == 2) { //���� ���� 2� �����
			int r = tmp_str[0].size(); //������ ������ ����� �����
			if (r > 0) { //���� ����� ����� ���-�� ����
				if(!isChrBeStr(tmp_str[0][0], "+-*/")) //���� ����� ����� �����  + - * /
					arg.str = name + tmp_str[0][r - 1] + tmp_str[1]; //������ � ��������
				else cout << "Unexpected sumbol" << endl; //���� ���-�� ������ ������
			}
			else arg.str = tmp_str[1]; //������ � ��������
		}
		else return false; //���� 2� ����� �� �������

		tmp.arg.push_back(arg); //��������� � ����� ������� ��������� ����� �������� ����������
		vct.body.push_back(tmp); //���������� � �������� ������ ����
	}
	return true;
}
bool Compiler::CallFunc(string name, string & istr, int & id, word & vct)
{
	word arg;
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
			if (istr[id] == '\"' || istr[id] == '\'')Bquotes = !Bquotes; //���� ���� ������� �� ��������� �� ����������
			if (!(istr[id] == ' ') || quotes)arg.str += istr[id]; //���� �� ������ �� ���������� � ������
			id++;
		}

		tmp.type = listFunc[isEql].type;
		tmp.arg.push_back(arg);
		vct.body.push_back(tmp);
	}
	else return false;
}

//���������� � ����� ������ ����
void Compiler::unpackBlock(word & vct)
{	
	//cout << "uB: " << vct.body.size() << endl;
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
	}
}
void Compiler::glueCode(word vct, vector<string>& str)
{
	for (int i = 0; i < vct.body.size();i++) {
		string tmp;
		if (vct.body[i].type == Var) {
			//���� ������������ ����� ����������(�� "none")
			//if (!(par == "none"))tmp += par + "."; //���������� � ����� ���������� ����� ������
			tmp += vct.body[i].name + "=" + vct.body[i].arg[0].str; //�������� ���������� � � ���������
			//cout << tmp << endl;
			str.push_back(tmp); //���������� � ������
		}
		if (vct.body[i].type == Func) {
			string func_bgn = vct.body[i].arg[0].str; //CharRand();
			tmp = "$" + func_bgn + "$";
			str.push_back(tmp);

			tmp = vct.body[i].name + "={}";
			str.push_back(tmp);
			tmp = "";

			//���� ���������� ������ ������ ����
			if (vct.body[i].arg[1].body.size() > 0) {
				
				//�������� ������ � ������� ���������� � ���������� �������
				for (int j = 0; j < vct.body[i].arg[1].body.size(); j++) {
					tmp += vct.body[i].arg[1].body[j].name; //������ ����������

					//���� �� ��������� ���������� �� ��������� �������
					if (!(j == vct.body[i].arg[1].body.size() - 1))tmp += ",";
				}

				tmp += "=GetArg()"; //������������ ��������� ���������� �������
				str.push_back(tmp); //���������� ������ � ������
			}

			glueCode(vct.body[i].body[0], str); //��������� ���� �������

			tmp = "ret()";
			str.push_back(tmp);
		}
		if (vct.body[i].type == Func_cl) {
			tmp = "SetArg(";
			if (vct.body[i].arg.size() > 0) {
				tmp += vct.body[i].arg[0].str + ")";
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
				tmp += vct.body[i].arg[0].str + ")";
			}
			str.push_back(tmp);
		}
		if (vct.body[i].type == While) {
			//cout << "===================" << endl;
			string Whl_end = CharRand(); //��������� ������� �� ����� �����. �������� ����������� ������ ��������
			string Whl_bgn = CharRand(); //��������� ������� �� ������ �����. �������� ����������� ������ ��������

			tmp = "$" + Whl_bgn + "$ "; //��������� ����� ������ �����
			str.push_back(tmp); //���������� � ������

			// ������� ��� ������� ���� ����� ����������� � ����� ��� ��������
			tmp = "if " + vct.body[i].arg[0].str + " then else jmp(@" + Whl_end + "@) end"; 
			str.push_back(tmp); //���������� � ������

			glueCode(vct.body[i].body[0], str); //������ ���� �����

			tmp = "jmp(@" + Whl_bgn + "@)"; //�������� ��������� ���������� �� ������ �����
			str.push_back(tmp); //���������� � ������

			tmp = "$" + Whl_end + "$"; //��������� ����� ��������� �����
			str.push_back(tmp); //���������� � ������
		}
		if (vct.body[i].type == Ret) {
			tmp = "ret(" + vct.body[i].name + ")"; //����������� 
			str.push_back(tmp); //���������� � ������
		}
		if (vct.body[i].type == If) {
			string if_end = CharRand(); //��������� ������� �� ����� ���� �������. �������� ����������� ������ ��������
			string else_end = CharRand(); //��������� ������� �� ����� else �������. �������� ����������� ������ ��������

			// ������� ��� ������� ��� ����� ����������� � ����� ��� ��������
			tmp = "if " + vct.body[i].arg[0].str + " then else jmp(@" + if_end + "@) end";
			str.push_back(tmp); //���������� � ������

			glueCode(vct.body[i].body[0], str); //������ ���� �������

			tmp = "jmp(@" + else_end + "@)";
			str.push_back(tmp); //���������� � ������

			tmp = "$" + if_end + "$"; //��������� ����� ��������� �������
			str.push_back(tmp); //���������� � ������

			glueCode(vct.body[i].body[1], str); //������ ���� �������

			tmp = "$" + else_end + "$"; //��������� ����� ��������� �������
			str.push_back(tmp); //���������� � ������
		}
	}
}

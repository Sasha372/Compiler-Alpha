#include "stdafx.h"
#include "fstream"
#include "PreCPU.h"
using namespace std;

vector<string> PreCPU::listDef_from;
vector<string> PreCPU::listDef_to;
int PreCPU::countDef;

string PreCPU::direct[] = { "req", "def" };
int countDir = 2;

int PreCPU::GetCountDef() { return listDef_from.size(); }
void PreCPU::GetListDef(int id, string & from, string & to) {
	from = listDef_from[id];
	to = listDef_to[id];
}

void PreCPU::processCode(string & inputFile, code & ostr)
{
	code codeIn;
	code woCom;

	//ifstream input(inputFile);
	//string in;
	//while (getline(input, in))//Получение строки файла
	//{
	//	if (in != "") {
	//		string s = PreCPU::delStrComment(in); //удаление строчных комментариев
	//		if (!str::onlySpace(s)) {
	//			codeIn.push_back(s);
	//			cout << s << endl;
	//		}
	//	}
	//}
	//input.close(); //Безопасное закрытие файла
	cout << "===============================================" << endl;

	PreCPU::delBlkComment(codeIn, woCom); //Удаление блочных комментариев
	for (int i = 0; i < woCom.size(); i++)
		cout << woCom[i] << endl;
	//cout << "===============================================" << endl;

	PreCPU::directPreCPU(woCom, ostr); //Чтение и удаление директив препроцессора
	//cout << ostr << endl;
	//cout << "===============================================" << endl;
}
string PreCPU::delStrComment(string & str)
{
	int posComment = str.find("//");
	//cout << posComment << " in string: " << str << endl;
	if (posComment <= str.size()) {
		string woComment;
		for (int i = 0; i < posComment; i++) {
			woComment += str[i];
		}
		return woComment;
	}else return str;
}
void PreCPU::SpaceCut(string & istr, string & ostr)
{
	int id = 0;
	while (!(istr[id] == 0)) {
		if ((int)istr[id] == 9) {
		}
		else ostr += istr[id];
		id++;
	}
}
void PreCPU::delBlkComment(code & str, code & woCom)
{
	string tmp;
	bool inComment = false;
	bool inQuotes = false;
	for (int i = 0; i < str.size(); i++) {
		for (int j = 0; j < str[i].size(); j++) {
			if ((str[i][j] == '\'') || (str[i][j] == '"')) {
				inQuotes = !inQuotes;
				if(!inComment){ tmp += str[i][j]; }
			}
			else 
				if (!inQuotes) {
					if (inComment) {
						if ((str[i][j] == '*') && (str[i][j + 1] == '/')) {
							inComment = false;
							j++;
						}
					}
					else {
						if ((str[i][j] == '/') || (str[i][j + 1] == '*')) { inComment = true; j++; }
						else tmp += str[i][j];
					}
				}else if (!inComment)tmp += str[i][j];
		}
		if ((!inComment) && (tmp != "")) {
			woCom.push_back(tmp);
			tmp = "";
		}
	}
	/*bool inComment = false;
	for (int i = 0; i < str.size(); i++) {
		if (inComment) {
			size_t found = str[i].find("* /");
			if (found != string::npos) {
				inComment = false;
			}
		}
		else {
			size_t found = str[i].find("/*");
			if (found != string::npos) {
				if (str[i][found - 1] != '\\') {
					woCom.push_back(str[i].substr(0, found));
					inComment = true;
				}
			}
			else {
				woCom.push_back(str[i]);
			}
		}
	}*/
}

void PreCPU::directPreCPU(code & istr, code & ostr)
{

	/*int id = 0;
	bool isDirect;
	int dire;
	while (!(istr[id] == 0)) //Пока не кончится сторка
	{
		if (istr[id] == '#') { //Если есть указатель на директиву
			for (int i = 0; i < countDir; i++) { //Цикл для проверки соответсвия одной из всех директив
				int j = 0; //Сдвиг по директиве
				string d = direct[i];
				while (!(d[j] == 0 && istr[id + j + 1] == ' '))
				{
					//Если буква не сооттсвует переход к следуйщей директиве
					//Если совпадает продолжаем сравнение
					if (istr[id + j + 1] == d[j])isDirect = true; else { isDirect = false; break; }
					j++;
				}
				//Если все буквы совпали то директива определена
				//Если последняя не совпала то проверяем есть ли ещё директивы. Если нет то выдаём ошибку, если есть то продолжаем
				if (isDirect) { dire = i; id += 3; break; }
				else if (i == countDir - 1) cout << "Error in directive preprocessor's" << endl;
			}
			if (isDirect) {
				int dir_id = 2;
				if (direct[dire] == "req") {
					direct_req(istr, id, dir_id, ostr);
				}
				if (direct[dire] == "def") {
					direct_def(istr, id, dir_id);
				}
				//cout << endl;
				isDirect = false;
				id += dir_id;
			}
		}
		else ostr += istr[id];
		id++;
	}
	istr = "";*/
}
void PreCPU::direct_def(code & str, int & id, int & dir_id)
{
/*	string tmp;
	while (!(str[id + dir_id] == ' ')) {
		tmp += str[id + dir_id];
		dir_id++;
	}
	listDef_from.push_back(tmp);
	tmp = "";
	dir_id++;
	while (!(str[id + dir_id] == ' ')) {
		tmp += str[id + dir_id];
		dir_id++;
	}
	listDef_to.push_back(tmp);*/
}
void PreCPU::direct_req(code & str, int & id, int & dir_id, code & ostr)
{
	/*string arg;
	while (!(str[id + dir_id] == ' ')) {
		arg += str[id + dir_id];
		dir_id++;
	}
	string outPr;
	processCode(arg, outPr);
	ostr += outPr;*/
}
#include "stdafx.h"
#include "Linker.h"
using namespace std;

namespace Linker {
	vector<string> listDot;
	vector<int> listPos;
}

void Linker::Process(vector<string>& istr, vector<string>& ostr)
{
	vector<string> tmp;
	Search(istr, tmp);
	Apply(tmp, ostr);
}

void Linker::Search(vector<string>& istr, vector<string>& ostr)
{
	int size = istr.size();
		
	//for (int i = 0; i < size; i++)
		//cout << istr[i] << endl;

	for (int i = 0; i < size; i++) {
		if (istr[i][0] == '$') {
			//cout << "S: " << (i + 2) - listDot.size() << ":" << istr[i] << endl;
			string tmp;
			int size2 = istr[i].size();
			for (int j = 1; j < size2 - 1; j++) {
				if ((istr[i][j] == ' ') || (istr[i][j] == '$'))break;
				tmp += istr[i][j];
			}
			listDot.push_back(tmp);
			listPos.push_back((i + 2) - listDot.size());
		}
		else {
			ostr.push_back(istr[i]);
		}
	}
}

void Linker::Apply(vector<string>& istr, vector<string>& ostr)
{
	int size = istr.size();
	for (int i = 0; i < size; i++){
		string tmp_str;
		int tmp_pos;
		int size2 = istr[i].size();
		bool Dog = false;
		bool quotes = false;
		string tmp_adr; //Сюда пишется имя ссылки
		int adr;
		for (int j = 0; j < size2; j++) {
			if (istr[i][j] == '\"' || istr[i][j] == '\'')quotes = !quotes; //Если знак кавычки то инверстия их соостояния
			if ((istr[i][j] == '@') && !quotes)
				if (Dog) {
					readAdr(istr[i], tmp_adr, tmp_pos, j);
					int t = searchAdr(tmp_adr);
					if(t > -1)
						setAdr(tmp_str, tmp_pos, t);
					else 
						cout << "hhnhhn" << endl;
					tmp_adr = "";
					Dog = false;
				}
				else {
					tmp_pos = j + 1;
					Dog = true;
				}
			else if (!Dog)tmp_str += istr[i][j];
		}
		ostr.push_back(tmp_str);
	}
}

int Linker::searchAdr(string & str)
{
	int size = listDot.size();
	for (int i = 0; i < size; i++) {
		if (listDot[i] == str) return i;
	}

	for (int i = 0; i < size; i++)
		cout << listDot[i] << endl;

	return -1;
}

void Linker::readAdr(string & istr, string & ostr, int id_b, int id_e)
{
	for (; id_b < id_e; id_b++) {
		ostr += istr[id_b];
	}
}

void Linker::setAdr(string & istr, int id, int adr)
{
	string tm = to_string(listPos[adr]);
	istr += tm;
}

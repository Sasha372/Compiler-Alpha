#include "stdafx.h"
#include "fstream"
#include "PreCPU.h"
using namespace std;

vector<string> PreCPU::listDef_from;
vector<string> PreCPU::listDef_to;
int PreCPU::countDef;

//vector<string> PreCPU::listReq; //���� � require
//vector<int> PreCPU::listReqPos; //���� ������� require

namespace PreCPU {
	//string *outStr;
}

string PreCPU::direct[] = { "req", "def" };
int countDir = 2;

int PreCPU::GetCountDef() { return listDef_from.size(); }
void PreCPU::GetListDef(int id, string & from, string & to) {
	from = listDef_from[id];
	to = listDef_to[id];
}

//int PreCPU::GetCountReq() { return listReq.size(); }
//int PreCPU::GetCountReqPos() { return listReqPos.size(); }

void PreCPU::processCode(string & inputFile, string & ostr)
{
	string codeIn;
	string woCom;
	string woSpace;
	string woDirect;

	ifstream input(inputFile);
	string in;
	while (getline(input, in))//��������� ������ �����
	{
		if (in != "") {
			codeIn += PreCPU::StrComment(in) + " ";//�������� �������� ������������
		}
	}
	input.close(); //���������� �������� �����

	PreCPU::SpaceCut(codeIn, woSpace); //�������� ������������� ��������
	//cout << woSpace << endl;
	//cout << "===============================================" << endl;

	PreCPU::BlkComment(woSpace, woCom); //�������� ������� ������������
	//cout << woCom << endl;
	//cout << "===============================================" << endl;

	PreCPU::directPreCPU(woCom, ostr); //������ � �������� �������� �������������
	//cout << ostr << endl;
	//cout << "===============================================" << endl;
}
string PreCPU::StrComment(string & str)
{
	string out = "";
	int id = 0;
	while (!(str[id] == 0))
	{
		//if (str[id] == ' ' && str[id + 1] == ' ')id++;  //if (str[id] == '\0' && str[id + 1] == '\0')
		if (str[id] == '/' && str[id + 1] == '/')break; else out += str[id]; // ���� ������ �������� ���������� �� ���������� �����
		id++;
	}
	return out;
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
void PreCPU::BlkComment(string & str, string & woCom)
{
	int id = 0;
	while (!(str[id] == 0))//���� ������ �� ��������
	{
		if ((str[id] == '/') && (str[id + 1] == '*')) { //���� ���������� ����������� ����������
			int j = id + 2;
			while (!(str[j] == 0))//���� ������ �� ��������
			{
				if ((str[j] == '*') && (str[j + 1] == '/')) { id = j + 2; break; }//���� ���������� ����������� ����������
				j++;
			}
		}
		else {
			if (((str[id] == '*') && (str[id + 1] == '/')))id++; else woCom += str[id];//����������� ����������, ������� �� ����� ����
		}		//|| ((str[id] == ' ') && (str[id + 1] == '/n'))
		id++;
	}
	str = "";
}

void PreCPU::directPreCPU(string & istr, string & ostr)
{
	int id = 0;
	bool isDirect;
	int dire;
	while (!(istr[id] == 0)) //���� �� �������� ������
	{
		if (istr[id] == '#') { //���� ���� ��������� �� ���������
			for (int i = 0; i < countDir; i++) { //���� ��� �������� ����������� ����� �� ���� ��������
				int j = 0; //����� �� ���������
				string d = direct[i];
				while (!(d[j] == 0 && istr[id + j + 1] == ' '))
				{
					//���� ����� �� ���������� ������� � ��������� ���������
					//���� ��������� ���������� ���������
					if (istr[id + j + 1] == d[j])isDirect = true; else { isDirect = false; break; }
					j++;
				}
				//���� ��� ����� ������� �� ��������� ����������
				//���� ��������� �� ������� �� ��������� ���� �� ��� ���������. ���� ��� �� ����� ������, ���� ���� �� ����������
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
	istr = "";
}
void PreCPU::direct_def(string & str, int & id, int & dir_id)
{
	string tmp;
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
	listDef_to.push_back(tmp);
}
void PreCPU::direct_req(string & str, int & id, int & dir_id, string & ostr)
{
	string arg;
	while (!(str[id + dir_id] == ' ')) {
		arg += str[id + dir_id];
		dir_id++;
	}
	string outPr;
	processCode(arg, outPr);
	ostr += outPr;
}
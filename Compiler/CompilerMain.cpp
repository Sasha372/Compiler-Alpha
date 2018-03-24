// CompilerMain.cpp: определяет точку входа для консольного приложения.
#include "stdafx.h"
#include "PreCPU.h"
#include "Compiler.h"
#include "Linker.h"
using namespace std;

//.prog - расширение программы
//.aip - файл пакета установки
//.apcp - файл после обработки препроцессором
//.atc - файл после компиляции

wstring s2ws(const string & s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	wstring r(buf);
	delete[] buf;
	return r;
}
bool isDirectoryExists(LPCWSTR filename)
{
	DWORD dwFileAttributes = GetFileAttributes((LPCTSTR)filename);
	if (dwFileAttributes == 0xFFFFFFFF)
		return false;
	return dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}
struct a {
public:
	string path;
	string filename;
	string file;
	string expansion;
};
a SplitFilename(const string& str)
{
	a d;
	size_t found = str.find_last_of("/\\");
	d.path = str.substr(0, found);
	d.filename = str.substr(found + 1);

	size_t dot = d.filename.find_last_of(".");
	d.file = d.filename.substr(0, dot);
	d.expansion = d.filename.substr(dot + 1);
	return d;
}

void Work(string inputFile, string preCPFile, string outputFile)
{
	Code TextCode(inputFile, "//", "/*", "*/");
	//PreCPU::processCode(inputFile, outPreCPU);

	//Запись результата работы препроцессора
	/*if (preCPFile != "") {
		ofstream preCPout(preCPFile + "\\" + SplitFilename(inputFile).file + ".pos");
		for (int i = 0; i < outPreCPU.size();i++) {
			preCPout << outPreCPU[i] << endl;
		}
		preCPout.close();
	}*/

	Compiler::processCode(TextCode); //Обработка компиляторо
	cout << "===============================================" << endl;
	//cout << "WWW" << endl;

	//rezult.push_back("1");
	//Linker::Process(outComp, rezult);
	/*
	if (outputFile != "") {
		ofstream preCPout(outputFile + ".prog");
		for (int i = 0; i < rezult.size(); i++)preCPout << rezult[i] << endl;
		preCPout.close();
	}

	for (int i = 0; i < rezult.size(); i++)
		cout << i << " : " << rezult[i] << endl;
	*/
}

int main(int argc, char *argv[])
{
	bool help = false;
	string input = "", preCPU = "", output = "";

	for (int i = 0; i < argc; i++) {
		string t = argv[i];
		if (t[0] == '-' || t[0] == '/') { //Если в аргументе параметр
			if (t[1] == '?')help = true;
			if (t[1] == 'i')input = argv[i + 1]; //Параметр: файл на обработку
			if (t[1] == 'p')preCPU = argv[i + 1]; //Параметр: файл после препроцесора
			if (t[1] == 'o')output = argv[i + 1]; //Параметр: конечный файл
		}
	}
	if (input != "") {
		Work(input, preCPU, output);
	}
	if (help) {
		cout << "/?	Help." << endl;
		cout << "/i	Input file." << endl;
		cout << "/p	Output in file after the proprocessor." << endl;
		cout << "	Write \"none\" that no create this file." << endl;
		cout << "/o	Output in file after the compiler." << endl;
		cout << "	This file with expansion \".prog\"." << endl;
	}
	//return 0;
}


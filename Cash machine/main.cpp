#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <time.h>
#include "bankFunctions.h"
using namespace std;

int main() { 
	setlocale(LC_ALL,"Russian");
	system("color 1E");
	srand( time( NULL ) );

	int summ = 0;
	string cassettes = "cassettes.txt";

	string *codes = new string[4];

	codes[0] = "�������� ��������� �������! ";
	codes[1] = "���������� ������� ���� � ����������� � �������� ";
	codes[2] = "��� ���������� � �������� ";
	codes[3] = "��������� ����� ������� �������� ������ ���������� ";

	for( ; ; ) {

		HANDLE h;
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 15);

		int i = rand() %301;
		SetConsoleTextAttribute(h, i);

		cout << endl << "������� ����������� �����:";
		cin >> summ;
		int errorCode = issuanceSum(cassettes, summ);

		cout << endl << codes[errorCode] << endl;

		int action;
		cout << "������� 0 ���� ������ ����� " << endl;
		cin >> action;
		if (action == 0) break;

		system("cls");
	}

	system("pause");
	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <time.h>
#include "bankFunctions.h"
using namespace std;

struct cassette {
	int banknotes;
	int numberOfBanknotes;
	int needBanknotes;
};

struct Bank {
	cassette *bank;
	Bank(int totalBanknotesNumber) {
		bank = new cassette [totalBanknotesNumber];
	}
};

int canOpenFileCassettes(string cassettes, int &errorCode) {

	ifstream file(cassettes);
	if (file) { 
		errorCode = 0; 
	}
	file.close();

	return 0;
}

int countBanknotes (string cassettes, int &errorCode) {
	string line;
	int totalBanknotesNumber = 0;
	ifstream file(cassettes);
	for( ; getline(file, line); totalBanknotesNumber++) {
	}
	file.close();

	return totalBanknotesNumber;
}

int readCassettesInfo (string cassettes, int totalBanknotesNumber, Bank &A, int &errorCode) {
	if (totalBanknotesNumber == 0) errorCode = 2; 
	else {
		ifstream file(cassettes);
		while (!file.eof()) {
			for (int i = 0; i < totalBanknotesNumber; i++) {
				file >> A.bank[i].banknotes >> A.bank[i].numberOfBanknotes;
			}
		}
		file.close();
	}
	return 0;
}

void outputBanknotesInformation(int totalBanknotesNumber, Bank &A, int &maxSum) {
	maxSum = 0;

	cout << endl << "Информация о кассетах : " << endl;

	for (int i = 0; i < totalBanknotesNumber; i++) {
		cout << A.bank[i].banknotes << ' ' << A.bank[i].numberOfBanknotes << endl;
		maxSum += (A.bank[i].banknotes * A.bank[i].numberOfBanknotes);
	}
	cout << "Максимальная сумма : " << maxSum << endl << endl;
}

int sort (const void *a, const void *b) {
	return ((cassette*) a) -> banknotes - ((cassette*) b) -> banknotes; 
}

int selectionBanknotes (int totalBanknotesNumber, Bank &A, int &errorCode, int &maxSum, int summ) {

	const int big = 1000000;
	int additionalSum = 0;

	if (summ > maxSum) {
		errorCode = 3;
		return errorCode;
	}

	int *minimumAmount = new int [summ + 1];  
	minimumAmount[0] = 0;

	for (int i = 0; i < totalBanknotesNumber; i++)  A.bank[i].needBanknotes = 0;

	for (additionalSum = 1; additionalSum <= summ; additionalSum++) {                       
		minimumAmount[additionalSum] = big;   
		for (int i = 0; i < totalBanknotesNumber; i++)  { 
			if (A.bank[i].needBanknotes < A.bank[i].numberOfBanknotes && A.bank[i].numberOfBanknotes !=0) {
				while (additionalSum >= A.bank[i].banknotes && minimumAmount[additionalSum - A.bank[i].banknotes] + 1 < minimumAmount[additionalSum] && A.bank[i].needBanknotes < A.bank[i].numberOfBanknotes) {
					minimumAmount[additionalSum] = minimumAmount[additionalSum - A.bank[i].banknotes] + 1;  
					A.bank[i].needBanknotes++;
				}
			}
		}
		for (int i = 0; i < totalBanknotesNumber; i++)  A.bank[i].needBanknotes = 0;
	}

	additionalSum = summ;

	if (minimumAmount[additionalSum] == big)   { 
		errorCode = 3;       
	}
	else	{
		while (additionalSum > 0) 
			for (int i = 0; i < totalBanknotesNumber ; i++) 
				if (minimumAmount[additionalSum - A.bank[i].banknotes] == minimumAmount[additionalSum]-1 && A.bank[i].numberOfBanknotes != 0) { 
					A.bank[i].needBanknotes++;
					additionalSum = additionalSum - A.bank[i].banknotes;
					break;
				}

				for (int i = 0; i < totalBanknotesNumber; i++)  {
					A.bank[i].numberOfBanknotes = A.bank[i].numberOfBanknotes - A.bank[i].needBanknotes;
					if (A.bank[i].needBanknotes != 0)	{
						if (((A.bank[i].needBanknotes % 10) == 0) || ((A.bank[i].needBanknotes % 11) == 11)) 	cout << A.bank[i].needBanknotes << " купюр по " << A.bank[i].banknotes << endl;
						else if (A.bank[i].needBanknotes == 1) 	cout << A.bank[i].needBanknotes << " купюра по " << A.bank[i].banknotes << endl;
						else if ((A.bank[i].needBanknotes % 10) < 5) cout << A.bank[i].needBanknotes << " купюры по " << A.bank[i].banknotes << endl;
						else if ((A.bank[i].needBanknotes % 10) > 4) cout << A.bank[i].needBanknotes << " купюр по " << A.bank[i].banknotes << endl;
					}
				}
	}
	cout << endl;
	return errorCode;
}

void rewriteInfo (string cassettes, int totalBanknotesNumber, Bank &A) {

	ofstream file(cassettes);
	for (int i = 0; i < totalBanknotesNumber; i++) {
		file << A.bank[i].banknotes << ' ' << A.bank[i].numberOfBanknotes <<endl;
	}
	file.close();
}

int issuanceSum (string cassettes, int summ) {
	int errorCode = 1;
	int moneyBanknotesNumber = 0;
	int maxSum = 0;

	canOpenFileCassettes(cassettes, errorCode);
	Bank A(countBanknotes(cassettes, errorCode));
	readCassettesInfo (cassettes, countBanknotes(cassettes, errorCode), A, errorCode);
	outputBanknotesInformation(countBanknotes(cassettes, errorCode), A, maxSum); 

	if (errorCode == 0) {
		qsort (A.bank, countBanknotes(cassettes, errorCode), sizeof(cassette), sort);
		selectionBanknotes(countBanknotes(cassettes, errorCode), A, errorCode, maxSum, summ);
		if (errorCode == 0) {
			rewriteInfo (cassettes, countBanknotes(cassettes, errorCode), A); 
			outputBanknotesInformation(countBanknotes(cassettes, errorCode), A, maxSum);
		}
	}
	return errorCode;
}





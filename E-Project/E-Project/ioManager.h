#ifndef __IO_MANAGER__
#define __IO_MANAGER__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include "commandClassType.h"

using namespace std;

class Validator {
public:
	bool isValid(char* buf) {
		for (int i = 0; buf[i]; i++) {
			if (buf[i] == '/') return false;
		}
		return true;
	}
};

class Parcer {
public:
	CmdParam parce(char* buf) {
		CmdParam cmdParam;
		string tmp;
		for (int i = 0; buf[i]; i++) {
			if (buf[i] == ',') {
				setFlag(tmp, cmdParam);
				tmp.clear();
			}
			else tmp.push_back(buf[i]);
		}
		if (tmp.empty() == false) setFlag(tmp, cmdParam);

		return cmdParam;
	}

private:
	void setFlag(string word, CmdParam& cmdParam) {
		if (word == "ADD") cmdParam.cmd = CmdType::ADD;
		else if (word == "DEL") cmdParam.cmd = CmdType::DEL;
		else if (word == "MOD") cmdParam.cmd = CmdType::MOD;
		else if (word == "SCH") cmdParam.cmd = CmdType::SCH;
		else if (word == "-p") cmdParam.printFlag = true;
		else if (word == "-f") cmdParam.firstNameFlag = true;
		else if (word == "-l") {
			cmdParam.lastNameFlag = true;
			cmdParam.lastNumFlag = true;
		}
		else if (word == "-m") cmdParam.midNumFlag = true;
		else if (word == "-y") cmdParam.yearFlag = true;
		else if (word == "-m") cmdParam.monthFlag = true;
		else if (word == "-d") cmdParam.dateFlag = true;
		else if (word == " ") {
			;
		}
		else {
			cmdParam.strs.push_back(word);
			if (word == "name") cmdParam.lastNumFlag = false;
			else if (word == "phoneNum") cmdParam.lastNameFlag = false;
		}
	}
};

class IoManager {
public:
	IoManager() {
		parcer = new Parcer();
		validator = new Validator();
	}

	void openIoFile(string inputFileName, string outputFileName) {
		inputFile.open(inputFileName, ios::in);
		outputFile.open(outputFileName, ios::out);
	}

	bool isInputFileOpen() {
		return inputFile.is_open();
	}

	bool isInputFileEnd() {
		return inputFile.eof();
	}

	void printString(string str) {
		outputFile << str << endl;
	}

	CmdParam getInput() {
		CmdParam cmdParam;
		char buf[256] = { 0, };
		inputFile.getline(buf, 256);	
		if (validator->isValid(buf)) {
			cmdParam = parcer->parce(buf);
		}
		return cmdParam;
	}

private:
	ifstream inputFile;
	ofstream outputFile;
	Parcer* parcer;
	Validator* validator;
};

#endif
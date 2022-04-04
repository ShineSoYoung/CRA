#ifndef __IO_MANAGER__
#define __IO_MANAGER__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include "parcedCommandType.h"

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

class Parser {
public:
	ParcedCmd parse(char* buf) {
		ParcedCmd parcedCmd;
		string tmp;
		for (int i = 0; buf[i]; i++) {
			if (buf[i] == ',') {
				setFlag(tmp, parcedCmd);
				tmp.clear();
			}
			else tmp.push_back(buf[i]);
		}
		if (tmp.empty() == false) setFlag(tmp, parcedCmd);

		return parcedCmd;
	}

private:
	void setFlag(string word, ParcedCmd& parcedCmd) {
		if (word == "ADD") parcedCmd.cmd = CmdType::ADD;
		else if (word == "DEL") parcedCmd.cmd = CmdType::DEL;
		else if (word == "MOD") parcedCmd.cmd = CmdType::MOD;
		else if (word == "SCH") parcedCmd.cmd = CmdType::SCH;
		else if (word == "-p") parcedCmd.printFlag = true;
		else if (word == "-f") parcedCmd.firstNameFlag = true;
		else if (word == "-l") {
			parcedCmd.lastNameFlag = true;
			parcedCmd.lastNumFlag = true;
		}
		else if (word == "-m") {
			parcedCmd.midNumFlag = true;
			parcedCmd.monthFlag = true;
		}
		else if (word == "-y") parcedCmd.yearFlag = true;
		else if (word == "-d") parcedCmd.dateFlag = true;
		else if (word == " ") {
			;
		}
		else {
			parcedCmd.strs.push_back(word);
			if (word == "name") parcedCmd.lastNumFlag = false;
			else if (word == "phoneNum") parcedCmd.lastNameFlag = false;

			if (word == "phoneNum") parcedCmd.monthFlag = false;
			else if (word == "birthday") parcedCmd.midNumFlag = false;
		}
	}
};

class IoManager {
public:
	IoManager() {
		parser = new Parser();
		validator = new Validator();
	}

	~IoManager() {
		delete parser;
		delete validator;
		if (inputFile.is_open()) inputFile.close();
		if (outputFile.is_open()) outputFile.close();
	}

	void openIoFiles(string inputFileName, string outputFileName) {
		inputFile.open(inputFileName, ios::in);
		outputFile.open(outputFileName, ios::out);
	}

	bool isInputFileOpen() {
		return inputFile.is_open();
	}

	bool isInputFileEnd() {
		return inputFile.eof();
	}

	void printStringToFile(string str) {
		outputFile << str;
	}

	void printString(string str) {
		cout << str;
	}

	ParcedCmd getDataByLine () {
		ParcedCmd parcedCmd;
		char buf[256] = { 0, };
		inputFile.getline(buf, 256);	
		if (validator->isValid(buf)) {
			parcedCmd = parser->parse(buf);
		}
		return parcedCmd;
	}

private:
	ifstream inputFile;
	ofstream outputFile;
	Parser* parser;
	Validator* validator;
};

#endif
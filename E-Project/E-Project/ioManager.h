#ifndef __IO_MANAGER__
#define __IO_MANAGER__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include "parsedCommandType.h"

using namespace std;

class Validator {
public:
	bool isValid(char* buf) {
		if (!buf[0]) {
			return false;
		}
		for (int i = 0; buf[i]; i++) {
			if (buf[i] == '/') return false;
		}
		return true;
	}
};

class Parser {
public:
	ParsedCmd parse(char* buf) {
		ParsedCmd ParsedCmd;
		string tmp;
		for (int i = 0; buf[i]; i++) {
			if (buf[i] == ',') {
				setFlag(tmp, ParsedCmd);
				tmp.clear();
			}
			else tmp.push_back(buf[i]);
		}
		if (tmp.empty() == false) setFlag(tmp, ParsedCmd);

		return ParsedCmd;
	}

private:
	void setFlag(string word, ParsedCmd& ParsedCmd) {
		if (word == "ADD") ParsedCmd.cmd = CmdType::ADD;
		else if (word == "DEL") ParsedCmd.cmd = CmdType::DEL;
		else if (word == "MOD") ParsedCmd.cmd = CmdType::MOD;
		else if (word == "SCH") ParsedCmd.cmd = CmdType::SCH;
		else if (word == "-p") ParsedCmd.printFlag = true;
		else if (word == "-f") ParsedCmd.firstNameFlag = true;
		else if (word == "-l") {
			ParsedCmd.lastNameFlag = true;
			ParsedCmd.lastNumFlag = true;
		}
		else if (word == "-m") {
			ParsedCmd.midNumFlag = true;
			ParsedCmd.monthFlag = true;
		}
		else if (word == "-y") ParsedCmd.yearFlag = true;
		else if (word == "-d") ParsedCmd.dateFlag = true;
		else if (word == " ") {
			;
		}
		else {
			ParsedCmd.strs.push_back(word);
			if (word == "name") ParsedCmd.lastNumFlag = false;
			else if (word == "phoneNum") ParsedCmd.lastNameFlag = false;

			if (word == "phoneNum") ParsedCmd.monthFlag = false;
			else if (word == "birthday") ParsedCmd.midNumFlag = false;
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

	void getDataByLine (char* buf, int n) {
		inputFile.getline(buf, n);	
	}

	ParsedCmd getParsedCmd(char* buf) {
		return parser->parse(buf);
	}

	bool isValid(char* buf) {
		return validator->isValid(buf);
	}

private:
	ifstream inputFile;
	ofstream outputFile;
	Parser* parser;
	Validator* validator;
};

#endif
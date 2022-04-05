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
	ParsedCmd parse(char* inputStr) {
		vector<string> strs = split(inputStr);
		return getParsedCmd(strs);
	}

private:
	vector<string> split(char* str) {
		vector<string> vstr;
		string buf;
		for (int i = 0; str[i]; i++) {
			if (str[i] == ',') {
				if (buf.empty()) buf += '_';
				vstr.push_back(buf);
				buf.clear();
			}
			else buf += str[i];
		}
		if (buf.empty() == false) vstr.push_back(buf);
		return vstr;
	}

	void setFlagCmd(vector<string> strs, ParsedCmd* parsedCmd) {
		string cmd = strs.at(0);
		if (cmd == "ADD") parsedCmd->cmd = CmdType::ADD;
		else if (cmd == "DEL") parsedCmd->cmd = CmdType::DEL;
		else if (cmd == "MOD") parsedCmd->cmd = CmdType::MOD;
		else if (cmd == "SCH") parsedCmd->cmd = CmdType::SCH;
	}

	void setFlagOpt(vector<string> strs, ParsedCmd* parsedCmd) {
		string opt = strs.at(1);
		if (opt == "-p") parsedCmd->printFlag = true;

		opt = strs.at(2);
		string word = strs.at(4);
		if (word == "name") {
			if (opt == "-f") parsedCmd->firstNameFlag = true;
			else if (opt == "-l") parsedCmd->lastNameFlag = true;
		}
		else if (word == "phoneNum") {
			if (opt == "-m") parsedCmd->midNumFlag = true;
			else if (opt == "-l") parsedCmd->lastNumFlag = true;
		}
		else if (word == "birthday") {
			if (opt == "-y") parsedCmd->yearFlag = true;
			else if (opt == "-m") parsedCmd->monthFlag = true;
			else if (opt == "-d") parsedCmd->dateFlag = true;
		}
	}

	ParsedCmd getParsedCmd(vector<string> strs) {
		ParsedCmd cmd;
		setFlagCmd(strs, &cmd);
		setFlagOpt(strs, &cmd);
		for (int i = 4; i < strs.size(); i++) {
			cmd.strs.push_back(strs.at(i));
		}
		return cmd;
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
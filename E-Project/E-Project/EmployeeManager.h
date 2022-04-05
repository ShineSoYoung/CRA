#include "ioManager.h"
#include "command.h"
#include "addCommand.h"
#include "deleteCommand.h"
#include "searchCommand.h"
#include "modifyCommand.h"

const int MAX_NUM_OF_CMD = 5;

class EmployeeManager {
public:
	EmployeeManager() {
		io = new IoManager();
		registerCmd(CmdType::ADD, &add);
		registerCmd(CmdType::DEL, &del);
		registerCmd(CmdType::SCH, &sch);
		registerCmd(CmdType::MOD, &mod);
	}

	~EmployeeManager() {
		delete io;
	}

	void setIoFiles(const char* inputFileName, const char* outputFileName) {
		io->openIoFiles(inputFileName, outputFileName);
	}

	void run() {
		if (io->isInputFileOpen()) {
			while (!io->isInputFileEnd()) {
				char buf[256] = { 0, };
				io->getDataByLine(buf, 256);
				if (io->isValid(buf) == false) break;

				ParsedCmd ParsedCmd = io->getParsedCmd(buf);

				string result;
				result = command[(int)ParsedCmd.cmd]->processCommand(DB, ParsedCmd);
				if (!result.empty()) io->printStringToFile(result);
			}
		}
	}

private:
	void registerCmd(CmdType cmdType, Command* cmd)
	{
		command[(int)cmdType] = cmd;
	}

	IoManager* io = nullptr;
	Command* command[MAX_NUM_OF_CMD];
	datamanager DB;

	addCommand add;
	deleteCommand del;
	searchCommand sch;
	modifyCommand mod;
};
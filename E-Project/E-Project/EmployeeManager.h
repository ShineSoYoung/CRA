#include "ioManager.h"
#include "command.h"
#include "addCommand.h"
#include "deleteCommand.h"
#include "searchCommand.h"
#include "modifyCommand.h"

class EmployeeManager {
public:
	EmployeeManager() {
		io = new IoManager();
	}

	~EmployeeManager() {
		delete io;
	}

	void setIoFiles() {
		io->openIoFiles("input.txt", "output.txt");
	}

	void setIoFiles(string inputFileName, string outputFileName) {
		io->openIoFiles(inputFileName, outputFileName);
	}

	void run() {
		if (io->isInputFileOpen()) {
			while (!io->isInputFileEnd()) {
				char buf[256] = { 0, };
				io->getDataByLine(buf, 256);
				if (io->isValid(buf) == false) break;

				ParsedCmd ParsedCmd = io->getParsedCmd(buf);
				switch (ParsedCmd.cmd) {
				case CmdType::ADD:
					command = &add;
					break;				
				case CmdType::DEL:
					command = &del;
					break;				
				case CmdType::SCH:
					command = &sch;
					break;				
				case CmdType::MOD:
					command = &mod;
					break;
				}

				string result;
				if (command->checkCommandIsValid(DB, ParsedCmd))
					result = command->processCommand(DB, ParsedCmd);
				if (!result.empty()) io->printStringToFile(result);
			}
		}
	}

private:
	IoManager* io = nullptr;
	Command* command = nullptr;
	datamanager DB;

	addCommand add;
	deleteCommand del;
	searchCommand sch;
	modifyCommand mod;
};
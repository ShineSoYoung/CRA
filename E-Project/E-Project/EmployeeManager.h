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

				ParcedCmd parcedCmd = io->getParcedCmd(buf);
				switch (parcedCmd.cmd) {
				case CmdType::ADD:
					command = new addCommand();
					break;				
				case CmdType::DEL:
					command = new deleteCommand();
					break;				
				case CmdType::SCH:
					command = new searchCommand();
					break;				
				case CmdType::MOD:
					command = new modifyCommand();
					break;
				}

				string result;
				result = command->processCommand(DB, parcedCmd);
				if (!result.empty()) io->printStringToFile(result);

				delete command;
			}
		}
	}

private:
	IoManager* io = nullptr;
	Command* command = nullptr;
	datamanager DB;
};
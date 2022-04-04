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

	void setIoFiles() {
		io->openIoFiles("input.txt", "output.txt");
	}

	void setIoFiles(string inputFileName, string outputFileName) {
		io->openIoFiles(inputFileName, outputFileName);
	}

	void run() {
		if (io->isInputFileOpen()) {
			while (!io->isInputFileEnd()) {
				CmdParam cmdParam = io->getDataByLine();

				switch (cmdParam.cmd) {
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
				result = command->processCommand(DB, cmdParam);
				if (!result.empty()) io->printStringToFile(result);
			}
		}
	}

private:
	IoManager* io = nullptr;
	Command* command = nullptr;
	datamanager DB;
};
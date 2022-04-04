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

	void setInputData(string inputFileName, string outputFileName) {
		io->openIoFile(inputFileName, outputFileName);
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
				io->printString(result);
			}
		}
	}

private:
	IoManager* io = nullptr;
	command* command = nullptr;
	datamanager DB;
};
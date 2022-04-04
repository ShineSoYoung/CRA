#ifndef __MODIFY_COMMAND__
#define __MODIFY_COMMAND__

#include "parcedCommandType.h"
#include "command.h"

class modifyCommand : public OptionalCommand
{
public:
    virtual string processCommand(datamanager& DB, ParcedCmd command) override
    {
        if (isValidModCmd(command) == false)
            return "FAIL";

        vector<Employee*> findArray = DB.search_data(command.strs[0], command.strs[1], makeOptionList(command));
        selectPrinter(findArray, command.printFlag);
        string result = printer->printFinalResult("MOD,", findArray);
        DB.modify_data(findArray, command.strs[2], command.strs[3]);
        releasePrinter();
        return result;
    }

private:

    bool isValidModCmd(CmdParam command) {
        if (command.strs[2] == "employeeNum")
            return false;

        return true;
    }
};

#endif
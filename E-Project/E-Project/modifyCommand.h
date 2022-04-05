#ifndef __MODIFY_COMMAND__
#define __MODIFY_COMMAND__

#include "parsedCommandType.h"
#include "command.h"

class modifyCommand : public OptionalCommand
{
public:
    virtual string processCommand(datamanager& DB, const ParsedCmd command) override
    {
        if (isValidModCmd(command) == false) 
            return "";

        vector<Employee*> findArray = DB.search_data(command.strs[findColumn], command.strs[findValue], makeOptionList(command));
        selectPrinter(findArray, command.printFlag);
        string result = printer->printFinalResult("MOD,", findArray);
        DB.modify_data(findArray, command.strs[targetColumn], command.strs[targetValue]);
        return result;
    }

private:

    bool isValidModCmd(const ParsedCmd command) {
        if (command.strs[targetColumn] == "employeeNum")
            return false;

        return true;
    }
};

#endif
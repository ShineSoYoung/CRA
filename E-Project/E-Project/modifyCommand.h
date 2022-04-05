#ifndef __MODIFY_COMMAND__
#define __MODIFY_COMMAND__

#include "parsedCommandType.h"
#include "command.h"

class modifyCommand : public OptionalCommand
{
public:
    virtual bool checkCommandIsValid(datamanager& DB, const ParsedCmd command) override
    {
        return (command.strs[targetColumn] != "employeeNum");
    }
    virtual string processCommand(datamanager& DB, const ParsedCmd command) override
    {
        vector<Employee*> findArray = findTargetArray(DB, command);
        string result = printCommandResult("MOD", findArray, command);
        DB.modify_data(findArray, command.strs[targetColumn], command.strs[targetValue]);
        return result;
    }

private:
};

#endif
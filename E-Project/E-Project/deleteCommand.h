#ifndef __DELETE_COMMAND__
#define __DELETE_COMMAND__

#include "parsedCommandType.h"
#include "command.h"

class deleteCommand : public OptionalCommand
{
public:
    virtual string processCommand(datamanager& DB, const ParsedCmd command) override
    {
        vector<Employee*> findArray = findTargetArray(DB, command);
        string result = printCommandResult("DEL", findArray, command);
        DB.delete_data(findArray);
        return result;
    }

private:
};

#endif
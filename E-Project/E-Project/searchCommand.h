#ifndef __SEARCH_COMMAND__
#define __SEARCH_COMMAND__

#include "parsedCommandType.h"
#include "command.h"

class searchCommand : public OptionalCommand
{
public:
    virtual string processCommand(datamanager& DB, const ParsedCmd command) override
    {
        vector<Employee*> findArray = findTargetArray(DB, command);
        return printCommandResult("SCH", findArray, command);
    }

private:
};

#endif
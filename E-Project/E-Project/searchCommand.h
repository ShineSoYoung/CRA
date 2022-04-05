#ifndef __SEARCH_COMMAND__
#define __SEARCH_COMMAND__

#include "parsedCommandType.h"
#include "command.h"

class searchCommand : public OptionalCommand
{
public:
    virtual bool checkCommandIsValid(datamanager& DB, const ParsedCmd command) override
    {
        return true;
    }
    virtual string processCommand(datamanager& DB, const ParsedCmd command) override
    {
        vector<Employee*> findArray = DB.search_data(command.strs[findColumn], command.strs[findValue], makeOptionList(command));
        selectPrinter(findArray, command.printFlag);
        string result = printer->printFinalResult("SCH,", findArray);
        return result;
    }

private:
};

#endif
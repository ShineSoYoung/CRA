#ifndef __SEARCH_COMMAND__
#define __SEARCH_COMMAND__

#include "commandClassType.h"
#include "command.h"

class searchCommand : public command
{
public:
    virtual string processCommand(CmdParam command) override
    {
        vector<Employee*> findArray = DB.search_data(command.strs[0], command.strs[1], makeOptionList(command));
        selectPrinter(findArray, command.printFlag);
        string result = printer->printFinalResult("SCH,", findArray);
        releasePrinter();
        return result;
    }

private:
};

#endif
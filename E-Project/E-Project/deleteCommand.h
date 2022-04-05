#ifndef __DELETE_COMMAND__
#define __DELETE_COMMAND__

#include "commandClassType.h"
#include "command.h"

class deleteCommand : public OptionalCommand
{
public:
    virtual string processCommand(datamanager& DB, const CmdParam command) override
    {
        vector<Employee*> findArray = DB.search_data(command.strs[findColumn], command.strs[findValue], makeOptionList(command));
        selectPrinter(findArray, command.printFlag);
        string result = printer->printFinalResult("DEL,", findArray);
        DB.delete_data(findArray);
        releasePrinter();
        return result;
    }

private:
};

#endif
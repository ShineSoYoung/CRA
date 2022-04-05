#include "gtest/gtest.h"
#include "../E-Project/deleteCommand.h"
#include "../E-Project/addCommand.h"
#include "../E-Project/searchCommand.h"
#include "../E-Project/datamanager.h"
#include "../E-Project/ioManager.h"

class stressfulTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        int baseNumber = 17000000;
        for (int i = 0; i < 99999; i++)
        {
            char buf[256];
            int employeeNumber = baseNumber + i;
            string cmd = "ADD, , , ," + to_string(employeeNumber) + ",VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV";
            strcpy_s(buf, cmd.c_str());
            addCmd.processCommand(DB, parser.parse(buf));
        }
        string cmd = "ADD, , , ,18000000,VXIHXOTH JHOP,CL4,010-3112-2609,19771211,ADV";
    }
    virtual void TearDown() override
    {
        int baseNumber = 17000000;
        for (int i = 0; i < 99999; i++)
        {
            char buf[256];
            int employeeNumber = baseNumber + i;
            string cmd = "DEL, , , ,employeeNum," + to_string(employeeNumber);
            strcpy_s(buf, cmd.c_str());
            delCmd.processCommand(DB, parser.parse(buf));
        }
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18000000"));
    }

    Parser parser;
    datamanager DB;
    addCommand addCmd;
    searchCommand schCmd;
    deleteCommand delCmd;
};

TEST_F(stressfulTest, stressTest)
{
    string result = schCmd.processCommand(DB, ParsedCmd{ CmdType::SCH,false,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "SCH,1\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::SCH,false,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "SCH,1\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::SCH,false,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "SCH,1\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::SCH,false,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "SCH,1\n");
}
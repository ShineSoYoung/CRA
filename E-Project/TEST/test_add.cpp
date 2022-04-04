#include "pch.h"
#include "../E-Project/deleteCommand.h"
#include "../E-Project/addCommand.h"
#include "../E-Project/modifyCommand.h"
#include "../E-Project/searchCommand.h"
#include "../E-Project/datamanager.h"
#include "../E-Project/ioManager.h"

extern Parcer * parcer;

class AddTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        parcer = new Parcer;
    }
    virtual void TearDown() override
    {
        delCmd.processCommand(parcer->parce("DEL, , , ,employeeNum,15120999"));
        delCmd.processCommand(parcer->parce("DEL, , , ,employeeNum,17112609"));
        delCmd.processCommand(parcer->parce("DEL, , , ,employeeNum,18115050"));
        delCmd.processCommand(parcer->parce("DEL, , , ,employeeNum,88114052"));
        delete parcer;
    }

    addCommand addCmd;
    deleteCommand delCmd;
};

TEST_F(AddTest, BasicAddCase) {

    EXPECT_EQ(addCmd.processCommand(parcer->parce("ADD, , , ,15120999,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV")), "");
    EXPECT_EQ(addCmd.processCommand(parcer->parce("ADD, , , ,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO")), "");
    EXPECT_EQ(addCmd.processCommand(parcer->parce("ADD, , , ,18115050,TTETHU HBO,CL3,010-4581-2050,20080718,ADV")), "");
}

TEST_F(AddTest, SameAddCase) {

    //같은 사번
    EXPECT_EQ(addCmd.processCommand(parcer->parce("ADD, , , ,88114052,NQ LVARW,CL4,010-4528-0959,19911021,PRO")), "");
    EXPECT_EQ(addCmd.processCommand(parcer->parce("ADD, , , ,88114052,SRERLALH HMEF,CL2,010-0991-9521,19640910,PRO")), "FAIL");
}

TEST_F(AddTest, NullAddCase) {

    //비어있는 정보가 있는 경우
    EXPECT_EQ(addCmd.processCommand(parcer->parce("ADD, , , ,,VSID TVO,CL1,010-3669-1077,20120718,PRO")), "FAIL");
    EXPECT_EQ(addCmd.processCommand(parcer->parce("ADD, , , ,17111236,,010-3669-1077,20120718,PRO")), "FAIL");
    EXPECT_EQ(addCmd.processCommand(parcer->parce("ADD, , , ,17111236,VSID TVO,,010-3669-1077,20120718,PRO")), "FAIL");
    EXPECT_EQ(addCmd.processCommand(parcer->parce("ADD, , , ,17111236,VSID TVO,CL1,,20120718,PRO")), "FAIL");
    EXPECT_EQ(addCmd.processCommand(parcer->parce("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,,PRO")), "FAIL");
    EXPECT_EQ(addCmd.processCommand(parcer->parce("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,20120718,")), "FAIL");
}

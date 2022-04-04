#include "pch.h"
#include "../E-Project/deleteCommand.h"
#include "../E-Project/addCommand.h"
#include "../E-Project/modifyCommand.h"
#include "../E-Project/searchCommand.h"
#include "../E-Project/datamanager.h"
#include "../E-Project/ioManager.h"

extern Parcer* parcer;

class DeleteTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        parcer = new Parcer;
        addCmd.processCommand(parcer->parce("ADD, , , ,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO"));
        addCmd.processCommand(parcer->parce("ADD, , , ,12345678,JAY HELLO,CL3,010-1234-1234,19901231,EX"));
    }

    virtual void TearDown() override
    {
        delCmd.processCommand(parcer->parce("DEL, , , ,employeeNum,18091234"));
        delCmd.processCommand(parcer->parce("DEL, , , ,employeeNum,12345678"));
        delete parcer;
    }

    addCommand addCmd;
    deleteCommand delCmd;
    searchCommand schCmd;
};

TEST_F(DeleteTest, delete_with_name) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"name", "LALALA HELLO"} });
    EXPECT_EQ(result, "DEL,1\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_cl) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "DEL,1\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_phonenumber) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"phoneNum", "010-9876-4321"} });
    EXPECT_EQ(result, "DEL,1\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_birthday) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"birthday", "20210101"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"birthday", "19890509"} });
    EXPECT_EQ(result, "DEL,1\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_name_option_p) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"name", "LALALA HELLO"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_cl_option_p) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_p) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"phoneNum", "010-9876-4321"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_birthday_option_p) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"birthday", "20210101"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"birthday", "19890509"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_name_option_f) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,true,false,false,false,false,false,false,{"name", "HIBONG"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,true,false,false,false,false,false,false,{"name", "LALALA"} });
    EXPECT_EQ(result, "DEL,1\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_name_option_l) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,false,true,false,false,false,false,false,{"name", "HWANG"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,true,false,false,false,false,false,{"name", "HELLO"} });
    EXPECT_EQ(result, "DEL,12345678,JAY HELLO,CL3,010-1234-1234,19901231,EX\nDEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_m) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,false,false,true,false,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,true,false,false,false,false,{"phoneNum","9876"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_l) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,false,false,false,false,true,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,true,false,false,false,{"phoneNum","4321"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_birthday_option_y) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,true,false,false,{"birthday","2000"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,true,false,false,{"birthday","1989"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_birthday_option_m) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,true,false,{"birthday","08"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,true,false,{"birthday","05"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_birthday_option_d) {
    string result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,true,{"birthday","20"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,true,{"birthday","09"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

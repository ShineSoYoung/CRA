#include "pch.h"
#include "../E-Project/deleteCommand.h"
#include "../E-Project/addCommand.h"
#include "../E-Project/searchCommand.h"
#include "../E-Project/datamanager.h"
#include "../E-Project/ioManager.h"

class DeleteTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        addCmd.processCommand(DB, parser.parse("ADD, , , ,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345678,JAY HELLO,CL3,010-1234-1234,19901231,EX"));
    }

    virtual void TearDown() override
    {
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,18091234"));
        delCmd.processCommand(DB, parser.parse("DEL, , , ,employeeNum,12345678"));
    }

    datamanager DB;
    Parser parser;
    addCommand addCmd;
    deleteCommand delCmd;
    searchCommand schCmd;
};

TEST_F(DeleteTest, delete_with_name) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,false,false,false,false,false,false,false,{"name", "LALALA HELLO"} });
    EXPECT_EQ(result, "DEL,1\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_cl) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "DEL,1\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_phonenumber) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,false,false,false,false,false,false,false,{"phoneNum", "010-9876-4321"} });
    EXPECT_EQ(result, "DEL,1\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_birthday) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,false,false,false,false,false,false,false,{"birthday", "20210101"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,false,false,false,false,false,false,false,{"birthday", "19890509"} });
    EXPECT_EQ(result, "DEL,1\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_name_option_p) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"name", "LALALA HELLO"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_cl_option_p) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_p) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"phoneNum", "010-9876-4321"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_birthday_option_p) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"birthday", "20210101"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"birthday", "19890509"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_name_option_f) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,true,false,false,false,false,false,false,{"name", "HIBONG"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,true,false,false,false,false,false,false,{"name", "LALALA"} });
    EXPECT_EQ(result, "DEL,1\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_name_option_l) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,false,true,false,false,false,false,false,{"name", "HWANG"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,true,false,false,false,false,false,{"name", "HELLO"} });
    EXPECT_EQ(result, "DEL,12345678,JAY HELLO,CL3,010-1234-1234,19901231,EX\nDEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_m) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,false,false,true,false,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,true,false,false,false,false,{"phoneNum","9876"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_l) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,false,false,false,false,true,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,true,false,false,false,{"phoneNum","4321"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_birthday_option_y) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,true,false,false,{"birthday","2000"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,true,false,false,{"birthday","1989"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_birthday_option_m) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,true,false,{"birthday","08"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,true,false,{"birthday","05"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

TEST_F(DeleteTest, delete_with_birthday_option_d) {
    string result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,true,{"birthday","20"} });
    EXPECT_EQ(result, "DEL,NONE\n");

    result = delCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,true,{"birthday","09"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");

    result = schCmd.processCommand(DB, ParsedCmd{ CmdType::DEL,true,false,false,false,false,false,false,false,{"employeeNum", "18091234"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

class DeleteMultipleTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345678,ABABAB JJJJ,CL4,010-9876-4321,19890509,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345680,ABABAB JJJJ,CL4,010-9876-4321,19890509,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345681,ABABAB JJJJ,CL4,010-9876-4321,19890509,PRO"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345682,XXXX AAAA,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345683,YYYY BBBB,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345684,ZZZZ CCCC,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345685,XXXX AAAA,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345686,YYYY BBBB,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345687,ZZZZ CCCC,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345688,XXXX AAAA,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345689,YYYY BBBB,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345690,ZZZZ CCCC,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345691,XXXX AAAA,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345692,YYYY BBBB,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345693,ZZZZ CCCC,CL3,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345694,CDCDCD KKKK,CL4,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345695,CDCDCD KKKK,CL4,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345696,CDCDCD KKKK,CL4,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345697,CDCDCD KKKK,CL4,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345698,CDCDCD KKKK,CL4,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345699,CDCDCD KKKK,CL4,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345700,CDCDCD KKKK,CL4,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345701,CDCDCD KKKK,CL4,010-1234-1234,19901231,EX"));
        addCmd.processCommand(DB, parser.parse("ADD, , , ,12345702,CDCDCD KKKK,CL4,010-1234-1234,19901231,EX"));
    }

    virtual void TearDown() override
    {
        char buf[100];
        string entry = "DEL, , , ,employeeNum,12345";
        int base = 678;
        for (int i = 0; i < 24; i++)
        {
            string command = entry + to_string(i + base) + "\n";
            strcpy_s(buf, command.c_str());
            delCmd.processCommand(DB, parser.parse(buf));
        }
    }

    datamanager DB;
    Parser parser;
    addCommand addCmd;
    deleteCommand delCmd;
    searchCommand schCmd;
};

TEST_F(DeleteMultipleTest, delete_multiple_entries) {
    string result = delCmd.processCommand(DB, CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"cl","CL4"} });
    EXPECT_EQ(result, "DEL,12\n");

    result = schCmd.processCommand(DB, CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "SCH,NONE\n");
}

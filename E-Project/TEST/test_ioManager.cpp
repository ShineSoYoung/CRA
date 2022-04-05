#include "gtest/gtest.h"
#include "../E-Project/ioManager.h"
#include "../E-Project/parsedCommandType.h"

TEST(IO_Test, Add_parsing_test) {
    vector<string> strs = { "15123099", "VXIHXOTH JHOP", "CL3", "010-3112-2609", "19771211", "ADV" };
    ParsedCmd expected(CmdType::ADD, false, false, false, false, false, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, Del_parsing_test) {
    vector<string> strs = { "employeeNum", "15123099" };
    ParsedCmd expected(CmdType::DEL, false, false, false, false, false, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("DEL, , , ,employeeNum,15123099");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, mod_parsing_test) {
    vector<string> strs = { "employeeNum", "15123099", "name", "ABCD EFG"};
    ParsedCmd expected(CmdType::MOD, false, false, false, false, false, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("MOD, , , ,employeeNum,15123099,name,ABCD EFG");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, sch_parsing_test) {
    vector<string> strs = { "employeeNum", "15123099" };
    ParsedCmd expected(CmdType::SCH, false, false, false, false, false, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("SCH, , , ,employeeNum,15123099");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p) {
    vector<string> strs = { "employeeNum", "15123099" };
    ParsedCmd expected(CmdType::DEL, true, false, false, false, false, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("DEL,-p, , ,employeeNum,15123099");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p_f_name) {
    vector<string> strs = { "name", "ABCD" };
    ParsedCmd expected(CmdType::DEL, true, true, false, false, false, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("DEL,-p,-f, ,name,ABCD");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p_l_name) {
    vector<string> strs = { "name", "ABCD" };
    ParsedCmd expected(CmdType::DEL, true, false, true, false, false, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("DEL,-p,-l, ,name,ABCD");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p_m_phonenum) {
    vector<string> strs = { "phoneNum", "1234" };
    ParsedCmd expected(CmdType::DEL, true, false, false, true, false, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("DEL,-p,-m, ,phoneNum,1234");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p_l_phonenum) {
    vector<string> strs = { "phoneNum", "1234" };
    ParsedCmd expected(CmdType::DEL, true, false, false, false, true, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("DEL,-p,-l, ,phoneNum,1234");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p_y_birthday) {
    vector<string> strs = { "birthday", "2000" };
    ParsedCmd expected(CmdType::DEL, true, false, false, false, false, true, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("DEL,-p,-y, ,birthday,2000");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p_m_birthday) {
    vector<string> strs = { "birthday", "08" };
    ParsedCmd expected(CmdType::DEL, true, false, false, false, false, false, true, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("DEL,-p,-m, ,birthday,08");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p_d_birthday) {
    vector<string> strs = { "birthday", "31" };
    ParsedCmd expected(CmdType::DEL, true, false, false, false, false, false, false, true, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("DEL,-p,-d, ,birthday,31");
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p_l_mod_name_phonenum) {
    vector<string> strs = { "name", "ABCD", "phoneNum", "010-1234-4563" };
    ParsedCmd expected(CmdType::MOD, true, false, true, false, false, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("MOD,-p,-l, ,name,ABCD,phoneNum,010-1234-4563");
    EXPECT_EQ(cmd.lastNumFlag, expected.lastNumFlag);
    EXPECT_EQ(cmd.lastNameFlag, expected.lastNameFlag);
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p_l_mod_phonenum_name) {
    vector<string> strs = { "phoneNum", "010-1234-4563", "name", "ABCD" };
    ParsedCmd expected(CmdType::MOD, true, false, false, false, true, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("MOD,-p,-l, ,phoneNum,010-1234-4563,name,ABCD");
    EXPECT_EQ(cmd.lastNumFlag, expected.lastNumFlag);
    EXPECT_EQ(cmd.lastNameFlag, expected.lastNameFlag);
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p_m_mod_phonenum_birthday) {
    vector<string> strs = { "phoneNum", "1234","birthday", "20000101" };
    ParsedCmd expected(CmdType::MOD, true, false, false, true, false, false, false, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("MOD,-p,-m, ,phoneNum,1234,birthday,20000101");
    EXPECT_EQ(cmd.midNumFlag, expected.midNumFlag);
    EXPECT_EQ(cmd.monthFlag, expected.monthFlag);
    EXPECT_EQ(true, (cmd == expected));
}

TEST(IO_Test, option_parsing_test_p_m_mod_birthday_phonenum) {
    vector<string> strs = { "birthday", "12", "phoneNum", "010-1234-4563" };
    ParsedCmd expected(CmdType::MOD, true, false, false, false, false, false, true, false, strs);
    Parser parser;
    ParsedCmd cmd = parser.parse("MOD,-p,-m, ,birthday,12,phoneNum,010-1234-4563");
    EXPECT_EQ(cmd.midNumFlag, expected.midNumFlag);
    EXPECT_EQ(cmd.monthFlag, expected.monthFlag);
    EXPECT_EQ(true, (cmd == expected));
}
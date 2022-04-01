#include "pch.h"
#include "../E-Project/main.cpp"
#include "../E-Project/deleteCommand.h"
#include "../E-Project/addCommand.h"
#include "../E-Project/modifyCommand.h"
#include "../E-Project/searchCommand.h"


class AddTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {

    }
    virtual void TearDown() override
    {
        for (Employee* em : list)
        {
            delete em;
        }
        list.clear();
    }

    addCommand addCmd;
};

TEST_F(AddTest, BasicAddCase) {

    EXPECT_EQ(addCmd.add_employee(list, getCmdParam("ADD, , , ,15120999,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV")), 0);
    EXPECT_EQ(addCmd.add_employee(list, getCmdParam("ADD, , , ,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO")), 0);
    EXPECT_EQ(addCmd.add_employee(list, getCmdParam("ADD, , , ,18115050,TTETHU HBO,CL3,010-4581-2050,20080718,ADV")), 0);
}

TEST_F(AddTest, SameAddCase) {

    //같은 사번
    EXPECT_EQ(addCmd.add_employee(list, getCmdParam("ADD, , , ,88114052,NQ LVARW,CL4,010-4528-0959,19911021,PRO")), 0);
    EXPECT_EQ(addCmd.add_employee(list, getCmdParam("ADD, , , ,88114052,SRERLALH HMEF,CL2,010-0991-9521,19640910,PRO")), -1);
}

TEST_F(AddTest, NullAddCase) {

    //비어있는 정보가 있는 경우
    EXPECT_EQ(addCmd.add_employee(list, getCmdParam("ADD, , , ,,VSID TVO,CL1,010-3669-1077,20120718,PRO")), -1);
    EXPECT_EQ(addCmd.add_employee(list, getCmdParam("ADD, , , ,17111236,,010-3669-1077,20120718,PRO")), -1);
    EXPECT_EQ(addCmd.add_employee(list, getCmdParam("ADD, , , ,17111236,VSID TVO,,010-3669-1077,20120718,PRO")), -1);
    EXPECT_EQ(addCmd.add_employee(list, getCmdParam("ADD, , , ,17111236,VSID TVO,CL1,,20120718,PRO")), -1);
    EXPECT_EQ(addCmd.add_employee(list, getCmdParam("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,,PRO")), -1);
    EXPECT_EQ(addCmd.add_employee(list, getCmdParam("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,20120718,")), -1);
}

class ModTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        list.push_back(new Employee{ "18050301","KYUMOK KIM","CL2","010-9777-6055","19980906","PRO" });
        list.push_back(new Employee{ "18050302","SEUNGWOO HYUN","CL3","010-1111-2233","19900302","PRO" });
    }

    virtual void TearDown() override
    {
        for (Employee* em : list)
        {
            delete em;
        }
        list.clear();
    }

    modifyCommand modCmd;
};

TEST_F(ModTest, mod_with_name) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "KYUMOK KIM");
    EXPECT_EQ(list[1]->name, "SEUNGWOO HYUN");

    string result = modCmd.modify_employee(list, CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"employeeNum", "18050301", "phoneNum", "010-0000-0000"}});
    EXPECT_EQ(result, "MOD,1\n");

    result = modCmd.modify_employee(list, CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"name", "SEUNGWOO HYUN", "certi", "EX"} });
    EXPECT_EQ(result, "MOD,1\n");
}


class DeleteTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        list.push_back(new Employee{ "18091234", "LALALA HELLO", "CL2", "010-9876-4321", "19890509", "PRO" });
        list.push_back(new Employee{ "12345678", "JAY HELLO", "CL3", "010-1234-1234", "19901231", "EX" });
    }

    virtual void TearDown() override
    {
        for (Employee* em : list)
        {
            delete em;
        }
        list.clear();
    }

    deleteCommand delCmd;
};

TEST_F(DeleteTest, delete_with_name) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"}});
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"name", "LALALA HELLO"} });
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_cl) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_phonenumber) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"phoneNum", "010-9876-4321"} });
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_birthday) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"birthday", "20210101"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"birthday", "19890509"} });
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_name_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"name", "LALALA HELLO"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_cl_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"phoneNum", "010-9876-4321"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_birthday_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"birthday", "20210101"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"birthday", "19890509"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_name_option_f) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,true,false,false,false,false,false,false,{"name", "HIBONG"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,true,false,false,false,false,false,false,{"name", "LALALA"} });
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_name_option_l) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,false,true,false,false,false,false,false,{"name", "HWANG"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,true,false,false,false,false,false,{"name", "HELLO"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\nDEL,12345678,JAY HELLO,CL3,010-1234-1234,19901231,EX\n");
    EXPECT_EQ(list.size(), 0);
}

TEST_F(DeleteTest, delete_with_phonenumber_option_m) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,false,false,true,false,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,true,false,false,false,false,{"phoneNum","9876"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_l) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,false,false,false,false,true,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,true,false,false,false,{"phoneNum","4321"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_birthday_option_y) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,true,false,false,{"birthday","2000"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,true,false,false,{"birthday","1989"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_birthday_option_m) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");
    
    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,true,false,{"birthday","08"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,true,false,{"birthday","05"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_birthday_option_d) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,true,{"birthday","20"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delCmd.delete_employee(list, CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,true,{"birthday","09"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

class SchTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp() override
    {
        list.push_back(new Employee{ "1700000","홍 길동","CL2","010-1111-2222","19900302","ADV" });
        list.push_back(new Employee{ "1700001","홍 길훈","CL3","010-1111-2233","19900302","PRO" });
        list.push_back(new Employee{ "1700002","홍 길순","CL2","010-1111-2244","19900306","ADV" });
    }
    virtual void TearDown() override
    {
        for (Employee* em : list)
        {
            delete em;
        }
        list.clear();
    }

    searchCommand schCmd;
};

TEST_F(SchTest, sch_none) {
    EXPECT_EQ(schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"employeeNum","1700333"} }), "SCH,NONE\n");
    EXPECT_EQ(schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"name","이 순신"} }), "SCH,NONE\n");
    EXPECT_EQ(schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"phoneNum","013-2222-3333"} }), "SCH,NONE\n");
    EXPECT_EQ(schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"cl","CL6"} }), "SCH,NONE\n");
    EXPECT_EQ(schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"certi","GOLD"} }), "SCH,NONE\n");
    EXPECT_EQ(schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"birthday","15930303"} }), "SCH,NONE\n");
}


TEST_F(SchTest, sch_with_name) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"name", "홍 길동"} });
    EXPECT_EQ(result, "SCH,1\n");
}

TEST_F(SchTest, sch_with_cl) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "SCH,2\n");
}

TEST_F(SchTest, sch_with_birthday) {
    EXPECT_EQ(schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"birthday","19900302"} }), "SCH,2\n");
    EXPECT_EQ(schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"birthday","19900306"} }), "SCH,1\n");
}

TEST_F(SchTest, sch_with_phonenumber) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"phoneNum", "010-1111-2222"} });
    EXPECT_EQ(result, "SCH,1\n");
}

TEST_F(SchTest, sch_with_name_option_p) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"name", "홍 길동"} });
    EXPECT_EQ(result, "SCH,1700000,홍 길동,CL2,010-1111-2222,19900302,ADV\n");
}

TEST_F(SchTest, sch_with_cl_option_p) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "SCH,1700000,홍 길동,CL2,010-1111-2222,19900302,ADV\nSCH,1700002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_phonenumber_option_p) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"phoneNum", "010-1111-2244"} });
    EXPECT_EQ(result, "SCH,1700002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_birthday_option_p) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"birthday", "20210101"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,false,{"birthday", "19900306"} });
    EXPECT_EQ(result, "SCH,1700002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_name_option_f) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,true,false,false,false,false,false,false,{"name", "HIBONG"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,true,false,false,false,false,false,false,{"name", "홍"} });
    EXPECT_EQ(result, "SCH,3\n");
}

TEST_F(SchTest, sch_with_name_option_l) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,true,false,false,false,false,false,{"name", "HWANG"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,true,false,false,false,false,false,{"name", "길동"} });
    EXPECT_EQ(result, "SCH,1700000,홍 길동,CL2,010-1111-2222,19900302,ADV\n");
}

TEST_F(SchTest, sch_with_phonenumber_option_m) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,true,false,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,true,false,false,false,false,{"phoneNum","1111"} });
    EXPECT_EQ(result, "SCH,1700000,홍 길동,CL2,010-1111-2222,19900302,ADV\nSCH,1700001,홍 길훈,CL3,010-1111-2233,19900302,PRO\nSCH,1700002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_phonenumber_option_l) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,false,false,false,false,true,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,true,false,false,false,{"phoneNum","2244"} });
    EXPECT_EQ(result, "SCH,1700002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_birthday_option_y) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,true,false,false,{"birthday","2000"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,true,false,false,{"birthday","1990"} });
    EXPECT_EQ(result, "SCH,1700000,홍 길동,CL2,010-1111-2222,19900302,ADV\nSCH,1700001,홍 길훈,CL3,010-1111-2233,19900302,PRO\nSCH,1700002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_birthday_option_m) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,true,false,{"birthday","08"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,true,false,{"birthday","03"} });
    EXPECT_EQ(result, "SCH,1700000,홍 길동,CL2,010-1111-2222,19900302,ADV\nSCH,1700001,홍 길훈,CL3,010-1111-2233,19900302,PRO\nSCH,1700002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST_F(SchTest, sch_with_birthday_option_d) {
    string result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,true,{"birthday","20"} });
    EXPECT_EQ(result, "SCH,NONE\n");

    result = schCmd.search_employee(list, CmdParam{ CmdType::SCH,true,false,false,false,false,false,false,true,{"birthday","06"} });
    EXPECT_EQ(result, "SCH,1700002,홍 길순,CL2,010-1111-2244,19900306,ADV\n");
}

TEST(IO_Test, InputTest_getCmdParam) {
    CmdParam cmd;
    CmdParam fake;
    vector<string> strs;
    cmd = getCmdParam("ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");
    strs.push_back("15123099");
    strs.push_back("VXIHXOTH JHOP");
    strs.push_back("CL3");
    strs.push_back("010-3112-2609");
    strs.push_back("19771211");
    strs.push_back("ADV");
    fake.set(CmdType::ADD, false, false, false, false, false, false, false, false, strs);
    EXPECT_EQ(true, (cmd == fake));
}
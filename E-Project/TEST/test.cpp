#include "pch.h"
#include "../E-Project/main.cpp"

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
};

TEST_F(AddTest, BasicAddCase) {

	EXPECT_EQ(add_employee("ADD, , , ,15120999,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV"), 0);
	EXPECT_EQ(add_employee("ADD, , , ,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO"), 0);
	EXPECT_EQ(add_employee("ADD, , , ,18115050,TTETHU HBO,CL3,010-4581-2050,20080718,ADV"), 0);
}

TEST_F(AddTest, SameAddCase) {

	//같은 사번
	EXPECT_EQ(add_employee("ADD, , , ,88114052,NQ LVARW,CL4,010-4528-0959,19911021,PRO"), 0);
	EXPECT_EQ(add_employee("ADD, , , ,88114052,SRERLALH HMEF,CL2,010-0991-9521,19640910,PRO"), -1);
}

TEST_F(AddTest, NullAddCase) {

	//비어있는 정보가 있는 경우
	EXPECT_EQ(add_employee("ADD, , , ,,VSID TVO,CL1,010-3669-1077,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,,010-3669-1077,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,,010-3669-1077,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,CL1,,20120718,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,,PRO"), -1);
	EXPECT_EQ(add_employee("ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,20120718,"), -1);
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
protected:
};

TEST_F(ModTest, mod_with_name) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "KYUMOK KIM");
    EXPECT_EQ(list[1]->name, "SEUNGWOO HYUN");

    string result = mod_empolyee(CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"employeeNum", "18050301", "phoneNum", "010-0000-0000"}});
    EXPECT_EQ(result, "MOD,1\n");

    result = mod_empolyee(CmdParam{ CmdType::MOD,false,false,false,false,false,false,false,false,{"name", "SEUNGWOO HYUN", "certi", "EX"} });
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
protected:
};

TEST_F(DeleteTest, delete_with_name) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"}});
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"name", "LALALA HELLO"} });
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_cl) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_phonenumber) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"phoneNum", "010-9876-4321"} });
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_birthday) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"birthday", "20210101"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,false,false,false,false,false,false,false,false,{"birthday", "19890509"} });
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_name_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"name", "HIBONG HWANG"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"name", "LALALA HELLO"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_cl_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"cl", "CL4"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"cl", "CL2"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"phoneNum", "010-4567-5678"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"phoneNum", "010-9876-4321"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_birthday_option_p) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"birthday", "20210101"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,false,{"birthday", "19890509"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_name_option_f) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,false,true,false,false,false,false,false,false,{"name", "HIBONG"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,false,true,false,false,false,false,false,false,{"name", "LALALA"} });
    EXPECT_EQ(result, "DEL,1\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_name_option_l) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,false,false,true,false,false,false,false,false,{"name", "HWANG"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,true,false,false,false,false,false,{"name", "HELLO"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\nDEL,12345678,JAY HELLO,CL3,010-1234-1234,19901231,EX\n");
    EXPECT_EQ(list.size(), 0);
}

TEST_F(DeleteTest, delete_with_phonenumber_option_m) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,false,false,false,true,false,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,true,false,false,false,false,{"phoneNum","9876"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_phonenumber_option_l) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,false,false,false,false,true,false,false,false,{"phoneNum","7894"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,true,false,false,false,{"phoneNum","4321"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_birthday_option_y) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,true,false,false,{"birthday","2000"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,true,false,false,{"birthday","1989"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_birthday_option_m) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");
    
    string result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,true,false,{"birthday","08"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,true,false,{"birthday","05"} });
    EXPECT_EQ(result, "DEL,18091234,LALALA HELLO,CL2,010-9876-4321,19890509,PRO\n");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0]->name, "JAY HELLO");
}

TEST_F(DeleteTest, delete_with_birthday_option_d) {
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0]->name, "LALALA HELLO");
    EXPECT_EQ(list[1]->name, "JAY HELLO");

    string result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,true,{"birthday","20"} });
    EXPECT_EQ(result, "DEL,NONE\n");
    EXPECT_EQ(list.size(), 2);

    result = delete_empolyee(CmdParam{ CmdType::DEL,true,false,false,false,false,false,false,true,{"birthday","09"} });
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
};

TEST_F(SchTest, SearchBirthDay) {
    EXPECT_EQ(sch_employee(CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"birthday","19900302"} }), "SCH,2");
    EXPECT_EQ(sch_employee(CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"birthday","19900306"} }), "SCH,1");
}

TEST_F(SchTest, SearchNone) {
    EXPECT_EQ(sch_employee(CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"name","이순신"} }), "SCH,NONE");
    EXPECT_EQ(sch_employee(CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"phoneNum","013-2222-3333"} }), "SCH,NONE");
    EXPECT_EQ(sch_employee(CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"cl","CL6"} }), "SCH,NONE");
    EXPECT_EQ(sch_employee(CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"certi","GOLD"} }), "SCH,NONE");
    EXPECT_EQ(sch_employee(CmdParam{ CmdType::SCH,false,false,false,false,false,false,false,false,{"birthday","15930303"} }), "SCH,NONE");
}

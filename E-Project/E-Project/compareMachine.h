#ifndef __COMPARE_MACHINE__
#define __COMPARE_MACHINE__

#include <string>
#include "parsedCommandType.h"

class Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) = 0;
private:
};

class EmployeeNumberComparemachine : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (value == em->employeeNum);
    }
private:
};

class NameComparemachine : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->name == value);
    }
private:
};

class FirstNameComparemachine : public NameComparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->name.substr(0, em->name.find(' ')) == value);
    }
private:
};

class LastNameComparemachine : public NameComparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->name.substr(em->name.find(' ') + 1, em->name.length() - em->name.find(' ')) == value);
    }
private:
};

class CareerLevelComparemachine : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->cl == value);
    }
private:
};

class PhoneNumberComparemachine : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->phoneNum == value);
    }
private:
};

class MiddlePhoneNumberComparemachine : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->phoneNum.substr(4, 4) == value);
    }
private:
};

class LastPhoneNumberComparemachine : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->phoneNum.substr(9, 4) == value);
    }
private:
};

class BirthdayComparemachine : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->birthday == value);
    }
private:
};

class BirthdayYearComparemachine : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->birthday.substr(0, 4) == value);
    }
private:
};

class BirthdayMonthComparemachine : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->birthday.substr(4, 2) == value);
    }
private:
};

class BirthdayDayComparemachine : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->birthday.substr(6, 2) == value);
    }
private:
};

class CertiComparemachine : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(const Employee* em, const string value) override
    {
        return (em->certi == value);
    }
private:
};

#endif
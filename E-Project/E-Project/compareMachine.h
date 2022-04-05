#ifndef __COMPARE_MACHINE__
#define __COMPARE_MACHINE__

#include <string>
#include "parcedCommandType.h"

class Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) = 0;
private:
};

class ComparemachineWithEmployeeNumber : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (value == em->employeeNum);
    }
private:
};

class ComparemachineWithName : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->name == value);
    }
private:
};

class ComparemachineWithFirstName : public ComparemachineWithName
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->name.substr(0, em->name.find(' ')) == value);
    }
private:
};

class ComparemachineWithLastName : public ComparemachineWithName
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->name.substr(em->name.find(' ') + 1, em->name.length() - em->name.find(' ')) == value);
    }
private:
};

class ComparemachineWithCL : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->cl == value);
    }
private:
};

class ComparemachineWithPhoneNumber : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->phoneNum == value);
    }
private:
};

class ComparemachineWithPhoneNumberOnlyMiddle : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->phoneNum.substr(4, 4) == value);
    }
private:
};

class ComparemachineWithPhoneNumberOnlyLast : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->phoneNum.substr(9, 4) == value);
    }
private:
};

class ComparemachineWithBirthday : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->birthday == value);
    }
private:
};

class ComparemachineWithBirthdayOnlyYear : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->birthday.substr(0, 4) == value);
    }
private:
};

class ComparemachineWithBirthdayOnlyMonth : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->birthday.substr(4, 2) == value);
    }
private:
};

class ComparemachineWithBirthdayOnlyDay : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->birthday.substr(6, 2) == value);
    }
private:
};

class ComparemachineWithCerti : public Comparemachine
{
public:
    virtual bool isSatifiedEntry(Employee* em, string value) override
    {
        return (em->certi == value);
    }
private:
};

#endif
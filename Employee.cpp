//
// Created by Muhammad Ghanayem on 23/04/2022.
//

#include "Employee.h"

Employee::Employee(int employee_id1, int salary1, int grade1, int company_id1,bool initial,
                   std::shared_ptr<int> company_id_ptr):
        employee_id(employee_id1),salary(salary1),grade(grade1),company_id(nullptr)
{
    if (initial)
    {
        company_id = std::make_shared<int>(company_id1);
    }
    else
    {
        company_id = company_id_ptr;
    }
}

Employee::Employee(int employee_id):employee_id(employee_id),salary(0), grade(0),company_id(nullptr){}


void Employee::count(const Employee &employee1, int min_salary, int min_grade,int *total_num, int *num)
{
    (*total_num)++;
    if (employee1.salary >= min_salary && employee1.grade >= min_grade)
    {
        (*num)++;
    }
}

void Employee::updateCompanyId(Employee &employee1, int company_id1)
{
    *(employee1.company_id) = company_id1;
}

bool operator<(const Employee& employee1, const Employee& employee2)
{
    if (employee1.employee_id >= employee2.employee_id)
    {
        return false;
    }
    return true;
}

bool operator>(const Employee& employee1, const Employee& employee2)
{
    if (employee1.employee_id <= employee2.employee_id)
    {
        return false;
    }
    return true;
}

bool operator==(const Employee& employee1, const Employee& employee2)
{
    if (employee1.employee_id == employee2.employee_id)
    {
        return true;
    }
    return false;
}

bool operator!=(const Employee& employee1, const Employee& employee2)
{
    if (employee1 == employee2)
    {
        return false;
    }
    return true;
}

bool operator>=(const Employee& employee1, const Employee& employee2)
{
    if (employee1 < employee2)
    {
        return false;
    }
    return true;
}

bool operator<=(const Employee& employee1, const Employee& employee2)
{
    if (employee1 > employee2)
    {
        return false;
    }
    return true;
}

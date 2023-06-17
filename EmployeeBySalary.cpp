//
// Created by Muhammad Ghanayem on 23/04/2022.
//

#include "EmployeeBySalary.h"

EmployeeBySalary::EmployeeBySalary(int employee_id1,int salary1):employee_id(employee_id1),salary(salary1){}

void EmployeeBySalary::store(const EmployeeBySalary &employee1, int *array, int *index)
{
    array[*index] = employee1.employee_id;
    (*index)++;
}

bool operator<(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2)
{
    if (employee1.employee_id == employee2.employee_id)
    {
        return false;
    }
    return employee1.salary != employee2.salary ?
           employee1.salary < employee2.salary : employee1.employee_id > employee2.employee_id;
}

bool operator>(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2)
{
    if (employee1.employee_id == employee2.employee_id)
    {
        return false;
    }
    return employee1.salary != employee2.salary ?
           employee1.salary > employee2.salary : employee1.employee_id < employee2.employee_id;
}

bool operator==(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2)
{
    return (employee1.salary == employee2.salary) && (employee1.employee_id == employee2.employee_id);
}

bool operator!=(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2)
{
    if (employee1 == employee2)
    {
        return false;
    }
    return true;
}

bool operator>=(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2)
{
    if (employee1 < employee2)
    {
        return false;
    }
    return true;
}

bool operator<=(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2)
{
    if (employee1 > employee2)
    {
        return false;
    }
    return true;
}

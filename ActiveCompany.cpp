//
// Created by Muhammad Ghanayem on 23/04/2022.
//

#include "ActiveCompany.h"


ActiveCompany::ActiveCompany(int company_id1):company_id(company_id1)
{
    employees_by_salary = std::make_shared<AvlTree<EmployeeBySalary>>();
    employees = std::make_shared<AvlTree<Employee>>();
}

void ActiveCompany::store(const ActiveCompany &active_company1, int *array, int *index)
{
    array[*index] = active_company1.employees_by_salary->getMax()->getValue().employee_id;
    (*index)++;
}

bool operator<(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2)
{
    if (activeCompany1.company_id >= activeCompany2.company_id)
    {
        return false;
    }
    return true;
}

bool operator>(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2)
{
    if (activeCompany1.company_id <= activeCompany2.company_id)
    {
        return false;
    }
    return true;
}

bool operator==(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2)
{
    if (activeCompany1.company_id == activeCompany2.company_id)
    {
        return true;
    }
    return false;
}

bool operator!=(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2)
{
    if (activeCompany1 == activeCompany2)
    {
        return false;
    }
    return true;
}

bool operator>=(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2)
{
    if (activeCompany1 < activeCompany2)
    {
        return false;
    }
    return true;
}

bool operator<=(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2)
{
    if (activeCompany1 > activeCompany2)
    {
        return false;
    }
    return true;
}

//
// Created by Muhammad Ghanayem on 23/04/2022.
//

#ifndef ACTIVECOMPANY_H_
#define ACTIVECOMPANY_H_

#include <iostream>
#include "AvlTree.h"
#include "EmployeeBySalary.h"
#include "Employee.h"

class ActiveCompany
{
public:
    int company_id;
    std::shared_ptr<AvlTree<EmployeeBySalary>> employees_by_salary;
    std::shared_ptr<AvlTree<Employee>> employees;
    explicit ActiveCompany(int company_id1);
    ~ActiveCompany() = default;
    ActiveCompany(const ActiveCompany& other) = default;
    ActiveCompany& operator=(const ActiveCompany& other) = default;
    static void store(const ActiveCompany& active_company1, int *array, int *index);
};

bool operator<(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2);
bool operator>(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2);
bool operator==(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2);
bool operator>=(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2);
bool operator<=(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2);
bool operator!=(const ActiveCompany& activeCompany1, const ActiveCompany& activeCompany2);

#endif //ACTIVECOMPANY_H_

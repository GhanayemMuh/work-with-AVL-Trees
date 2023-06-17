//
// Created by Muhammad Biadsy on 23/04/2022.
//

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <iostream>
#include <memory>


class Employee {
public:
    int employee_id;
    int salary;
    int grade;
    std::shared_ptr<int> company_id;
    explicit Employee(int employee_id);
    Employee() = default;
    Employee(int employee_id1, int salary1, int grade1, int company_id1,bool initial = false,
             std::shared_ptr<int> company_id_ptr = nullptr);
    ~Employee() = default;
    Employee(const Employee& other) = default;
    Employee& operator=(const Employee& other) = default;
    static void count(const Employee& employee1,int min_salary,int min_grade,int* total_num,int* num);
    static void updateCompanyId(Employee& employee1,int company_id1);
};

bool operator<(const Employee& employee1, const Employee& employee2);
bool operator>(const Employee& employee1, const Employee& employee2);
bool operator==(const Employee& employee1, const Employee& employee2);
bool operator>=(const Employee& employee1, const Employee& employee2);
bool operator<=(const Employee& employee1, const Employee& employee2);
bool operator!=(const Employee& employee1, const Employee& employee2);


#endif //EMPLOYEE_H_

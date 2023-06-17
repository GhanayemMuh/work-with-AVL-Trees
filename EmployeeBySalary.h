//
// Created by Muhammad Ghanayem on 23/04/2022.
//

#ifndef EMPLOYEEBYSALARY_H_
#define EMPLOYEEBYSALARY_H_

#include <iostream>
#include <memory>

class EmployeeBySalary {
public:
    int employee_id;
    int salary;
    EmployeeBySalary(int employee_id1,int salary1);
    EmployeeBySalary() = default;
    ~EmployeeBySalary() = default;
    EmployeeBySalary(const EmployeeBySalary& other) = default;
    EmployeeBySalary& operator=(const EmployeeBySalary& other) = default;
    static void store(const EmployeeBySalary& employee1,int *array,int* index);
};

bool operator<(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2);
bool operator>(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2);
bool operator==(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2);
bool operator!=(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2);
bool operator>=(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2);
bool operator<=(const EmployeeBySalary& employee1, const EmployeeBySalary& employee2);


#endif //EMPLOYEEBYSALARY_H_

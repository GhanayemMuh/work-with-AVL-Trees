//
// Created by Muhammad Ghanayem on 20/04/2022.
//

#ifndef EMPLOYEEMANAGER_H_
#define EMPLOYEEMANAGER_H_

#include <iostream>
#include <memory>
#include <stdio.h>
#include "library1.h"
#include "AvlTree.h"
#include "Vertex.h"
#include "Company.h"
#include "Employee.h"
#include "EmployeeBySalary.h"
#include "ActiveCompany.h"

class EmployeeManager {
    AvlTree<Company> companies;
    AvlTree<ActiveCompany> active_companies;
    AvlTree<Employee> employees;
    AvlTree<EmployeeBySalary> employees_by_salary;
public:
    EmployeeManager();
    ~EmployeeManager() = default;
    EmployeeManager(const EmployeeManager& other) = default;
    EmployeeManager& operator=(const EmployeeManager& other) = default;
    StatusType AddCompany(int CompanyID, int Value);
    StatusType AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);
    StatusType RemoveCompany(int CompanyID);
    StatusType RemoveEmployee(int EmployeeID);
    StatusType GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);
    StatusType GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade);
    StatusType IncreaseCompanyValue(int CompanyID, int ValueIncrease);
    StatusType PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);
    StatusType HireEmployee(int EmployeeID, int NewCompanyID);
    StatusType AcquireCompany(int AcquirerID, int TargetID, double Factor);
    StatusType GetHighestEarner(int CompanyID, int *EmployeeID);
    StatusType GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees);
    StatusType GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);
    StatusType GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,int MinSalary,
                                       int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);
};

#endif //EMPLOYEEMANAGER_H_

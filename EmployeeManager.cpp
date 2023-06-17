//
// Created by Muhammad Ghanayem on 20/04/2022.
//

#include "EmployeeManager.h"


EmployeeManager::EmployeeManager():companies(),employees(),employees_by_salary(){}

StatusType EmployeeManager::AddCompany(int CompanyID, int Value)
{
    if (CompanyID <= 0 || Value <= 0)
    {
        return INVALID_INPUT;
    }
    Company company(CompanyID,Value);
    try
    {
        companies.insert(company);
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch (Failure&)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType EmployeeManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade)
{
    if(EmployeeID <=0 || CompanyID <=0 || Salary <=0 || Grade < 0)
    {
        return INVALID_INPUT;
    }
    ActiveCompany* company = active_companies.getPtrValue(ActiveCompany(CompanyID));
    if (!companies.getPtrValue(Company(CompanyID)) ||
        employees.getPtrValue(Employee(EmployeeID)))
    {
        return FAILURE;
    }
    try
    {
        Employee employee(EmployeeID,Salary,Grade,CompanyID, true);
        EmployeeBySalary employee_by_salary(EmployeeID,Salary);
        if (!company)
        {
            ActiveCompany add(CompanyID);
            add.employees_by_salary->insert(employee_by_salary);
            add.employees->insert(employee);
            active_companies.insert(add);
            employees.insert(employee);
            employees_by_salary.insert(employee_by_salary);
        }
        else
        {
            company->employees_by_salary->insert(employee_by_salary);
            company->employees->insert(employee);
            employees_by_salary.insert(employee_by_salary);
            employees.insert(employee);
        }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch (Failure&)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType EmployeeManager::RemoveEmployee(int EmployeeID)
{
    if(EmployeeID <=0)
    {
        return INVALID_INPUT;
    }
    Employee* employee = employees.getPtrValue(Employee(EmployeeID));
    if(!employee)
    {
        return FAILURE;
    }
    try
    {
        ActiveCompany* company = active_companies.getPtrValue(ActiveCompany(*employee->company_id));
        company->employees_by_salary->remove(EmployeeBySalary(EmployeeID,employee->salary));
        company->employees->remove(*employee);
        employees_by_salary.remove(EmployeeBySalary(EmployeeID,employee->salary));
        employees.remove(*employee);
        if (!company->employees_by_salary->getSize() || !company->employees->getSize())
        {
            active_companies.remove(*company);
        }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch(Failure&)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType EmployeeManager::RemoveCompany(int CompanyID)
{
    if(CompanyID <=0)
    {
        return INVALID_INPUT;
    }
    ActiveCompany* active_to_remove = active_companies.getPtrValue(ActiveCompany(CompanyID));
    if(active_to_remove)
    {
        return FAILURE;
    }
    try
    {
        companies.remove(Company(CompanyID));
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch(Failure&)
    {
        return FAILURE;
    }
    return SUCCESS;
}


StatusType EmployeeManager::GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees)
{
    if (!Value || !NumEmployees || CompanyID <= 0)
    {
        return INVALID_INPUT;
    }
    Company* company = companies.getPtrValue(Company(CompanyID));
    ActiveCompany* active_company = active_companies.getPtrValue(ActiveCompany(CompanyID));
    if (!company)
    {
        return FAILURE;
    }
    try
    {
        *Value = company->value;
        if (!active_company)
        {
            *NumEmployees = 0;
        }
        else
        {
            *NumEmployees = active_company->employees_by_salary->getSize();
        }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType EmployeeManager::GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade)
{
    if (!EmployerID || !Salary || !Grade || EmployeeID <= 0)
    {
        return INVALID_INPUT;
    }
    Employee* employee = employees.getPtrValue(Employee(EmployeeID));
    if (!employee)
    {
        return FAILURE;
    }
    try
    {
        *EmployerID = *employee->company_id;
        *Salary = employee->salary;
        *Grade = employee->grade;
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType EmployeeManager::IncreaseCompanyValue(int CompanyID, int ValueIncrease)
{
    if (CompanyID <= 0 || ValueIncrease <= 0)
    {
        return INVALID_INPUT;
    }
    Company* company = companies.getPtrValue(Company(CompanyID));
    if (!company)
    {
        return FAILURE;
    }
    try
    {
        company->value += ValueIncrease;
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType EmployeeManager::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    if(EmployeeID <=0 || SalaryIncrease <=0)
    {
        return INVALID_INPUT;
    }
    Employee* employee = employees.getPtrValue(Employee(EmployeeID));
    if (!employee)
    {
        return FAILURE;
    }
    try
    {
        ActiveCompany* company = active_companies.getPtrValue(ActiveCompany(*employee->company_id));
        Employee* company_employee = company->employees->getPtrValue(*employee);
        employees_by_salary.remove(EmployeeBySalary(EmployeeID,employee->salary));
        company->employees_by_salary->remove(EmployeeBySalary(EmployeeID,employee->salary));
        employee->salary += SalaryIncrease;
        company_employee->salary += SalaryIncrease;
        employees_by_salary.insert(EmployeeBySalary(EmployeeID,employee->salary));
        company->employees_by_salary->insert(EmployeeBySalary(EmployeeID,employee->salary));
        if (BumpGrade > 0)
        {
            (employee->grade)++;
            (company_employee->grade)++;
        }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch(Failure&)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType EmployeeManager::HireEmployee(int EmployeeID, int NewCompanyID)
{
    if (EmployeeID <= 0 || NewCompanyID <= 0)
    {
        return INVALID_INPUT;
    }
    Employee* employee = employees.getPtrValue(Employee(EmployeeID));
    Company* new_company = companies.getPtrValue(Company(NewCompanyID));
    if (!employee || *employee->company_id == NewCompanyID || !new_company)
    {
        return FAILURE;
    }
    try
    {
        ActiveCompany* active_old_company = active_companies.getPtrValue(ActiveCompany(
                *employee->company_id));
        active_old_company->employees_by_salary->remove(EmployeeBySalary(employee->employee_id,
                                                                           employee->salary));
        active_old_company->employees->remove(Employee(EmployeeID));
        if (!active_old_company->employees->getSize())
        {
            active_companies.remove(*active_old_company);
        }
        *employee->company_id = NewCompanyID;
        ActiveCompany* active_new_company = active_companies.getPtrValue(ActiveCompany(NewCompanyID));
        if (!active_new_company)
        {
            ActiveCompany add(NewCompanyID);
            add.employees_by_salary->insert(EmployeeBySalary(EmployeeID,employee->salary));
            add.employees->insert(*employee);
            active_companies.insert(add);
        }
        else
        {
            active_new_company->employees_by_salary->insert(EmployeeBySalary(EmployeeID,
                                                                             employee->salary));
            active_new_company->employees->insert(*employee);
        }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch(Failure&)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType EmployeeManager::AcquireCompany(int AcquirerID, int TargetID, double Factor)
{
    if (AcquirerID <= 0 || TargetID <= 0 || AcquirerID==TargetID || Factor < 1)
    {
        return INVALID_INPUT;
    }
    Company* acquirer = companies.getPtrValue(Company(AcquirerID));
    Company* target = companies.getPtrValue(Company(TargetID));
    if (!acquirer || !target || (acquirer->value < (10*target->value)))
    {
        return FAILURE;
    }
    ActiveCompany* active_acquirer = active_companies.getPtrValue(ActiveCompany(AcquirerID));
    ActiveCompany* active_target = active_companies.getPtrValue(ActiveCompany(TargetID));
    try
    {
        if (active_target)         //t is the abbreviation of the word target
        {
            std::shared_ptr<AvlTree<EmployeeBySalary>> t_employees_by_salary = active_target->employees_by_salary;
            std::shared_ptr<AvlTree<Employee>> t_employees = active_target->employees;
            t_employees->changeField(AcquirerID,t_employees->getRoot(),Employee::updateCompanyId);
            if (!active_acquirer)
            {
                active_companies.insert(ActiveCompany(AcquirerID));
                ActiveCompany* new_acquirer = active_companies.getPtrValue(ActiveCompany(AcquirerID));
                new_acquirer->employees_by_salary = t_employees_by_salary;
                new_acquirer->employees = t_employees;
            }
            else
            {
                active_acquirer->employees_by_salary  = AvlTree<EmployeeBySalary>::mergeTrees(
                        *t_employees_by_salary,*(active_acquirer->employees_by_salary));
                active_acquirer->employees = AvlTree<Employee>::mergeTrees(*t_employees,*(active_acquirer->employees));
            }
            active_companies.remove(*active_target);
        }
        acquirer->value = (acquirer->value + target->value)*Factor;
        companies.remove(*target);
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch (Failure&)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType EmployeeManager::GetHighestEarner(int CompanyID, int *EmployeeID)
{
    if(!EmployeeID || !CompanyID)
    {
        return INVALID_INPUT;
    }
    try
    {
        if(CompanyID > 0)
        {
            ActiveCompany* company = active_companies.getPtrValue(ActiveCompany(CompanyID));
            if(!company || company->employees_by_salary->getSize() <= 0)
            {
                return FAILURE;
            }
            *EmployeeID = company->employees_by_salary->getMax()->getValue().employee_id;
        }
        else
        {
            if (employees_by_salary.getSize() <= 0)
            {
                return FAILURE;
            }
            *EmployeeID = employees_by_salary.getMax()->getValue().employee_id;
        }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType EmployeeManager::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees)
{
    if(!Employees || !NumOfEmployees || !CompanyID)
    {
        return INVALID_INPUT;
    }
    try
    {
       if(CompanyID > 0)
       {
           ActiveCompany* company = active_companies.getPtrValue(ActiveCompany(CompanyID));
           if(!company || company->employees_by_salary->getSize() <= 0)
           {
               return FAILURE;
           }
           int i=0, number = company->employees_by_salary->getSize();
           *Employees = (int*)malloc(number * sizeof(int));
           if(!*Employees)
           {
               return ALLOCATION_ERROR;
           }
           company->employees_by_salary->storeReverseInorder(company->employees_by_salary->getRoot(),
                                                             *Employees,&i,number,
                                                             EmployeeBySalary::store);
           *NumOfEmployees = number;
       }
       else
       {
           if (employees_by_salary.getSize() <= 0)
           {
               return FAILURE;
           }
           int i=0, number = employees_by_salary.getSize();
           *Employees = (int*)malloc(sizeof(int)*number);
           if(!*Employees)
           {
               return ALLOCATION_ERROR;
           }
           employees_by_salary.storeReverseInorder(employees_by_salary.getRoot(),*Employees,
                                                   &i,number,EmployeeBySalary::store);
           *NumOfEmployees = number;
       }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType EmployeeManager::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees)
{
    if(!Employees || NumOfCompanies < 1)
    {
        return INVALID_INPUT;
    }
    if(companies.getSize() < NumOfCompanies)
    {
        return FAILURE;
    }
    try
    {
        int i=0;
        *Employees = (int*)malloc(NumOfCompanies * sizeof(int));
        if(!*Employees)
        {
            return ALLOCATION_ERROR;
        }
        active_companies.storeInorder(active_companies.getRoot(),*Employees,&i,
                                      NumOfCompanies,ActiveCompany::store);
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType EmployeeManager::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary,
                                                    int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    if(!TotalNumOfEmployees || !NumOfEmployees || !CompanyID || MinEmployeeID<0 || MaxEmployeeId<0 ||
       MinSalary<0 || MinGrade<0 || MinEmployeeID > MaxEmployeeId)
    {
        return INVALID_INPUT;
    }
    try
    {
        if (CompanyID > 0)
        {
            Company* company = companies.getPtrValue(Company(CompanyID));
            ActiveCompany* active_company = active_companies.getPtrValue(ActiveCompany(CompanyID));
            if(!company || !active_company)
            {
                return FAILURE;
            }
            *TotalNumOfEmployees = 0;
            *NumOfEmployees = 0;
            active_company->employees->countWithinCondition(active_company->employees->getRoot(),
                                                            TotalNumOfEmployees,NumOfEmployees,
                                                            Employee(MinEmployeeID),
                                                            Employee(MaxEmployeeId),
                                                            MinSalary,MinGrade,Employee::count);
        }
        else
        {
            if (employees_by_salary.getSize() <= 0)
            {
                return FAILURE;
            }
            *TotalNumOfEmployees = 0;
            *NumOfEmployees = 0;
            employees.countWithinCondition(employees.getRoot(),
                                           TotalNumOfEmployees,NumOfEmployees,
                                           Employee(MinEmployeeID),
                                           Employee(MaxEmployeeId),
                                           MinSalary,MinGrade,Employee::count);
        }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

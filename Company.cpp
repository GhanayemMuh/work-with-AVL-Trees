//
// Created by Muhammad Ghanayem on 23/04/2022.
//

#include "Company.h"

Company::Company(int company_id):company_id(company_id),value(0){}

Company::Company(int company_id, int value):company_id(company_id),value(value){}

bool operator<(const Company& company1, const Company& company2)
{
    if (company1.company_id >= company2.company_id)
    {
        return false;
    }
    return true;
}

bool operator>(const Company& company1, const Company& company2)
{
    if (company1.company_id <= company2.company_id)
    {
        return false;
    }
    return true;
}

bool operator==(const Company& company1, const Company& company2)
{
    if (company1.company_id == company2.company_id)
    {
        return true;
    }
    return false;
}

bool operator!=(const Company& company1, const Company& company2)
{
    if (company1 == company2)
    {
        return false;
    }
    return true;
}

bool operator>=(const Company& company1, const Company& company2)
{
    if (company1 < company2)
    {
        return false;
    }
    return true;
}

bool operator<=(const Company& company1, const Company& company2)
{
    if (company1 > company2)
    {
        return false;
    }
    return true;
}

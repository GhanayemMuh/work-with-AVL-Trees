//
// Created by Muhammad Ghanayem on 23/04/2022.
//

#ifndef COMPANY_H_
#define COMPANY_H_

#include <iostream>

class Company{
public:
    int company_id;
    int value;
    explicit Company(int company_id);
    Company(int company_id, int value);
    ~Company() = default;
    Company(const Company& other) = default;
    Company& operator=(const Company& other) = default;
};

bool operator<(const Company& company1, const Company& company2);
bool operator>(const Company& company1, const Company& company2);
bool operator==(const Company& company1, const Company& company2);
bool operator>=(const Company& company1, const Company& company2);
bool operator<=(const Company& company1, const Company& company2);
bool operator!=(const Company& company1, const Company& company2);

#endif //COMPANY_H_

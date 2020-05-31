#pragma once
#include<iostream>
using namespace std;
#include "worker.h"


//员工类
class employee : public worker
{
public:
    employee(int id,string name,int did);
    
    //显示个人信息
    virtual void showInfo();

    //获取职工岗位名称
    virtual string getDeptName();
};

















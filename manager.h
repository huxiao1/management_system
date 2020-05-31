#pragma once
#include<iostream>
using namespace std;
#include "worker.h"

//经理类
class manager : public worker
{
public:
    manager (int id,string name,int did);

    //显示个人信息
    virtual void showInfo();

    //获取职工岗位名称
    virtual string getDeptName();
};

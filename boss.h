#pragma once
#include<iostream>
using namespace std;
#include "worker.h"

//老板类
class boss : public worker
{
public:
    boss(int id,string name,int did);

    //显示个人信息
    virtual void showInfo();

    //获取员工岗位名称
    virtual string getDeptName();
};

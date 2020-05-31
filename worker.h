#pragma once
#include<iostream>
#include<string>

using namespace std;

class worker  //职工抽象类 负责实现多态
{
public:
    //显示个人信息
    virtual void showInfo() = 0;
    //获取岗位名称
    virtual string getDeptName() = 0;

    int m_Id;      //职工编号
    string m_Name; //职工姓名
    int m_DeptId;  //职工所在部门名称编号
};
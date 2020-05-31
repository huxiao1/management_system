#include "employee.h"

employee::employee(int id,string name,int did)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = did;
}

void employee::showInfo()
{
    cout << "worker number:" << this->m_Id
		<< " \tworker name:" << this->m_Name
		<< " \tjob:" << this->getDeptName()
		<< " \tjob duty:finish work giben by manager" << endl;
}

string employee::getDeptName()
{
    return string("s1mple worker");
}
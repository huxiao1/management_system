#include "boss.h"

boss::boss(int id,string name,int did)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = did;
}

void boss::showInfo()
{
    cout << "worker number:" << this->m_Id
		<< " \tworker name:" << this->m_Name
		<< " \tjob:" << this->getDeptName()
		<< " \tjob duty:manage everything" << endl;
}

string boss::getDeptName()
{
    return string("boss");
}
#include "manager.h"

manager::manager(int id,string name,int did)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = did;
}

void manager::showInfo()
{
    cout << "worker number:" << this->m_Id
		<< " \tworker name:" << this->m_Name
		<< " \tjob:" << this->getDeptName()
		<< " \tjob duty:finish work giben by boss and give to workers" << endl;
}

string manager::getDeptName()
{
    return string("manager");
}
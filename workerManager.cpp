#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

workManager::workManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在情况
	if (!ifs.is_open())
	{
		cout << "file not exist" << endl; //测试输出
		this->m_EmpNum = 0;  //初始化人数
		this->m_FileIsEmpty = true; //初始化文件为空标志
		this->m_EmpArray = NULL; //初始化数组
		ifs.close(); //关闭文件
		return;
	}
	//文件存在，并且没有记录
	char ch;
	ifs >> ch;  //ifs右移读一个字符
	if (ifs.eof())
	{
		cout << "file is empty!" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//文件存在，并且记录数据
	this->m_FileIsEmpty = false;
	int num = this->get_EmpNum();
	cout<<"The numbe of workers are:"<<num<<endl;
	this->m_EmpNum = num;  //更新成员属性
	//根据职工数创建数组
	this->m_EmpArray = new worker *[this->m_EmpNum];
	//初始化职工
	init_Emp();
	//测试代码
	/*
	for (int i = 0; i < m_EmpNum; i++)
	{
		cout << "worker number:" << this->m_EmpArray[i]->m_Id
			<< " worker name:" << this->m_EmpArray[i]->m_Name
			<< " dept number:" << this->m_EmpArray[i]->m_DeptId << endl;
	}
	*/
}

workManager::~workManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
	}
}

void workManager::Show_Menu()
{
    cout << "********************************************" << endl;
	cout << "*************     welcome         ******" << endl;
	cout << "*************  0.exit             *********" << endl;
	cout << "************   1.add worker info  *************" << endl;
	cout << "*************  2.show worker info *************" << endl;
	cout << "*************  3.del worker       *************" << endl;
	cout << "*************  4.alter worker info*************" << endl;
	cout << "*************  5.search worker    *************" << endl;
	cout << "*************  6.sort as number   *************" << endl;
	cout << "*************  7.clear all document*************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void workManager::exitSystem()
{
	cout<<"See you next time"<<endl;
	exit(0);
}

void workManager::Add_Emp()
{
	cout<<"add number:"<<endl;

	int addnumber = 0;
	cin>>addnumber;

	if (addnumber > 0)
	{
		//计算要分配的新空间大小
		int newSize = this->m_EmpNum + addnumber;

		//开辟新空间
		worker ** newSpace = new worker*[newSize];

		//将原空间下内容存放到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addnumber; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "input the number" << i + 1 <<"'s number"<< endl;
			cin >> id;


			cout << "input the number" << i + 1 <<"'s name"<< endl;
			cin >> name;


			cout << "job?" << endl;
			cout << "1.worker" << endl;
			cout << "2.manager" << endl;
			cout << "3.boss" << endl;
			cin >> dSelect;

			worker *worker = NULL;
			switch (dSelect)
			{
			case 1: //普通员工
				worker = new employee(id, name, 1);
				break;
			case 2: //经理
				worker = new manager(id, name, 2);
				break;
			case 3:  //老板
				worker = new boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		
		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的个数
		this->m_EmpNum = newSize;

		//更新文件判空标志
		this->m_FileIsEmpty = false;

		//提示信息
		cout << "succeed to add" << addnumber << "new workers" << endl;

		this->save();
	}
	else
	{
		cout << "error input" << endl;
	}

	system("pause");
	system("cls");
}

void workManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME,ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id<<" "
			<< this->m_EmpArray[i]->m_Name<<" "
			<<this->m_EmpArray[i]->m_DeptId<<endl;
	}
	ofs.close();
}

int workManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int did;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> did)
	{
		//记录人数
		num++;
	}
	ifs.close();
	return num;
}

void workManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker *worker = NULL;
		//根据不同的部门id创建不同对象
		if (did == 1)
		{
			worker = new employee(id,name,did);
		}
		if (did == 2)
		{
			worker = new manager(id,name,did);
		}
		else
		{
			worker = new boss(id,name,did);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
}

//显示职工
void workManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"file is not exist or record is empty!"<<endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

int workManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//删除职工
void workManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"file is not exist or record is empty!"<<endl;
	}
	else
	{
		//按编号删除
		cout<<"input the id want to del:"<<endl;
		int id = 0;
		cin>>id;

		int index = this->IsExist(id);

		if (index != -1)  //找到可删除的数据了
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i+1];
			}
			this->m_EmpNum--;
			this->save(); //删除后同步数据到文件中
			cout<<"del succeed!"<<endl;
		}
		else
		{
			cout<<"del error,not find the worker"<<endl;
		}
	}
	system("pause");
	system("cls");
}

//修改职工
void workManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"File not exist or record is empty!"<<endl;
	}
	else
	{
		cout<<"please input the number of the worker:"<<endl;
		int id;
		cin>>id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查到编号的职工
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout<<"get :"<<id<<"th worker,please input new worker number:"<<endl;
			cin>>newId;

			cout<<"please input the new name:"<<endl;
			cin>>newName;

			cout<<"please input the job:"<<endl;
			cout<<"1.worker"<<endl;
			cout<<"2.manager"<<endl;
			cout<<"3.boss"<<endl;
			cin>>dSelect;

			worker *worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new employee(newId,newName,dSelect);
				break;
			case 2:
				worker = new manager(newId,newName,dSelect);
				break;
			case 3:
				worker = new boss(newId,newName,dSelect);
				break;
			default:
				break;
			}
			//更改数据到数组中
			this->m_EmpArray[ret] = worker;
			cout<<"alert succeed!"<<endl;

			//保存到文件中
			this->save();
		}
		else
		{
			cout<<"alert error!"<<endl;
		}
	}
	//清屏
	system("pause");
	system("cls");
}

void workManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"File not exist or record is empty!"<<endl;
	}
	else
	{
		cout<<"input search type:"<<endl;
		cout<<"1.search by worker number"<<endl;
		cout<<"2.search by name"<<endl;

		int select = 0;
		cin>>select;

		if (select == 1)
		{
			int id;
			cout<<"please input the worker number:"<<endl;
			cin>>id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout<<"search succeed!This is the information of this worker:"<<endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout<<"search error"<<endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout<<"please input the search name:"<<endl;
			cin>>name;	

			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_Name == name)
				{
					cout << "search succeed! The number of the worker is:"<< m_EmpArray[i]->m_Id<<"and information below:"<< endl;
					
					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout <<"search error"<< endl;
			}
		}
		else
		{
			cout<<"input error"<<endl;
		}
	}
	system("pause");
	system("cls");
}

void workManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"File not exist or record is empty!"<<endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout<<"please choose sort type:"<<endl;
		cout<<"1.sort by worker number(ASC)"<<endl;
		cout<<"2.sort by worker number(DEC)"<<endl;

		int select = 0;
		cin>>select;

		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;

			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1) //升序
				{
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else  //降序
				{
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)
			{
				worker * temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}

		cout<<"sort succeed,the result after sorting:"<<endl;
		this->save();
		this->Show_Emp();
	}
}

void workManager::Clean_File()
{
	cout<<"Are you sure?(it will clear the txt file)"<<endl;
	cout<<"1.yes"<<endl;
	cout<<"2.no"<<endl;

	int select = 0;
	cin>>select;

	if (select == 1)
	{
		ofstream ofs(FILENAME,ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout<<"clear succeed!"<<endl;
	}
	system("pause");
	system("cls");
}



#include<iostream>
#include<fstream>
using namespace std;
#include "worker.h"
#define FILENAME "empFile.txt"



class workManager
{
    public:
        workManager();

        ~workManager();

        void Show_Menu();

        void exitSystem(); //退出系统

        void Add_Emp();  //增加职工
 
        void save(); //保存文件

        void init_Emp(); //初始化员工

        int get_EmpNum();  //统计人数

        void Show_Emp();  //显示职工

        void Del_Emp();  //删除职工

        int IsExist(int id); //按照职工编号判断职工是否存在,若存在返回职工在数组中位置，不存在返回-1

        void Mod_Emp();  //修改职工

        void Find_Emp(); //查找职工

        void Sort_Emp(); //排序职工

        void Clean_File(); //清空文件

        
        int m_EmpNum;  //记录文件中的人数个数
        
        worker **m_EmpArray;  //员工数组的指针
        
        bool m_FileIsEmpty;  //标志文件是否为空
};
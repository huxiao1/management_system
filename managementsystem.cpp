#include<iostream>
using namespace std;
#include "workerManager.h"

int main()
{
    workManager wm;
    int choice = 0;

    while (1)
    {
        wm.Show_Menu();
        cout<<"input your choice:";
        cin>>choice;

        switch (choice)
        {
        case 0: //退出系统
            wm.exitSystem();
			break;
		case 1: //添加职工
			wm.Add_Emp();
			break;
		case 2: //显示职工
			wm.Show_Emp();
			break;
		case 3: //删除职工
			wm.Del_Emp();
			break;
		case 4: //修改职工
			wm.Mod_Emp();
			break;
		case 5: //查找职工
			wm.Find_Emp();
			break;
		case 6: //排序职工
			wm.Sort_Emp();
			break;
		case 7: //清空文件
			wm.Clean_File();
			break;
		default:  //清屏
			system("cls");
			break;        
        }
    }
    return 0;
}
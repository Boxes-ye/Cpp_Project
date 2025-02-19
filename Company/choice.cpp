#include "choice.h"

void choose(WorkManger &workmanger)
{

	int choice = 0;

	while (true)
	{

		std::cout << "请输入功能对应数字" << std::endl;

		std::cin >> choice;

		switch (choice)
		{
		case 0: //退出系统
			workmanger.Exit_Menu();
			return;
		case 1: //添加职工
			workmanger.Add_Staff();
			break;
		case 2: //显示职工
			workmanger.Load_Staff();
			break;
		case 3: //删除职工
			workmanger.Del_Staff();
			break;
		case 4: //修改职工
			workmanger.Mod_Staff();
			break;
		case 5: //查找职工
			workmanger.Find_Staff();
			break;
		case 6: //排序职工
			workmanger.Sort_Staff();
			break;
		case 7: //清空文件
			workmanger.Clear_File();
			break;
		default:
			system("cls");
			break;
		}
	}
}

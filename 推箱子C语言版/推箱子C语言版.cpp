// 推箱子C语言版.cpp : 定义控制台应用程序的入口点。
//
/*
实验要求：
完成以下任务为及格或中
1.有些方向的移动不能工作，需要根据能工作的进行对比研究后修改，确保四个方向都能正常移动
2.计数器工作有故障，需要根据实际效果找到问题解决之

再完成以下任务为良
3.添加新的关数的基础数据并使之在软件开始玩和重新玩中全部承认
增加的关数的难度应该高于原来默认的五关。


再完成以下任务为优
4.添加栈的机制使得可以在推到墙体时可以后退一步或者数步


再完成以下任务为优+
4.添加队列的机制使得可以复盘，即全部自动跑一遍



*/
//推箱子小游戏C版
//请在VC 6.0下运行
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
const int roomsize = 9;                          //设计房间内部为正方形，边长为9
int map[roomsize + 2][roomsize + 2];           //推箱子房间布局的数据结构：二维数组
int data;                                  //记录最短步骤数目                               
int times = 0;
int array[2] = { 100,100 };                    //记录最好成绩
char string[30] = "正在装入..................";
//以下为前几轮游戏房间中细节布局的数据结构：二维数组的实际内容
int map1[roomsize + 2][roomsize + 2] =
{   //0,1,2,3,4,5,6,7,8,9,10
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }, //0
	{ -1,0,0,0,0,1,1,1,1,1,-1 },          //1
	{ -1,0,0,0,0,1,0,0,0,1,-1 },          //2 
	{ -1,1,1,1,0,1,0,0,0,1,-1 },          //3
	{ -1,1,2,1,0,1,0,0,0,1,-1 },          //4
	{ -1,1,2,1,0,1,0,3,0,1,-1 },          //5
	{ -1,1,2,1,1,1,0,3,0,1,-1 },          //6
	{ -1,1,0,0,0,0,3,4,0,1,-1 },          //7
	{ -1,1,0,0,1,0,0,0,0,1,-1 },          //8
	{ -1,1,1,1,1,1,1,1,1,1,-1 },          //9 
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 } //10
};
int map2[roomsize + 2][roomsize + 2] =
{   //0,1,2,3,4,5,6,7,8,9,10
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },//0
	{ -1,0,1,1,1,1,0,0,0,-1,-1 },        //1
	{ -1,0,1,4,0,1,1,1,0,-1,-1 },        //2
	{ -1,0,1,0,3,0,0,1,0,-1,-1 },        //3
	{ -1,1,1,1,0,1,0,1,1,-1,-1 },        //4  
	{ -1,1,2,1,0,1,0,0,1,-1,-1 },        //5
	{ -1,1,2,3,0,0,1,0,1,-1,-1 },        //6
	{ -1,1,2,0,0,0,3,0,1,-1,-1 },        //7
	{ -1,1,1,1,1,1,1,1,1,-1,-1 },        //8
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },//9
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 } //10
};
int map3[roomsize + 2][roomsize + 2] =
{   //0,1,2,3,4,5,6,7,8,9,10
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },//0
	{ -1,1,1,1,1,1,1,1,1,-1,-1 },        //1
	{ -1,1,4,0,0,0,1,1,1,-1,-1 },        //2
	{ -1,1,0,3,3,0,0,0,1,-1,-1 },        //36
	{ -1,1,0,2,1,2,0,0,1,-1,-1 },        //4
	{ -1,1,0,0,1,1,3,0,1,-1,-1 },        //5
	{ -1,1,0,0,1,1,2,1,1,-1,-1 },        //6
	{ -1,1,0,0,0,0,0,1,1,-1,-1 },        //7
	{ -1,1,1,1,1,1,1,1,1,-1,-1 },        //8
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },//9
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 } //10
};
int map4[roomsize + 2][roomsize + 2] =
{   //0,1,2,3,4,5,6,7,8,9,10
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },//0
	{ -1,1,1,1,1,1,1,1,1,-1,-1 },		   //1
	{ -1,1,0,0,1,0,0,0,1,-1,-1 },        //2
	{ -1,1,0,3,2,2,3,0,1,-1,-1 },        //3
	{ -1,1,4,3,2,5,0,1,1,-1,-1 },        //4
	{ -1,1,0,3,2,2,3,0,1,-1,-1 },        //5
	{ -1,1,0,0,1,0,0,0,1,-1,-1 },        //6
	{ -1,1,1,1,1,1,1,1,1,-1,-1 },        //7 
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },//8
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },//9
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 } //10
};
int positionh;//人的位置纵坐标
int positionl;//人的位置横坐标
int flag;//标志位，记录人在目标位置上
int gate;//记录关数
int step;//记录步数
void initbox();//初始化函数
void begin();//开始界面
void choose_gate();//选关提示
void choose();//游戏时c选项的提示
void replay();//重玩
void playing();//玩游戏时界面
void display();//显示地图
void moveleft();//移向左方向
void moveright();//移向右方向
void movedown();//移向下方向
void moveup();//移向上方向
void test_flag();//过关提示
void record();//成绩排行榜
			  //=====
void playing()//Ascii码键盘键位：左为75 右为77 上为72 下为80
{
	int choice;
	step = 0;
	printf("开始游戏！");
	while (1)
	{
		display();
		switch (getch())
		{
		case 72:
			moveup();
			step++;
			break;
		case 80:
			movedown();
			step++;
			break;
		case 75:
			moveleft();
			step++;
			break;
		case 77:
			moveright();
			step++;
			break;
		case 'c':
		case 'C':
			choose();
			break;
		case 'q':
		case 'Q':
			printf("  ╭─────────────╮\n");
			printf(" │是退出游戏还是返回到主界面? │\n");
			printf(" │   1. 返回主界面            │\n");
			printf(" │   2. 退出游戏              │\n");
			printf(" ╰──────────────╯\n");
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:
				step = 0;
				Sleep(500);
				system("cls");
				begin();
				break;
			case 2:
				exit(0);
			}
		default:
			break;
		}
		system("cls");
	}
}
void display()
{
	printf("\n\n\n\n\n");
	for (int i = 1;i <= roomsize;i++)
	{
		printf("         ");
		for (int j = 1;j <= roomsize;j++)
		{
			if (map[i][j] == 0) printf("  ");
			if (map[i][j] == 1) printf("■");//墙
			if (map[i][j] == 2) printf("○");//目标位置
			if (map[i][j] == 3) printf("★");//箱子
			if (map[i][j] == 4) printf("♀");//人
			if (map[i][j] == 5) printf("㊣");//箱子在目标位置上
		}
		printf("\n");
	}
	printf("\n\n");
	printf("选项(c) 步数：%d\n", step);
}
void moveleft()
{
	if (map[positionh][positionl - 1] == 0)//向空白位置移动
	{
		map[positionh][positionl - 1] = 4;
		if (flag == 1)
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else
			map[positionh][positionl] = 0;
		positionl--;
	}
	else if (map[positionh][positionl - 1] == 2)//人要到目标位置上
	{
		map[positionh][positionl - 1] = 4;
		if (flag == 1)//人在目标位置上
			map[positionh][positionl] = 2;//恢复目标位置
		else
		{
			map[positionh][positionl] = 0;//恢复原来的状态
			flag = 1;//标志位，记录人在目标位置上
		}
		positionl--;
	}
	else if (map[positionh][positionl - 1] == 3 && map[positionh][positionl - 2] == 0)//将箱子推到空白位置上
	{
		map[positionh][positionl - 2] = 3;
		map[positionh][positionl - 1] = 4;
		if (flag == 1)
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else
			map[positionh][positionl] = 0;
		positionl--;
	}
	else if (map[positionh][positionl - 1] == 5 && map[positionh][positionl - 2] != 1 && map[positionh][positionl - 2] != 5 && map[positionh][positionl - 2] != 3)//要将箱子从目标位置上推出
	{
		if (map[positionh][positionl - 2] == 2)//下一个位置还是目标位置
		{
			map[positionh][positionl - 2] = 5;
			map[positionh][positionl - 1] = 4;
			if (flag == 1)
				map[positionh][positionl] = 2;
			else
			{
				map[positionh][positionl] = 0; flag = 1;
			}
		}
		else if (map[positionh][positionl - 2] == 0)//下一个位置是空白
		{
			map[positionh][positionl - 2] = 3;
			map[positionh][positionl - 1] = 4;
			if (flag == 1)
				map[positionh][positionl] = 2;
			else
			{
				map[positionh][positionl] = 0; flag = 1;
			}
		}
		positionl--;
	}
	else if (map[positionh][positionl - 1] == 3 && map[positionh][positionl - 2] == 2)//要将箱子推到目标位置上
	{
		map[positionh][positionl - 2] = 5;//箱子在目标位置上
		map[positionh][positionl - 1] = 4;
		if (flag == 1)//人在目标位置上
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else //人不在目标位置上
			map[positionh][positionl] = 0;
		positionl--;
	}
	else step--;//抵消人不动的情况
	test_flag();
}
void moveright()
{
	if (map[positionh][positionl + 1] == 0)//向空白位置移动
	{
		map[positionh][positionl + 1] = 4;
		if (flag == 1)
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else
			map[positionh][positionl] = 0;
		positionl++;
	}
	else if (map[positionh][positionl + 1] == 2)//人要到目标位置上
	{
		map[positionh][positionl + 1] = 4;
		if (flag == 1)//人在目标位置上
			map[positionh][positionl] = 2;//恢复目标位置
		else
		{
			map[positionh][positionl] = 0;//恢复原来的状态
			flag = 1;//标志位，记录人在目标位置上
		}
		positionl++;
	}
	else if (map[positionh][positionl + 1] == 3 && map[positionh][positionl + 2] == 0)//将箱子推到空白位置上
	{
		map[positionh][positionl + 2] = 3;
		map[positionh][positionl + 1] = 4;
		if (flag == 1)
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else
			map[positionh][positionl] = 0;
		positionl++;
	}
	else if (map[positionh][positionl + 1] == 5 && map[positionh][positionl + 2] != 1 && map[positionh][positionl + 2] != 5 && map[positionh][positionl + 2] != 3)//要将箱子从目标位置上推出
	{
		if (map[positionh][positionl + 2] == 2)//下一个位置还是目标位置
		{
			map[positionh][positionl + 2] = 5;
			map[positionh][positionl + 1] = 4;
			if (flag == 1)
				map[positionh][positionl] = 2;
			else
			{
				map[positionh][positionl] = 0; flag = 1;
			}
		}
		else if (map[positionh][positionl + 2] == 0)//下一个位置是空白
		{
			map[positionh][positionl + 2] = 3;
			map[positionh][positionl + 1] = 4;
			if (flag == 1)
				map[positionh][positionl] = 2;
			else
			{
				map[positionh][positionl] = 0; flag = 1;
			}
		}
		positionl++;
	}
	else if (map[positionh][positionl + 1] == 3 && map[positionh][positionl + 2] == 2)//要将箱子推到目标位置上
	{
		map[positionh][positionl + 2] = 5;//箱子在目标位置上
		map[positionh][positionl + 1] = 4;
		if (flag == 1)//人在目标位置上
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else //人不在目标位置上
			map[positionh][positionl] = 0;
		positionl++;
	}
	else step--;//抵消人不动的情况
	test_flag();
}
void movedown()
{
	if (map[positionh + 1][positionl] == 0)//向空白位置移动
	{
		map[positionh + 1][positionl] = 4;
		if (flag == 1)
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else
			map[positionh][positionl] = 0;
		positionh++;
	}
	else if (map[positionh + 1][positionl] == 2)//人要到目标位置上
	{
		map[positionh + 1][positionl] = 4;
		if (flag == 1)//人在目标位置上
			map[positionh][positionl] = 2;//恢复目标位置
		else
		{
			map[positionh][positionl] = 0;//恢复原来的状态
			flag = 1;//标志位，记录人在目标位置上
		}
		positionh++;
	}
	else if (map[positionh + 1][positionl] == 3 && map[positionh + 2][positionl] == 0)//将箱子推到空白位置上
	{
		map[positionh + 2][positionl] = 3;
		map[positionh + 1][positionl] = 4;
		if (flag == 1)
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else
			map[positionh][positionl] = 0;
		positionh++;
	}
	else if (map[positionh + 1][positionl] == 5 && map[positionh + 2][positionl] != 1 && map[positionh + 2][positionl] != 5 && map[positionh + 2][positionl] != 3)//要将箱子从目标位置上推出
	{
		if (map[positionh + 2][positionl] == 2)//下一个位置还是目标位置
		{
			map[positionh + 2][positionl] = 5;
			map[positionh + 1][positionl] = 4;
			if (flag == 1)
				map[positionh][positionl] = 2;
			else
			{
				map[positionh][positionl] = 0; flag = 1;
			}
		}
		else if (map[positionh + 2][positionl] == 0)//下一个位置是空白
		{
			map[positionh + 2][positionl] = 3;
			map[positionh + 1][positionl] = 4;
			if (flag == 1)
				map[positionh][positionl] = 2;
			else
			{
				map[positionh][positionl] = 0; flag = 1;
			}
		}
		positionh++;
	}
	else if (map[positionh + 1][positionl] == 3 && map[positionh + 2][positionl] == 2)//要将箱子推到目标位置上
	{
		map[positionh + 2][positionl] = 5;//箱子在目标位置上
		map[positionh + 1][positionl] = 4;
		if (flag == 1)//人在目标位置上
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else //人不在目标位置上
			map[positionh][positionl] = 0;
		positionh++;
	}
	else step--;//抵消人不动的情况
	test_flag();
}
void moveup()
{
	if (map[positionh - 1][positionl] == 0)//向空白位置移动
	{
		map[positionh - 1][positionl] = 4;
		if (flag == 1)
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else
			map[positionh][positionl] = 0;
		positionh--;
	}
	else if (map[positionh - 1][positionl] == 2)//人要到目标位置上
	{
		map[positionh - 1][positionl] = 4;
		if (flag == 1)//人在目标位置上
			map[positionh][positionl] = 2;//恢复目标位置
		else
		{
			map[positionh][positionl] = 0;//恢复原来的状态
			flag = 1;//标志位，记录人在目标位置上
		}
		positionh--;
	}
	else if (map[positionh - 1][positionl] == 3 && map[positionh - 2][positionl] == 0)//将箱子推到空白位置上
	{
		map[positionh - 2][positionl] = 3;
		map[positionh - 1][positionl] = 4;
		if (flag == 1)
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else
			map[positionh][positionl] = 0;
		positionh--;
	}
	else if (map[positionh - 1][positionl] == 5 && map[positionh - 2][positionl] != 1 && map[positionh - 2][positionl] != 5 && map[positionh - 2][positionl] != 3)//要将箱子从目标位置上推出
	{
		if (map[positionh - 2][positionl] == 2)//下一个位置还是目标位置
		{
			map[positionh - 2][positionl] = 5;
			map[positionh - 1][positionl] = 4;
			if (flag == 1)
				map[positionh][positionl] = 2;
			else
			{
				map[positionh][positionl] = 0; flag = 1;
			}
		}
		else if (map[positionh - 2][positionl] == 0)//下一个位置是空白
		{
			map[positionh - 2][positionl] = 3;
			map[positionh - 1][positionl] = 4;
			if (flag == 1)
				map[positionh][positionl] = 2;
			else
			{
				map[positionh][positionl] = 0; flag = 1;
			}
		}
		positionh--;
	}
	else if (map[positionh - 1][positionl] == 3 && map[positionh - 2][positionl] == 2)//要将箱子推到目标位置上
	{
		map[positionh - 2][positionl] = 5;//箱子在目标位置上
		map[positionh - 1][positionl] = 4;
		if (flag == 1)//人在目标位置上
		{
			map[positionh][positionl] = 2; flag = 0;
		}
		else //人不在目标位置上
			map[positionh][positionl] = 0;
		positionh--;
	}
	else step--;//抵消人不动的情况
	test_flag();
}

void initbox()//初始化函数
{
	positionh = 0;
	positionl = 0;
	flag = 0;
	step = 0;
	gate = 0;
}
void begin()
{
	printf("  ╭────────────────────────────────╮\n");
	printf(" │                                                                  │\n");
	printf(" │              ★☆★    推箱子 小组名称        ★☆★             │\n");
	printf(" │                           ╭─────╮                         │\n");
	printf(" │                          │  游戏简介  │                        │\n");
	printf(" │                          ╰──────╯                        │\n");
	printf(" │推箱子游戏:最终目的是操作一个人(♀)将箱子(★)推到目标位置(○)上。 │\n");
	printf(" │当箱子在目标位置上时显示㊣.                                       │\n");
	printf(" │                           ╭─────╮                         │\n");
	printf(" │                          │  操作说明  │                        │\n");
	printf(" │                          ╰──────╯                        │\n");
	printf(" │按方向键移动，'c'选项，'q'退出                                    │\n");
	printf(" │(建议使用最大化窗口，这样效果较好。)                              │\n");
	printf(" │                                                                  │\n");
	printf(" ╰─────────────────────────────────╯\n");
	choose_gate();//选择关数
	printf("%s\n", string);
	Sleep(500);
	system("cls");
	playing();
}
void choose_gate()
{
	int j, k;
	printf(" ╭──────╮\n");
	printf("│ 1.第一关     │\n");
	printf("│ 2.第二关     │\n");
	printf("│ 3.第三关     │\n");
	printf("│ 4.第四关     │\n");
	printf("╰───────╯\n");
	printf("请选择：");
	//	scanf("%d",&gate);
	do
	{
		scanf("%d", &gate);
		switch (gate)
		{
		case 1:
			for (j = 0;j<roomsize + 2;j++)//此处 j控制行，k控制列
				for (k = 0;k<roomsize + 2;k++)
					map[j][k] = map1[j][k];
			positionh = 7; positionl = 7;
			break;
		case 2:
			for (j = 0;j<roomsize + 2;j++)
				for (k = 0;k<roomsize + 2;k++)
					map[j][k] = map2[j][k];
			positionh = 2; positionl = 3;
			break;
		case 3:
			for (j = 0;j<roomsize + 2;j++)
				for (k = 0;k<roomsize + 2;k++)
					map[j][k] = map3[j][k];
			positionh = positionl = 2;
			break;
		case 4:
			for (j = 0;j<roomsize + 2;j++)
				for (k = 0;k<roomsize + 2;k++)
					map[j][k] = map4[j][k];
			positionh = 4;positionl = 2;
			break;
		default:
			printf("输出有误！重新输入");
		}
	} while (gate>4);
}
void choose()//选项
{
	int choice;
	printf(" ╭──────--╮\n");
	printf("│ 1. 重玩        │\n");
	printf("│ 2. 返回主界面  │\n");
	printf("│ 3. 最佳记录    │\n");
	printf("│ 4. 退出        │\n");
	printf("╰────────╯\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		system("cls");
		replay();
		break;
	case 2:
		system("cls");
		begin();
		break;
	case 3:
		record();
		system("cls");
		playing();
		break;
	case 4:
		exit(0);
	}
}
void replay()
{
	int j, k;
	step = 0;
	flag = 0;
	do
	{
		switch (gate)
		{
		case 1:
			for (j = 0;j<roomsize + 2;j++)
				for (k = 0;k<roomsize + 2;k++)
					map[j][k] = map1[j][k];
			positionh = 7; positionl = 7;
			break;
		case 2:
			for (j = 0;j<roomsize + 2;j++)
				for (k = 0;k<roomsize + 2;k++)
					map[j][k] = map2[j][k];
			positionh = 2; positionl = 3;
			break;
		case 3:
			for (j = 0;j<roomsize + 2;j++)
				for (k = 0;k<roomsize + 2;k++)
					map[j][k] = map3[j][k];
			positionh = positionl = 2;
			break;
		case 4:
			for (j = 0;j<roomsize + 2;j++)
				for (k = 0;k<roomsize + 2;k++)
					map[j][k] = map4[j][k];
			positionh = 4;positionl = 2;
			break;
		}
	} while (gate>4);
	playing();
}
void test_flag()
{
	int choice;
	for (int i = 1;i <= roomsize;i++)
		for (int j = 1;j <= roomsize;j++)
		{
			if (map[i][j] == 3)
				return;
		}
	system("cls");
	step++;
	data = step;
	times++;
	display();
	printf(" ╭─────────────╮\n");
	printf("│ 恭喜你！你已经通过了这关。 │\n");
	printf("│是不是很有成就感？是否继续？│\n");
	printf("│1. 继续                     │\n");
	printf("│2. 最佳记录                 │\n");
	printf("│3. 退出                     │\n");
	printf("╰──────────────╯\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		step = 0;
		Sleep(500);
		system("cls");
		begin();
		break;
	case 2:
		record();
		system("cls");
		printf("按任意键返回主界面...\n");
		begin();
		break;
	case 3:
		printf("欢迎再来玩！\n");
		printf("按任意键退出...\n");
		getchar();
		exit(0);
	}
}
void record()//最佳记录
{
	int rhigh;
	if (times % 2)
		array[0] = data;
	else
		array[1] = data;
	if (array[0]>array[1])
		rhigh = array[1];
	else
		rhigh = array[0];
	if (times % 2)
		array[0] = rhigh;
	else
		array[1] = rhigh;
	printf("最佳记录：%d\n", rhigh);
	system("pause");
}
//主函数
void main(void)
{
	system("color f0");//设置颜色
	SetConsoleTitle("推箱子小游戏（C版）"); //设置标题
	initbox();//初始化
	begin();//开始游戏
}


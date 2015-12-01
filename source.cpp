#include"examination.h"
#include<cstdio>
void listScores()
{
	ifstream fin("scores.txt");//打开成绩单文件
	string number;//用于读入学号
	double score;//用于读入成绩
	time_t t;//用于读入时间
	int i = 0;//用于记录是否存在已参加考试的学生
	int position;//用于记录名次
	cout << "学 号\t\t成 绩\t\t名 次\t\t参 加 考 试 时 间 " << endl;
	while (fin >> number)//读入学号
	{
		if(!i) i++;//如果i=0，i++
		fin >> score >>position>> t;//读入成绩、名次、时间
		cout << number << "\t" << score <<"\t\t"<<position<< "\t\t" << asctime(localtime(&t)) << endl;//输出
	}
	if (!i) cout << "暂时没有人参加过考试" << endl;
	fin.close();//关闭文件
}
int main()
{
	cout << "########################################################" << endl;
	cout << "########################################################" << endl;
	cout << "###########       欢迎使用考试管理系统       ###########" << endl;
	cout << "#                     1.考生信息管理                   #" << endl;
	cout << "#                       2.试题管理                     #" << endl;
	cout << "#                       3.成绩查询                     #" << endl;
	cout << "#                       4.开始考试                     #" << endl;
	cout << "#                       5.查看榜单                     #" << endl;
	cout << "#                         0.退出                       #" << endl;
	cout << "########################################################" << endl;
	cout << "########################################################" << endl;
	cout << "########################################################" << endl;
	char lll;//用于记录用户输入的主菜单选项
	cout << endl << "请输入你的选项:";
	cin >> lll;
	getchar();
	while (lll)
	{
		switch (lll)
		{
		case '0'://退出
		{
			cout << "谢谢使用！" << endl;
			exit(0);
		}
		case '1'://考生信息管理
		{
			int m = changeStudentInfo();//使用改变考生信息的函数
			if (m == 101)return 0;
			break;
		}
		case '2'://试题管理
		{
			int m=changeQuestionInfo();
			if (m == 101)return 0;
			break;
		}
		case '3'://成绩查询
		{
			inquiry();
			break;
		}
		case '4'://考试
		{
			examination();
			break;
		}
		case '5'://查看榜单
		{
			listScores();
			break;
		}
		default:
			cout << "错误的输入!" << endl;
			break;
		}
		cout << endl;
		cout << "########################################################" << endl;
		cout << "########################################################" << endl;
		cout << "###########       欢迎使用考试管理系统       ###########" << endl;
		cout << "#                     1.考生信息管理                   #" << endl;
		cout << "#                       2.试题管理                     #" << endl;
		cout << "#                       3.成绩查询                     #" << endl;
		cout << "#                       4.开始考试                     #" << endl;
		cout << "#                       5.查看榜单                     #" << endl;
		cout << "#                         0.退出                       #" << endl;
		cout << "########################################################" << endl;
		cout << "########################################################" << endl;
		cout << "########################################################" << endl;
		cout << endl << "请输入你的选项:";
		cin >> lll;//再次读入选项
		getchar();
	}
	return 0;
}
//当考试题目数量不足时进行提示
//填空题的答案并列情况
//读取问题文件时getline的使用

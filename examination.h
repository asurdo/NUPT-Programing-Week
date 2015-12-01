#include"inquiry.h"
int examination()
{
	cout << "请输入你的学号(按回车结束)：";
	string num;//输入学号
	getline(cin,num);
	num = "E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\" + num;
	ifstream fin(num.c_str());//打开学生文件
	if (!fin.is_open())//如果不能成功打开
	{
		cout << "输入错误，不存在此学号" << endl;
		return 0;
	}
	string number;
	string name;
	bool a;
	double score;
	int position;
	fin >> number >> name >> score >> a >> position;//读入此考生信息
	fin.close();
	if (a)//如果未参加考试
	{
		student m(number, name, score, a, position);//创建对象m
		exam h(m);//创建exam对象
		h.start();//开始考试
	}
	else {//参加过考试
		cout << "已经参加过考试的不准第二次参加" << endl;
	}
	return 0;
}

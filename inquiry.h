#include "changeStudentInfo.h"
int inquiry()
{
	cout << endl;
	cout << "###########考试管理系统查询成绩查询二级菜单#############" << endl;
	cout << "#                 1.考生学号进行查询                   #" << endl;
	cout << "#                 2.考生姓名进行查询                   #" << endl;
	cout << "########################################################" << endl;
	cout << endl;
	cout <<"请输入你的选项:";
	char flag;
	cin >> flag;
	getchar();
	switch (flag)
	{
	case '1'://通过考生学号查询
	{
		cout << "请输入学号：" << endl;
		string info;
		getline(cin, info);//读入考生学号
		info = "E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\" + info;
		ifstream fin(info.c_str());//直接打开考生文件
		if (!fin.is_open())//如果打开不成功，则表示不存在此考生
		{
			cout << "没有此考生" << endl;
			break;
		}
		string number;//创建对象储存此考生信息
		string name;
		bool a;
		double score;
		int position;
		time_t t;
		fin >> number >> name >> score >> a;//读取信息
		cout << number << "\t" << name << "\t是否已经参加考试:";//输出考生信息
		if (a)cout << " 否   " << endl;
		else
		{
			fin >> position >> t;
			cout << "是" << "\t成绩:" << score << "\t名次:" << position << endl;
			cout << "参加考试的时间" << asctime(localtime(&t)) << endl;
		}
		fin.close();
		break;
	}
	case '2':
	{
		int i = 0;//用于记录考生个数
		long handle;//遍历考生文件夹事件句柄
		struct _finddata_t fileinfo[1001];//记录考生信息文件信息
		handle = _findfirst("E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\*", fileinfo);//扫描整个文件夹
		if (strcmp(fileinfo->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
			i++;
		while (!_findnext(handle, fileinfo + i))
		{
			if (strcmp((fileinfo + i)->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
				i++;
		}
		_findclose(handle);
		cout << "请输入姓名" << endl;
		string info;//储存姓名
		getline(cin, info);//读取姓名
		int aaa = 0;//记录重名个数
		for (int j = 0; j < i; j++)//不断打开文件并对比是否为要查找的学生
		{
			string nnn = fileinfo[j].name;
			nnn = "E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\" + nnn;
			ifstream fin(nnn);
			string number;
			string name;
			fin >> number >> name;
			if (name == info)
			{
				aaa++;
				double score;
				bool a;
				fin >> score >> a;
				if (a)
				{
					cout << "尚未参加考试，无成绩" << endl;
				}
				else
				{
					int position;
					time_t t;
					fin >> position >> t;
					cout << number << " " << name;
					cout << " 成绩：" << score << "\t" << "名次：" << position << "\t" << asctime(localtime(&t)) << endl;
				}
			}
			fin.close();
		}
		if (aaa > 0)//如果有重名现象
		{
			cout << "有"<<aaa<<"个考生重名，已输出所有此名字的考生信息" << endl;
		}
		else
			cout << "并未存在此考生" << endl;
		break;
	}
	default:
		cout << "错误的输入!" << endl;
		return 0;
	}
}

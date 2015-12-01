#include "changeQuestionsInfo.h"
int changeStudentInfo()
{
	cout << endl;
	cout << "############    考试管理系统考生信息子菜单   ###########" << endl;
	cout << "#                  1.修改已有考生信息                  #" << endl;
	cout << "#                      2.增加考生                      #" << endl;
	cout << "#                      3.删除考生                      #" << endl;
	cout << "#                  4.退出考生管理系统                  #" << endl;
	cout << "#                5.查看当前所有考生的信息              #" << endl;
	cout << "#                    0.返回上级菜单                    #" << endl;
	cout << "########################################################" << endl;
	cout << endl << "请输入你的选项:";
	char qqqq;//考生信息菜单用户输入选项
	cin >> qqqq;
	getchar();
	switch (qqqq)
	{
	case '0':
		return 0;
	case '1'://修改已有考生信息
	{
		cout << "请输入需要修改的考生学号" << endl;
		string Num;
		getline(cin,Num);
		Num = "E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\" + Num;
		ifstream fin;
		fin.open(Num);//打开考生文件
		if (!fin.is_open())
		{
			cout << "输入错误，不存在此学号" << endl;
			return 0;
		}
		string number;
		string name;
		bool a;
		double score;
		int position=-1;
		time_t t=NULL;
		fin >> number >> name >> score >> a;//读取考生信息
		if (!a)//如果参加过考试
		{
			fin >> position >> t;
		}
		cout << number << " " << name << " 是否已经参加考试:";
		if (a)cout << "否   " << endl;
		else
		{
			cout << "是" << " 成绩:" << score << " 名次:" << position << endl;
			cout << asctime(localtime(&t)) << endl;
		}
		fin.close();
		remove(number.c_str());//删除此考生文件
		cout << "输入新的考生姓名:" ;
		cin  >> name;//修改考生名字
		if (success == student(number, name, score, a, position, t).ctrls())//将修改后的信息储存
			cout << "修改成功！" << endl;
		else
			cout << "修改失败" << endl;
		return 0;
	}
	case '2'://增加考生
	{
		cout <<"请首先输入考生学号:" << endl;//读入新的考生文件
		string number, name;
		cin >> number ;
		cout << "请输入考生姓名:" << endl;
		cin >> name;
		student mm(number, name);
		if (mm.ctrls() == success)//储存考生信息
		{
			cout << "成功！" << endl;
		}
		else cout << "增加失败！" << endl;
		return 0;
	}
	case '3'://删除考生信息
	{
		cout << "请输入需要删除的考生的学号" << endl;
		string m;
		getline(cin, m);
		m = "E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\" + m;
		if (!remove(m.c_str()))//直接删除考生文件
			cout << "删除成功！" << endl;
		else cout << "删除失败！" << endl;
		int i = 0;//删除文件后重新写scores.txt和theScore.txt文件
		long handle;
		struct _finddata_t fileinfo[1001];
		handle = _findfirst("E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\*", fileinfo);
		if (strcmp(fileinfo->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
			i++;
		while (!_findnext(handle, fileinfo + i))
		{
			if (strcmp((fileinfo + i)->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
				i++;
		}
		_findclose(handle);
		student stu[1001];
		for (int j = 0; j < i; j++)
		{
			string mmm = fileinfo[j].name;
			mmm = "E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\" + mmm;
			ifstream fin(mmm);
			string number;
			string name;
			double score;
			bool a;
			int position;
			time_t t;
			fin >> number >> name >> score >> a;
			if (a)
			{
				fin.close();
				continue;
			}
			fin >> position >> t;
			stu[j] = student(number, name, score, a, position, t);
			fin.close();
		}
		for (int ab = 0; ab < i; ab++)
		{
			if (stu[ab].getA())
			{
				for (int ac = ab; ac < i; ac++)
				{
					stu[ac] = stu[ac + 1];
				}
				i--;
			}
		}
		for (int ab = 0; ab < i; ab++)
		{
			for (int ac = i - 1; ac > ab; ac--)
			{
				if (stu[ab].getScore() < stu[ac].getScore())
				{
					student temp = stu[ab];
					stu[ab] = stu[ac];
					stu[ac] = temp;
				}
			}
		}
		for (int j = 0; j < i; j++)
		{
			if (j == 0)
			{
				stu[j].changePosition(1);
				continue;
			}
			if (stu[j].getScore() == stu[j - 1].getScore())
				stu[j].changePosition(stu[j - 1].getPosition());
			else
				stu[j].changePosition(j + 1);
		}
		ofstream fot("theScore.txt");
		ofstream fout("scores.txt", ios_base::out);
		for (int j = 0; j < i; j++)
		{
			time_t ttt = stu[j].getTime();
			fout << stu[j].getNumber() << " " << stu[j].getScore() << " " << stu[j].getPosition() << " " << ttt << " " << endl;
			fot << stu[j].getNumber() << " " << stu[j].getScore() << " " << stu[j].getPosition() << " " << asctime(localtime(&ttt)) << " " << endl;
		}
		fout.close();
		fot.close();
		return 0 ;
	}
	case '4':
		cout << "谢谢使用！" << endl;
		return 101;
	case'5'://查询所有学生信息
	{
		int i=0;//用于记录已有考生个数
		student stu[1001];//用来储存从文件中提取的所有学生信息
		long handle;
		struct _finddata_t fileinfo[1001];//获取学生文件信息
		handle = _findfirst("E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\*", fileinfo);
		if (strcmp(fileinfo->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
			i++;
		while (!_findnext(handle, fileinfo + i))
		{
			if (strcmp((fileinfo + i)->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
				i++;
		}
		_findclose(handle);
		for (int j = 0; j < i; j++)//输出考生信息
		{
			if (j == 0)cout << "学号\t\t\t姓名\t\t\t考试情况" << endl;
			ifstream fin;
			string mm =fileinfo[j].name;
			mm = "E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\" + mm;
			fin.open(mm.c_str());
			string name, number;
			double score;
			bool flag;
			cout.setf(ios::left);
			fin >> number >> name >> score >> flag;
			cout <<setw(16)<< number<<"\t" <<setw(16)<< name<<"\t";
			if (flag)
				cout << "尚未参加考试" << endl;
			else
				cout << "考试成绩:" << score << endl;
		}
		if (i == 0)
		{
			cout << endl << "当前没有考生信息!" << endl;
		}
		cout << endl;
		break;
	}
	default:
		cout << "错误的输入!" << endl;
		return 0;
	}
}
//33787592
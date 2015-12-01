#include"exam.h"
int changeQuestionInfo()
{
	cout << endl;
	cout << "############    考试管理系统试题管理子菜单   ###########" << endl;
	cout << "#                      1.增加题目                      #" << endl;
	cout << "#                      2.删除题目                      #" << endl;
	cout << "#                      3.修改题目                      #" << endl;
	cout << "#                    4.输出所有题目                    #" << endl;
	cout << "#                  5.退出考试管理系统                  #" << endl;
	cout << "#                    0.返回上级菜单                    #" << endl;
	cout << "########################################################" << endl;
	cout << endl << "请输入你的选项:" << endl;
	char qqqq;//记录选项的变量
	cin >> qqqq;
	getchar();
	question questions[1001];//定义question类数组来将题库中所有题目加载到内存中
	ifstream fin;
	fin.open("questions.txt", ios_base::in);//打开题库
	int i = 0;//用于记录题库中题目数量
	int s;//用于每次读入题目记录题库中题目的答案个数
	string answer[5];//用于记录答案
	string title;//用于记录题目
	int abc;//记录是否为并列答案
	while (fin >> s)//每次循环读入一个题目，首先读取答案个数
	{
		string mmmm;//将答案个数后的空行读取掉
		getline(fin, mmmm);//
		getline(fin,title);//读取题目
		for (int i = 0; i < s; i++)//读取s个答案
		{
			getline(fin, answer[i]);
		}
		fin >> abc;
		getline(fin, mmmm);
		question mm(title, answer, s,abc);//创建mm question对象，并将其赋给questions数组的第i个元素
		questions[i] = mm;
		i++;
	}
	fin.close();
	switch (qqqq)
	{
	case '0':
		break;
	case '1':			//增加题目
	{
		cout << "请输入题目：\n";
		string title1;//记录题目
		getline(cin, title1);
		cout << "请输入答案的个数(最多五个)：" ;
		char nuum;
		string ans[5];
		cin >> nuum;
		getchar();
		while ('1' > nuum || nuum > '5')//如果输入的答案个数不对，要求重新输入
		{
			cout << "输入错误" << endl;
			cout << "请重新输入答案的个数(最多五个)：";
			cin >> nuum;
			getchar();
		}
		int abc;
		if (nuum > '1')
		{
			cout << "答案是否并列？（是输入1，不是输入0）" << endl;
			cin >> abc;
			getchar();
		}
		else
			abc = 0;
		if (nuum-'0' > 1)//读入答案
		{
			cout << "请依次输入答案（每输入一个答案，输入一个回车）：" << endl;
			for (int i = 0; i < nuum-'0'; i++)
			{
				getline(cin, ans[i]);
			}
		}
		else if (nuum-'0' == 1)
		{
			cout << "请输入答案" << endl;
			getline(cin,ans[0]);
		}
		question mm(title1, ans, nuum-'0',abc);//建立question mm
		result res;//用于记录问题的添加结果
		res = mm.addQuestion(questions, i);//调用mm的类函数
		if (res == alreadyExist)
		{
			cout << "此问题已存在" << endl;
			break;
		}
		else if (res == fileOpenFaild)
		{
			cout << "问题增加失败" << endl;
			break;
		}
		else
		{
			questions[i] = mm;
			i++;
			cout << "问题增加成功！" << endl;
		}
		break;
	}
	case '2'://删除题目
	{
		for (int j = 0; j < i; j++)//输出所有题目
		{
			cout << j + 1 << ". " << questions[j].getTitle() << endl;
			cout << endl;
		}
		cout << "请输入要删除的题目题号：" << endl;
		int dddd;
		cin >> dddd;
		dddd = dddd - 1;
		getchar();
		while (dddd>i||dddd<1)
		{
			cout << "输入错误，请重新输入：";
			cin >> dddd;
			dddd = dddd - 1;
			getchar();
		}
		result resss = deleteQuestion(questions, dddd, i);//调用deleteQuestion函数，在内存中删除此题目
		if (resss == success)//将内存中题库储存
		{
			ofstream fout;
			fout.open("questions.txt");
			if (!fout.is_open())
			{
				cout << "删除失败" << endl;
				break;
			}
			for (int j = 0; j < i; j++)
			{
				fout << questions[j].getS() <<endl << questions[j].getTitle() <<endl;
				for (int k = 0; k < questions[j].getS(); k++)
				{
					fout << questions[j].getAnswer(k)<<endl;
				}
				fout << questions[j].getAbc() << endl;
			}
			fout.close();
			cout << "删除成功" << endl;
		}
		else if (resss == notExist)
		{
			cout << "并不存在此问题，删除失败" << endl;
		}
		break;
	}
	case '3'://修改题目
	{
		for (int j = 0; j < i; j++)//输出所有题目
		{
			cout << j + 1 << ". " << questions[j].getTitle() << endl;
			cout << endl;
		}
		cout << "请输入要修改的题目序号：" << endl;
		int dddd;
		cin >> dddd;
		dddd = dddd - 1;
		getchar();
		while (dddd>i || dddd<1)
		{
			cout << "输入错误，请重新输入：";
			cin >> dddd;
			dddd = dddd - 1;
			getchar();
		}
		cout << "请输入问题：" << endl;//得到问题信息
		string tt;
		getline(cin, tt);
		cout << "请输入答案个数（最多五个）：" << endl;
		char t1;
		cin >> t1;
		t1 = t1 - '0';
		getchar();
		while (t1 > 5 || t1 < 1)
		{
			cout << "输入错误" << endl;
			cout << "请重新输入答案的个数(最多五个)：";
			cin >> t1;
			t1 = t1 - '0';
			getchar();
		}
		int abc;
		if (t1 > 1)
		{
			cout << "请输入是否有并列答案（是请输入1，不是请输入0）：" << endl;
			cin >> abc;
			getchar();
		}
		else 
			abc = 0;
		cout << "请依次输入答案：" << endl;
		string aa[5];
		for (int k = 0; k < t1; k++)
		{
			getline(cin,aa[k]);
		}
		questions[dddd] = question(tt, aa, t1,abc);//将问题信息储存到数组中
		ofstream fout;//输出流对象
		fout.open("questions.txt");
		if (!fout.is_open())
		{
			cout << "修改失败" << endl;
			break;
		}
		cout << "修改成功！" << endl;
		for (int j = 0; j < i; j++)//将内存中题库储存到硬盘中
		{
			fout << questions[j].getS() << endl << questions[j].getTitle() << endl;
			for (int k = 0; k < questions[j].getS(); k++)
			{
				fout << questions[j].getAnswer(k) << endl;
			}
			fout << questions[j].getAbc() << endl;
		}
		fout.close();
		break;
	}
	case '4'://输出所有的题目
	{
		for (int j = 0; j < i; j++)
		{
			cout <<j+1<<". "<< questions[j].getTitle()<< endl;
			cout << "答案：" << endl;
			for (int k = 0; k < questions[j].getS(); k++)
			{
				cout << "		"<<questions[j].getAnswer(k) << endl;
			}
			cout << endl;
		}
		break;
	}
	case '5':
		cout << "谢谢使用！" << endl;
		return 101;
	default:
		cout << "错误的输入!" << endl;
		return 0;
	}
}

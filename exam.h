#include "question.h"
class exam
{
private:
	question ques[41];//用于储存抽取出的题目
	student pe;//参加此次考试的学生
	int amount;//题目数量
public:
	exam() {}//构造函数
	exam(student mmm);//构造函数
	void extract();//抽取题目
	void start();//考试
};
exam::exam(student mmm)
{
	pe = mmm;
}
void exam::extract()//抽取题目
{
	int b[1001] = { 0 };//用于标记是否重复抽取
	question questions[1001];//储存题库
	ifstream fin;
	fin.open("questions.txt", ios_base::in);//打开题库
	int i = 0;//用于记录题库中题目个数
	int s;//用于读入题目信息
	string answer[5];//用于读入题目信息
	string title;//用于读入题目信息
	while (fin >> s)//不断读入
	{
		int abc;
		string mmmm;//用于移动读取进度到下一行
		getline(fin, mmmm);
		getline(fin, title);
		for (int i = 0; i < s; i++)
		{
			getline(fin, answer[i]);
		}
		fin >> abc;
		getline(fin, mmmm);
		question mm(title, answer, s, abc);
		questions[i] = mm;
		i++;
	}
	srand(time(0));
	int m = 0;
	while (m < amount)//随机抽取amount个题目
	{
		int random = rand() % i;
		if (b[random] == 0)
		{
			b[random]++;
			ques[m] = questions[random];
			m++;
		}
	}
	fin.close();
}
void exam::start()
{
	int score = 0;//用于储存题目
	char x;
	cout << "是否更改默认题目数量（20），如需更改，直接输入题目数量(小于40)，否则请输入0" << endl;
	cin >> x;
	x = x - '0';
	getchar();
	if (!x)
	{
		x = 20;
	}
	else if (x > 40)
	{
		cout << "输入过大，以默认数量（20）进行考试" << endl;
		x = 20;
	}
	amount = x;
	extract();//抽取题目
	time_t now;
	now = time(0);
	pe.begin(now);//储存考试时间
	cout << "**********************开始考试************************" << endl;
	cout << "             多个空的题目请依次给出答案（跳过某空可以直接回车）" << endl;
	cout << "                   每答一空回车一次" << endl;
	for (int i = 0; i <amount; i++)//不断出题
	{
		cout << 1 + i << ". " << ques[i].getTitle() << endl;
		string answer[5];
		for (int j = 0; j < ques[i].getS(); j++)
		{
			getline(cin, answer[j]);
		}
		score += ques[i].judge(answer);//每做完一个题目进行一次判分并加到总成绩上
	}
	pe.changeScore(score);
	cout << "考试结束，考试成绩：" << score << endl;
	int i = 0;
	long handle;
	struct _finddata_t fileinfo[1001];//读取所有考生信息文件信息的数组
	handle = _findfirst("E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\*", fileinfo);//读取文件信息
	if (strcmp(fileinfo->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)//读取文件信息
		i++;
	while (!_findnext(handle, fileinfo + i))//读取文件信息
	{
		if (strcmp((fileinfo + i)->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
			i++;
	}
	_findclose(handle);
	student stu[1001];//储存考生信息
	for (int j = 0; j < i; j++)//不断打开文件，并将其读入stu数组
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
	for (int ab = 0; ab < i; ab++)//将未参加考试的在数组中剔除
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
	for (int ab = 0; ab < i; ab++)//将stu按照成绩排序
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
	for (int j = 0; j < i; j++)//将考生排名并储存
	{
		if (j == 0)
		{
			stu[j].changePosition(1);
			continue;
		}
		if (stu[j].getScore() == stu[j - 1].getScore())//如果成绩等于上一个的，则将名次等于上一个人
			stu[j].changePosition(stu[j - 1].getPosition());
		else
			stu[j].changePosition(j + 1);//否则等于i+1
	}
	ofstream fot("theScore.txt");//将这些信息写入theScore.txt和scores.txt两个文件，其中第一个文件是用于给老师看的
	ofstream fout("scores.txt");
	for (int j = 0; j < i; j++)
	{
		time_t ttt = stu[j].getTime();
		fout << stu[j].getNumber() << " " << stu[j].getScore() << " " << stu[j].getPosition() << " " << ttt << " " << endl;
		fot << stu[j].getNumber() << " " << stu[j].getScore() << " " << stu[j].getPosition() << " " << asctime(localtime(&ttt)) << " " << endl;
	}
	fout.close();
	fot.close();
	for (int j = 0; j < i; j++)
	{
		if (pe.getNumber() == stu[j].getNumber())
			pe.changePosition(stu[j].getPosition());
	}
}

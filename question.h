#include "student.h"
class question
{
private:
	int abc;//用于记录答案是否并列
	int s;//用于记录答案个数
	string title;//题目
	string answer[5];//答案，最多五个
public:
	question();//构造函数
	question(string a, string *r, int m, int ab);//构造函数
	question(const question & m);//拷贝构造函数
	int getS();//返回题目答案个数
	string getAnswer(int i);//返回answers数组中第i个元素
	string getTitle();//返回题目
	bool getAbc();//返回是否为并列答案
	int judge(string *m);//将m与答案进行比较并算出此题得分返回
	result addQuestion(question m[], int &ll);//m为题库，ll，为题库中题目数量
	//将此题储存，先与m中题目进行比较，如果有重复则退出
};
question::question()
{
	title = "";
	s = 0;
}
question::question(string a, string *r, int m, int ab)
{
	abc = ab;
	s = m;
	title = a;
	for (int i = 0; i < m; i++)
	{
		answer[i] = r[i];
	}

}
question::question(const question & m)
{
	abc = m.abc;
	title = m.title;
	s = m.s;
	for (int i = 0; i < s; i++)
	{
		answer[i] = m.answer[i];
	}
}
int question::getS()
{
	return s;
}
string question::getAnswer(int i)
{
	return answer[i];
}
string question::getTitle()
{
	return title;
}
bool question::getAbc()
{
	return abc;
}
int question::judge(string *m)
{
	int sss = 0;//记录此题成绩
	if (!abc)//如果不是并列答案
	{
		for (int i = 0; i < s; i++)//依次比较
		{
			if (answer[i] == m[i])sss++;
		}
	}
	else {
		int ss[5] = { 0 };//用于标识答案是否被比较
		for (int i = 0; i < s; i++)//二重循环比较
		{
			for (int j = 0; j < s; j++)
			{
				if (!ss[j] && answer[j] == m[i])//如果这一空的答案未被匹配过且匹配成功
				{
					sss++;//成绩加一
					ss[j] = 1;//标记为匹配过
				}
			}
		}
	}
	return sss;//返回此题得分
}
result question::addQuestion(question m[], int &ll)
{
	for (int i = 0; i < ll; i++)//先遍历题库寻找是否有重复的
	{
		if (m[i].getTitle() == title) 
			return alreadyExist;
	}
	ofstream fout;
	fout.open("questions.txt", ios_base::out | ios_base::app);//打开题库
	if (fout.is_open())//如果打开成功
	{
		fout << s << endl << title << endl;//写入数据
		for (int i = 0; i < s; i++)
		{
			fout << answer[i] << endl;
		}
		fout << abc << endl;
		fout.close();
		return success;
	}
	return fileOpenFaild;
}
result deleteQuestion(question *m, int a, int &number)//在m数组中删除第a个题目并返回
{
		for (int j = a; j < number+1; j++)
		{
			m[j] = m[j + 1];
		}
		number--;
		return success;
}

#include<iostream>
#include<string>
#include<ctime>
#include<fstream>
#include<io.h>
#include<cstdlib>
#include<iomanip>
using namespace std;
enum result//枚举
{
	alreadyExist,
	fileOpenFaild,
	success,
	notExist,
};
class student
{
private:
	string name;//用于记录学生名字
	string number;//用于记录学生学号
	double score;//成绩
	bool a;//是否参加过考试
	int position;//名次
	time_t beginTime;//参加考试的时间
public:
	student();//构造函数
	student(string num, string na);//构造函数
	student(string num, string na, double sc, bool aa, int pos, time_t t);//构造函数
	student(const student &m);//拷贝构造函数
	void begin(time_t t);//更改考试时间为t
	bool changeName(string na);//更改名字并储存到硬盘中
	bool changeScore(double m);//更改成绩并储存到硬盘中
	int getPosition();//得到名次
	bool changePosition(int  num);//改变名次为num并储存到硬盘中
	time_t getTime();//获得考试时间
	string getName();//获得名字
	string getNumber();//获得学号
	double getScore();//获得成绩
	bool getA();//获得a
	result ctrls();//储存此学生的信息于硬盘中
}; 
student::student()
{
	a = true;
	name = "";
	number = "";
	score = -1;
	position = -1;
	beginTime = NULL;
}
student::student(string num, string na)
{
	a = true;
	name = na;
	number = num;
	score = -1;
	position = -1;
	beginTime = NULL;
}
student::student(string num, string na, double sc, bool aa, int pos, time_t t = NULL)
{
	beginTime = t;
	a = aa;
	name = na;
	number = num;
	score = sc;
	position = pos;
}
student::student(const student &m)
{
	beginTime = m.beginTime;
	name = m.name;
	score = m.score;
	a = m.a;
	number = m.number;
	position = m.position;
}
bool student::changeName(string na)
{
	name = na;
	if (ctrls() == success)
		return true;
	return false;
}
bool student::changeScore(double m)
{
	a = false;//改变考试权限为无权限
	score = m;
	if (ctrls() == success)
		return true;
	return false;
}
int student::getPosition()
{
	return position;
}
bool student::changePosition(int  num)
{
	position = num;
	if (ctrls() == success)
		return true;
	return false;
}
time_t student::getTime()
{
	return beginTime;
}
string student::getName()
{
	return name;
}
string student::getNumber()
{
	return number;
}
double student::getScore()
{
	return score;
}
bool student::getA()
{
	return a;
}
void student::begin(time_t t)
{
	beginTime = t;
}
result student::ctrls()
{
	string nnn = "E:\\B140403_学生材料\\杨昌钦_考试信息管理系统\\kao\\" + number;//学生储存文件目录
	ofstream f(nnn.c_str());//打开此文件
	if (f.is_open())//如果打开成功
	{
		f << number << " " << name << " " << score << " " << a << " " << position << " ";//写入信息
		if (beginTime)f << beginTime;
		f.close();
		return success;//返回成功
	}
	return fileOpenFaild;//返回失败
}

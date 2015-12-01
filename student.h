#include<iostream>
#include<string>
#include<ctime>
#include<fstream>
#include<io.h>
#include<cstdlib>
#include<iomanip>
using namespace std;
enum result//ö��
{
	alreadyExist,
	fileOpenFaild,
	success,
	notExist,
};
class student
{
private:
	string name;//���ڼ�¼ѧ������
	string number;//���ڼ�¼ѧ��ѧ��
	double score;//�ɼ�
	bool a;//�Ƿ�μӹ�����
	int position;//����
	time_t beginTime;//�μӿ��Ե�ʱ��
public:
	student();//���캯��
	student(string num, string na);//���캯��
	student(string num, string na, double sc, bool aa, int pos, time_t t);//���캯��
	student(const student &m);//�������캯��
	void begin(time_t t);//���Ŀ���ʱ��Ϊt
	bool changeName(string na);//�������ֲ����浽Ӳ����
	bool changeScore(double m);//���ĳɼ������浽Ӳ����
	int getPosition();//�õ�����
	bool changePosition(int  num);//�ı�����Ϊnum�����浽Ӳ����
	time_t getTime();//��ÿ���ʱ��
	string getName();//�������
	string getNumber();//���ѧ��
	double getScore();//��óɼ�
	bool getA();//���a
	result ctrls();//�����ѧ������Ϣ��Ӳ����
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
	a = false;//�ı俼��Ȩ��Ϊ��Ȩ��
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
	string nnn = "E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\" + number;//ѧ�������ļ�Ŀ¼
	ofstream f(nnn.c_str());//�򿪴��ļ�
	if (f.is_open())//����򿪳ɹ�
	{
		f << number << " " << name << " " << score << " " << a << " " << position << " ";//д����Ϣ
		if (beginTime)f << beginTime;
		f.close();
		return success;//���سɹ�
	}
	return fileOpenFaild;//����ʧ��
}

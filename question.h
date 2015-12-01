#include "student.h"
class question
{
private:
	int abc;//���ڼ�¼���Ƿ���
	int s;//���ڼ�¼�𰸸���
	string title;//��Ŀ
	string answer[5];//�𰸣�������
public:
	question();//���캯��
	question(string a, string *r, int m, int ab);//���캯��
	question(const question & m);//�������캯��
	int getS();//������Ŀ�𰸸���
	string getAnswer(int i);//����answers�����е�i��Ԫ��
	string getTitle();//������Ŀ
	bool getAbc();//�����Ƿ�Ϊ���д�
	int judge(string *m);//��m��𰸽��бȽϲ��������÷ַ���
	result addQuestion(question m[], int &ll);//mΪ��⣬ll��Ϊ�������Ŀ����
	//�����ⴢ�棬����m����Ŀ���бȽϣ�������ظ����˳�
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
	int sss = 0;//��¼����ɼ�
	if (!abc)//������ǲ��д�
	{
		for (int i = 0; i < s; i++)//���αȽ�
		{
			if (answer[i] == m[i])sss++;
		}
	}
	else {
		int ss[5] = { 0 };//���ڱ�ʶ���Ƿ񱻱Ƚ�
		for (int i = 0; i < s; i++)//����ѭ���Ƚ�
		{
			for (int j = 0; j < s; j++)
			{
				if (!ss[j] && answer[j] == m[i])//�����һ�յĴ�δ��ƥ�����ƥ��ɹ�
				{
					sss++;//�ɼ���һ
					ss[j] = 1;//���Ϊƥ���
				}
			}
		}
	}
	return sss;//���ش���÷�
}
result question::addQuestion(question m[], int &ll)
{
	for (int i = 0; i < ll; i++)//�ȱ������Ѱ���Ƿ����ظ���
	{
		if (m[i].getTitle() == title) 
			return alreadyExist;
	}
	ofstream fout;
	fout.open("questions.txt", ios_base::out | ios_base::app);//�����
	if (fout.is_open())//����򿪳ɹ�
	{
		fout << s << endl << title << endl;//д������
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
result deleteQuestion(question *m, int a, int &number)//��m������ɾ����a����Ŀ������
{
		for (int j = a; j < number+1; j++)
		{
			m[j] = m[j + 1];
		}
		number--;
		return success;
}

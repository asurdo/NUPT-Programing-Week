#include "question.h"
class exam
{
private:
	question ques[41];//���ڴ����ȡ������Ŀ
	student pe;//�μӴ˴ο��Ե�ѧ��
	int amount;//��Ŀ����
public:
	exam() {}//���캯��
	exam(student mmm);//���캯��
	void extract();//��ȡ��Ŀ
	void start();//����
};
exam::exam(student mmm)
{
	pe = mmm;
}
void exam::extract()//��ȡ��Ŀ
{
	int b[1001] = { 0 };//���ڱ���Ƿ��ظ���ȡ
	question questions[1001];//�������
	ifstream fin;
	fin.open("questions.txt", ios_base::in);//�����
	int i = 0;//���ڼ�¼�������Ŀ����
	int s;//���ڶ�����Ŀ��Ϣ
	string answer[5];//���ڶ�����Ŀ��Ϣ
	string title;//���ڶ�����Ŀ��Ϣ
	while (fin >> s)//���϶���
	{
		int abc;
		string mmmm;//�����ƶ���ȡ���ȵ���һ��
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
	while (m < amount)//�����ȡamount����Ŀ
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
	int score = 0;//���ڴ�����Ŀ
	char x;
	cout << "�Ƿ����Ĭ����Ŀ������20����������ģ�ֱ��������Ŀ����(С��40)������������0" << endl;
	cin >> x;
	x = x - '0';
	getchar();
	if (!x)
	{
		x = 20;
	}
	else if (x > 40)
	{
		cout << "���������Ĭ��������20�����п���" << endl;
		x = 20;
	}
	amount = x;
	extract();//��ȡ��Ŀ
	time_t now;
	now = time(0);
	pe.begin(now);//���濼��ʱ��
	cout << "**********************��ʼ����************************" << endl;
	cout << "             ����յ���Ŀ�����θ����𰸣�����ĳ�տ���ֱ�ӻس���" << endl;
	cout << "                   ÿ��һ�ջس�һ��" << endl;
	for (int i = 0; i <amount; i++)//���ϳ���
	{
		cout << 1 + i << ". " << ques[i].getTitle() << endl;
		string answer[5];
		for (int j = 0; j < ques[i].getS(); j++)
		{
			getline(cin, answer[j]);
		}
		score += ques[i].judge(answer);//ÿ����һ����Ŀ����һ���зֲ��ӵ��ܳɼ���
	}
	pe.changeScore(score);
	cout << "���Խ��������Գɼ���" << score << endl;
	int i = 0;
	long handle;
	struct _finddata_t fileinfo[1001];//��ȡ���п�����Ϣ�ļ���Ϣ������
	handle = _findfirst("E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\*", fileinfo);//��ȡ�ļ���Ϣ
	if (strcmp(fileinfo->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)//��ȡ�ļ���Ϣ
		i++;
	while (!_findnext(handle, fileinfo + i))//��ȡ�ļ���Ϣ
	{
		if (strcmp((fileinfo + i)->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
			i++;
	}
	_findclose(handle);
	student stu[1001];//���濼����Ϣ
	for (int j = 0; j < i; j++)//���ϴ��ļ������������stu����
	{
		string mmm = fileinfo[j].name;
		mmm = "E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\" + mmm;
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
	for (int ab = 0; ab < i; ab++)//��δ�μӿ��Ե����������޳�
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
	for (int ab = 0; ab < i; ab++)//��stu���ճɼ�����
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
	for (int j = 0; j < i; j++)//����������������
	{
		if (j == 0)
		{
			stu[j].changePosition(1);
			continue;
		}
		if (stu[j].getScore() == stu[j - 1].getScore())//����ɼ�������һ���ģ������ε�����һ����
			stu[j].changePosition(stu[j - 1].getPosition());
		else
			stu[j].changePosition(j + 1);//�������i+1
	}
	ofstream fot("theScore.txt");//����Щ��Ϣд��theScore.txt��scores.txt�����ļ������е�һ���ļ������ڸ���ʦ����
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

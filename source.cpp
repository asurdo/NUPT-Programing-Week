#include"examination.h"
#include<cstdio>
void listScores()
{
	ifstream fin("scores.txt");//�򿪳ɼ����ļ�
	string number;//���ڶ���ѧ��
	double score;//���ڶ���ɼ�
	time_t t;//���ڶ���ʱ��
	int i = 0;//���ڼ�¼�Ƿ�����Ѳμӿ��Ե�ѧ��
	int position;//���ڼ�¼����
	cout << "ѧ ��\t\t�� ��\t\t�� ��\t\t�� �� �� �� ʱ �� " << endl;
	while (fin >> number)//����ѧ��
	{
		if(!i) i++;//���i=0��i++
		fin >> score >>position>> t;//����ɼ������Ρ�ʱ��
		cout << number << "\t" << score <<"\t\t"<<position<< "\t\t" << asctime(localtime(&t)) << endl;//���
	}
	if (!i) cout << "��ʱû���˲μӹ�����" << endl;
	fin.close();//�ر��ļ�
}
int main()
{
	cout << "########################################################" << endl;
	cout << "########################################################" << endl;
	cout << "###########       ��ӭʹ�ÿ��Թ���ϵͳ       ###########" << endl;
	cout << "#                     1.������Ϣ����                   #" << endl;
	cout << "#                       2.�������                     #" << endl;
	cout << "#                       3.�ɼ���ѯ                     #" << endl;
	cout << "#                       4.��ʼ����                     #" << endl;
	cout << "#                       5.�鿴��                     #" << endl;
	cout << "#                         0.�˳�                       #" << endl;
	cout << "########################################################" << endl;
	cout << "########################################################" << endl;
	cout << "########################################################" << endl;
	char lll;//���ڼ�¼�û���������˵�ѡ��
	cout << endl << "���������ѡ��:";
	cin >> lll;
	getchar();
	while (lll)
	{
		switch (lll)
		{
		case '0'://�˳�
		{
			cout << "ллʹ�ã�" << endl;
			exit(0);
		}
		case '1'://������Ϣ����
		{
			int m = changeStudentInfo();//ʹ�øı俼����Ϣ�ĺ���
			if (m == 101)return 0;
			break;
		}
		case '2'://�������
		{
			int m=changeQuestionInfo();
			if (m == 101)return 0;
			break;
		}
		case '3'://�ɼ���ѯ
		{
			inquiry();
			break;
		}
		case '4'://����
		{
			examination();
			break;
		}
		case '5'://�鿴��
		{
			listScores();
			break;
		}
		default:
			cout << "���������!" << endl;
			break;
		}
		cout << endl;
		cout << "########################################################" << endl;
		cout << "########################################################" << endl;
		cout << "###########       ��ӭʹ�ÿ��Թ���ϵͳ       ###########" << endl;
		cout << "#                     1.������Ϣ����                   #" << endl;
		cout << "#                       2.�������                     #" << endl;
		cout << "#                       3.�ɼ���ѯ                     #" << endl;
		cout << "#                       4.��ʼ����                     #" << endl;
		cout << "#                       5.�鿴��                     #" << endl;
		cout << "#                         0.�˳�                       #" << endl;
		cout << "########################################################" << endl;
		cout << "########################################################" << endl;
		cout << "########################################################" << endl;
		cout << endl << "���������ѡ��:";
		cin >> lll;//�ٴζ���ѡ��
		getchar();
	}
	return 0;
}
//��������Ŀ��������ʱ������ʾ
//�����Ĵ𰸲������
//��ȡ�����ļ�ʱgetline��ʹ��

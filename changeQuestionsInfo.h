#include"exam.h"
int changeQuestionInfo()
{
	cout << endl;
	cout << "############    ���Թ���ϵͳ��������Ӳ˵�   ###########" << endl;
	cout << "#                      1.������Ŀ                      #" << endl;
	cout << "#                      2.ɾ����Ŀ                      #" << endl;
	cout << "#                      3.�޸���Ŀ                      #" << endl;
	cout << "#                    4.���������Ŀ                    #" << endl;
	cout << "#                  5.�˳����Թ���ϵͳ                  #" << endl;
	cout << "#                    0.�����ϼ��˵�                    #" << endl;
	cout << "########################################################" << endl;
	cout << endl << "���������ѡ��:" << endl;
	char qqqq;//��¼ѡ��ı���
	cin >> qqqq;
	getchar();
	question questions[1001];//����question���������������������Ŀ���ص��ڴ���
	ifstream fin;
	fin.open("questions.txt", ios_base::in);//�����
	int i = 0;//���ڼ�¼�������Ŀ����
	int s;//����ÿ�ζ�����Ŀ��¼�������Ŀ�Ĵ𰸸���
	string answer[5];//���ڼ�¼��
	string title;//���ڼ�¼��Ŀ
	int abc;//��¼�Ƿ�Ϊ���д�
	while (fin >> s)//ÿ��ѭ������һ����Ŀ�����ȶ�ȡ�𰸸���
	{
		string mmmm;//���𰸸�����Ŀ��ж�ȡ��
		getline(fin, mmmm);//
		getline(fin,title);//��ȡ��Ŀ
		for (int i = 0; i < s; i++)//��ȡs����
		{
			getline(fin, answer[i]);
		}
		fin >> abc;
		getline(fin, mmmm);
		question mm(title, answer, s,abc);//����mm question���󣬲����丳��questions����ĵ�i��Ԫ��
		questions[i] = mm;
		i++;
	}
	fin.close();
	switch (qqqq)
	{
	case '0':
		break;
	case '1':			//������Ŀ
	{
		cout << "��������Ŀ��\n";
		string title1;//��¼��Ŀ
		getline(cin, title1);
		cout << "������𰸵ĸ���(������)��" ;
		char nuum;
		string ans[5];
		cin >> nuum;
		getchar();
		while ('1' > nuum || nuum > '5')//�������Ĵ𰸸������ԣ�Ҫ����������
		{
			cout << "�������" << endl;
			cout << "����������𰸵ĸ���(������)��";
			cin >> nuum;
			getchar();
		}
		int abc;
		if (nuum > '1')
		{
			cout << "���Ƿ��У���������1����������0��" << endl;
			cin >> abc;
			getchar();
		}
		else
			abc = 0;
		if (nuum-'0' > 1)//�����
		{
			cout << "����������𰸣�ÿ����һ���𰸣�����һ���س�����" << endl;
			for (int i = 0; i < nuum-'0'; i++)
			{
				getline(cin, ans[i]);
			}
		}
		else if (nuum-'0' == 1)
		{
			cout << "�������" << endl;
			getline(cin,ans[0]);
		}
		question mm(title1, ans, nuum-'0',abc);//����question mm
		result res;//���ڼ�¼�������ӽ��
		res = mm.addQuestion(questions, i);//����mm���ຯ��
		if (res == alreadyExist)
		{
			cout << "�������Ѵ���" << endl;
			break;
		}
		else if (res == fileOpenFaild)
		{
			cout << "��������ʧ��" << endl;
			break;
		}
		else
		{
			questions[i] = mm;
			i++;
			cout << "�������ӳɹ���" << endl;
		}
		break;
	}
	case '2'://ɾ����Ŀ
	{
		for (int j = 0; j < i; j++)//���������Ŀ
		{
			cout << j + 1 << ". " << questions[j].getTitle() << endl;
			cout << endl;
		}
		cout << "������Ҫɾ������Ŀ��ţ�" << endl;
		int dddd;
		cin >> dddd;
		dddd = dddd - 1;
		getchar();
		while (dddd>i||dddd<1)
		{
			cout << "����������������룺";
			cin >> dddd;
			dddd = dddd - 1;
			getchar();
		}
		result resss = deleteQuestion(questions, dddd, i);//����deleteQuestion���������ڴ���ɾ������Ŀ
		if (resss == success)//���ڴ�����ⴢ��
		{
			ofstream fout;
			fout.open("questions.txt");
			if (!fout.is_open())
			{
				cout << "ɾ��ʧ��" << endl;
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
			cout << "ɾ���ɹ�" << endl;
		}
		else if (resss == notExist)
		{
			cout << "�������ڴ����⣬ɾ��ʧ��" << endl;
		}
		break;
	}
	case '3'://�޸���Ŀ
	{
		for (int j = 0; j < i; j++)//���������Ŀ
		{
			cout << j + 1 << ". " << questions[j].getTitle() << endl;
			cout << endl;
		}
		cout << "������Ҫ�޸ĵ���Ŀ��ţ�" << endl;
		int dddd;
		cin >> dddd;
		dddd = dddd - 1;
		getchar();
		while (dddd>i || dddd<1)
		{
			cout << "����������������룺";
			cin >> dddd;
			dddd = dddd - 1;
			getchar();
		}
		cout << "���������⣺" << endl;//�õ�������Ϣ
		string tt;
		getline(cin, tt);
		cout << "������𰸸���������������" << endl;
		char t1;
		cin >> t1;
		t1 = t1 - '0';
		getchar();
		while (t1 > 5 || t1 < 1)
		{
			cout << "�������" << endl;
			cout << "����������𰸵ĸ���(������)��";
			cin >> t1;
			t1 = t1 - '0';
			getchar();
		}
		int abc;
		if (t1 > 1)
		{
			cout << "�������Ƿ��в��д𰸣���������1������������0����" << endl;
			cin >> abc;
			getchar();
		}
		else 
			abc = 0;
		cout << "����������𰸣�" << endl;
		string aa[5];
		for (int k = 0; k < t1; k++)
		{
			getline(cin,aa[k]);
		}
		questions[dddd] = question(tt, aa, t1,abc);//��������Ϣ���浽������
		ofstream fout;//���������
		fout.open("questions.txt");
		if (!fout.is_open())
		{
			cout << "�޸�ʧ��" << endl;
			break;
		}
		cout << "�޸ĳɹ���" << endl;
		for (int j = 0; j < i; j++)//���ڴ�����ⴢ�浽Ӳ����
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
	case '4'://������е���Ŀ
	{
		for (int j = 0; j < i; j++)
		{
			cout <<j+1<<". "<< questions[j].getTitle()<< endl;
			cout << "�𰸣�" << endl;
			for (int k = 0; k < questions[j].getS(); k++)
			{
				cout << "		"<<questions[j].getAnswer(k) << endl;
			}
			cout << endl;
		}
		break;
	}
	case '5':
		cout << "ллʹ�ã�" << endl;
		return 101;
	default:
		cout << "���������!" << endl;
		return 0;
	}
}

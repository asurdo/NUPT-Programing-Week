#include "changeQuestionsInfo.h"
int changeStudentInfo()
{
	cout << endl;
	cout << "############    ���Թ���ϵͳ������Ϣ�Ӳ˵�   ###########" << endl;
	cout << "#                  1.�޸����п�����Ϣ                  #" << endl;
	cout << "#                      2.���ӿ���                      #" << endl;
	cout << "#                      3.ɾ������                      #" << endl;
	cout << "#                  4.�˳���������ϵͳ                  #" << endl;
	cout << "#                5.�鿴��ǰ���п�������Ϣ              #" << endl;
	cout << "#                    0.�����ϼ��˵�                    #" << endl;
	cout << "########################################################" << endl;
	cout << endl << "���������ѡ��:";
	char qqqq;//������Ϣ�˵��û�����ѡ��
	cin >> qqqq;
	getchar();
	switch (qqqq)
	{
	case '0':
		return 0;
	case '1'://�޸����п�����Ϣ
	{
		cout << "��������Ҫ�޸ĵĿ���ѧ��" << endl;
		string Num;
		getline(cin,Num);
		Num = "E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\" + Num;
		ifstream fin;
		fin.open(Num);//�򿪿����ļ�
		if (!fin.is_open())
		{
			cout << "������󣬲����ڴ�ѧ��" << endl;
			return 0;
		}
		string number;
		string name;
		bool a;
		double score;
		int position=-1;
		time_t t=NULL;
		fin >> number >> name >> score >> a;//��ȡ������Ϣ
		if (!a)//����μӹ�����
		{
			fin >> position >> t;
		}
		cout << number << " " << name << " �Ƿ��Ѿ��μӿ���:";
		if (a)cout << "��   " << endl;
		else
		{
			cout << "��" << " �ɼ�:" << score << " ����:" << position << endl;
			cout << asctime(localtime(&t)) << endl;
		}
		fin.close();
		remove(number.c_str());//ɾ���˿����ļ�
		cout << "�����µĿ�������:" ;
		cin  >> name;//�޸Ŀ�������
		if (success == student(number, name, score, a, position, t).ctrls())//���޸ĺ����Ϣ����
			cout << "�޸ĳɹ���" << endl;
		else
			cout << "�޸�ʧ��" << endl;
		return 0;
	}
	case '2'://���ӿ���
	{
		cout <<"���������뿼��ѧ��:" << endl;//�����µĿ����ļ�
		string number, name;
		cin >> number ;
		cout << "�����뿼������:" << endl;
		cin >> name;
		student mm(number, name);
		if (mm.ctrls() == success)//���濼����Ϣ
		{
			cout << "�ɹ���" << endl;
		}
		else cout << "����ʧ�ܣ�" << endl;
		return 0;
	}
	case '3'://ɾ��������Ϣ
	{
		cout << "��������Ҫɾ���Ŀ�����ѧ��" << endl;
		string m;
		getline(cin, m);
		m = "E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\" + m;
		if (!remove(m.c_str()))//ֱ��ɾ�������ļ�
			cout << "ɾ���ɹ���" << endl;
		else cout << "ɾ��ʧ�ܣ�" << endl;
		int i = 0;//ɾ���ļ�������дscores.txt��theScore.txt�ļ�
		long handle;
		struct _finddata_t fileinfo[1001];
		handle = _findfirst("E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\*", fileinfo);
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
		cout << "ллʹ�ã�" << endl;
		return 101;
	case'5'://��ѯ����ѧ����Ϣ
	{
		int i=0;//���ڼ�¼���п�������
		student stu[1001];//����������ļ�����ȡ������ѧ����Ϣ
		long handle;
		struct _finddata_t fileinfo[1001];//��ȡѧ���ļ���Ϣ
		handle = _findfirst("E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\*", fileinfo);
		if (strcmp(fileinfo->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
			i++;
		while (!_findnext(handle, fileinfo + i))
		{
			if (strcmp((fileinfo + i)->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
				i++;
		}
		_findclose(handle);
		for (int j = 0; j < i; j++)//���������Ϣ
		{
			if (j == 0)cout << "ѧ��\t\t\t����\t\t\t�������" << endl;
			ifstream fin;
			string mm =fileinfo[j].name;
			mm = "E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\" + mm;
			fin.open(mm.c_str());
			string name, number;
			double score;
			bool flag;
			cout.setf(ios::left);
			fin >> number >> name >> score >> flag;
			cout <<setw(16)<< number<<"\t" <<setw(16)<< name<<"\t";
			if (flag)
				cout << "��δ�μӿ���" << endl;
			else
				cout << "���Գɼ�:" << score << endl;
		}
		if (i == 0)
		{
			cout << endl << "��ǰû�п�����Ϣ!" << endl;
		}
		cout << endl;
		break;
	}
	default:
		cout << "���������!" << endl;
		return 0;
	}
}
//33787592
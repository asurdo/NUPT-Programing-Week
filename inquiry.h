#include "changeStudentInfo.h"
int inquiry()
{
	cout << endl;
	cout << "###########���Թ���ϵͳ��ѯ�ɼ���ѯ�����˵�#############" << endl;
	cout << "#                 1.����ѧ�Ž��в�ѯ                   #" << endl;
	cout << "#                 2.�����������в�ѯ                   #" << endl;
	cout << "########################################################" << endl;
	cout << endl;
	cout <<"���������ѡ��:";
	char flag;
	cin >> flag;
	getchar();
	switch (flag)
	{
	case '1'://ͨ������ѧ�Ų�ѯ
	{
		cout << "������ѧ�ţ�" << endl;
		string info;
		getline(cin, info);//���뿼��ѧ��
		info = "E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\" + info;
		ifstream fin(info.c_str());//ֱ�Ӵ򿪿����ļ�
		if (!fin.is_open())//����򿪲��ɹ������ʾ�����ڴ˿���
		{
			cout << "û�д˿���" << endl;
			break;
		}
		string number;//�������󴢴�˿�����Ϣ
		string name;
		bool a;
		double score;
		int position;
		time_t t;
		fin >> number >> name >> score >> a;//��ȡ��Ϣ
		cout << number << "\t" << name << "\t�Ƿ��Ѿ��μӿ���:";//���������Ϣ
		if (a)cout << " ��   " << endl;
		else
		{
			fin >> position >> t;
			cout << "��" << "\t�ɼ�:" << score << "\t����:" << position << endl;
			cout << "�μӿ��Ե�ʱ��" << asctime(localtime(&t)) << endl;
		}
		fin.close();
		break;
	}
	case '2':
	{
		int i = 0;//���ڼ�¼��������
		long handle;//���������ļ����¼����
		struct _finddata_t fileinfo[1001];//��¼������Ϣ�ļ���Ϣ
		handle = _findfirst("E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\*", fileinfo);//ɨ�������ļ���
		if (strcmp(fileinfo->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
			i++;
		while (!_findnext(handle, fileinfo + i))
		{
			if (strcmp((fileinfo + i)->name, ".") != 0 && strcmp((fileinfo + i)->name, "..") != 0)
				i++;
		}
		_findclose(handle);
		cout << "����������" << endl;
		string info;//��������
		getline(cin, info);//��ȡ����
		int aaa = 0;//��¼��������
		for (int j = 0; j < i; j++)//���ϴ��ļ����Ա��Ƿ�ΪҪ���ҵ�ѧ��
		{
			string nnn = fileinfo[j].name;
			nnn = "E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\" + nnn;
			ifstream fin(nnn);
			string number;
			string name;
			fin >> number >> name;
			if (name == info)
			{
				aaa++;
				double score;
				bool a;
				fin >> score >> a;
				if (a)
				{
					cout << "��δ�μӿ��ԣ��޳ɼ�" << endl;
				}
				else
				{
					int position;
					time_t t;
					fin >> position >> t;
					cout << number << " " << name;
					cout << " �ɼ���" << score << "\t" << "���Σ�" << position << "\t" << asctime(localtime(&t)) << endl;
				}
			}
			fin.close();
		}
		if (aaa > 0)//�������������
		{
			cout << "��"<<aaa<<"��������������������д����ֵĿ�����Ϣ" << endl;
		}
		else
			cout << "��δ���ڴ˿���" << endl;
		break;
	}
	default:
		cout << "���������!" << endl;
		return 0;
	}
}

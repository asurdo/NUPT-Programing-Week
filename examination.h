#include"inquiry.h"
int examination()
{
	cout << "���������ѧ��(���س�����)��";
	string num;//����ѧ��
	getline(cin,num);
	num = "E:\\B140403_ѧ������\\�����_������Ϣ����ϵͳ\\kao\\" + num;
	ifstream fin(num.c_str());//��ѧ���ļ�
	if (!fin.is_open())//������ܳɹ���
	{
		cout << "������󣬲����ڴ�ѧ��" << endl;
		return 0;
	}
	string number;
	string name;
	bool a;
	double score;
	int position;
	fin >> number >> name >> score >> a >> position;//����˿�����Ϣ
	fin.close();
	if (a)//���δ�μӿ���
	{
		student m(number, name, score, a, position);//��������m
		exam h(m);//����exam����
		h.start();//��ʼ����
	}
	else {//�μӹ�����
		cout << "�Ѿ��μӹ����ԵĲ�׼�ڶ��βμ�" << endl;
	}
	return 0;
}

#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
#define M_ROW_SIZE 1024//��λ��bit
#define M_COL_SIZE 8
#define INSTRUCTION_SIZE 26
#define DATA_SIZE 8
#define ADDRESS_SIZE 3

/*MUXʹ��class����������class��*/
/*�������ú�������*/


int main()
{
	/*����M����־λ��*/
	int M[M_ROW_SIZE][M_COL_SIZE];//�ڴ�//һ��ָ�����һ��ָ����ݣ�
	int R[4][DATA_SIZE];//�Ĵ���
	int DR[DATA_SIZE];//DATA_register
	int AR[ADDRESS_SIZE];//ADDRESS_register
	int IR[INSTRUCTION_SIZE];//INSTRUCTION register
	int ZF, CF, OF, NF, TF;//״̬�Ĵ���
	int PC[ADDRESS_SIZE];//���������PC�������һ��ָ�����ڵ�Ԫ�ĵ�ַ ������Ҫclass����

	
	/*���ļ��������,д��M*/
	ifstream f_prog("program.txt", ios::in);
	if (f_prog)
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		exit(0);
	}
	f_prog.seekg(0, fstream::beg);
	while (f_prog.eof())//??
	{
		f_prog>>
	}
	cout << "����������ɡ�" << endl;

	cout<<"������TF����0����ִ��"
	/*ȡָ-����-ִ��*/
	while ()
	{
		copy(PC, PC + ADDRESS_SIZE, AR);//PC->AR
		//AR->M//��Ҫ��ַ��������

		
	}



}
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

/*ȫ�ֱ���*/
/*����M����־λ��*/
int M[M_ROW_SIZE][M_COL_SIZE];//�ڴ�//һ��ָ�����һ��ָ����ݣ�
char R[4][DATA_SIZE];//�Ĵ���
//int DR[DATA_SIZE];//DATA_register
int AR[ADDRESS_SIZE];//ADDRESS_register
int IR[INSTRUCTION_SIZE];//INSTRUCTION register
int ZF, CF, OF, NF, TF;//״̬�Ĵ���
int PC[ADDRESS_SIZE];//���������PC�������һ��ָ�����ڵ�Ԫ�ĵ�ַ ������Ҫclass����
int DBUS[DATA_SIZE],IBUS[INSTRUCTION_SIZE];//����
int ALU_A[DATA_SIZE], ALU_B[DATA_SIZE];


int main()
{
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
		copy(PC, PC + ADDRESS_SIZE, AR);//PC->
		//AR->M//��Ҫ��ַ��������

		
	}



}
void add(char R0[], char R1[])
{
	copy(R0, R0 + DATA_SIZE, ALU_A);//R0->MUX_A->ALU
	copy(R1, R1 + DATA_SIZE, ALU_B);//R1->MUX_B->ALU
	//ALU->DBUS
	int C = 0;//��λ
	for (int i = 0; i < DATA_SIZE; i++)//ȫ����
	{
		DBUS[i] = ALU_A[i] ^ ALU_B[i] ^ C;
		C = (ALU_A[i] & ALU_B[i]) | (C&(ALU_A[i] ^ ALU_B[i]));
	}
	if (TF) display();
	
	/*ʱ��������ô���֣�������������*/
	copy(DBUS, DBUS + DATA_SIZE, R0);//DBUS->R0
	/*��־λ*/
	if (C) CF = 1;//��λ?????????
	if (atoi(R0) - atoi(R1) == 0)
		ZF = 1;
	else
		ZF = 0;
}
void cmp(char R1[],char R2[])//�Ƚ������Ĵ�������СΪDATA_SIZE
{
	if (atoi(R1) - atoi(R2) == 0)
		ZF = 1;
	else
		ZF = 0;
	//CF????
}
void jle()
{
	if ((NF^OF) | ZF)
		copy(IR + 23, IR + INSTRUCTION_SIZE, PC);
	else
		PC++
}

void display()
{
	cout << "R0:"; print_array(R[0], DATA_SIZE);
	cout << "  R1:"; print_array(R[1], DATA_SIZE);
	cout << "  R2:"; print_array(R[2], DATA_SIZE);
	cout << "  R3:"; print_array(R[3], DATA_SIZE);

	cout << "\nALU_A:"; print_array(ALU_A, DATA_SIZE);
	cout << "  ALU_B:"; print_array(ALU_B, DATA_SIZE);

	cout << "\nAR:"; print_array(AR, ADDRESS_SIZE);
	cout << "\nIR:"; print_array(IR, INSTRUCTION_SIZE);
	
	cout << "\nPC:"; print_array(PC, ADDRESS_SIZE);
	cout << "\nDBUS:"; print_array(DBUS, DATA_SIZE);
	cout << "\nIBUS:"; print_array(IBUS, INSTRUCTION_SIZE);

	cout << "ZF:" << ZF << "CF:" << CF << "OF:" << OF << "NF:" << NF << endl;
	getchar();
}
void print_array(int a[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << a[i];
	}
}
void print_array(char a[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << a[i];
	}
}
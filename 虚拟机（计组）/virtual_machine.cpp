#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
#define M_ROW_SIZE 1024//单位是bit
#define M_COL_SIZE 8
#define INSTRUCTION_SIZE 26
#define DATA_SIZE 8
#define ADDRESS_SIZE 3

/*MUX使用class？译码器用class？*/
/*译码器用函数？？*/

/*全局变量*/
/*申请M，标志位等*/
int M[M_ROW_SIZE][M_COL_SIZE];//内存//一半分给程序，一半分给数据？
char R[4][DATA_SIZE];//寄存器
//int DR[DATA_SIZE];//DATA_register
int AR[ADDRESS_SIZE];//ADDRESS_register
int IR[INSTRUCTION_SIZE];//INSTRUCTION register
int ZF, CF, OF, NF, TF;//状态寄存器
int PC[ADDRESS_SIZE];//程序计数器PC，存放下一条指令所在单元的地址 可能需要class？？
int DBUS[DATA_SIZE],IBUS[INSTRUCTION_SIZE];//总线
int ALU_A[DATA_SIZE], ALU_B[DATA_SIZE];


int main()
{
	/*从文件读入程序,写到M*/
	ifstream f_prog("program.txt", ios::in);
	if (f_prog)
	{
		cout << "文件打开失败！" << endl;
		exit(0);
	}
	f_prog.seekg(0, fstream::beg);
	while (f_prog.eof())//??
	{
		f_prog>>
	}
	cout << "程序载入完成。" << endl;

	cout<<"请设置TF：（0单步执行"
	/*取指-译码-执行*/
	while ()
	{
		copy(PC, PC + ADDRESS_SIZE, AR);//PC->
		//AR->M//需要地址译码器？

		
	}



}
void add(char R0[], char R1[])
{
	copy(R0, R0 + DATA_SIZE, ALU_A);//R0->MUX_A->ALU
	copy(R1, R1 + DATA_SIZE, ALU_B);//R1->MUX_B->ALU
	//ALU->DBUS
	int C = 0;//进位
	for (int i = 0; i < DATA_SIZE; i++)//全加器
	{
		DBUS[i] = ALU_A[i] ^ ALU_B[i] ^ C;
		C = (ALU_A[i] & ALU_B[i]) | (C&(ALU_A[i] ^ ALU_B[i]));
	}
	if (TF) display();
	
	/*时钟脉冲怎么体现？？？？？？？*/
	copy(DBUS, DBUS + DATA_SIZE, R0);//DBUS->R0
	/*标志位*/
	if (C) CF = 1;//进位?????????
	if (atoi(R0) - atoi(R1) == 0)
		ZF = 1;
	else
		ZF = 0;
}
void cmp(char R1[],char R2[])//比较两个寄存器，大小为DATA_SIZE
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
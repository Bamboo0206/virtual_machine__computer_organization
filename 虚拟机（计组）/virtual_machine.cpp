#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;
#define M_ROW_SIZE 16//单位是bit
//#define M_COL_SIZE 8
#define INSTRUCTION_SIZE 16
#define DATA_SIZE 16
#define ADDRESS_SIZE 4

/*全局变量*/
/*申请M，标志位等*/
int IM[M_ROW_SIZE][INSTRUCTION_SIZE];//内存：指存
int DM[M_ROW_SIZE][DATA_SIZE];//内存：数存
int R[4][DATA_SIZE];//寄存器
//int DR[DATA_SIZE];//DATA_register
int AR[ADDRESS_SIZE];//ADDRESS_register
int IR[INSTRUCTION_SIZE];//INSTRUCTION register
int ZF, CF, OF, NF, TF;//状态寄存器
int PC[ADDRESS_SIZE];//程序计数器PC，存放下一条指令所在单元的地址 可能需要class？？
int DBUS[DATA_SIZE],IBUS[INSTRUCTION_SIZE];//总线
int ALU_A[DATA_SIZE], ALU_B[DATA_SIZE];


void print_array(int a[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << a[i];
	}
}

int bin_to_dec(int a[], int size)
{
	int base = 1, result = 0;
	for (int i = 0; i < size; i++)
	{
		result += a[i] * base;
		base *=2;
	}
	return result;
}
void dtob(int num,int a[])//dec to bin
{
	int base = 1, result = 0;
	for (int i = 0; num!=0; i++)
	{
		a[i] = num % 2;
		num /= 2;
	}
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
	cout << "\nDBUS(DR):"; print_array(DBUS, DATA_SIZE);
	cout << "\nIBUS:"; print_array(IBUS, INSTRUCTION_SIZE);

	cout << "\nZF:" << ZF << "  CF:" << CF << "  OF:" << OF << "  NF:" << NF << endl;
	//getchar();
}
void my_copy(int *a, int *b, int *c)//[a,b)拷到c
{
	if (!c) cout << "访问空指针" << endl;
	for (int i = 0; a < b; a++)
	{
		c[i] = *a;
		i++;
	}
}


void add(int R0[], int R1[])
{
	cout << "add Rx,Ry\n";
		//<< "R0->MUX_A->ALU\tR1->MUX_B->ALU\tALU->DBUS\n";
	my_copy(R0, R0 + DATA_SIZE, ALU_A);//R0->MUX_A->ALU
	my_copy(R1, R1 + DATA_SIZE, ALU_B);//R1->MUX_B->ALU
	/*ALU->DBUS*/
	int C0 = 0,C1=0;//进位
	for (int i = 0; i < DATA_SIZE; i++)//全加器
	{
		DBUS[i] = ALU_A[i] ^ ALU_B[i] ^ C0;
		C1 = (ALU_A[i] & ALU_B[i]) | (C0&(ALU_A[i] ^ ALU_B[i]));
		C0 = C1;
	}
	//if (TF) display();
	

	my_copy(DBUS, DBUS + DATA_SIZE, R0);//DBUS->R0
	/*标志位*/
	CF = C1;//进位
	if (bin_to_dec(R0, DATA_SIZE) == 0)
		ZF = 1;
	else
		ZF = 0;
	//cout << "DBUS->R0\n";
	if (TF) display();
}
void my_or (int R0[], int R1[])//计算R0 | R1，结果保存在R0

{
	for (int i = 0; i < DATA_SIZE; i++)
	{
		R0[i] = R0[i] | R1[i];
	}
}
void my_xor(int R0[], int R1[])//计算R0^R1，结果保存在R0

{
	for (int i = 0; i < DATA_SIZE; i++)
	{
		R0[i] = R0[i] ^ R1[i];
	}
}
void my_not(int R0[])//R0各位取反，结果保存在R0
{
	for (int i = 0; i < DATA_SIZE; i++)
	{
		R0[i] = R0[i] ^ 1;
	}
}
void sub(int R0[], int R1[])//计算R0-R1，结果保存在R0
{
	int temp = bin_to_dec(R0, DATA_SIZE) - bin_to_dec(R1, DATA_SIZE);
	for (int i = 0; temp > 0; i++)
	{
		R0[i] = temp % 2;
		temp /= 2;
	}
}
void sto(int R0[], int R1[])//将R0储存到R1指向的内存单元
{
	int loc = bin_to_dec(R0, DATA_SIZE);
	my_copy(R1, R1 + DATA_SIZE, DM[loc]);
}
void cmp(int R0[],int R1[])//比较两个寄存器，大小为DATA_SIZE
{
	cout << "cmp Rx,Ry\n";
	if (bin_to_dec(R0, DATA_SIZE) - bin_to_dec(R1, DATA_SIZE) == 0)
		ZF = 1;
	else
		ZF = 0;
	if (bin_to_dec(R0, DATA_SIZE) - bin_to_dec(R1, DATA_SIZE) < 0)
		NF = 1;
	else
		NF = 0;

	if (TF) display();
}
void jle()
{
	cout << "jle\n";
	if ((NF^OF) | ZF)
	{
		my_copy(IR + 4, IR + 8, PC);
	}
	if (TF) display();
}
void mov()
{
	cout << "mov\n";
	int *Rx=NULL;
	if (bin_to_dec(IR + 4, 4) == 0) Rx = R[0];
	else if (bin_to_dec(IR + 4, 4) == 1) Rx = R[1];
	else if (bin_to_dec(IR + 4, 4) == 2) Rx = R[2];
	else if (bin_to_dec(IR + 4, 4) == 3) Rx = R[3];
	else cout << "不存在的寄存器！\n";
	//for (int i = DATA_SIZE-1; i > 7; i--)R[i] = 0;//0扩展到16位
	my_copy(IR + 8, IR + 16, Rx);//将立即数送到R寄存器
	if (TF) display();
}
void pcadd()//PC++
{
	int C0 = 1,C1=0;//进位
	for (int i = 0; i < ADDRESS_SIZE; i++)//全加器
	{
		C1 = PC[i] & C0;
		PC[i] = PC[i] ^ C0;
		C0 = C1;
	}
}
void jmp()//无条件转跳
{
	cout << "jmp\n";
	my_copy(IR + 4, IR +8, PC);//修改PC内的地址
	if (TF) display();
}



int main()
{
	/*从文件读入程序,写到M*/
	ifstream f_prog("program.txt", ios::in);
	if (!f_prog)
	{
		cout << "文件打开失败！" << endl;
		exit(0);
	}
	f_prog.seekg(0, fstream::beg);
	char ch;
	for (int row = 0, col = 0; !f_prog.eof();)
	{
		//f_prog >> ch;
		f_prog.get(ch);
		if (ch != '\n')
		{
			IM[row][col] = ch - '0';
			col++;
		}
		else
		{
			row++;
			col = 0;
		}
	}
	cout << "程序载入完成。" << endl;

	cout << "请设置TF：（1）单步调试，（0）全部执行\n";
	cin >> TF;

	/*初始化*/
	for (int i = 0; i < ADDRESS_SIZE; i++) PC[i] = 0;//初始化PC为第一条指令地址
	for (int k = 0; k < 4; k++)
		for (int i = 0; i < DATA_SIZE; i++)
			R[k][i] = 0;

	/*取指-译码-执行*/
	while (true)
	{
		/*取指令*/
		int row = bin_to_dec(PC, ADDRESS_SIZE);
		my_copy(IM[row], IM[row] + INSTRUCTION_SIZE, IBUS);//PC->M->IBUS
		my_copy(IBUS, IBUS + INSTRUCTION_SIZE, IR);//IBUS->IR
		pcadd();//PC+1->PC

		/*执行*/
		int OP = bin_to_dec(IR, 4);
		if (OP == 1) mov();/*mov*/
		else if (OP == 2) jmp();/*jmp*/
		else if (OP == 3)//add	
		{
			int x = bin_to_dec(IR + 4, 2), y = bin_to_dec(IR + 6, 8);
			add(R[x], R[y]);
		}
		else if (OP == 4)//cmp
		{
			int x = bin_to_dec(IR + 4, 2), y = bin_to_dec(IR + 6, 8);
			cmp(R[x], R[y]);
		}
		else if (OP == 5) jle();
		else if (OP == 6)//sto
		{
			int x = bin_to_dec(IR + 4, 2), y = bin_to_dec(IR + 6, 8);
			sto(R[x], R[y]);
		}
		else if (OP == 7)//sub
		{
			int x = bin_to_dec(IR + 4, 2), y = bin_to_dec(IR + 6, 8);
			sub(R[x], R[y]);
		}
		else if (OP == 8)//xor
		{
			int x = bin_to_dec(IR + 4, 2), y = bin_to_dec(IR + 6, 8);
			my_xor(R[x], R[y]);
		}
		else if (OP == 9)//or
		{
			int x = bin_to_dec(IR + 4, 2), y = bin_to_dec(IR + 6, 8);
			my_or(R[x], R[y]);
		}
		else if (OP == 9)//not
		{
			int x = bin_to_dec(IR + 4, 2);
			my_not(R[x]);
		}
		else if (OP == 15)//ret
		{
			cout << "程序运行结束。结果为：" << bin_to_dec(R[0], DATA_SIZE) << endl;
			return 0;
		}
		else cout << "不存在的指令\n";


		/*公操作*/
		//判断是否输入
		if (TF)
		{
			cout << "是否修改寄存器的值（0不修改/1修改）：";
			int change = 0;
			cin >> change;
			if (change)
			{
				int x = 0;
				cout << "请输入修改的寄存器的编号(0~3)：";
				cin >> x;
				string data;
				cout << "请输入修改的值（16位二进制，左端为最低位）：";
				cin >> data;
				for (int i = 0; i < DATA_SIZE; i++)
					R[x][i] = data[i]-'0';
			}
		}
	}


	return 0;
}


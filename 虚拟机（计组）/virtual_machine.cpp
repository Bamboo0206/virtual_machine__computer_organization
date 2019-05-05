#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
#define M_ROW_SIZE 16//��λ��bit
//#define M_COL_SIZE 8
#define INSTRUCTION_SIZE 16
#define DATA_SIZE 16
#define ADDRESS_SIZE 4

/*ȫ�ֱ���*/
/*����M����־λ��*/
int IM[M_ROW_SIZE][INSTRUCTION_SIZE];//�ڴ�//һ��ָ�����һ��ָ����ݣ�
int R[4][DATA_SIZE];//�Ĵ���
//int DR[DATA_SIZE];//DATA_register
int AR[ADDRESS_SIZE];//ADDRESS_register
int IR[INSTRUCTION_SIZE];//INSTRUCTION register
int ZF, CF, OF, NF, TF;//״̬�Ĵ���
int PC[ADDRESS_SIZE];//���������PC�������һ��ָ�����ڵ�Ԫ�ĵ�ַ ������Ҫclass����
int DBUS[DATA_SIZE],IBUS[INSTRUCTION_SIZE];//����
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
//int reverse_btod(int a[], int size)//���±���ǵ�λ
//{
//	int base = 1, result = 0;
//	for (int i = size-1; i >=0; i--)
//	{
//		result += a[i] * base;
//		base *= 2;
//	}
//	return result;
//}
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

	cout << "\nZF:" << ZF << "  CF:" << CF << "  OF:" << OF << "  NF:" << NF << endl;
	//getchar();
}
void my_copy(int *a, int *b, int *c)//[a,b)����c
{
	if (!c) cout << "���ʿ�ָ��" << endl;
	for (int i = 0; a < b; a++)
	{
		c[i] = *a;
		i++;
	}
}


void add(int R0[], int R1[])
{
	cout << "add Rx,Ry\n"
		<< "R0->MUX_A->ALU\tR1->MUX_B->ALU\tALU->DBUS\n";
	my_copy(R0, R0 + DATA_SIZE, ALU_A);//R0->MUX_A->ALU
	my_copy(R1, R1 + DATA_SIZE, ALU_B);//R1->MUX_B->ALU
	/*ALU->DBUS*/
	int C0 = 0,C1=0;//��λ
	for (int i = 0; i < DATA_SIZE; i++)//ȫ����
	{
		DBUS[i] = ALU_A[i] ^ ALU_B[i] ^ C0;
		C1 = (ALU_A[i] & ALU_B[i]) | (C0&(ALU_A[i] ^ ALU_B[i]));
		C0 = C1;
	}
	/*int temp = bin_to_dec(R0, DATA_SIZE) + bin_to_dec(R1, DATA_SIZE);
	cout << "add�����" << temp << endl;
	dtob(temp, R0);*/
	if (TF) display();
	

	my_copy(DBUS, DBUS + DATA_SIZE, R0);//DBUS->R0
	/*��־λ*/
	CF = C1;//��λ?????????
	if (bin_to_dec(R0, DATA_SIZE) == 0)
		ZF = 1;
	else
		ZF = 0;
	cout << "add:   DBUS->R0\n";
	if (TF) display();
}
void cmp(int R0[],int R1[])//�Ƚ������Ĵ�������СΪDATA_SIZE
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

	//CF????
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
	else cout << "�����ڵļĴ�����\n";
	//for (int i = DATA_SIZE-1; i > 7; i--)R[i] = 0;//0��չ��16λ
	my_copy(IR + 8, IR + 16, Rx);//���������͵�R�Ĵ���
	if (TF) display();
}
void pcadd()
{
	int C0 = 1,C1=0;//��λ
	for (int i = 0; i < ADDRESS_SIZE; i++)//ȫ����
	{
		C1 = PC[i] & C0;
		PC[i] = PC[i] ^ C0;
		C0 = C1;
	}
}
void jmp()//������ת��
{
	cout << "jmp\n";
	my_copy(IR + 4, IR +8, PC);//�޸�PC�ڵĵ�ַ
	if (TF) display();
}



int main()
{
	/*���ļ��������,д��M*/
	ifstream f_prog("program.txt", ios::in);
	if (!f_prog)
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
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
	cout << "����������ɡ�" << endl;

	cout << "������TF����1���������ԣ���0��ȫ��ִ��\n";
	cin >> TF;

	/*��ʼ��*/
	for (int i = 0; i < ADDRESS_SIZE; i++) PC[i] = 0;//��ʼ��PCΪ��һ��ָ���ַ
	for (int k = 0; k < 4; k++)
		for (int i = 0; i < DATA_SIZE; i++)
			R[k][i] = 0;

	/*ȡָ-����-ִ��*/
	while (true)
	{
		/*ȡָ��*/
		int row = bin_to_dec(PC, ADDRESS_SIZE);
		my_copy(IM[row], IM[row] + INSTRUCTION_SIZE, IBUS);//PC->M->IBUS
		my_copy(IBUS, IBUS + INSTRUCTION_SIZE, IR);//IBUS->IR
		pcadd();//PC+1->PC

		/*ִ��*/
		int OP = bin_to_dec(IR, 4);
		if (OP == 1) mov();/*mov*/
		else if (OP == 2) jmp();/*jmp*/
		else if (OP == 3)//add	
		{
			int x = bin_to_dec(IR + 4, 2), y = bin_to_dec(IR + 6, 8);
			add(R[x], R[y]);
		}
		else if (OP == 4)
		{
			int x = bin_to_dec(IR + 4, 2), y = bin_to_dec(IR + 6, 8);
			cmp(R[x], R[y]);
		}
		else if (OP == 5) jle();
		else if (OP == 15)
		{
			cout << "�������н��������Ϊ��" << bin_to_dec(R[0], DATA_SIZE) << endl;
			return 0;
		}
		else cout << "�����ڵ�ָ��\n";


		/*������*/
		//getchar();
		//�ж��Ƿ�����
		if (TF)
		{
			cout << "�Ƿ��޸ļĴ�����ֵ��0���޸�/1�޸ģ���";
			int change = 0;
			cin >> change;
			if (change)
			{
				int x = 0;
				cout << "�������޸ĵļĴ����ı�ţ�";
				cin >> change;
				string data;
				cout << "�������޸ĵ�ֵ��16λ����";
				cin >> change;
				for (int i = 0; i < DATA_SIZE; i++)
					R[x][i] = data[i];
			}
		}
	}


	return 0;
}


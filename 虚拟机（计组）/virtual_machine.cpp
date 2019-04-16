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


int main()
{
	/*申请M，标志位等*/
	int M[M_ROW_SIZE][M_COL_SIZE];//内存//一半分给程序，一半分给数据？
	int R[4][DATA_SIZE];//寄存器
	int DR[DATA_SIZE];//DATA_register
	int AR[ADDRESS_SIZE];//ADDRESS_register
	int IR[INSTRUCTION_SIZE];//INSTRUCTION register
	int ZF, CF, OF, NF, TF;//状态寄存器
	int PC[ADDRESS_SIZE];//程序计数器PC，存放下一条指令所在单元的地址 可能需要class？？

	
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
		copy(PC, PC + ADDRESS_SIZE, AR);//PC->AR
		//AR->M//需要地址译码器？

		
	}



}
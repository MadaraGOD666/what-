#include <fstream>
#include <ctype.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class account //��������������� ������� �� �������
{
	int acc_nomer;
	char name[50];
	int depozit;
	char type;

public:
	void create_account(); //��������� �� ���������� - ������� �� ������
	void show_account();  //������� ���������� �� ������
	void modify();       //��������� �� ���� ����������
	void dep(int);      //��������� ������� - ������ ����
	void draw(int);    //������ ������� - ������ ����
	void report();    //������� ���������� � �������� ������
	int retacno();      //����� ������ �� ������� (return)
	int	retdeposit();  //����� ���������� �� ������� (return)
	char rettype();   //����� ���� �� ������� (return)
};
void account::create_account()
{
	cout<<"\n�������� ������ �� �������";
	cin>>acc_nomer;
	cout<<"\n�������� ����� �� �������:";
	gets(name); //'gets' �� ������ ������ '[50]', ��� '[50]' ---> 'cout'
	cout<<"\n�������� ���� �� ������� (� �� ���������, � �� �����)";
	cin>>type; type=toupper(type); //����� ������� ����� ������
	cout<<"\n�������� ������������ �������� �� �������"
	"\n(500 �� ��� ������ �� ����������� ��� 1000 � ������ �� ������ ������";
	cin<<depozit;
	cout<<"\n\n\n������ ��������!";
}
void account::show_account()
{
	cout<<"\n����� �� �������: "<<acc_nomer;
	cout<<"\n��� �� �������:\n";
	cout<<name;
	cout<<"\n��� �� �������: "<<type;
	cout<<"\n������ ���� � �������: "<<depozit;
}
void account::modify()
{
	cout<<"\n�������� ����� �� �������"<<acc_nomer;
	cout<<"\n�������� ����� �� �������"<<name;
	cout<<"\n�������� ���� �� ������� (� �� ���������, � �� �����)"<<type;
	cin>>type; type=toupper(type);
	cout<<"\n�������� ����";
	cin>>depozit;
}
void account::dep(int x)
{
	depozit+=x;
}
void account::draw(int x)
{
	depozit+=x;
}
void account::report()
{
	cout<<acc_nomer<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<depozit<<endl;
}
int account::retacno()
{
	return acc_nomer;
}
int account::retdeposit()
{
	return depozit;
}
char account::rettype()
{
	return type;
}

void write_account();	     //��������� �� �����
void display_info(int);	    //��������� �� ������� �� �����������
void modify_account(int);  //��������� �� ����������
void delete_account(int); //��������� �� ����
void display_all();		          //��������� �� ������������ �� ������ �������
void deposit_withdraw(int, int); //������� � ������� �� ���� �� ������
void intro();	                //������� �����

int main()
{
	char ch;
	int num;
	clrscr();
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\t������ ����";
		cout<<"\n\n\t01. ��� ������";
		cout<<"\n\n\t02. �������";
		cout<<"\n\n\t03. �������";
		cout<<"\n\n\t04. ������� �� �������";
		cout<<"\n\n\t05. ���� � ������ �������";
		cout<<"\n\n\t06. ������� ������";
		cout<<"\n\n\t07. ������� ������";
		cout<<"\n\n\t08. �����";
		cout<<"\n\n\t�������� ����� (1-8)";
		cin>>ch;
		clrscr();
		switch(ch)
		{
			case '1':
				write_account();
				break;
			case '2':
				cout<<"\n\n\t�������� ����� �� �������: "; cin>>num;
				deposit_withdraw(num, 1);
				break;
			case '3':
				cout<<"\n\n\t�������� ����� �� �������: "; cin>>num;
				deposit_withdraw(num, 2);
				break;
			case '4':
				cout<<"\n\n\t�������� ����� �� �������: "; cin>>num;
				display_info(num);
				break;
			case '5':
				display_all();
				break;
			case '6':
				cout<<"\n\n\t�������� ����� �� �������: "; cin>>num;
				delete_account(num);
				break;
			 case '7':
				cout<<"\n\n\t�������� ����� �� �������: "; cin>>num;
				modify_account(num);
				break;
			 case '8':
				cout<<"\n\n\t���������� �� �� ����������� �������� ��!";
				break;
			 default :cout<<"\a";
		}
			getch();
	}while(ch!='8');
	return 0;
}
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write((char *) &ac, sizeof(account));
	outFile.close();
}
void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"������ �� ���� �� ���� ������� !! ��������� �����...";
		return;
	}
	cout<<"\n������� �� ��������\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\n������ �� ������� �� ����������";
}
void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"������ �� ���� �� ���� ������� !! ��������� �����...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\n�������� ������ ����� �� �������"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t �������� �������������";
			found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n �������� �� ���� �� ���� �������� ";
}
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"������ �� ���� �� ���� ������� !! ��������� �����...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write((char *) &ac, sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\t�������� �������";
}
void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"������ �� ���� �� ���� ������� !! ��������� �����...";
		return;
	}
	cout<<"\n\n\t\t���� � �������\n\n";
	cout<<"====================================================\n";
	cout<<"�/� �      ���           ���  ������\n";
	cout<<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//function to deposit and withdraw amounts
void deposit_withdraw(int n, int option)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"������ �� ���� �� ���� ������� !! ��������� �����...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\t�������";
				cout<<"\n\n�������� ���� �� �������";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\t�������";
				cout<<"\n\n�������� ���� �� �������";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='�') || (bal<1000 && ac.rettype()=='�'))
					cout<<"������������ ������";
				else
					ac.draw(amt);
			}
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t �������� �������������";
			found=1;
	       }
	}
	File.close();
	if(found==0)
		cout<<"\n\n�������� �� ���� �� ���� ��������";
}
void intro()
{
	cout<<"\n\n\n\t�������";
	cout<<"\n\n\t��";
	cout<<"\n\n\t���������";
	cout<<"\n\n\n\n��������: ������ ��������";
	cout<<"\n\n�����������/��������/�������: ��-�����/����/���";
	getch();
}

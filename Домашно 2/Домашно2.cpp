#include <fstream>
#include <ctype.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class account //информационните единици на акаунта
{
	int acc_nomer;
	char name[50];
	int depozit;
	char type;

public:
	void create_account(); //прибавяне не информация - създава се акаунт
	void show_account();  //показва информация на екрана
	void modify();       //прибавяне на нова информация
	void dep(int);      //увеличава числото - влагаш пари
	void draw(int);    //намаля числото - теглиш пари
	void report();    //показва информация в табличен формат
	int retacno();      //връща номера на акаунта (return)
	int	retdeposit();  //връща стойността на акоунта (return)
	char rettype();   //връща вида на акоунта (return)
};
void account::create_account()
{
	cout<<"\nВъведете номера на акаунта";
	cin>>acc_nomer;
	cout<<"\nВъведете името на клиента:";
	gets(name); //'gets' се ползва заради '[50]', без '[50]' ---> 'cout'
	cout<<"\nВъведете вида на акаунта (С за спестовен, Т за текущ)";
	cin>>type; type=toupper(type); //прави малките букви ГЛАВНИ
	cout<<"\nВъведете първоначална стойност на акаунта"
	"\n(500 лв или повече за спестявания или 1000 и повече за текуща сметка";
	cin<<depozit;
	cout<<"\n\n\nАкаунт създаден!";
}
void account::show_account()
{
	cout<<"\nНомер на акаунта: "<<acc_nomer;
	cout<<"\nИме на клиента:\n";
	cout<<name;
	cout<<"\nВид на акаунта: "<<type;
	cout<<"\nТекуща сума в акаунта: "<<depozit;
}
void account::modify()
{
	cout<<"\nВъведете номер на акаунта"<<acc_nomer;
	cout<<"\nВъведете името на клиента"<<name;
	cout<<"\nВъведете вида на акаунта (С за спестовен, Т за текущ)"<<type;
	cin>>type; type=toupper(type);
	cout<<"\nВъведете сума";
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

void write_account();	     //записване на данни
void display_info(int);	    //показване на данните на потребителя
void modify_account(int);  //променяне на информация
void delete_account(int); //изтриване на файл
void display_all();		          //показване на информацията на всички акаунти
void deposit_withdraw(int, int); //внасяне и теглене на пари от акаунт
void intro();	                //начален екран

int main()
{
	char ch;
	int num;
	clrscr();
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tГЛАВНО МЕНЮ";
		cout<<"\n\n\t01. НОВ АКАУНТ";
		cout<<"\n\n\t02. ВНАСЯНЕ";
		cout<<"\n\n\t03. ТЕГЛЕНЕ";
		cout<<"\n\n\t04. СПРАВКА НА БАЛАНСА";
		cout<<"\n\n\t05. ЛИСТ С ВСИЧКИ АКАУНТИ";
		cout<<"\n\n\t06. ЗАТВОРИ АКАУНТ";
		cout<<"\n\n\t07. ПРОМЕНИ АКАУНТ";
		cout<<"\n\n\t08. ИЗХОД";
		cout<<"\n\n\tИзберете Опция (1-8)";
		cin>>ch;
		clrscr();
		switch(ch)
		{
			case '1':
				write_account();
				break;
			case '2':
				cout<<"\n\n\tВъведете номер на акаунта: "; cin>>num;
				deposit_withdraw(num, 1);
				break;
			case '3':
				cout<<"\n\n\tВъведете номер на акаунта: "; cin>>num;
				deposit_withdraw(num, 2);
				break;
			case '4':
				cout<<"\n\n\tВъведете номер на акаунта: "; cin>>num;
				display_info(num);
				break;
			case '5':
				display_all();
				break;
			case '6':
				cout<<"\n\n\tВъведете номер на акаунта: "; cin>>num;
				delete_account(num);
				break;
			 case '7':
				cout<<"\n\n\tВъведете номер на акаунта: "; cin>>num;
				modify_account(num);
				break;
			 case '8':
				cout<<"\n\n\tБлагодарим ви че използвахте услугите ни!";
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
		cout<<"Файлът не може да бъде отворен !! Натиснете бутон...";
		return;
	}
	cout<<"\nДетайли на сметката\n";
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
		cout<<"\n\nНомера на акаунта не съществува";
}
void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Файлът не може да бъде отворен !! Натиснете бутон...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nВъведете новите данни на акаунта"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Сметката Актуализирана";
			found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n Сметката не може да бъде намарена ";
}
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Файлът не можа да бъде отворен !! Натиснете бутон...";
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
	cout<<"\n\n\tСметката закрита";
}
void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Файлът не може да бъде отворен !! Натиснете бутон...";
		return;
	}
	cout<<"\n\n\t\tЛист с акаунти\n\n";
	cout<<"====================================================\n";
	cout<<"А/к №      ИМЕ           Вид  Сметка\n";
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
		cout<<"Файлът не може да бъде отворен !! Натиснете бутон...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tВНАСЯНЕ";
				cout<<"\n\nВъведете сума за внасяне";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tТЕГЛЕНЕ";
				cout<<"\n\nВъведете сума за теглене";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='Т') || (bal<1000 && ac.rettype()=='С'))
					cout<<"Недостатъчна сметка";
				else
					ac.draw(amt);
			}
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Сметката Актуализирана";
			found=1;
	       }
	}
	File.close();
	if(found==0)
		cout<<"\n\nСметката не може да бъде намерена";
}
void intro()
{
	cout<<"\n\n\n\tСИСТЕМА";
	cout<<"\n\n\tЗА";
	cout<<"\n\n\tБАНКИРАНЕ";
	cout<<"\n\n\n\nНаправил: Реджеб Искренов";
	cout<<"\n\nУниверситет/Факултет/Катедра: ТУ-варна/ФИТА/СИТ";
	getch();
}

#include <iostream>
#include <string>
using namespace std;

int main()
 {
	int teglo,Kteglo;
	while (teglo<0||teglo>10)
	{
		cout<<"�������� ������� �� ������ (�� 0 �� 10).\n";
		cin>>teglo;

		if(teglo>0||teglo<=1)
		{
			Kteglo=2;
		}
		if(teglo>1||teglo<=2)
		{
			Kteglo=3.5;
		}
		if(teglo>2||teglo<=5)
		{
			Kteglo=7;
		}
		if(teglo>7||teglo<=10)
		{
			Kteglo=12;
		}
	}

	int zona,Kzona;
	while (zona<1||zona>3)
	{
		cout<<"�������� ������ �� ��������� (�� 1 �� 3).\n";
		cin>>zona;

		if(zona==1)
		{
			Kzona=2;
		}
		if(zona==2)
		{
			Kzona=3.5;
		}
		if(zona==3)
		{
			Kzona=7;
		}
	}

	int K,L,M,N;
	L=0.05;
	M=0.5;
	N=1;


	cout<<"�������� �� ���������� �� 3 ���� �����.\n";









	int zona;
	cout<<"�������� ���� �� ��������� (�� 1 �� 3)\n";
	cin>>zona;



	return 0;
}

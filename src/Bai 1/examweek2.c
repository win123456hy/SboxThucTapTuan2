// examweek2.cpp : Defines the entry point for the console application.
//

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
void docFile(char*a) {//doc file co ten file la chuoi a
	FILE *f= f = fopen(a, "r");;
	char chuoi[255];
	fgets(chuoi, 255, f);
	puts(chuoi);
	fclose(f);
}
void nhapmang(char*a) {
	int kt;
	printf("Nhap chuoi ngoac can kiem tra:");
	do {
		
		gets(a);
		for (int i = 0; i < strlen(a); i++)
		{
			if (a[i] == '(' || a[i] == ')') {
				kt = 1;
				continue;
			}
			else {
				kt = 0;
				break;
			}
		}
		if (kt == 0)
			printf("Nhap lai:");
	} while (kt!=1);
	printf("Chuoi vua nhap:%s",a);
}
void ghiFile(char*a,char *b)//ghi ra file gia tri a, ten file b
{
	FILE *f=fopen(b, "w");
	fprintf(f,a);
	fclose(f);
}
int kiemtradayngoac(char*a) {
	char temp;
	label:
	temp = a[0];
	if (temp == ')')
		return 0;
	else if(temp=='(')
	for (int i = 1; i < strlen(a); i++)
	{
		if (a[i] == ')') {
			XoaTaiViTri(a, 0); XoaTaiViTri(a, i-1);
			goto label;
		}
		else
			continue;
	}
	int check=0;
	if (a[0] ==NULL ) {
		check = 1;
		return 1;
	}
	else
		return 0;
}
int XoaTaiViTri(char*a, int vitri)
{
	for (int i = vitri; i < strlen(a); i++)
		a[i] = a[i + 1];
}
void suadayngoacsai() {
	FILE *f = f = fopen("BRACKET.INP", "r");;
	char chuoi[255];
	fgets(chuoi, 255, f);
	int sodaumongoac=0,sodaudongngoac=0,sodaucanthem=0;
	//=================================================================================================================
	// Dem so dau ngoac mo va so dau ngoac dong trong chuoi
	for (int i = 0; i < strlen(chuoi); i++)
	{
		if (chuoi[i] == '(')
			sodaumongoac++;
		else if (chuoi[i] == ')')
			sodaudongngoac++;
	}
	//=================================================================================================================
	FILE *f1 = fopen("BRACKET.OUT", "w");
	int flag = 0;
	//=================================================================================================================
	// Neu so ngoac dong bang so ngoac mo thi check tiep
	if (sodaumongoac == sodaudongngoac) {

		// Neu dau chuoi la dau dong ngoac thi them 2 dau vao file BRACKET.OUT: 1 dau mo ngoac o dau chuoi va mot dau dong ngoac o cuoi chuoi
		if (chuoi[0] == ')') {
			sodaucanthem = 2;
			fprintf(f1, "%d", sodaucanthem);
			fprintf(f1, "\n( %d", 0);
			fprintf(f1, "\n) %d", strlen(chuoi)-1);
		}
	}
	//=================================================================================================================


	//=================================================================================================================
	//Neu so ngoac dong < so ngoac mo thi so ngoac can them(o day la so ngoac dong) bang so mo ngoac -so dong ngoac roi check tiep:
	if (sodaumongoac > sodaudongngoac) {
	

			sodaucanthem = sodaumongoac - sodaudongngoac;
			// Neu dau chuoi la dau dong ngoac thi tang so luong dau can them len va them 1 dau mo ngoac o dau chuoi
			if (chuoi[0] == ')') {
				sodaucanthem++;
				flag = 1;
			}
			fprintf(f1, "%d", sodaucanthem);
			if (flag == 1) {
				fprintf(f1, "\n( %d", 0);
			}
			// Tiep tuc them cac dau dong ngoac con lai bang voi so dau can them
		for (int i = strlen(chuoi); i <strlen(chuoi)+sodaucanthem ; i++)
		{
			
			fprintf(f1,"\n) %d",i);
			
		}
	}
	//=================================================================================================================
	
	//=================================================================================================================
	// Nguoc lai neu so dau mo ngoac < so dau song ngoac thi so dau can them(o day la so ngoac mo) bang so dau dong ngoac tru di so dau mo ngoac
	else if (sodaumongoac < sodaudongngoac) {
		sodaucanthem = sodaudongngoac - sodaumongoac;
		// Neu cuoi chuoi la dau mo ngoac thi tang so luong dau can them
		if (chuoi[strlen(chuoi) - 1] == '(') {
			sodaucanthem++;
			flag = 1;
		}
		fprintf(f1, "%d", sodaucanthem);
	
		// Tiep tuc la them so luong dau mo ngoac bang voi so luong dau can them
		for (int i = 0; i>-sodaucanthem; i--)
		{
			fprintf(f1, "\n( %d", i);
		}
		// Cuoi cung them 1 dau dong ngoac o cuoi chuoi
		if (flag == 1) {
			fprintf(f1, "\n) %d", strlen(chuoi));
		}
	}
	//=================================================================================================================
	fclose(f1);
	fclose(f);
}
int main()
{
	char a[255];
	nhapmang(a);
	ghiFile(a,"BRACKET.INP");

	int check=kiemtradayngoac(a);
	if (check == 1)
	{
		printf("\nChuoi da nhap la day ngoac dung");
		ghiFile("0", "BRACKET.OUT");
	}
	else {
		printf("\nChuoi da nhap khong phai la day ngoac dung");
		suadayngoacsai();
	}
	_getch();
	return 0;
}


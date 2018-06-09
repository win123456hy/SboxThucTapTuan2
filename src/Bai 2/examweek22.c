#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define max_length_one_line 128// Gioi han chieu dai cua mot dong trong file
//================================================================================================================
/*
Ghi chu:
file input.txt: File dau vao
file input2.txt: File tam dung de luu tat ca du lieu o file input.txt o dang chu thuong khi dung ham Replace
file input3.txt: File tam dung de luu du lieu khi hoan tat quy trinh thay the tu khoa cu sang tu
khoa moi khi doc tu file input2.txt len de xu ly
file resultsearch.txt: File luu tru gia tri tim kiem 
file resultsearch2.txt: File luu tru gia tri tim kiem khi thay the thanh cong
file tmpinput.txt: File tam dung de luu tat ca du lieu o file input.txt o dang chu thuong khi dunh ham Search
file output.txt: File dau ra luu lai lich su va ngu canh gan nhat
*/
//================================================================================================================
char *thaythe(const char *chuoibandau, const char *chuoicu,
	const char *chuoithaythe)
{
	char *kqtrave;
	int i, cnt = 0;
	int moi = strlen(chuoithaythe);
	int cu = strlen(chuoicu);

	// Dem so lan gap cua chuoi cu trong chuoi ban dau
	for (i = 0; chuoibandau[i] != '\0'; i++)
	{
		if (strstr(&chuoibandau[i], chuoicu) == &chuoibandau[i])
		{
			cnt++;

			// Nhay den vi tri sau chuoi cu
			i += cu - 1;
		}
	}

	// Tao khong gian cho ket qua tra ve
	kqtrave = (char *)malloc(i + cnt * (moi - cu) + 1);

	i = 0;
	while (*chuoibandau)
	{
		// So sanh chuoi con voi ket ket qua
		if (strstr(chuoibandau, chuoicu) == chuoibandau)
		{
			strcpy(&kqtrave[i], chuoithaythe);
			i += moi;
			chuoibandau += cu;
		}
		else
			kqtrave[i++] = *chuoibandau++;
	}

	kqtrave[i] = '\0';
	return kqtrave;
}
void nhap() {
	FILE *f,*f1;
	char a[255];
label:
	printf("> Enter file:");
	do {
		gets(a);
		f = fopen(a, "r");
		if (f == NULL)
		{
			printf("\n> File not exists");
			goto label;
		}
		else {
			printf("\n> Valid file, please choose the features:");
			break;
		}
	} while (f==NULL);
	f1 = fopen("output.txt","w");
	fprintf(f1,"Input file: %s\n",a);
	fclose(f);
	chuongtrinh(a,f1);
}
void Search(char *a,FILE *ff) {
	FILE *f,*f1,*f2;
	char chuoi[max_length_one_line], chuoi1[max_length_one_line], chuoi2[max_length_one_line];
	char key[255];

	int dong = 0,sokqtrave=0;
	fprintf(ff,"Context 1: search keyword\n");

	printf("> Enter keyword:");
	getchar();
	gets(key);
	fprintf(ff, "Keyword: %s\n", key);
	//================================================================================================================
	//  Thay the tu khoa sang chu thuong
	for (int i = 0; i < strlen(key); i++)
	{
		if (isupper(key[i])) {
			char c =key[i];
			key[i] = tolower(c);
		}
	}
	//================================================================================================================

	f = fopen(a, "r");
	f1= fopen("resultsearch.txt", "w");
	f2 = fopen("tmpinput.txt", "w");
	//================================================================================================================
	// Doc tung dong tu file input.txt va bien tung dong do thanh chu thuong. Cuoi cung in ra file tmpinput.txt
	while (fgets(chuoi, max_length_one_line, f)) {
		fprintf(f2,"%s", _strlwr(chuoi));
	}
	fclose(f2);
	//================================================================================================================
	f2 = fopen("tmpinput.txt", "r");

	//================================================================================================================
	// Tim vi tri cua tu khoa tren moi dong cua file tmpinput.txt
	while(fgets(chuoi2, max_length_one_line, f2)){
		dong++;
		    char* vtri=chuoi2;
	
			while (vtri = strstr(vtri, key))
			{
				sokqtrave++;
				fprintf(f1, "\t\tLine %d Col %d\n", dong, (int)(vtri - chuoi2) + 1);
				vtri++;
			}
	}
	//================================================================================================================
	fclose(f1);
	fclose(f2);
	
	f1 = fopen("resultsearch.txt", "r");
	printf("> Total appeared time:%d\n", sokqtrave);
	if (sokqtrave == 0)
		printf("Value not exists in file!");
	fprintf(ff,"Total postions(s): %d\n",sokqtrave);
	//================================================================================================================
	// Doc file resultsearch.txt va in ra man hinh va file output.txt
	while (fgets(chuoi1, max_length_one_line, f1)) {
		printf("%s",chuoi1);
		fprintf(ff,"%s",chuoi1);
	}
	//================================================================================================================

	fclose(f1);
	fclose(f);
}
void Replace(char *a,FILE *ff) {
	FILE *f = fopen(a,"r+");
	FILE *f2 = fopen("input2.txt", "w");
	printf("> Enter word<s>:");
	char words[255];
	getchar();
	gets(words);
	fprintf(ff,"Context 2: replace by new keyword\n");
	fprintf(ff, "Keyword: %s\n",words);

	printf("> Enter new word<s>:");
	char newwords[255];
	char word2[100];
	memset(word2, '\0', sizeof(word2));
	strcpy(word2, words);
	gets(newwords);
	fprintf(ff, "New keyword: %s\n", newwords);

	char sucess[200];
	memset(sucess, '\0', sizeof(sucess));
	strcat(sucess,"\t\tReplace \"");
	strcat(sucess, words);
	strcat(sucess,"\" by \"");
	strcat(sucess, newwords);
	strcat(sucess, "\" successfully");


	for (int i = 0; i < strlen(words); i++)
	{
		if (isupper(words[i])) {
			char c = words[i];
			words[i] = tolower(c);
		}
	}
	//================================================================================================================
	// Doc file input.txt va ghi ra file input2.txt theo tung dong voi dinh dang chu thuong
	char chuoi[max_length_one_line],chuoi2[max_length_one_line];
	char *chuoimodif,*chuoimodif2;
	while (fgets(chuoi, max_length_one_line, f)) {
		char *w1 = word2; char *w2 = _strlwr(words);
		chuoimodif = thaythe(chuoi,w1 ,w2 );
		fprintf(f2, "%s", chuoimodif);
	}
	//================================================================================================================
	fclose(f2);
	int dong = 0, sokqtrave = 0;
	char chuoi5[max_length_one_line];
	FILE *f5 = fopen("resultsearch2.txt","w");
	f2 = fopen("input2.txt", "r");
	//================================================================================================================
	// Doc file input2.txt va tim kiem tu khoa tren tung dong roi ghi ket qua tim kiem duoc ra file resultsearch2.txt
	while (fgets(chuoi5, max_length_one_line, f2)) {
		dong++;
		char* vtri = chuoi5;

		while (vtri = strstr(vtri, _strlwr(words)))
		{
			sokqtrave++;
			fprintf(f5, "\t\tLine %d Col %d\n", dong, (int)(vtri - chuoi5) + 1);
			vtri++;
		}
	}
	//================================================================================================================
	fclose(f2);
	fclose(f5);
	f5 = fopen("resultsearch2.txt", "r");
	printf("> Total appeared time:%d\n", sokqtrave);
	if (sokqtrave == 0)
		printf("> Value not exists in file!");
	fprintf(ff, "Total postions(s): %d\n", sokqtrave);
	char chuoii[max_length_one_line];
	//================================================================================================================
	// Doc file resultsearch2.txt va in ra man hinh va file output.txt
	while (fgets(chuoii, max_length_one_line, f5)) {
		printf("%s", chuoii);
		fprintf(ff, "%s", chuoii);
	}
	//================================================================================================================
	printf(sucess);
	fclose(f5);
	//================================================================================================================
	// Doc file input2.txt va thay the toan bo tu giong voi tu khoa bang tu khoa moi. Sau do in ra file input3.txt
	f2 = fopen("input2.txt", "r");
	FILE *f3 = fopen("input3.txt", "w");
	while (fgets(chuoi2, max_length_one_line, f2)) {
		chuoimodif2 = thaythe(chuoi2, _strlwr(words), newwords);
		fprintf(f3,"%s",chuoimodif2);
	}
	//================================================================================================================

	fclose(f3);
	fclose(f);
	fclose(f2);
	f = fopen(a, "r+");
	f3 = fopen("input3.txt", "r");
	char chuoi3[max_length_one_line];
	//================================================================================================================
	// Doc file input3.txt va ghi ra file input.txt
	while (fgets(chuoi3, max_length_one_line, f3)) {
		fprintf(f, "%s", chuoi3);
	}
	//================================================================================================================
	fclose(f3);
	fclose(f);
	
}
int chuongtrinh(char *a,FILE *f) {
	int chon;
	do {
		printf("\n--------------------------------------------------------");
		printf("\n\t\t1. Search");
		printf("\n\t\t2. Replace");
		printf("\n\t\t3. Exit");
		printf("\n--------------------------------------------------------");

		printf("\n> Choose the features::");
		scanf("%d", &chon);
		switch (chon)
		{
		case 1:Search(a,f); break;
		case 2:Replace(a,f); break;
		case 3:
			fclose(f); exit(0); break;
		default:
			break;
		}
	} while (chon > 0 || chon<4);
	

	
}

void main() {
	nhap();
	
	_getch();
}


#include<stdio.h>
#include<conio.h>
#include<string.h>
int mangso[1000];

void main() {
	
	FILE *f = fopen("INPUT.txt","r");
	FILE *f1 = fopen("OUTPUT.txt", "w");
	int i = 0;
	int mang[1000];
	while (fscanf(f,"%d",&mangso[i])>0)
	{
		mang[i] = mangso[i];
		i++;
	}
	
	int start = mang[2], next, end = mang[3], min = 0;
	fprintf(f1, "%d ", start);
	label:
	for (int i = 4; i < 1000; i=i+2)
	{
		if (mang[i] > 0 && mang[i] < 100 && mang[i+1] > 0 && mang[i+1] < 100) {
			if (min>0 &&(mang[i] + mang[i + 1]) > min&&(mang[i] == start || mang[i + 1] == start)&&next>start ){
				if (mang[i] == start) {
					next = mang[i-2];
				}
				else if (mang[i+1] == start)
				{
					next = mang[i - 1];
				}
			}
			else if (mang[i] == start) {
				next = mang[i + 1];
				min = start + next;
				if(next>start)
				continue;
			}
			else if (mang[i+1] == start) {
				next = mang[i];
				min = start + next;
				if(next>start)
				continue;
			}
			
		}
		else
		{
			break;
		}
	}
	
	start = next;
		fprintf(f1, "%d ", start);
		if (next == end)
			goto label1;
		else {
			min = 0;
			goto label;
		}
	label1:
	fclose(f);
	fclose(f1);
	char a[100];
	printf("Da tim ra duong di ngan nhat la:");
	f1 = fopen("OUTPUT.TXT","r");
	fgets(a,100,f1);
	printf(a);
	_getch();
}

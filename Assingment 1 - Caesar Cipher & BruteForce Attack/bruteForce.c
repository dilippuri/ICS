#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
	char s[1000]={'\0'};
	FILE *fs;
	fs=fopen("ciphertext.txt","r");
	fscanf(fs,"%[^\n]",s);
	fclose(fs);
	printf("Cipher text is : %s\n",s);
	char test[1000]={'\0'};
	int n;
	//here bruteForce starts....
	for(int i=1;i<=26;i++){
		int j=0;
		for(;j<strlen(s);j++){
			if(islower(s[j]))
				test[j] = ((s[j] - i - 122) % 26) + 122;
		    else if(isupper(s[j]))
				test[j] = ((s[j] - i - 90) % 26) + 90;
			else
				test[j] = s[j];
		}
		test[j]='\0';
		printf("%s\nPress 0 to continue and 1 to exit\n",test);
		scanf("%d",&n);
		if(n)
			exit(0);
	}
	return 0;
}
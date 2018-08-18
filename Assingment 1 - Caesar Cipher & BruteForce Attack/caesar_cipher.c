#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void plain_to_cipher(char *plain_text,char *cipher_text,int key){
	int i=0;
	for(;i<strlen(plain_text);i++){
		if(islower(plain_text[i]))
			cipher_text[i] = ((plain_text[i] + key - 97) % 26) + 97;
		else if(isupper(plain_text[i]))
			cipher_text[i] = ((plain_text[i] + key - 65) % 26) + 65;
		else
			cipher_text[i] = plain_text[i];
	}
	cipher_text[i]='\0';
}

void cipher_to_plain(char *plain_text,char *cipher_text,int key){
	int i=0;
	for(;i<strlen(cipher_text);i++){
		if(islower(cipher_text[i]))
			plain_text[i] = ((cipher_text[i] - key - 122) % 26) + 122;
		else if(isupper(cipher_text[i]))
			plain_text[i] = ((cipher_text[i] - key - 90) % 26) + 90;
		else
			plain_text[i] = cipher_text[i];
	}
	plain_text[i]='\0';
}

int main(){
	char plain_text[100];
	char cipher_text[100];
	printf("Enter key value\n");
	int key;
	scanf("%d",&key);
	
	FILE *fp,*fq;
	fp=fopen("plaintext.txt","r");
	fscanf(fp,"%99[^\n]",plain_text);
	fclose(fp);
	
	plain_to_cipher(plain_text,cipher_text,key);
	
	printf("%s\n",cipher_text);
	
	remove("ciphertext.txt");
	
	fq=fopen("ciphertext.txt","w");
	fprintf(fq,"%s",cipher_text);
	fclose(fq);
	
	//memset(plain_text, 0, 99);
	
	cipher_to_plain(plain_text,cipher_text,key);
	
	printf("%s\n",plain_text);
	
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void plain_to_cipher(char *plain_text,char *cipher_text,int key){
	int i=0;
	while(plain_text[i] != '\0'){
		if(islower(plain_text[i]))
			cipher_text[i] = ((plain_text[i] + key - 97) % 26) + 97;
		else if(isupper(plain_text[i]))
			cipher_text[i] = ((plain_text[i] + key - 65) % 26) + 65;
		else 
			cipher_text[i] = plain_text[i];
		i++;
	}
	cipher_text[i]='\0';
}

void freqAnalysis(int indx, char *cipher_text){

	int key = abs(indx - 4);//e has highest frequency , 4 is index value of e
		printf("key : %d ",key);
	char plain[100000] = {'\0'};
	for(int i=0;i<strlen(cipher_text);i++){
		if(islower(cipher_text[i]))
			plain[i] = ((cipher_text[i] - key - 122) % 26) + 122;
		else if(isupper(cipher_text[i]))
			plain[i] = ((cipher_text[i] - key - 90) % 26) + 90;
		else
			plain[i] = cipher_text[i];
	}
	printf("\n%s\n", plain);
}

int main(){
	char plain_text[100000];
	char cipher_text[100000];
	printf("Enter key value\n");
	int key;
	scanf("%d",&key);
	
	FILE *fp;
	fp=fopen("plaintext.txt","r");
	fscanf(fp,"%[^\n]" ,plain_text);
	fclose(fp);
	
	printf("\n%s\n",plain_text);
	
	plain_to_cipher(plain_text,cipher_text,key);
	
	printf("\n%s\n",cipher_text);
	

	int freq[26]={0};
	
	for(int i=0;i<strlen(cipher_text);i++){
		if(islower(cipher_text[i]))
			++freq[(cipher_text[i] % 97)];
		if(isupper(cipher_text[i]))
			++freq[(cipher_text[i] % 65)];
	}
	
	printf("\n");
	
	for(int i=0;i<26;i++)
		printf("%d ",freq[i]);
	
	printf("\n");
	
	while(1){
		int max=0,index=0,ex=1;
		for(int i=0;i<26;i++){
			if(max < freq[i]){
				max = freq[i];
			    index = i;
			    //freq[i] = 0;
		    }
	    }
	
	    printf("max : %d, index : %d\n",max,index);
	
	    freqAnalysis(index, cipher_text);
		
		freq[index]=0;
		
	    scanf("%d",&ex);
	    if(ex)
		    exit(1);
	}
	
	return 0;
}
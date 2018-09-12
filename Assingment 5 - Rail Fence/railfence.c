#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void removeSpaces(char *str){
    int count = 0;
	
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i]; 

    str[count] = '\0';
}

int upDown(int n){
	static int up = 0;
	static int down = 1;
	//printf("up =%d\n",up);
	//printf("down =%d\n",down);
	if(down == n){
		down = 0;
		up++;
	}
	if(up == n){
		up = 0;
		down++;
	}
	if(up){
		up++;
		return 1;
	}
	if(down){
		down++;
		return -1;
	}
	return 0;
}

int main(){
	char plain_text[1000];
	FILE *fs;
	fs = fopen("plaintext.txt","r");
    fscanf(fs,"%[^\n]",plain_text);
	printf("%s\n",plain_text);
	removeSpaces(plain_text);
	int n;
    printf("Enter number of levels\n");
	scanf("%d",&n);
	char rail[n][1000];
	for (int i=0;i<n;i++)
        for (int j=0;j<strlen(plain_text);j++)
            rail[i][j] = '\0';
	int j_idx[n];
	for(int i=0;i<n;i++)
		j_idx[i] = 0;
	int i_idx = 0;
	int k = 0;
	for(int i=0;i<strlen(plain_text);i++){
		if(i < n){
		   rail[i][j_idx[k]] = plain_text[i];
		   j_idx[k] = j_idx[k] + 1;
		   //printf("j_idx=%d\n",j_idx[k]);
		   if(k < n-1)
			   k++;
		   //printf("if k =%d\n",k);
		   //printf("%c\n",plain_text[i]);
		}
	    else{
			k += upDown(n);
			rail[k][j_idx[k]] = plain_text[i];
			j_idx[k] = j_idx[k] + 1;
			//printf("el k =%d\n",k);
			//printf("j_idx=%d\n",j_idx[k]);
			//printf("%c\n",plain_text[i]);
		}
	}
	/*for (int i=0;i<n;i++)
        for (int j=0;j<strlen(plain_text);j++)
            printf("%c ",rail[i][j]);
		printf("\n");*/
	char cipher_text[1000];
	i_idx = 0;
	k = 0;
	int x = 0;
	for(x=0;x<strlen(plain_text);x++){
		if(rail[i_idx][k] == '\0'){
			i_idx++;
			k = 0;
		}
		//printf("i_idx=%d k=%d\n",i_idx,k);
		//printf("%c\n",plain_text[x]);
		//printf("%c\n",rail[i_idx][k]);
		cipher_text[x] = rail[i_idx][k++];
	}
    cipher_text[x] = '\0';
	//printf("\n");
	printf("%s\n",cipher_text);
	FILE *fp;
	fp = fopen("ciphertext.txt","w");
	fprintf(fp,"%s",cipher_text);
	return 0;
}
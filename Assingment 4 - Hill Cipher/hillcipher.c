#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

void removeSpaces(char *str){
    int count = 0;
	
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i]; 

    str[count] = '\0';
}

void toLower(char s[]){
   int c = 0;
   while (s[c] != '\0'){
      if (s[c] >= 'A' && s[c] <= 'Z'){
	  
         s[c] = s[c] + 32;
      }
      c++;
   }
}

int main(){
	char plain_text[1000];
	
	FILE *fs;
	fs= fopen("plaintext.txt","r");
	fscanf(fs,"%[^\n]",plain_text);
	fclose(fs);
	
	printf("Plain text: %s\n",plain_text);
	
	removeSpaces(plain_text);
	
	toLower(plain_text);
	
	char key[25];
	printf("Enter key\n");
	scanf("%s",key);
	
	int n=sqrt(strlen(key));
	int kvalue[n][n];
	int i=0,j=0,k=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			kvalue[i][j] = key[k++]%97;
		}
	}
	
	printf("\n");
	printf("Key in matrix form\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d ",kvalue[i][j]);
		}
		printf("\n");
	}
	
	int len = strlen(plain_text);
	if(len % n == 1){
		//int pad = len % n;
		//for(int i=0;i<pad;i++)
		plain_text[len++] = 'x'; // padding
		plain_text[len] = '\0';
	}
	
	int N;
	N = strlen(plain_text)/n;
	//(n%2 == 0) ? (N = strlen(plain_text)/n) : (N = strlen(plain_text)/n + 1);
	int pvalue[n][N];
	k=0;
	for(i=0;i<n;i++){
		for(j=0;j<N;j++){
			pvalue[i][j] = plain_text[k++]%97;
		}
	}
	
	printf("\n");
	printf("Plain text in matrix form\n");
	for(i=0;i<n;i++){
		for(j=0;j<N;j++){
			printf("%d ",pvalue[i][j]);
		}
		printf("\n");
	}
	
	int cvalue[n][N];
	for(i=0;i<n;i++){
		for(j=0;j<N;j++){
			cvalue[i][j]=0;
			for(k=0;k<n;k++){
				cvalue[i][j]=(cvalue[i][j]+kvalue[i][k]*pvalue[k][j])%26;
			}
		}
	}
	
	printf("\n");
	printf("Cipher text in matrix form\n");
	for(i=0;i<n;i++){
		for(j=0;j<N;j++){
			printf("%d ",cvalue[i][j]);
		}
		printf("\n");
	}
	
	char ascii_to_char[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

	fs=fopen("ciphertext.txt","w");
	for(i=0;i<n;i++){
		for(j=0;j<N;j++){
			fprintf(fs,"%c",ascii_to_char[cvalue[i][j]]);
		}
	}
	fs = fopen("key.txt","w");
	fprintf(fs,"%s",key);
	fclose(fs);
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

int main(){
	char plain_text[100];
	printf("Enter plain text\n");
	scanf("%[^\n]",plain_text);
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
	int N=strlen(plain_text)/n;
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
	FILE *fs;
	fs=fopen("ciphertext.txt","w");
	for(i=0;i<n;i++){
		for(j=0;j<N;j++){
			fprintf(fs,"%c",ascii_to_char[cvalue[i][j]]);
		}
	}
	fclose(fs);
	return 0;
}
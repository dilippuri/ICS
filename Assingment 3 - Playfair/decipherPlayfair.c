#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

void revMap(int i,int j,int x,int y,char key[5][5],char plain_text[],int idx){
	printf("i=%d, j=%d\nx=%d y=%d\n",i,j,x,y);
	printf("idx = %d\n",idx);
	if(j == y){
			((i-1) % 5 > -1) ? (i = (i-1) % 5) : (i = (i+4) % 5);
		    ((x-1) % 5 > -1) ? (x = (x-1) % 5) : (x = (x+4) % 5);
	}
	
	else if(i == x){
		    ((j-1) % 5 > -1) ? (j = (j-1) % 5) : (j = (j+4) % 5);
		    ((y-1) % 5 > -1) ? (y = (y-1) % 5) : (y = (y+4) % 5);
	}
	
	else{
		int temp = j;
		j = y;
		y = temp;
	}
	printf("i=%d, j=%d\nx=%d y=%d\n",i,j,x,y);
	plain_text[idx] = key[i][j];
	plain_text[idx+1] = key[x][y];
	printf("%c  %c\n",key[i][j],key[x][y]);
}

void decipher(char key[5][5],char cipher_text[]){
	char plain_text[1000];
	int n = strlen(cipher_text);
	if(n%2 == 1)
		cipher_text[n] = 'X';
	n = strlen(cipher_text);
	
	int c_i;
	for(c_i=0;c_i<n;c_i+=2){
		int x1 = 0,y1 = 0,x2 = 0,y2 = 0;
	    bool mod1 = false,mod2 = false;
		printf("%c\n",cipher_text[c_i]);
		printf("%c\n",cipher_text[c_i + 1]);
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				if(cipher_text[c_i] == key[i][j]){
					x1 = i;
					y1 = j;
					mod1 = true;
				}
                if(cipher_text[c_i + 1] == key[i][j]){
					x2 = i;
					y2 = j;
					mod2 = true;
				}
                if(mod1 && mod2)
                    break;					
			}
		}
		revMap(x1,y1,x2,y2,key,plain_text,c_i);
	}
	plain_text[c_i] = '\0';
	
	printf("%s\n",plain_text);
}

int main(){
	char cipher_text[1000];
	char key[25];
	
	
	FILE *fs;
	fs = fopen("key.txt","r");
	fscanf(fs,"%s",key);
	fclose(fs);
	
	FILE *fp;
	fp = fopen("ciphertext.txt","r");
	fscanf(fp,"%s",cipher_text);
	fclose(fp);
	
	printf("%s\n",cipher_text);
	printf("%s\n",key);
	
	char keyMatrix[5][5];
	
	int k=0;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			keyMatrix[i][j] = key[k++];
		}
	}
	
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			printf("%c ",keyMatrix[i][j]);
		}
		printf("\n");
	}
	
	decipher(keyMatrix,cipher_text);
	
	return 0;
}
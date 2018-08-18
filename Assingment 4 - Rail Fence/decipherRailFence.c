#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

void removeSpaces(int key,int n,char rail[key][n]){
	
	for(int i=0;i<key;i++){
		int k = 0;
		for(int j=0;j<n;j++){
			if(rail[i][j] == '*'){
				rail[i][k] = rail[i][j];
				if(k != j)
					rail[i][j] = '\0';
				k++;
			}				
		}
	}
}

int main(){
	int n;
	printf("Enter the number of levels\n");
	scanf("%d",&n);
	char cipher_text[1000];
	FILE *fs;
	fs = fopen("ciphertext.txt","r");
	fscanf(fs,"%s",cipher_text);
	char rail[n][strlen(cipher_text)];
	for (int i=0;i<n;i++)
        for (int j=0;j<strlen(cipher_text);j++)
            rail[i][j] = '\0';
		
	bool dir_down;
 
    int row = 0, col = 0;
 
    // mark the places with '*'
    for (int i=0;i <strlen(cipher_text);i++){
        if (row == 0)
            dir_down = true;
	
        if (row == n-1)
            dir_down = false;
 
        // place the marker
        rail[row][col++] = '*';
 
        // find the next row using direction flag
        dir_down ? row++ : row--;
    }
	
	for (int i=0;i<n;i++){
        for (int j=0;j<strlen(cipher_text);j++)
            printf("%c ",rail[i][j]);
		printf("\n");
	}
	
	removeSpaces(n,strlen(cipher_text),rail);
	
	for (int i=0;i<n;i++){
        for (int j=0;j<strlen(cipher_text);j++)
            printf("%c ",rail[i][j]);
		printf("\n");
	}
	
	int index = 0;
    for (int i=0;i<n;i++)
        for (int j=0;j<strlen(cipher_text);j++)
            if (rail[i][j] == '*' && index<strlen(cipher_text))
                rail[i][j] = cipher_text[index++];
	
    for (int i=0;i<n;i++){
        for (int j=0;j<strlen(cipher_text);j++)
            printf("%c ",rail[i][j]);
		printf("\n");
	}
	
	char plain_text[1000];
	int j_idx[n];
	for(int i=0;i<n;i++)
		j_idx[i] = 0;
	row = 0, index = 0;
    for (int i=0;i<strlen(cipher_text);i++){
		
		col = j_idx[row];
		
        // check the direction of flow
        if (row == 0)
            dir_down = true;
			
        if (row == n-1)
            dir_down = false;
 
        // place the marker
        if (rail[row][col] != '\0'){
            plain_text[index++] = rail[row][col];
			++j_idx[row];
		}
 
        // find the next row using direction flag
        dir_down ? row++: row--;
    }
	plain_text[index] = '\0';
	printf("%s\n",plain_text);
	
	fs = fopen("plaintext.txt","a");
	fprintf(fs,"\nAfter Decryption : %[^\n]",plain_text);
	
	return 0;
}
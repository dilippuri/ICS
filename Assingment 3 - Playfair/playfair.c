#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

void removeSpaces(char *str){
    int count = 0;
	
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i]; 

    str[count] = '\0';
}

void toUpper(char s[]){
   int c = 0;
   while (s[c] != '\0'){
      if (s[c] >= 'a' && s[c] <= 'z'){
	  
         s[c] = s[c] - 32;
      }
      c++;
   }
}

void generateKey(char key[5][5], char plain_text[]){
	char alpha[25] = {'A','B','C','D','E','F','G','H','I','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char K[25];
	int i=0,k=0;
	while(plain_text[i] != '\0'){
		if(plain_text[i] < 'J' && alpha[(plain_text[i]%65)] == '\0')
			i++;
		else if(plain_text[i] > 'J' && plain_text[i] <= 'Z' && alpha[(plain_text[i]%65)-1] == '\0')
			i++;
		else{
			K[k++] = plain_text[i];
			(plain_text[i] < 'J') ? (alpha[(plain_text[i]%65)] = '\0') : (alpha[(plain_text[i]%65)-1] = '\0');
			i++;
		}
	}
	i=0;
	while(k < 26){
		if(alpha[i] == '\0')
			i++;
		else{
			K[k++] = alpha[i];
			alpha[i] = '\0';
			i++;
		}
	}
	//printf("%s\n",K);
	k=0;
    for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			key[i][j] = K[k++];
		}
	}
}

void map(int i,int j,int x,int y,char key[5][5],char cipher_text[],int idx){
	//printf("i=%d, j=%d\nx=%d y=%d\n",i,j,x,y);
	//printf("idx = %d\n",idx);
	if(j == y){
			i = (i+1) % 5;
		    x = (x+1) % 5;
	}
	
	else if(i == x){
		    j = (j+1) % 5;
		    y = (y+1) % 5;
	}
	
	else{
		int temp = j;
		j = y;
		y = temp;
	}
	//printf("i=%d, j=%d\nx=%d y=%d\n",i,j,x,y);
	cipher_text[idx] = key[i][j];
	cipher_text[idx+1] = key[x][y];
	//printf("%c  %c\n",key[i][j],key[x][y]);
}

void playfair(char key[5][5],char plain_text[],char cipher_text[]){
	
	int n = strlen(plain_text);
	if(n%2 == 1){//padding if length of plain text is odd
		plain_text[n] = 'X';
		plain_text[n+1] = '\0';
	}
	n = strlen(plain_text);
	
	int p_i;
	for(p_i=0;p_i<n;p_i+=2){
		int x1 = 0,y1 = 0,x2 = 0,y2 = 0;
	    bool mod1 = false,mod2 = false;
		//printf("%c\n",plain_text[p_i]);
		//printf("%c\n",plain_text[p_i + 1]);
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				if(plain_text[p_i] == key[i][j]){
					x1 = i;
					y1 = j;
					mod1 = true;
				}
                if(plain_text[p_i + 1] == key[i][j]){
					x2 = i;
					y2 = j;
					mod2 = true;
				}
                if(mod1 && mod2)
                    break;					
			}
		}
		map(x1,y1,x2,y2,key,cipher_text,p_i);
	}
	cipher_text[p_i] = '\0';
}

int main(){
	char plain_text[1000];
	FILE *fp,*fs;
	fp = fopen("plaintext.txt","r");
	fscanf(fp,"%[^\n]",plain_text);
	removeSpaces(plain_text);//just removes spaces
	toUpper(plain_text);//converts text to uppercase
	printf("%s\n",plain_text);
	
	char key[5][5];
	
	generateKey(key, plain_text);//generate 5x5 key
	
	printf("Key :\n");
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			printf("%c ",key[i][j]);
		}
		printf("\n");
	}
	
	char cipher_text[1000];
	
	playfair(key, plain_text, cipher_text);
	
	printf("%s\n",cipher_text);
	//printf("%s",key);
	
	fp = fopen("ciphertext.txt","w");
	fprintf(fp,"%s",cipher_text);
	fclose(fp);
	
	fs = fopen("key.txt","w");
	fprintf(fs,"%s",key);
	fclose(fs);
	
	return 0;
}
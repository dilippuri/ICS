#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

int main(){
	char cipher_text[1000];
	FILE *fs;
	fs = fopen("ciphertext.txt","r");
    fscanf(fs,"%[^\n]",cipher_text);
	fclose(fs);
	printf("%s\n",cipher_text);
	int n;
    printf("Enter number of levels\n");
	scanf("%d",&n);
	int len = strlen(cipher_text);
	fs = fopen("plaintext.txt","a+");
    fprintf(fs,"\n",cipher_text);
	int maxspread = len / n;
	char plain_text[1000];
	int level = 0;
	bool dir_down;
	int i = 0;
	while(i < len){
		printf("level = %d\n",level);
		int index = 0;
		if(n % 2 == 1){
			int oddcount = 0;
		    for(int i=3;i<=n;i+=2)
				oddcount++;
		    printf("oddcount = %d\n",oddcount);
		    int nextrail = oddcount * 4;
	        printf("nextrail = %d\n",nextrail);
			printf("maxspread = %d\n",maxspread);
	
			if(level == 0 || level == n-1){
				index = level;
				for(int j=0;j<maxspread;j++){
					printf("index = %d i = %d %c\n",index,i,cipher_text[i]);
					if(index < len){
						plain_text[index] = cipher_text[i];
						i++;
					}
					index += nextrail;
		        }
			}
		    else{
				int station = n-1;
				int countour = (n-1) - level;
				
				for(int j=0;j<maxspread;j++){
				    printf("station = %d\n",station);
				    printf("countour = %d\n",countour);
					index = station - countour;
					printf("index = %d i = %d %c\n",index,i,cipher_text[i]);
					if(index < len){
						plain_text[index] = cipher_text[i];
						i++;
					}
                    index =  station + countour;
				    printf("index = %d i = %d %c\n",index,i,cipher_text[i]);
					if(index < len){
						plain_text[index] = cipher_text[i];
						i++;
					}
					station += nextrail;
			    }
		    }
		}
			
		else{
			int evencount = 0;
		    for(int i=6;i<=n;i+=2)
				evencount++;
		    printf("evencount = %d\n",evencount);
		    int nextrail = 6 + evencount * 4;
			if(level == 0 || level == n-1){
				index = level;
				printf("index = %d i = %d %c\n",index,i,cipher_text[i]);
				for(int j=0;j<maxspread;j++){
					if(index < len){
						plain_text[index] = cipher_text[i];
						i++;
					}
					index += nextrail;
				}
			}
			else{
				int station = n-1;
				int countour = (n-1) - level;
				
				for(int j=0;j<maxspread;j++){
					printf("station = %d\n",station);
				    printf("countour = %d\n",countour);
					index = station - countour;
					printf("index = %d i = %d %c\n",index,i,cipher_text[i]);
					if(index < len){
						plain_text[index] = cipher_text[i];
						i++;
					}
                    index =  station + countour;
					printf("index = %d i = %d %c\n",index,i,cipher_text[i]);
					if(index < len){
						plain_text[index] = cipher_text[i];
                        i++;  					
					}
					station += nextrail;
			    }
		    }
		}
		
		if (level == 0)
            dir_down = true;
	
        if (level == n-1)
            dir_down = false;
 
        // find the next level
        dir_down ? level++ : level--;
	}
	
	fprintf(fs,"%s",plain_text);
	fclose(fs);
	
	for(int c=0;c<strlen(plain_text);c++)
		printf("%c",plain_text[c]);
	
	return 0;
}
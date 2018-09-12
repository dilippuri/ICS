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

int addpadding(char *plain_text, int n){
	int i = strlen(plain_text);
	while(i < n){
		plain_text[i] = 'x';
		i++;
	}
	plain_text[i] = '\0';
	return i;
}

int main(){
	char plain_text[1000];
	FILE *fs;
	fs = fopen("plaintext.txt","r");
    fscanf(fs,"%[^\n]",plain_text);
	fclose(fs);
	printf("%s\n",plain_text);
	removeSpaces(plain_text);
	int n;
    printf("Enter number of levels\n");
	scanf("%d",&n);
	fs = fopen("ciphertext.txt","a+");
	if(n % 2 == 1 && n > 3){
		int oddcount = 0;
		for(int i=3;i<=n;i+=2)
			oddcount++;
		printf("oddcount = %d\n",oddcount);
		int nextrail = oddcount * 4;//number of elements between levels
	    printf("nextrail = %d\n",nextrail);
		int endlv = nextrail + n;//index at last level
		printf("endlv = %d\n",endlv);
		int len = strlen(plain_text);//length of plain text
		printf("len = %d\n",len);
		int maxlen = 0;//total length after padding
		while(endlv < len)
			endlv += nextrail;
		if(len < endlv)
			maxlen = addpadding(plain_text, endlv);
		printf("maxlen = %d\n",maxlen);
		printf("%s\n",plain_text);
		int maxspread = maxlen / n;
		fs = fopen("ciphertext.txt","a+");
	
		for(int i=0;i<n;i++){
			int index = i;
			if(i == 0 || i == n-1){
				for(int j=0;j<maxspread;j++){
					if(index < maxlen)
						fprintf(fs,"%c",plain_text[index]);
					printf("index = %d  %c\n",index,plain_text[index]);
					index += nextrail;
				}
			}
			else{
				int station = n-1;
				int countour = (n-1) - i;
				
				for(int j=0;j<maxspread;j++){
					printf("station = %d\n",station);
				    printf("countour = %d\n",countour);
					index = station - countour;
					printf("index = %d  %c\n",index,plain_text[index]);
					if(index < maxlen)
						fprintf(fs,"%c",plain_text[index]);
                    index =  station + countour;
					printf("index = %d  %c\n",index,plain_text[index]);
					if(index < maxlen)
						fprintf(fs,"%c",plain_text[index]);
					station += nextrail;
			   }
		   }
	    }
		fclose(fs);
	}
	else{
		int evencount = 0;
		for(int i=6;i<=n;i+=2)
			evencount++;
		printf("evencount = %d\n",evencount);
		int nextrail = 6 + evencount * 4;//number of elements between levels
	    printf("nextrail = %d\n",nextrail);
		int endlv = nextrail + n;//index at last level
		printf("endlv = %d\n",endlv);
		int len = strlen(plain_text);//length of plain text
		printf("len = %d\n",len);
		int maxlen = 0;//total length after padding
		while(endlv < len)
			endlv += nextrail;
		if(len <= endlv)
			maxlen = addpadding(plain_text, endlv);
		printf("maxlen = %d\n",maxlen);
		printf("%s\n",plain_text);
		int maxspread = maxlen / n;
		fs = fopen("ciphertext.txt","a+");
	
		for(int i=0;i<n;i++){
			int index = i;
			if(i == 0 || i == n-1){
				for(int j=0;j<maxspread;j++){
					if(index < maxlen)
						fprintf(fs,"%c",plain_text[index]);
					printf("index = %d  %c\n",index,plain_text[index]);
					index += nextrail;
				}
			}
			else{
				int station = n-1;
				int countour = (n-1) - i;
				
				for(int j=0;j<maxspread;j++){
					printf("station = %d\n",station);
				    printf("countour = %d\n",countour);
					index = station - countour;
					printf("index = %d  %c\n",index,plain_text[index]);
					if(index < maxlen)
						fprintf(fs,"%c",plain_text[index]);
                    index =  station + countour;
					printf("index = %d  %c\n",index,plain_text[index]);
					if(index < maxlen)
						fprintf(fs,"%c",plain_text[index]);
					station += nextrail;
			   }
		   }
	    }
		fclose(fs);
	}
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h> 

void hexTobinary(char hex[],char bin[]){
	for(int i=0; hex[i]!='\0'; i++){
        switch(hex[i]){
            case '0':
                strcat(bin, "0000");
                break;
            case '1':
                strcat(bin, "0001");
                break;
            case '2':
                strcat(bin, "0010");
                break;
            case '3':
                strcat(bin, "0011");
                break;
            case '4':
                strcat(bin, "0100");
                break;
            case '5':
                strcat(bin, "0101");
                break;
            case '6':
                strcat(bin, "0110");
                break;
            case '7':
                strcat(bin, "0111");
                break;
            case '8':
                strcat(bin, "1000");
                break;
            case '9':
                strcat(bin, "1001");
                break;
            case 'a':
            case 'A':
                strcat(bin, "1010");
                break;
            case 'b':
            case 'B':
                strcat(bin, "1011");
                break;
            case 'c':
            case 'C':
                strcat(bin, "1100");
                break;
            case 'd':
            case 'D':
                strcat(bin, "1101");
                break;
            case 'e':
            case 'E':
                strcat(bin, "1110");
                break;
            case 'f':
            case 'F':
                strcat(bin, "1111");
                break;
            default:
                printf("Invalid hexadecimal input.");
        }
    }
}

void charToHex(char a[],char hex[]) {
   memset(hex, 0, sizeof(char));
   int i,j;
    /*converting character into Hex and adding into hex[]*/
    for(i=0,j=0; i<strlen(a); i++,j+=2){ 
        sprintf((char*)hex+j,"%02X",a[i]);
    }
    hex[j]='\0';
}

int main(){
	char plain_text[1000];
	FILE *fs;
	fs = fopen("plaintext.txt","r");
	fscanf(fs,"%[^\n]",plain_text);
	fclose(fs);
	char hex[1000];
	charToHex(plain_text,hex);
	printf("%s\n",hex);
	char bin[10000];
	hexTobinary(hex,bin);
	printf("%s\n",bin);
	return 0;
}
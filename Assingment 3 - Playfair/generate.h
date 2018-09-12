void generateKey(char key[5][5], char plain_text[]){
	char alpha[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int k=0,x=0,y=0;
	int n = strlen(plain_text);
	for(int i=0;i<n-1;i++){
		if(plain_text[i] == plain_text[n-1]){
			y++;
			break;
		}
	}

	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(plain_text[k] != '\0' && k < n-y){
					while(alpha[(plain_text[k])%65] == '\0')
						k++;
					key[i][j] = plain_text[k];
				    alpha[(plain_text[k])%65] = '\0';
				    k++;
			}
			else{
				if(alpha[x] != '\0'){
					key[i][j] = alpha[x];
				    alpha[x] = '\0';
				    x++;
				}
				else{
					while(alpha[x] == '\0')
						x++;
					key[i][j] = alpha[x];
					x++;
				}
			}
		}
			
	}
	 /*int i=0,j=0;
		while(key[i][j] != '\0'){
	    if(j==4){
			j=0;
		    i++;
		}
		j++;
		printf("i =%d j=%d\n",i,j);
        } */
}
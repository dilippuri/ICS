#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

int modulo(int det){
	printf("det %d\n",det);
	int mod = det % 26;
	if(mod > 0){
		for(int i=1;i<=1000;i++){
			if((i * mod) % 26 == 1)
				return i;
		}
	}
	else{
		mod = 26 + (det % 26);//mod+26
		printf("mod = %d\n",mod);
		for(int i=1;i<=1000;i++){
			printf("i = %d (i * mod) % 26 = %d\n",i,(i * mod) % 26);
			if((i * mod) % 26 == 1)
				return i;
		}
	}
	return 0;
}

void getCofactor(int n, int A[n][n], int temp[n][n], int p, int q){
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q){
                temp[i][j++] = A[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
/* Recursive function for finding determinant of matrix.
   n is current dimension of A[][]. */
int determinant(int N, int A[N][N]){
    int D = 0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (N == 1)
        return A[0][0];
 
    int temp[N][N]; // To store cofactors
 
    int sign = 1;  // To store sign multiplier
 
     // Iterate for each element of first row
    for (int f = 0; f < N; f++){
        // Getting Cofactor of A[0][f]
        getCofactor(N, A, temp, 0, f);
        D += sign * A[0][f] * determinant(N - 1, temp);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return D;
}

void adjoint(int N,int A[N][N],int adj[N][N]){
    if (N == 1){
        adj[0][0] = 1;
        return;
    }
 
    // temp is used to store cofactors of A[][]
    int sign = 1, temp[N][N];
 
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            // Get cofactor of A[i][j]
            getCofactor(N, A, temp, i, j);
 
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;
 
            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(determinant(N-1, temp));
        }
    }
}

bool inverse(int N, int A[N][N], int inverse[N][N]){
    // Find determinant of A[][]
    int det = determinant(N, A);
    if (det == 0){
        printf("Singular matrix, can't find its inverse");
        return false;
    }
    
	//find inverse modulo
	int mod = modulo(det);
	printf("mod inv = %d\n",mod);

    int adj[N][N];
    adjoint(N, A, adj);
 
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
			int temp = (adj[i][j] * mod) % 26;
			if(temp < 0)
				inverse[i][j] = temp + 26;
			else
				inverse[i][j] = temp;
		}
	}
 
    return true;
}

void inv_key(int n,int key[n][n],int invKey[n][n]){
 
    printf("\nThe Inverse is :\n");
    if (inverse(n, key, invKey)){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)
				printf("%d ",invKey[i][j]);
			printf("\n");
		}
	}
 
}

int main(){
	char cipher_text[1000];
	FILE *fs;
	fs=fopen("ciphertext.txt","r");
	fscanf(fs,"%s",cipher_text);
	fclose(fs);
	printf("%s\n",cipher_text);
	//--------------------------------------------------------
    char key[25];
	fs = fopen("key.txt","r");
	fscanf(fs,"%s",key);
	fclose(fs);
	printf("\nkey: %s\n",key);
	int n=sqrt(strlen(key));
	int kvalue[n][n];
	int k=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			kvalue[i][j] = key[k++]%97;
		}
	}
	printf("\n");
	printf("Key in matrix form\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%d ",kvalue[i][j]);
		}
		printf("\n");
	}
//----------------------------------------------------
	int N=strlen(cipher_text)/n;
	int cvalue[n][N];
	k=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<N;j++){
			cvalue[i][j] = cipher_text[k++]%97;
		}
	}
	printf("\n");
	printf("Cipher text in matrix form\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<N;j++){
			printf("%d ",cvalue[i][j]);
		}
		printf("\n");
	}

//-------------------------------------------------------------

    int invKey[n][n];
    
	inv_key(n,kvalue,invKey);
	
	int pvalue[n][N];
	for(int i=0;i<n;i++){
		for(int j=0;j<N;j++){
			pvalue[i][j]=0;
			for(int k=0;k<n;k++){
				pvalue[i][j]=(pvalue[i][j]+invKey[i][k]*cvalue[k][j])%26;
			}
		}
	}
	
	printf("\n");
	printf("Plain text in matrix form\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<N;j++){
			printf("%d ",pvalue[i][j]);
		}
		printf("\n");
	}
//--------------------------------------------------------------------
    
    char plain_text[1000];
    int x = 0;
	char alpha[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for(int i=0;i<n;i++){
		for(int j=0;j<N;j++){
			plain_text[x] = alpha[(pvalue[i][j])];
			x++;
		}
	}
    plain_text[x] = '\0';
    printf("\n%s\n",plain_text);
	
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

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
 
// Function to get adjoint of A[N][N] in adj[N][N].
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
 
// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(int N, int A[N][N], float inverse[N][N]){
    // Find determinant of A[][]
    int det = determinant(N, A);
    if (det == 0){
        printf("Singular matrix, can't find its inverse");
        return false;
    }
 
    // Find adjoint
    int adj[N][N];
    adjoint(N, A, adj);
 
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            inverse[i][j] = adj[i][j]/(det);
 
    return true;
}

void inv_key(int n,int key[n][n]){
	int adj[n][n];  // To store adjoint of A[][]
 
    float inv[n][n]; // To store inverse of A[][]
 
    adjoint(n, key, adj);
 
    printf("The Inverse is :\n");
    if (inverse(n, key, inv)){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)
				printf("%d ",key[i][j]);
			printf("\n");
		}
	}
 
}

int main(){
	char cipher_text[100];
	FILE *fs;
	fs=fopen("ciphertext.txt","r");
	fscanf(fs,"%s",cipher_text);
	fclose(fs);
	printf("%s\n",cipher_text);
	//--------------------------------------------------------
    char key[25];
	printf("Enter key\n");
	scanf("%s",key);
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

    inv_key(n,kvalue);
	
	return 0;
}
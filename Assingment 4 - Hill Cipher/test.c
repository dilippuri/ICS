#include<stdio.h>
#include<stdbool.h>

int modulo(int det){
	int mod = det % 26;
	if(mod > 0){
		for(int i=1;i<=26;i++){
			if((i * mod) % 26 == 1)
				return i;
		}
	}
	else{
		mod = 26 + mod;
		for(int i=1;i<=26;i++){
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
	//printf("%d\n",mod);

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

int main(){
	int n;
	scanf("%d",&n);
	int a[n][n];
	int inv[n][n];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d",&a[i][j]);
		}
	}
	inverse(n,a,inv);
	printf("\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%d ",inv[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	//printf("%d\n",determinant(n, adj));
	return 0;
}
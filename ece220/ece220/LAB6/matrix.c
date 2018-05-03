/* Function matrix_multiply
 * matrixA, matrixB, and matrix C are matrices represented as
 * one-dimensional arrays in row-major order. This function must
 * perform matrix multiplication so that C=A*B.
 * INPUT: matrixA, a one dimensional array of size m*k
 *        matrixB, a one dimensional double array of size k*n
 * OUTPUT: matrixC, a one dimensional double array of size m*n
 */
void matrix_multiply(double *matrixA, double *matrixB, double *matrixC, int m, int k, int n)
{
//YOUR CODE HERE
	int x,y,z;
	for(x = 0; x < m; x++){
		// Go through every row of Matrix A
		for(z = 0; z < n; z++){
			double sum = 0;
			for(y = 0; y < k; y++){
				// Go through every element of row x of matrix A
				sum += matrixA[x*k + y] * matrixB[y*n + z];
			}
			matrixC[x*n + z] = sum;
		}
	}
}

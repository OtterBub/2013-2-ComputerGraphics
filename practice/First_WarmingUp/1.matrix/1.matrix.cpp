#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 4

typedef struct _MATRIX{
	double mat[4][4];
	int column;
	int row;
}MATRIX;

MATRIX CreateMatrix(int row, int column)
{
	MATRIX temp;
	int i, j;
	temp.column = column;
	temp.row = row;

	for(i = 0; i < row; i++) {
		for(j = 0; j < column; j++) {
			temp.mat[i][j] = rand() % MAX_NUM;
		}
	}
	return temp;
}

void PrintMatrix(MATRIX a)
{
	int i, j;
	for(i = 0; i < a.row; i++) {
		printf("| ");
		for(j = 0; j < a.column; j++) {
			printf("%.2f ", a.mat[i][j]);
		}
		printf("|\n");
	}
}

MATRIX AddMatrix(MATRIX a, MATRIX b)
{
	MATRIX result = {0,};
	int i;
	int j;

	if((a.column != b.column) || (a.row != b.row)) {
		printf("can't add matrix\n");
		return result;
	}

	result.column = a.column;
	result.row = a.row;

	for(i = 0; i < a.row; i++) {
		for(j = 0; j < a.column; j++) {
			result.mat[i][j] = a.mat[i][j] + b.mat[i][j];
		}
	}
	return result;
}

MATRIX MulMatrix(MATRIX a, MATRIX b)
{
	MATRIX result = {0,};
	int i, j, k;
	
	if(a.column != b.row)
	{
		printf("can't Multiplication\n");
		return result;
	}

	result = CreateMatrix(a.row, b.column);

	for(i = 0; i < a.row; i++){
		for(j = 0; j < b.column; j++){
			result.mat[i][j] = 0;
			for(k = 0; k < a.column; k++)
				result.mat[i][j] += a.mat[i][k] * b.mat[k][j];
		}
	}

	return result;	
}

double GetDet(MATRIX a)
{
	return 0.0f;
}

int main()
{
	int num;
	MATRIX a;
	MATRIX b;
	MATRIX test_mat;
	MATRIX add_mat;
	MATRIX mul_mat;
	double det;

	srand((unsigned)time(NULL));

	test_mat = CreateMatrix(3, 3);
	
	test_mat.mat[0][0] = 7;
	test_mat.mat[0][1] = -1;
	test_mat.mat[0][2] = -1;
	
	test_mat.mat[1][0] = 10;
	test_mat.mat[1][1] = -2;
	test_mat.mat[1][2] = 1;

	test_mat.mat[2][0] = 6;
	test_mat.mat[2][1] = 3;
	test_mat.mat[2][2] = -2;

	a = CreateMatrix(4, 4);
	b = CreateMatrix(3, 4);
	printf("Matrix A\n");
	PrintMatrix(a);
	printf("Matrix B\n");
	PrintMatrix(b);

	printf("A + B \n");
	add_mat = AddMatrix(a, b);
	PrintMatrix(add_mat);

	printf("A X B \n");
	mul_mat = MulMatrix(a, b);
	PrintMatrix(mul_mat);

	//det = GetDet(test_mat);
	//printf("%.2f \n", det);

	

	return 0;
}

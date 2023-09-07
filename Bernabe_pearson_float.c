#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct PAR{
    int start;
    int end;
    int size;
}parameter;

// 1.) Create Random Numbers based on command line prompt * check *
// 2.) Create non zero elements * check *
// 3.) Do the formulations


// Global Variables for easy access
int** matrix;
int* vector;

// float because answer can be in decimals
float* correct_vector;


// Functions to be used
// n is equal to the size given in prompt
int** createMatrix(int n){
	int** matrix = (int**)malloc(n* sizeof(int*));
	for(int i = 0; i < n; i++) matrix[i] = malloc(n*sizeof(int));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			// For random variables
			matrix[i][j] = ((rand() % 100) + 1);	
		}
	}
	return(matrix);
}

// Same as createMatrix but single array instead of 2d
int* createVector(int n){
	int* vector = (int*)malloc(n*sizeof(int));
	for(int i = 0; i < n; i++){
		vector[i] = ((rand() % 100) + 1); 
	}
	
	return(vector);
}

int** testMatrix(int n){
	int** matrix = (int**)malloc(n* sizeof(int*));
	for(int i = 0; i < n; i++) matrix[i] = malloc(n*sizeof(int));
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			// For random variables
			matrix[i][j] = (i + 1);	
		}
	}
	return(matrix);
}

int* testVector(int n){
	int* vector = (int*)malloc(n*sizeof(int));
	for(int i = 0; i < n; i++){
		vector[i] = (i + 1); 
	}
	
	return(vector);
}

void printMatrix(int** matrix, int n){
	printf("Test Matrix\n");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void printVector(int* vector, int n){
	printf("Test Vector\n");
	for(int i = 0; i < n; i++){
		printf("%d ", vector[i]);
	}
}

void printFloat(float* vector, int n){
	printf("Test Float\n");
	for(int i = 0; i < n; i++){
		printf("%f ", vector[i]);
	}
	printf("\n");
}

// Pearson Coefficient Formulas
int xj(int** matrix, int* vector, int j, int m){
	int sum = 0;
	for(int i = 0; i < m; i++){
		sum += matrix[i][j];
	}
	return sum;
}

int x2j(int** matrix, int* vector, int j, int m){
	int sum = 0;
	for(int i = 0; i < m; i++){
		sum += (matrix[i][j] * matrix[i][j]);
	}
	return sum;
}


int y(int** matrix, int* vector, int j, int m){
	int sum = 0;
	for(int i = 0; i < m; i++){
		sum += vector[i];
	}
	return sum;
}

int y2(int** matrix, int* vector, int j, int m){
	int sum = 0;
	for(int i = 0; i < m; i++){
		sum += (vector[i] * vector[i]);
	}
	return sum;
}

int x2y(int** matrix, int* vector, int j, int m){
	int sum = 0;
	for(int i = 0; i < m; i++){
		sum += (matrix[i][j] * vector[i]);
	}
	return sum;
}	

float* pearson_cor(int** matrix, int* vector, int m){
	float* v = (float*)malloc(sizeof(float)*m);
	// for i:=1 to n
	printf("hi\n");
	for (int i = 0; i < m; i++){
		// Convert answers to float to be able to have final answer as float
		float x = xj(matrix, vector, i,m);
		float x2 = x2j(matrix, vector, i, m);
		float yj = y(matrix, vector, i, m);
		float y2j = y2(matrix, vector, i, m);
		float xy = x2y(matrix, vector, i, m);
		v[i] = ((m * xy) - (x * yj)) / sqrt( ((m * x2) - (x*x))  * ((m * y2j) - (yj*yj)) );
	}
	return v;
	
}


// main program
int main(int argc, char* argv[]){
	time_t t;
	
	// for random numbers per run
	srand(time(NULL));
	
	// number which nxn is based off
	int n = strtol(argv[1], NULL, 10);
	
	// Generate the matrix and vector
	matrix = createMatrix(n);
	vector = createVector(n);
	
	// For debugging
	//matrix = testMatrix(5);
	//vector = testVector(5);
	
	// test the matrix and vector if generating
	// printMatrix(matrix, n);
	// printVector(vector, n);
	
	clock_t begin = clock();
	
	correct_vector = pearson_cor(matrix, vector, n);
	
	clock_t end = clock();
	printFloat(correct_vector, n);
	
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	
	printf("%lf\n", time_spent);
		
	return 0;
}



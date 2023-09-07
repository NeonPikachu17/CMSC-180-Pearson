#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

typedef struct PAR{
    int start;
    int end;
    int size;
}parameter;

// 1.) Create Random Numbers based on command line prompt * check *
// 2.) Create non zero elements * check *
// 3.) Do the formulations


// Global Variables for easy access
double** matrix;
double* vector;

// float because answer can be in decimals
double* correct_vector;


// Functions to be used
// n is equal to the size given in prompt
double** createMatrix(int n){
	double** matrix = (double**)malloc(n* sizeof(double*));
	for(int i = 0; i < n; i++) matrix[i] = malloc(n*sizeof(double));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			// For random variables
			matrix[i][j] = (double) ((rand() % 100) + 1);
		}
	}
	return(matrix);
}

// Same as createMatrix but single array instead of 2d
double* createVector(int n){
	double* vector = (double*)malloc(n*sizeof(double));
	for(int i = 0; i < n; i++){
		vector[i] = (double) ((rand() % 100) + 1); ; 
	}
	
	return(vector);
}

double** testMatrix(int n){
	double** matrix = (double**)malloc(n* sizeof(double*));
	for(int i = 0; i < n; i++) matrix[i] = malloc(n*sizeof(double));
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			// For random variables
			matrix[i][j] = (i + 1);	
		}
	}
	return(matrix);
}

double* testVector(int n){
	double* vector = (double*)malloc(n*sizeof(double));
	for(int i = 0; i < n; i++){
		vector[i] = (i + 1); 
	}
	
	return(vector);
}

void printMatrix(double** matrix, int n){
	printf("Test Matrix\n");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
}

void printVector(double* vector, int n){
	printf("Test Vector\n");
	for(int i = 0; i < n; i++){
		printf("%f ", vector[i]);
	}
}

// Pearson Coefficient Formulas
double xj(double** matrix, double* vector, int j, int m){
	double sum = 0;
	for(int i = 0; i < m; i++){
		sum += matrix[i][j];
	}
	return sum;
}

double x2j(double** matrix, double* vector, int j, int m){
	double sum = 0;
	for(int i = 0; i < m; i++){
		sum += (matrix[i][j] * matrix[i][j]);
	}
	return sum;
}


double y(double** matrix, double* vector, int j, int m){
	double sum = 0;
	for(int i = 0; i < m; i++){
		sum += vector[i];
	}
	return sum;
}

double y2(double** matrix, double* vector, int j, int m){
	double sum = 0;
	for(int i = 0; i < m; i++){
		sum += (vector[i] * vector[i]);
	}
	return sum;
}

double x2y(double** matrix, double* vector, int j, int m){
	double sum = 0;
	for(int i = 0; i < m; i++){
		sum += (matrix[i][j] * vector[i]);
	}
	return sum;
}	

double* pearson_cor(double** matrix, double* vector, int m){
	double* v = (double*)malloc(sizeof(double)*m);
	// for i:=1 to n
	for (int i = 0; i < m; i++){
		// Convert answers to float to be able to have final answer as float
		double x = xj(matrix, vector, i,m);
		double x2 = x2j(matrix, vector, i, m);
		double yj = y(matrix, vector, i, m);
		double y2j = y2(matrix, vector, i, m);
		double xy = x2y(matrix, vector, i, m);
		v[i] = ((m * xy) - (x * yj)) / sqrt( ((m * x2) - (x*x))  * ((m * y2j) - (yj*yj)) );
	}
	return v;
	
}


// main program
int main(int argc, char* argv[]){
	// struct timeval start_time, end_time;
	time_t t;

  
	// for random numbers per run
	srand(time(NULL));
	
	
	// number which nxn is based off
	int n = strtol(argv[1], NULL, 10);
	
	// Generate the matrix and vector

	printf("hi\n");
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
	// printVector(correct_vector, n);
	
	printf("\nTime Spent == %f\n", execution_time);
		
	return 0;
}



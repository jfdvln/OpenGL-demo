#include "mylib.h"
#include <stdio.h>

int main(void)
{	
	vec4 v1 = {1, 2, 3, 4};
	vec4 v2 = {5, 6, 7, 8};
	mat4 m1 = {{1,-5,9,13},{2,6,-10,14},{3,7,11,15},{4,8,12,-16}};
	mat4 m2 = {{4,8,12,16},{3,7,11,15},{2,6,10,14},{1,5,9,13}};
	float s = 3.0;
	
	printf("\nScalar multiplication of s and v1:\n");
	print_vec4(svmult(s, v1));			//scalar-vector multiplication
	printf("Vector addition of v1 + v2:\n");
	print_vec4(add(v1, v2));			//vector addition
	printf("Vector subtraction of v1 - v2:\n");
	print_vec4(sub(v1, v2));			//vector subtraction
	
	printf("Magnitude of v1:\n");
	printf("%.2f\n\n", mag(v1));		//magnitude of vector (assuming v1)
	printf("Normalize v1:\n");
	print_vec4(norm(v1));				//normalize vector (assuming v1)
	
	printf("Dot product of v1 and v2:\n");
	printf("%.2f\n\n", dot(v1, v2));	//dot product
	printf("Cross product of v1 and v2:\n");
	print_vec4(cross(v1, v2));			//cross product
	
	printf("Scalar multiplication of s and m1:\n");
	print_mat4(smmult(s, m1));			//scalar-matrix multiplication
	printf("Matrix addition of m1 + m2:\n");
	print_mat4(madd(m1, m2));			//matrix addition
	printf("Matrix subtraction of m1 - m2:\n");
	print_mat4(msub(m1, m2));			//matrix subtraction
	
	printf("Matrix multiplication of m1 * m2:\n");
	print_mat4(mmmult(m1, m2));			//matrix-matrix multiplication
	printf("Inverse of m1:\n");
	print_mat4(inverse(m1));			//inverse of matrix
	printf("Transpose of m1:\n");
	print_mat4(trans(m1));				//transpose matrix
	printf("Matrix-vector multiplication of m1 and v1:\n");
	print_vec4(mvmult(m1, v1));			//matrix-vector multiplication
}

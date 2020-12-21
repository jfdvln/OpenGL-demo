#include <stdio.h>
#include <math.h>
#include "mylib.h"

void print_vec4(vec4 v)	//print a vector
{
	printf("[ %.2f %.2f %.2f %.2f ]\n\n", v.x, v.y, v.z, v.w);
}

vec4 svmult(float s, vec4 v)	//scalar multiplication on a vector (s * v)
{
	vec4 result;
	result.x = s * v.x;
	result.y = s * v.y;
	result.z = s * v.z;
	result.w = s * v.w;
	return result;
}

vec4 add(vec4 v1, vec4 v2)	//vector addition (v1 + v2)
{
	vec4 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	result.w = v1.w + v2.w;
	return result;
}

vec4 sub(vec4 v1, vec4 v2)	//vector subtraction (v1 - v2)
{
	vec4 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	result.w = v1.w - v2.w;
	return result;
}

float mag(vec4 v)	//magnitude of a vector (|v|)
{
	float result;
	result = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
	return result;
}

vec4 norm(vec4 v)	//normalize a vector (v hat)
{
	vec4 result;
	float div = mag(v);
	div = 1 / div;	//create the scalar to normalize v
	result = svmult(div, v);
	return result;
}

float dot(vec4 v1, vec4 v2)	//dot product (v1 . v2)
{
	float result;
	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
	return result;
}

vec4 cross(vec4 v1, vec4 v2)	//cross product (v1 x v2)
{
	vec4 result;
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	result.w = 0.0;
	return result;
}

void print_mat4(mat4 m)	//print a matrix
{
	printf("[ %.2f  %.2f  %.2f  %.2f ]\n", m.x.x, m.y.x, m.z.x, m.w.x);
	printf("| %.2f  %.2f  %.2f  %.2f |\n", m.x.y, m.y.y, m.z.y, m.w.y);
	printf("| %.2f  %.2f  %.2f  %.2f |\n", m.x.z, m.y.z, m.z.z, m.w.z);
	printf("[ %.2f  %.2f  %.2f  %.2f ]\n\n", m.x.w, m.y.w, m.z.w, m.w.w);
}

mat4 smmult(float s, mat4 m)	//scalar-matrix multiplication (s * m)
{
	mat4 r;
	r.x.x = s * m.x.x;
	r.x.y = s * m.x.y;
	r.x.z = s * m.x.z;
	r.x.w = s * m.x.w;
	
	r.y.x = s * m.y.x;
	r.y.y = s * m.y.y;
	r.y.z = s * m.y.z;
	r.y.w = s * m.y.w;
	
	r.z.x = s * m.z.x;
	r.z.y = s * m.z.y;
	r.z.z = s * m.z.z;
	r.z.w = s * m.z.w;
	
	r.w.x = s * m.w.x;
	r.w.y = s * m.w.y;
	r.w.z = s * m.w.z;
	r.w.w = s * m.w.w;
	return r;
}

mat4 madd(mat4 A, mat4 B)	//matrix-matrix addition (m1 + m2)
{
	mat4 r;
	r.x.x = A.x.x + B.x.x;
	r.x.y = A.x.y + B.x.y;
	r.x.z = A.x.z + B.x.z;
	r.x.w = A.x.w + B.x.w;
	
	r.y.x = A.y.x + B.y.x;
	r.y.y = A.y.y + B.y.y;
	r.y.z = A.y.z + B.y.z;
	r.y.w = A.y.w + B.y.w;
	
	r.z.x = A.z.x + B.z.x;
	r.z.y = A.z.y + B.z.y;
	r.z.z = A.z.z + B.z.z;
	r.z.w = A.z.w + B.z.w;
	
	r.w.x = A.w.x + B.w.x;
	r.w.y = A.w.y + B.w.y;
	r.w.z = A.w.z + B.w.z;
	r.w.w = A.w.w + B.w.w;
	return r;
}

mat4 msub(mat4 A, mat4 B)	//matrix-matrix subtraction (A - B)
{
	mat4 r;
	r.x.x = A.x.x - B.x.x;
	r.x.y = A.x.y - B.x.y;
	r.x.z = A.x.z - B.x.z;
	r.x.w = A.x.w - B.x.w;
	
	r.y.x = A.y.x - B.y.x;
	r.y.y = A.y.y - B.y.y;
	r.y.z = A.y.z - B.y.z;
	r.y.w = A.y.w - B.y.w;
	
	r.z.x = A.z.x - B.z.x;
	r.z.y = A.z.y - B.z.y;
	r.z.z = A.z.z - B.z.z;
	r.z.w = A.z.w - B.z.w;
	
	r.w.x = A.w.x - B.w.x;
	r.w.y = A.w.y - B.w.y;
	r.w.z = A.w.z - B.w.z;
	r.w.w = A.w.w - B.w.w;
	return r;
}

mat4 mmmult(mat4 A, mat4 B)	//matrix-matrix multiplication (A x B)
{
	mat4 r;
	r.x.x = (A.x.x * B.x.x) + (A.y.x * B.x.y) + (A.z.x * B.x.z) + (A.w.x * B.x.w);
	r.x.y = (A.x.y * B.x.x) + (A.y.y * B.x.y) + (A.z.y * B.x.z) + (A.w.y * B.x.w);
	r.x.z = (A.x.z * B.x.x) + (A.y.z * B.x.y) + (A.z.z * B.x.z) + (A.w.z * B.x.w);
	r.x.w = (A.x.w * B.x.x) + (A.y.w * B.x.y) + (A.z.w * B.x.z) + (A.w.w * B.x.w);
	
	r.y.x = (A.x.x * B.y.x) + (A.y.x * B.y.y) + (A.z.x * B.y.z) + (A.w.x * B.y.w);
	r.y.y = (A.x.y * B.y.x) + (A.y.y * B.y.y) + (A.z.y * B.y.z) + (A.w.y * B.y.w);
	r.y.z = (A.x.z * B.y.x) + (A.y.z * B.y.y) + (A.z.z * B.y.z) + (A.w.z * B.y.w);
	r.y.w = (A.x.w * B.y.x) + (A.y.w * B.y.y) + (A.z.w * B.y.z) + (A.w.w * B.y.w);
	
	r.z.x = (A.x.x * B.z.x) + (A.y.x * B.z.y) + (A.z.x * B.z.z) + (A.w.x * B.z.w);
	r.z.y = (A.x.y * B.z.x) + (A.y.y * B.z.y) + (A.z.y * B.z.z) + (A.w.y * B.z.w);
	r.z.z = (A.x.z * B.z.x) + (A.y.z * B.z.y) + (A.z.z * B.z.z) + (A.w.z * B.z.w);
	r.z.w = (A.x.w * B.z.x) + (A.y.w * B.z.y) + (A.z.w * B.z.z) + (A.w.w * B.z.w);
	
	r.w.x = (A.x.x * B.w.x) + (A.y.x * B.w.y) + (A.z.x * B.w.z) + (A.w.x * B.w.w);
	r.w.y = (A.x.y * B.w.x) + (A.y.y * B.w.y) + (A.z.y * B.w.z) + (A.w.y * B.w.w);
	r.w.z = (A.x.z * B.w.x) + (A.y.z * B.w.y) + (A.z.z * B.w.z) + (A.w.z * B.w.w);
	r.w.w = (A.x.w * B.w.x) + (A.y.w * B.w.y) + (A.z.w * B.w.z) + (A.w.w * B.w.w);
	return r;
}

mat4 minor(mat4 m)	//minor of a matrix
{
	mat4 r;
	r.x.x = (m.y.y * m.z.z * m.w.w) + (m.z.y * m.w.z * m.y.w) + (m.w.y * m.y.z * m.z.w) - (m.y.w * m.z.z * m.w.y) - (m.z.w * m.w.z * m.y.y) - (m.w.w * m.y.z * m.z.y);
	r.x.y = (m.y.x * m.z.z * m.w.w) + (m.z.x * m.w.z * m.y.w) + (m.w.x * m.y.z * m.z.w) - (m.y.w * m.z.z * m.w.x) - (m.z.w * m.w.z * m.y.x) - (m.w.w * m.y.z * m.z.x);
	r.x.z = (m.y.x * m.z.y * m.w.w) + (m.z.x * m.w.y * m.y.w) + (m.w.x * m.y.y * m.z.w) - (m.y.w * m.z.y * m.w.x) - (m.z.w * m.w.y * m.y.x) - (m.w.w * m.y.y * m.z.x);
	r.x.w = (m.y.x * m.z.y * m.w.z) + (m.z.x * m.w.y * m.y.z) + (m.w.x * m.y.y * m.z.z) - (m.y.z * m.z.y * m.w.x) - (m.z.z * m.w.y * m.y.x) - (m.w.z * m.y.y * m.z.x);
	
	r.y.x = (m.x.y * m.z.z * m.w.w) + (m.z.y * m.w.z * m.x.w) + (m.w.y * m.x.z * m.z.w) - (m.x.w * m.z.z * m.w.y) - (m.z.w * m.w.z * m.x.y) - (m.w.w * m.x.z * m.z.y);
	r.y.y = (m.x.x * m.z.z * m.w.w) + (m.z.x * m.w.z * m.x.w) + (m.w.x * m.x.z * m.z.w) - (m.x.w * m.z.z * m.w.x) - (m.z.w * m.w.z * m.x.x) - (m.w.w * m.x.z * m.z.x);
	r.y.z = (m.x.x * m.z.y * m.w.w) + (m.z.x * m.w.y * m.x.w) + (m.w.x * m.x.y * m.z.w) - (m.x.w * m.z.y * m.w.x) - (m.z.w * m.w.y * m.x.x) - (m.w.w * m.x.y * m.z.x);
	r.y.w = (m.x.x * m.z.y * m.w.z) + (m.z.x * m.w.y * m.x.z) + (m.w.x * m.x.y * m.z.z) - (m.x.z * m.z.y * m.w.x) - (m.z.z * m.w.y * m.x.x) - (m.w.z * m.x.y * m.z.x);
	
	r.z.x = (m.x.y * m.y.z * m.w.w) + (m.y.y * m.w.z * m.x.w) + (m.w.y * m.x.z * m.y.w) - (m.x.w * m.y.z * m.w.y) - (m.y.w * m.w.z * m.x.y) - (m.w.w * m.x.z * m.y.y);
	r.z.y = (m.x.x * m.y.z * m.w.w) + (m.y.x * m.w.z * m.x.w) + (m.w.x * m.x.z * m.y.w) - (m.x.w * m.y.z * m.w.x) - (m.y.w * m.w.z * m.x.x) - (m.w.w * m.x.z * m.y.x);
	r.z.z = (m.x.x * m.y.y * m.w.w) + (m.y.x * m.w.y * m.x.w) + (m.w.x * m.x.y * m.y.w) - (m.x.w * m.y.y * m.w.x) - (m.y.w * m.w.y * m.x.x) - (m.w.w * m.x.y * m.y.x);
	r.z.w = (m.x.x * m.y.y * m.w.z) + (m.y.x * m.w.y * m.x.z) + (m.w.x * m.x.y * m.y.z) - (m.x.z * m.y.y * m.w.x) - (m.y.z * m.w.y * m.x.x) - (m.w.z * m.x.y * m.y.x);
	
	r.w.x = (m.x.y * m.y.z * m.z.w) + (m.y.y * m.z.z * m.x.w) + (m.z.y * m.x.z * m.y.w) - (m.x.w * m.y.z * m.z.y) - (m.y.w * m.z.z * m.x.y) - (m.z.w * m.x.z * m.y.y);
	r.w.y = (m.x.x * m.y.z * m.z.w) + (m.y.x * m.z.z * m.x.w) + (m.z.x * m.x.z * m.y.w) - (m.x.w * m.y.z * m.z.x) - (m.y.w * m.z.z * m.x.x) - (m.z.w * m.x.z * m.y.x);
	r.w.z = (m.x.x * m.y.y * m.z.w) + (m.y.x * m.z.y * m.x.w) + (m.z.x * m.x.y * m.y.w) - (m.x.w * m.y.y * m.z.x) - (m.y.w * m.z.y * m.x.x) - (m.z.w * m.x.y * m.y.x);
	r.w.w = (m.x.x * m.y.y * m.z.z) + (m.y.x * m.z.y * m.x.z) + (m.z.x * m.x.y * m.y.z) - (m.x.z * m.y.y * m.z.x) - (m.y.z * m.z.y * m.x.x) - (m.z.z * m.x.y * m.y.x);
	return r;
}

mat4 cofactor(mat4 m)	//cofactor of a matrix
{
	mat4 r;
	r.x.x = m.x.x;
	r.x.y = -1 * m.x.y;
	r.x.z = m.x.z;
	r.x.w = -1 * m.x.w;
	
	r.y.x = -1 * m.y.x;
	r.y.y = m.y.y;
	r.y.z = -1 * m.y.z;
	r.y.w = m.y.w;
	
	r.z.x = m.z.x;
	r.z.y = -1 * m.z.y;
	r.z.z = m.z.z;
	r.z.w = -1 * m.z.w;
	
	r.w.x = -1 * m.w.x;
	r.w.y = m.w.y;
	r.w.z = -1 * m.w.z;
	r.w.w = m.w.w;
	return r;
}

mat4 trans(mat4 m)	//transpose a matrix
{
	mat4 r;
	r.x.x = m.x.x;
	r.x.y = m.y.x;
	r.x.z = m.z.x;
	r.x.w = m.w.x;
	
	r.y.x = m.x.y;
	r.y.y = m.y.y;
	r.y.z = m.z.y;
	r.y.w = m.w.y;
	
	r.z.x = m.x.z;
	r.z.y = m.y.z;
	r.z.z = m.z.z;
	r.z.w = m.w.z;
	
	r.w.x = m.x.w;
	r.w.y = m.y.w;
	r.w.z = m.z.w;
	r.w.w = m.w.w;
	return r;
}

float det(mat4 A, mat4 m)	//determinant of A (|A|) (given matrix A and its minor m)
{
	float r = (A.x.x * m.x.x) - (A.y.x * m.y.x) + (A.z.x * m.z.x) - (A.w.x * m.w.x);
	return r;
}

mat4 inverse(mat4 m)	//inverse of a matrix
{
	mat4 A_inv;
	mat4 temp = m;
	mat4 min = minor(temp);
	mat4 cof = cofactor(min);
	mat4 transpose = trans(cof);
	float determinant = det(temp, min);	//see det() for explanation
	A_inv = smmult(1/determinant, transpose);	//scalar multiplication
	return A_inv;
}

vec4 mvmult(mat4 m, vec4 v)	//matrix-vector multiplication (m * v)
{
	vec4 r;
	r.x = (m.x.x * v.x) + (m.y.x * v.y) + (m.z.x * v.z) + (m.w.x * v.w);
	r.y = (m.x.y * v.x) + (m.y.y * v.y) + (m.z.y * v.z) + (m.w.y * v.w);
	r.z = (m.x.z * v.x) + (m.y.z * v.y) + (m.z.z * v.z) + (m.w.z * v.w);
	r.w = (m.x.w * v.x) + (m.y.w * v.y) + (m.z.w * v.z) + (m.w.w * v.w);
	return r;
}

#ifndef _MYLIB_H_
#define _MYLIB_H_

typedef struct
{
	float x;
	float y;
	float z;
	float w;
} vec4;

typedef struct
{
	vec4 x;
	vec4 y;
	vec4 z;
	vec4 w;
} mat4;

void print_vec4(vec4 v);
vec4 svmult(float s, vec4 v);
vec4 add(vec4 v1, vec4 v2);
vec4 sub(vec4 v1, vec4 v2);
float mag(vec4 v);
vec4 norm(vec4 v);
float dot(vec4 v1, vec4 v2);
vec4 cross(vec4 v1, vec4 v2); 

void print_mat4(mat4 m);
mat4 smmult(float s, mat4 m);
mat4 madd(mat4 A, mat4 B);
mat4 msub(mat4 A, mat4 B);
mat4 mmmult(mat4 A, mat4 B);
mat4 minor(mat4 m);
mat4 cofactor(mat4 m);
mat4 trans(mat4 m);
float det(mat4 A, mat4 m);
mat4 inverse(mat4 m);
vec4 mvmult(mat4 m, vec4 v);

#endif

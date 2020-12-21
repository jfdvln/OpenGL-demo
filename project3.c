/*
 * template.c
 *
 * An OpenGL source code template.
 */


//need to do next:
//will have to check perspective and eye point and all that here
//figure out the texture mapping, put the textures on the spheres instead of the colors, and deal with it if it looks shitty
//do the animation section
//do the lighting section
//if time, make the fake shadows

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "../mylib/initShader.h"
#include "../mylib/mylib.h"


#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))
#define PI 3.1415926535

typedef struct
{
    GLfloat x;
    GLfloat y;
} vec2;

GLuint ctm_location, model_view_location, projection_location, orthop_location, light_position_location;
mat4 ctm = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
mat4 model_view = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
mat4 projection = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
mat4 orthop = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
vec4 prev = {0,0,1.0,0};
vec4 light_position = {0.0, 1.0, 0.0, 1.0};

mat4 light_ctm = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
mat4 ball_ctms[16] = {{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
						{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}};

vec4 light_location = {0.0, 1.0, 0.0, 1.0};		//light source
vec4 ball_locations[16] = {{-1.5 * 0.2, 0.1, -1.5 * 0.2, 1.0},	//index is ball #-1, 15 is cue ball
							{-0.5 * 0.2, 0.1, -1.5 * 0.2, 1.0},
							{0.5 * 0.2, 0.1, -1.5 * 0.2, 1.0},
							{1.5 * 0.2, 0.1, -1.5 * 0.2, 1.0},
							{-1.5 * 0.2, 0.1, -0.5 * 0.2, 1.0},
							{-0.5 * 0.2, 0.1, -0.5 * 0.2, 1.0},
							{0.5 * 0.2, 0.1, -0.5 * 0.2, 1.0},
							{1.5 * 0.2, 0.1, -0.5 * 0.2, 1.0},
							{-1.5 * 0.2, 0.1, 0.5 * 0.2, 1.0},
							{-0.5 * 0.2, 0.1, 0.5 * 0.2, 1.0},
							{0.5 * 0.2, 0.1, 0.5 * 0.2, 1.0},
							{1.5 * 0.2, 0.1, 0.5 * 0.2, 1.0},
							{-1.5 * 0.2, 0.1, 1.5 * 0.2, 1.0},
							{-0.5 * 0.2, 0.1, 1.5 * 0.2, 1.0},
							{0.5 * 0.2, 0.1, 1.5 * 0.2, 1.0},
							{1.5 * 0.2, 0.1, 1.5 * 0.2, 1.0}};


float x_degree = 0.0;
float y_degree = 0.0;
int num_vertices = 15120 * 17 + 6;	//testing
//total vertices, 17 spheres + table, = 257046
int cur_vertex = 0;
int cur_svertex = 0;
int cur_color = 0;
int cur_tex = 15126;
int cur_norm = 0;
int scount = 15120;	//number of vertices per sphere
int tcount = 6;		//number of vertices for surface


//void coneVertices(vec4 * v);
void tableVertices(vec4 * v);
void sphereVertices(vec4 * v);
void tableColors(vec4 * c);
void sphereColors(vec4 * c);
void world(vec4 * v);

vec4 vertices[15120 * 17 + 6];
vec4 colors[15120 * 17 + 6];
vec4 svertices[15120];
vec2 tex_coords[15120 * 17 + 6];	//texture
GLuint use_texture_location;
vec4 normals[15120 * 17 + 6];	//normals of vertices

vec4 eye = {0.0, 0.0, 0.0, 0.0};
vec4 at;
vec4 up;
float dist = 1.0; 	//for zoom

int state = 0;	//no move, 1 = line up, 2 = rotate around (animation)
int cur_ball = 0;	//use to index into ball_locations array
float radii[16] = {0.2 * 15, 0.2 * 14, 0.2 * 13, 0.2 * 12, 0.2 * 11, 0.2 * 10, 0.2 * 9, 0.2 * 8, 0.2 * 7, 0.2 * 6, 0.2 * 5, 0.2 * 4, 0.2 * 3, 0.2 * 2, 0.2 * 1, 0};

void init(void)
{
	tableVertices(vertices);
	tableColors(colors);
	sphereVertices(vertices);
	world(vertices);
	
	eye.x = 0.0;
    eye.y = 2.0;
    eye.z = 5.0;
    eye.w = 0.0;
    vec4 temp = {0.0, 0.0, 0.0, 0.0};
    at = temp;
    vec4 temp1 = {0.0, 1.0, 0.0, 0.0};
    up = temp1;
    model_view = look_at(eye, at, up);
	
	//texture stuff
	int width = 512;
	int height = 512;
	GLubyte my_texels[width][height][3];
	
	FILE *fp = fopen("pb_512_512.raw", "r");
	if (fp == NULL)
	{
		printf("Unable to open file.\n");
		exit(1);
	}
	fread(my_texels, width * height * 3, 1, fp);
	fclose(fp);
	
	//was here before texture stuff
    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);
    
    GLuint mytex[1];
    glGenTextures(1, mytex);
    glBindTexture(GL_TEXTURE_2D, mytex[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, my_texels);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    
    int param;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &param);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors) + sizeof(tex_coords), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), sizeof(tex_coords), tex_coords);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) sizeof(vertices));
    
    GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");
    glEnableVertexAttribArray(vTexCoord);
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0 + (sizeof(vertices) + sizeof(colors)));
    
    GLuint texture_location = glGetUniformLocation(program, "texture");
    glUniform1i(texture_location, 0);

    printf("texture_location: %i\n", texture_location);
    
    ctm_location = glGetUniformLocation(program, "ctm");
    ctm = identity();
    
    //light_ctm_location = glGetUniformLocation(program, "light_ctm");
    
    use_texture_location = glGetUniformLocation(program, "use_texture");
    
    model_view_location = glGetUniformLocation(program, "model_view");
    
   	projection_location = glGetUniformLocation(program, "projection");
   	
   	//orthop_location = glGetUniformLocation(program, "orthop");
   	
   	light_position_location = glGetUniformLocation(program, "light_position");
   	glUniform1i(light_position_location, 0);
    

	glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);
    
    //have to do this to set matrices in vshader
   
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) &model_view);
    
    projection = frustum(-0.1, 0.1, -0.1, 0.1, -0.5, -20.0);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    
    glUniform4fv(light_position_location, 1, (GLfloat *) &light_position);
    
    //orthop = ortho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
    //glUniformMatrix4fv(orthop_location, 1, GL_FALSE, (GLfloat *) &orthop);
    
    //draw without using texture (this sets use_texture = 0 in fshader)
    glUniform1i(use_texture_location, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);	//table
    
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &light_ctm);
    glDrawArrays(GL_TRIANGLES, 6, scount);	//light sphere	
    
    //draw WITH texture (sets use_texture = 1 in fshader)
    glUniform1i(use_texture_location, 1);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[0]);
    glDrawArrays(GL_TRIANGLES, 15126, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[1]);
    glDrawArrays(GL_TRIANGLES, (2 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[2]);
    glDrawArrays(GL_TRIANGLES, (3 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[3]);
    glDrawArrays(GL_TRIANGLES, (4 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[4]);
    glDrawArrays(GL_TRIANGLES, (5 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[5]);
    glDrawArrays(GL_TRIANGLES, (6 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[6]);
    glDrawArrays(GL_TRIANGLES, (7 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[7]);
    glDrawArrays(GL_TRIANGLES, (8 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[8]);
    glDrawArrays(GL_TRIANGLES, (9 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[9]);
    glDrawArrays(GL_TRIANGLES, (10 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[10]);
    glDrawArrays(GL_TRIANGLES, (11 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[11]);
    glDrawArrays(GL_TRIANGLES, (12 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[12]);
    glDrawArrays(GL_TRIANGLES, (13 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[13]);
    glDrawArrays(GL_TRIANGLES, (14 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[14]);
    glDrawArrays(GL_TRIANGLES, (15 * 15120) + 6, scount);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ball_ctms[15]);
    glDrawArrays(GL_TRIANGLES, (16 * 15120) + 6, scount);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q')
    	glutLeaveMainLoop();
    if (key == 'b')
    {
    	if (state == 0)
    		state++;
    	else if (state == 1)
    		state = 2;
    }
    if (key == 'z') //eye zoom in
   		model_view = mmmult(model_view, scale(1.02, 1.02, 1.02));	
   	if (key == 'x')	//eye zoom out
   		model_view = mmmult(model_view, scale(0.98, 0.98, 0.98));
   	if (key == 'w')	//eye rotate up
   	{
   		float m = mag(eye);
   		vec4 temp = norm(eye);
   		if (temp.y <= .96)
   			temp.y += 0.03;
   		temp = norm(temp);
   		eye = svmult(m, temp);
   		model_view = look_at(eye, at, up);//mmmult(model_view, rotate_x(0.03));
   	}
   	if (key == 's') //eye rotate down
   	{
   		float m = mag(eye);
   		vec4 temp = norm(eye);
   		if (temp.y >= 0.04)
   			temp.y -= 0.03;
   		temp = norm(temp);
   		eye = svmult(m, temp);
   		model_view = look_at(eye, at, up);
   	}
   	if (key == 'a') //eye rotate left
   		model_view = mmmult(model_view, rotate_y(-0.03));
   	if (key == 'd')	//eye rotate right
   		model_view = mmmult(model_view, rotate_y(0.03));
   	

    glutPostRedisplay();
}

void special(int key, int mousex, int mousey)
{
	mat4 change;
	if (key == GLUT_KEY_UP)	// z +
		change = translate(0.0, 0.0, -0.03);
    else if (key == GLUT_KEY_DOWN) 	//z -
    	change = translate(0.0, 0.0, 0.03);
    else if (key == GLUT_KEY_LEFT)	//x -
    	change = translate(-0.03, 0.0, 0.0);
    else if (key == GLUT_KEY_RIGHT)	//x +
    	change = translate(0.03, 0.0, 0.0);
    else if (key == GLUT_KEY_PAGE_UP)	//y +
    	change = translate(0.0, 0.03, 0.0);
    else if (key == GLUT_KEY_PAGE_DOWN)	//y -
    	change = translate(0.0, -0.03, 0.0);

    light_ctm = mmmult(light_ctm, change);
    light_location = mvmult(change, light_location);
    light_position = mvmult(change, light_position);
    
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	//printf("mouse: %i %i %i %i\n", button, state, x, y);
	
	if (button == 3 && state == 1)
	{
		//scrolling up
		//want to zoom in
		mat4 s = scale(1.02, 1.02, 1.02);
		ctm = mmmult(s, ctm);
	}
	else if (button == 4 && state == 1)
	{
		//scrolling down
		//zoom out
		mat4 s = scale(1/1.02, 1/1.02, 1/1.02);
		ctm = mmmult(s, ctm);
	}
	
	if (button == GLUT_LEFT_BUTTON && state == 0)
	{
		prev.x = (float) (x - 256) / 256;
		prev.y = (float) (y - 256) / 256;
		prev.z = (float) sqrt(1 - prev.x*prev.x - prev.y*prev.y);
		prev.w = 0.0;
	}
	
	glutPostRedisplay();
}

void motion(int xi, int yi)
{
	//printf("motion: %i %i\n", xi, yi);
	
	float x, y, z, d;
	x = (float) (xi - 256) / 256;
	y = (float) (yi - 256) / 256;
	z = (float) sqrt(1 - x*x - y*y);
	
	
	
	//printf("%.4f\t%.4f\t%.4f\n", x, y, z); 
	//printf("%i\n", isnan(z));
	//isnan() returns nonzero if argument IS NaN, 0 if NOT NaN
	
	if (z > 0.0 && isnan(z) == 0)	//do nothing outside sphere (where z is nan)
	{
		vec4 cur = {x, y, z, 0.0};	//vector
		
		vec4 v = cross(prev, cur);	//about vector
		v = norm(v);	//normalize it
		
		d = sqrt(v.y*v.y + v.z*v.z);
		
		mat4 Rx = {{1, 0, 0, 0}, {0, v.z/d, v.y/d, 0}, {0, -v.y/d, v.z/d, 0}, {0, 0, 0, 1}};
		mat4 Ry = {{d, 0, -v.x, 0}, {0, 1, 0, 0}, {v.x, 0, d, 0}, {0, 0, 0, 1}};
		mat4 Ry1 = trans(Ry);
		mat4 Rx1 = trans(Rx);
		mat4 Rz = rotate_z(acos(dot(prev, cur)));	
			//dot product gives cos(theta), since vectors are both mag = 1
			//take acos(cos(theta)) to get angle of rotation about z axis

		mat4 R;
		R = mmmult(Ry, Rx);
		R = mmmult(Rz, R);
		R = mmmult(Ry1, R);
		R = mmmult(Rx1, R);
		
		ctm = mmmult(R, ctm);		
		prev = cur;	//v is now the next u		
	}
	
	glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, 512, 512);
}	

void sphereVertices(vec4 *vertices)
{
	//make as radius 1
	//then make 16 copies, put into right places
	
	int num_rows = 50;
	int num_slices = 50;
	
	float row = PI / num_rows;
	float slice = (2 * PI) / num_slices;
	
	float sph, cph; 	//sin(phi) and cos(phi)
	float sth, cth;		//sin(theta) and cos(theta)
	
	for (float phi = -PI / 2; phi < PI / 2; phi += row)
	{
		sph = sin(phi);
		cph = cos(phi);
		
		for (float theta = 0; theta < 2 * PI; theta += slice)
		{
			sth = sin(theta);
			cth = cos(theta);
			
			if (phi == 0)	//bottom endcap
			{
				vec4 v1 = {0.0, -1.0, 0.0, 1.0};
				vec4 v2 = {cph * cos(theta + slice), sph, cph * sin(theta + slice), 1.0};
				vec4 v3 = {cph * cos(theta + slice), sin(phi + row), cph * sin(theta + slice), 1.0};
				
				svertices[cur_svertex++] = v1;
				svertices[cur_svertex++] = v3;
				svertices[cur_svertex++] = v2;
				
			}
			else if (phi == PI - row)	//top endcap
			{
				vec4 v1 = {0.0, 1.0, 0.0, 1.0};
				vec4 v2 = {cph * cos(theta + slice), sph, cph * sin(theta + slice), 1.0};
				vec4 v3 = {cph * cos(theta + slice), sin(phi - row), cph * sin(theta + slice), 1.0};
				
				svertices[cur_svertex++] = v1;
				svertices[cur_svertex++] = v2;
				svertices[cur_svertex++] = v3;
			}
			else
			{
				vec4 v1 = {cph * cth, sph, cph * sth, 1.0};
				vec4 v2 = {cos(phi) * cos(theta + slice), sph, cos(phi) * sin(theta + slice), 1.0};
				vec4 v3 = {cos(phi + row) * cos(theta + slice), sin(phi + row), cos(phi + row) * sin(theta + slice), 1.0};
				vec4 v4 = {cos(phi + row) * cos(theta + slice), sin(phi + row), cos(phi + row) * sin(theta + slice), 1.0};
				vec4 v5 = {cos(phi + row) * cth, sin(phi + row), cos(phi + row) * sin(theta), 1.0};
				vec4 v6 = {cph * cth, sph, cph * sth, 1.0};
			
				//order???
				svertices[cur_svertex++] = v1;
				svertices[cur_svertex++] = v3;
				svertices[cur_svertex++] = v2;
				svertices[cur_svertex++] = v4;
				svertices[cur_svertex++] = v6;
				svertices[cur_svertex++] = v5;
				
			}
		}
		
	}
}

void tableVertices(vec4 * vertices) 
{	
	//triangles
	vec4 v1 = {5.0, 0.0, -5.0, 1.0};
	vec4 v2 = {-5.0, 0.0, 5.0, 1.0};
	vec4 v3 = {-5.0, 0.0, -5.0, 1.0};
	
	vertices[cur_vertex++] = v1;
	vertices[cur_vertex++] = v3;
	vertices[cur_vertex++] = v2;
	
	vec4 v4 = {5.0, 0.0, -5.0, 1.0};
	vec4 v5 = {5.0, 0.0, 5.0, 1.0};
	vec4 v6 = {-5.0, 0.0, 5.0, 1.0};
	
	vertices[cur_vertex++] = v4;
	vertices[cur_vertex++] = v6;
	vertices[cur_vertex++] = v5;
	
	vec4 temp = {0.0, 1.0, 0.0, 0.0};
	for (int i = 0; i < 6; i++)
		normals[cur_norm++] = temp;
}

void tableColors(vec4 *colors)
{
	vec4 c = {0.0, 1.0, 0.0, 1.0};	//green
	
	for (int i = 0; i < 6; i++)
	{
		colors[cur_color++] = c;
	}
}


void sphereColors(vec4 *colors)
{
	srand(time(NULL));	//set seed
	
	int triangles = (int) scount/3;
	
	float val1, val2, val3;	//for random colors
	
	for (int i = 0; i < triangles-1; i++)
	{
		val1 = rand() / ((float) RAND_MAX);
		val2 = rand() / ((float) RAND_MAX);
		val3 = rand() / ((float) RAND_MAX);
		
		vec4 c = {val1, val2, val3, 1.0};
		//make each triangle one color - each point must have same vals
		colors[cur_color++] = c;
		colors[cur_color++] = c;
		colors[cur_color++] = c;
	}
}

void world(vec4 *vertices)
{
	
	//move spheres into grid
	
	vec4 c = {1.0, 1.0, 1.0, 1.0};	//white
	
	//stuff for light source
	mat4 light_ctm = ctm;
	light_ctm = mmmult(light_ctm, translate(0.0, 1.0, 0.0));	//move to (0,1,0)
	light_ctm = mmmult(light_ctm, scale(0.05, 0.05, 0.05));	//scale down
	
	for (int i = 0; i < scount; i++)
		vertices[cur_vertex++] = mvmult(light_ctm, svertices[i]);
	
	for (int i = 0; i < scount; i++)
	{
		normals[cur_norm].x = svertices[i].x;
		normals[cur_norm].y = svertices[i].y;
		normals[cur_norm].z = svertices[i].z;
		normals[cur_norm++].w = 0.0;
	}
	
	for (int i = 0; i < scount; i++)
		colors[cur_color++] = c;
		
	
		
	//16 other spheres
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			
			mat4 sphere_ctm = ctm;
			sphere_ctm = mmmult(sphere_ctm, translate((j - 1.5) * 0.2, 0.1, (i - 1.5) * 0.2));	//place in 4x4 grid
			sphere_ctm = mmmult(sphere_ctm, scale(0.1, 0.1, 0.1));	//scale down to r=0.1
			sphere_ctm = mmmult(sphere_ctm, rotate_x(PI/2));		//rotate 90 degrees about x
			
			
			for (int k = 0; k < scount; k++)
			{	
				//if (k % 3 == 0)
				//{
					/*vec4 p1 = vertices[cur_vertex];
					vec4 p2 = vertices[cur_vertex + 1];
					vec4 p3 = vertices[cur_vertex + 2];
					vec4 v1 = sub(p2, p1);
					vec4 v2 = sub(p3, p2);
					vec4 ans = norm(cross(v1, v2));
					
					normals[cur_norm++] = ans;
					normals[cur_norm++] = ans;
					normals[cur_norm++] = ans;*/
					
					normals[cur_norm].x = svertices[k].x;
					normals[cur_norm].y = svertices[k].y;
					normals[cur_norm].z = svertices[k].z;
					normals[cur_norm++].w = 0.0;
				//}
				
				vertices[cur_vertex++] = mvmult(sphere_ctm, svertices[k]);
				vec2 tex;
				
				if (j == 0 && i == 0)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.01;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.01;
				}
				else if (j == 1 && i == 0)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.26;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.01;
				}
				else if (j == 2 && i == 0)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.51;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.01;
				}
				else if (j == 3 && i == 0)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.76;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.01;
				}
				else if (j == 0 && i == 1)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.01;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.26;
				}
				else if (j == 1 && i == 1)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.26;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.26; 
				}
				else if (j == 2 && i == 1)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.51;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.26;
				}
				else if (j == 3 && i == 1)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.76;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.26; 
				}
				else if (j == 0 && i == 2)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.01;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.511;
				}
				else if (j == 1 && i == 2)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.26;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.511;
				}
				else if (j == 2 && i == 2)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.51;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.511; 
				}
				else if (j == 3 && i == 2)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.76;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.511;
				}
				else if (j == 0 && i == 3)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.01;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.7625;
				}
				else if (j == 1 && i == 3)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.26;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.7625; 
				}
				else if (j == 2 && i == 3)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.51;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.7625;
				}
				else if (j == 3 && i == 3)
				{
					tex.x = (((svertices[k].x + 1) / 2) * 0.23) + 0.76;
					tex.y = (((svertices[k].y + 1) / 2) * 0.23) + 0.7625;
				}
				
				tex_coords[cur_tex++] = tex;
				
			}
			
			for (int k = 0; k < scount; k++)
				colors[cur_color++] = c;
				
			
		}
	}
}

void idle(void)
{
	mat4 change;
	vec4 end = {0.0, 0.1, -3.0 + 0.2 * cur_ball, 1.0};
	vec4 y = {0.0, 1.0, 0.0, 1.0};
	vec4 dir; 	//direction of step
	vec4 temp_dir;
	vec4 about;	//for arbitrary rotation axis
	float inc = 0.06;	//magnitude of step?
	float d;
	float theta;
	//line balls up
	
	if (state == 1)		//first phase of animation	(line up along z axis)
	{
		vec4 check = sub(end, ball_locations[cur_ball]);
		
		if ((check.x != 0) || (check.y != 0) || (check.z != 0))	//check that not yet in final location
		{
			//translation
			temp_dir = sub(end, ball_locations[cur_ball]);	//get direction vector for necessary path/change
			about = cross(y, temp_dir);	//about vector for rotation
			dir = norm(temp_dir);
			dir = svmult(inc, dir);	//actual change
			change = translate(dir.x, dir.y, dir.z);
			
			//rotation
			ball_ctms[cur_ball] = mmmult(translate(-1 * ball_locations[cur_ball].x, -1 * ball_locations[cur_ball].y, -1 * ball_locations[cur_ball].z), ball_ctms[cur_ball]);	//move ball to origin
			about = norm(about);	//normalize it
		
			d = sqrt(about.y * about.y + about.z * about.z);
		
			mat4 Rx = {{1, 0, 0, 0}, {0, about.z / d, about.y / d, 0}, {0, -about.y / d, about.z / d, 0}, {0, 0, 0, 1}};
			mat4 Ry = {{d, 0, -about.x, 0}, {0, 1, 0, 0}, {about.x, 0, d, 0}, {0, 0, 0, 1}};
			mat4 Ry1 = trans(Ry);
			mat4 Rx1 = trans(Rx);
			mat4 Rz = rotate_z(-0.2 * acos(dot(y, temp_dir)));	
			//dot product gives cos(theta), since vectors are both mag = 1
			//take acos(cos(theta)) to get angle of rotation about z axis

			mat4 R;
			R = mmmult(Ry, Rx);
			R = mmmult(Rz, R);
			R = mmmult(Ry1, R);
			R = mmmult(Rx1, R);
			
			ball_ctms[cur_ball] = mmmult(R, ball_ctms[cur_ball]);	//perform rotation
			ball_ctms[cur_ball] = mmmult(translate(ball_locations[cur_ball].x, ball_locations[cur_ball].y, ball_locations[cur_ball].z), ball_ctms[cur_ball]);
			
			
			ball_ctms[cur_ball] = mmmult(change, ball_ctms[cur_ball]); //perform translation
			
			ball_locations[cur_ball] = mvmult(change, ball_locations[cur_ball]);
			
			if (mag(check) < 0.06)
			{	
				vec4 remain = sub(end, ball_locations[cur_ball]);
				change = translate(remain.x, remain.y, remain.z);
				
				ball_ctms[cur_ball] = mmmult(ball_ctms[cur_ball], change);
				ball_locations[cur_ball] = mvmult(change, ball_locations[cur_ball]);	
				print_vec4(ball_locations[cur_ball]);
			}
		}
		else	
		{
			cur_ball++; 	//next ball when prev ball is at its end location
			
			if (cur_ball == 16)
			{
				state++;
				//inc = 0.006;
			}
		}
		
		
	}
	else if (state == 2)	//second phase of animation (rotate around cue ball)
	{
		inc = 0.04;
		for (int i = 0; i < 15; i++)	//moving all balls at once
		{
			theta = inc / radii[i];
			ball_ctms[i] = mmmult(rotate_y(theta), ball_ctms[i]);
			
			/*theta[i] += inc / radii[i];
			if (theta[i] >= 2 * PI)
				theta[i] = 0.0;
			float rx = radii[i] * cos(theta[i]);
			float rz = radii[i] * sin(theta[i]);
			
			change = translate(rx, 0.0, rz);
			ball_ctms[i] = mmmult(ball_ctms[i], change);
			ball_locations[i] = mvmult(change, ball_locations[i]);*/
		}
		
	}	
	
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	//build table
	//build ball vertices (balls)
	//do ball transformations

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("project3");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
//#include <glm/glm/glm.hpp>
//#include <glm/glm/ext.hpp>
//#include <glm/glm/gtc/matrix_transform.hpp>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include "objReader.h"
#include <cmath>

using namespace std;

int stage = 1;
int limit = 4;
bool reset;

//맵
struct Map {
	bool isCube;
	int cubeNum;
	bool isPlayer;
};
Map map[8][8][8];


//발판
struct Cube {
	int x, y, z;
	bool fall;
	bool move;
};

Cube cube[8];

glm::vec3 CT1[31] = {

					glm::vec3(0, 0, 0) , //바닥부분 시작
					glm::vec3(1, 0, 0) ,
					glm::vec3(2, 0, 0) ,
					glm::vec3(3, 0, 0) ,
					glm::vec3(4, 0, 0) , //바닥부분 끝
					glm::vec3(0, 1, -1) , //벽부분 시작
					glm::vec3(1, 1, -1) ,
					glm::vec3(2, 1, -1) ,
					glm::vec3(3, 1, -1) ,
					glm::vec3(4, 1, -1) ,
					glm::vec3(0, 2, -1) ,
					glm::vec3(1, 2, -1) ,
					glm::vec3(2, 2, -1) ,
					glm::vec3(3, 2, -1) ,
					glm::vec3(4, 2, -1) ,
					glm::vec3(0, 3, -1) ,
					glm::vec3(1, 3, -1) ,
					glm::vec3(2, 3, -1) ,
					glm::vec3(3, 3, -1) ,
					glm::vec3(4, 3, -1) ,
					glm::vec3(0, 4, -1) ,
					glm::vec3(1, 4, -1) ,
					glm::vec3(2, 4, -1) ,
					glm::vec3(3, 4, -1) ,
					glm::vec3(4, 4, -1) ,
					glm::vec3(0, 5, -1) ,
					glm::vec3(1, 5, -1) ,
					glm::vec3(2, 5, -1) ,
					glm::vec3(3, 5, -1) ,
					glm::vec3(4, 5, -1) , //벽부분 끝
					glm::vec3(2, 6, -1)
};
glm::vec3 CT2[19] = {

					glm::vec3(0, 0, 0) , //바닥부분 시작
					glm::vec3(1, 0, 0) ,
					glm::vec3(2, 0, 0) , //바닥부분 끝
					glm::vec3(0, 1, -1) , //벽부분 시작
					glm::vec3(1, 1, -1) ,
					glm::vec3(2, 1, -1) ,
					glm::vec3(0, 2, -1) ,
					glm::vec3(1, 2, -1) ,
					glm::vec3(2, 2, -1) ,
					glm::vec3(0, 3, -1) ,
					glm::vec3(1, 3, -1) ,
					glm::vec3(2, 3, -1) ,
					glm::vec3(0, 4, -1) ,
					glm::vec3(1, 4, -1) ,
					glm::vec3(2, 4, -1) ,
					glm::vec3(0, 5, -1) ,
					glm::vec3(1, 5, -1) ,
					glm::vec3(2, 5, -1) , //벽부분 끝
					glm::vec3(1, 6, -1)
};
glm::vec3 CT3[25] = {
					glm::vec3(0, 0, 0) ,//바닥부분 시작
					glm::vec3(1, 0, -1) ,
					glm::vec3(2, 0, -2) ,
					glm::vec3(3, 0, -3) , //바닥부분 끝
					glm::vec3(0, 1, -1) , //벽부분 시작
					glm::vec3(0, 2, -1) ,
					glm::vec3(0, 3, -1) ,
					glm::vec3(0, 4, -1) ,
					glm::vec3(0, 5, -1) ,
					glm::vec3(1, 1, -2) ,
					glm::vec3(1, 2, -2) ,
					glm::vec3(1, 3, -2) ,
					glm::vec3(1, 4, -2) ,
					glm::vec3(1, 5, -2) ,
					glm::vec3(2, 1, -3) ,
					glm::vec3(2, 2, -3) ,
					glm::vec3(2, 3, -3) ,
					glm::vec3(2, 4, -3) ,
					glm::vec3(2, 5, -3) ,
					glm::vec3(3, 1, -4) ,
					glm::vec3(3, 2, -4) ,
					glm::vec3(3, 3, -4) ,
					glm::vec3(3, 4, -4) ,
					glm::vec3(3, 5, -4) , //벽부분 끝
					glm::vec3(3, 6, -4)
};

glm::vec3 CR = glm::vec3(0, 0, 0);

GLfloat CC[31] = { 
	(0.0f, 1.0f, 0.0f),//발판 색
	(0.0f, 1.0f, 0.0f),
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f), 
	(0.0f, 1.0f, 0.0f),
	(0.0f, 1.0f, 0.0f),
	(0.0f, 1.0f, 0.0f),
	(0.0f, 1.0f, 0.0f),
	(0.0f, 1.0f, 0.0f),
	(0.0f, 1.0f, 0.0f),
	(0.0f, 1.0f, 0.0f),
	(0.0f, 1.0f, 0.0f)
};

//플레이어(크레인)
struct Player {
	int x, y, z;
	int look;
};

Player crain;


//---윈도우 사이즈 변수
int WinSize_r = 1000;
int WinSize_w = 1000;
int windowID;		//---윈도우 아이디



//---콜백 함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);

//---glsl
void make_vertexShader();
void make_fragmentShader();
void InitShader();
void InitBuffer();
char* filetobuf(const char* file);
GLchar* vertexsource[3], * fragmentsource[3];		//---소스코드 저장 변수
GLuint vertexshader[3], fragmentshader[3];		//---세이더 객체
GLuint vao[3];
GLuint vbo[3];
GLuint vbo_color[3];
GLuint ebo[3];

GLuint vao_cube1[4];
GLuint vbo_cube1[4];
GLuint vbo_color_cube1[4];
GLuint ebo_cube1[4];

GLuint vao_cube2[4];
GLuint vbo_cube2[4];
GLuint vbo_color_cube2[4];
GLuint ebo_cube2[4];

GLuint vao_cube3[4];
GLuint vbo_cube3[4];
GLuint vbo_color_cube3[4];
GLuint ebo_cube3[4];

GLuint vao_cube4[4];
GLuint vbo_cube4[4];
GLuint vbo_color_cube4[4];
GLuint ebo_cube4[4];

GLuint vao_cube5[4];
GLuint vbo_cube5[4];
GLuint vbo_color_cube5[4];
GLuint ebo_cube5[4];

GLuint vao_cube6[4];
GLuint vbo_cube6[4];
GLuint vbo_color_cube6[4];
GLuint ebo_cube6[4];

GLuint vao_cube7[4];
GLuint vbo_cube7[4];
GLuint vbo_color_cube7[4];
GLuint ebo_cube7[4];

GLuint vao_cube8[4];
GLuint vbo_cube8[4];
GLuint vbo_color_cube8[4];
GLuint ebo_cube8[4];

//---쉐이더 프로그램
GLuint s_program;
GLuint s_program_line;
GLuint s_program_floor;

//-----색
GLfloat cube_color[4][24];


void RandRGB()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<GLclampf> rd_RGB(0.0, 1.0f);

	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cube_color[j][i] = rd_RGB(eng);
		}
	}
}

glm::vec3 Cube_trans[4] = { glm::vec3(0, 1, 0),
							glm::vec3(0, 0.5, 0) ,
							glm::vec3(-0.15, 0.3, 0) ,
							glm::vec3(0.15, 0.3, 0) };
glm::vec3 Cube_rotate[4] = { glm::vec3(0, 0, 0),
							glm::vec3(0, 0, 0) ,
							glm::vec3(0, 0, 0) ,
							glm::vec3(0, 0, 0) };
glm::vec3 pos_trans(3.5f, 6.0f, 5.5f);//초기 카메라 위치
glm::vec3 dir_trans(0.0f, 0.0f, 0.0f);
GLfloat rotate_screen = 0.0;
GLfloat rotate_camera_y = 0.0;
GLfloat rotate_camera_x = 0.0;
GLfloat rotate_camera_z = 0.0;

struct Camera_pos {
	GLfloat x, y, z;
};

Camera_pos camera_pos = { 0, 0, 0 };

void main(int argc, char** argv)		//---윈도우 출력, 콜백함수 설정
{
	//---윈도우 생성
	glutInit(&argc, argv);		//glut초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	//디스플레이 모드 설정
	glutInitWindowPosition(0, 0);					//윈도우 위치 지정
	glutInitWindowSize(WinSize_r, WinSize_w);					//윈도우 크기 지정
	windowID = glutCreateWindow("Example1");					//윈도우 생성

	//---GLEW 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)		//glew 초기화에 실패할 경우
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW initialized\n";


	RandRGB();
	InitShader();
	InitBuffer();


	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	//glutTimerFunc(10, TimerFunction, 0);

	glutMainLoop();
}
GLvoid drawScene()
{
	//---배경 초기화
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//---카메라 설정
	glm::vec4 cameraPos_trans(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 cameraDirection_trans(-5.0f, -8.0f, -10.0f, 1.0f);//카메라가 바라보는 각도

	glm::mat4 pos = glm::mat4(1.0f);
	pos = glm::translate(pos, glm::vec3(camera_pos.x, camera_pos.y, camera_pos.z));//카메라 회전의 중심점 변경
	pos = glm::rotate(pos, (GLfloat)glm::radians(rotate_screen), glm::vec3(0.0, 1.0, 0.0));
	pos = glm::translate(pos, glm::vec3(pos_trans.x, pos_trans.y, pos_trans.z));
	cameraPos_trans = pos * cameraPos_trans;

	glm::mat4 dir = glm::mat4(1.0f);
	dir = glm::translate(dir, glm::vec3(dir_trans.x, dir_trans.y, dir_trans.z));
	dir = glm::rotate(dir, (GLfloat)glm::radians(rotate_camera_x), glm::vec3(1.0, 0.0, 0.0));
	dir = glm::rotate(dir, (GLfloat)glm::radians(rotate_camera_y), glm::vec3(0.0, 1.0, 0.0));
	dir = glm::rotate(dir, (GLfloat)glm::radians(rotate_camera_z), glm::vec3(0.0, 0.0, 1.0));


	cameraDirection_trans = pos * dir * cameraDirection_trans;

	glm::vec3 cameraPos = glm::vec3(cameraPos_trans.x, cameraPos_trans.y, cameraPos_trans.z);		 //--- 카메라 위치 변경
	glm::vec3 cameraDirection = glm::vec3(cameraDirection_trans.x, cameraDirection_trans.y, cameraDirection_trans.z); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);		 //--- 카메라 위쪽 방향
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLoc_shape = glGetUniformLocation(s_program, "view"); //--- 뷰잉 변환 설정
	unsigned int viewLoc_line = glGetUniformLocation(s_program_line, "view"); //--- 뷰잉 변환 설정
	unsigned int viewLoc_floor = glGetUniformLocation(s_program_floor, "view"); //--- 뷰잉 변환 설정

	//---투영변환
	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
	//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0)); //--- 공간을 약간 뒤로 미뤄줌


	unsigned int projLoc_shape = glGetUniformLocation(s_program, "projection");
	unsigned int projLoc_line = glGetUniformLocation(s_program_line, "projection");
	unsigned int projLoc_floor = glGetUniformLocation(s_program_floor, "projection");

	//----------- 선 그리기
	glUseProgram(s_program_line);
	glUniformMatrix4fv(viewLoc_line, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projLoc_line, 1, GL_FALSE, &projection[0][0]);
	glPointSize(10.0);
	glDrawArrays(GL_LINES, 0, 6);

	//----------- 바닥 그리기
	//glUseProgram(s_program_floor);
	//glUniformMatrix4fv(viewLoc_floor, 1, GL_FALSE, &view[0][0]);
	//glUniformMatrix4fv(projLoc_floor, 1, GL_FALSE, &projection[0][0]);
	//glPointSize(10.0);
	//glDrawArrays(GL_TRIANGLES, 0, 6);


	//---------- 사각형 1 그리기
	glUseProgram(s_program);

	unsigned int modelLoc = glGetUniformLocation(s_program, "model");
	int vColorLocation = glGetUniformLocation(s_program, "vColor");

	glUniformMatrix4fv(viewLoc_shape, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projLoc_shape, 1, GL_FALSE, &projection[0][0]);

	//플레이어
	glm::mat4 Model_transfrom[4] = { glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f) };
	
	for (int i = 0; i < 4; i++)
	{
		if(i == 3)
			glBindVertexArray(vao[2]);
		else
			glBindVertexArray(vao[i]);

		if(i > 0 && i < 3)
			Model_transfrom[i] *= Model_transfrom[i - 1];
		else if(i == 3)
			Model_transfrom[i] *= Model_transfrom[1];

		
		Model_transfrom[i] = glm::translate(Model_transfrom[i], glm::vec3(Cube_trans[i].x, Cube_trans[i].y, Cube_trans[i].z));
		Model_transfrom[i] = glm::rotate(Model_transfrom[i], (GLfloat)glm::radians(Cube_rotate[i].x), glm::vec3(1.0, 0.0, 0.0));
		Model_transfrom[i] = glm::rotate(Model_transfrom[i], (GLfloat)glm::radians(Cube_rotate[i].y), glm::vec3(0.0, 1.0, 0.0));
		Model_transfrom[i] = glm::rotate(Model_transfrom[i], (GLfloat)glm::radians(Cube_rotate[i].z), glm::vec3(0.0, 0.0, 1.0));
		Model_transfrom[i] = glm::scale(Model_transfrom[i], glm::vec3(1.0, 1.0, 1.0));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(Model_transfrom[i]));

		glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);
	}

	//0-3
	glm::mat4 cube1_Model_transfrom[4] = { glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f) };
	for (int i = 0; i < 4; i++) {
		
		glBindVertexArray(vao_cube1[i]);

		if (stage == 1) cube1_Model_transfrom[i] = glm::translate(cube1_Model_transfrom[i], glm::vec3(CT1[i].x, CT1[i].y, CT1[i].z));
		else if (stage == 2) cube1_Model_transfrom[i] = glm::translate(cube1_Model_transfrom[i], glm::vec3(CT2[i].x, CT2[i].y, CT2[i].z));
		else if (stage == 3) cube1_Model_transfrom[i] = glm::translate(cube1_Model_transfrom[i], glm::vec3(CT3[i].x, CT3[i].y, CT3[i].z));
		cube1_Model_transfrom[i] = glm::rotate(cube1_Model_transfrom[i], (GLfloat)glm::radians(CR.x), glm::vec3(1.0, 0.0, 0.0));
		cube1_Model_transfrom[i] = glm::rotate(cube1_Model_transfrom[i], (GLfloat)glm::radians(CR.y), glm::vec3(0.0, 1.0, 0.0));
		cube1_Model_transfrom[i] = glm::rotate(cube1_Model_transfrom[i], (GLfloat)glm::radians(CR.z), glm::vec3(0.0, 0.0, 1.0));
		cube1_Model_transfrom[i] = glm::scale(cube1_Model_transfrom[i], glm::vec3(1.0, 2.0, 1.0));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube1_Model_transfrom[i]));
		glUniform4f(vColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	//4-7
	glm::mat4 cube2_Model_transfrom[4] = { glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f) };
	for (int i = 0; i < 4; i++) {

		glBindVertexArray(vao_cube2[i]);

		if (stage == 1) cube2_Model_transfrom[i] = glm::translate(cube2_Model_transfrom[i], glm::vec3(CT1[i+4].x, CT1[i+4].y, CT1[i+4].z));
		else if (stage == 2) cube2_Model_transfrom[i] = glm::translate(cube2_Model_transfrom[i], glm::vec3(CT2[i + 4].x, CT2[i + 4].y, CT2[i + 4].z));
		else if (stage == 3) cube2_Model_transfrom[i] = glm::translate(cube2_Model_transfrom[i], glm::vec3(CT3[i + 4].x, CT3[i + 4].y, CT3[i + 4].z));
		cube2_Model_transfrom[i] = glm::rotate(cube2_Model_transfrom[i], (GLfloat)glm::radians(CR.x), glm::vec3(1.0, 0.0, 0.0));
		cube2_Model_transfrom[i] = glm::rotate(cube2_Model_transfrom[i], (GLfloat)glm::radians(CR.y), glm::vec3(0.0, 1.0, 0.0));
		cube2_Model_transfrom[i] = glm::rotate(cube2_Model_transfrom[i], (GLfloat)glm::radians(CR.z), glm::vec3(0.0, 0.0, 1.0));
		cube2_Model_transfrom[i] = glm::scale(cube2_Model_transfrom[i], glm::vec3(1.0, 2.0, 1.0));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube2_Model_transfrom[i]));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	//8-11
	glm::mat4 cube3_Model_transfrom[4] = { glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f) };
	for (int i = 0; i < 4; i++) {

		glBindVertexArray(vao_cube3[i]);

		if (stage == 1) cube3_Model_transfrom[i] = glm::translate(cube3_Model_transfrom[i], glm::vec3(CT1[i + 8].x, CT1[i + 8].y, CT1[i + 8].z));
		else if (stage == 2) cube3_Model_transfrom[i] = glm::translate(cube3_Model_transfrom[i], glm::vec3(CT2[i + 8].x, CT2[i + 8].y, CT2[i + 8].z));
		else if (stage == 3) cube3_Model_transfrom[i] = glm::translate(cube3_Model_transfrom[i], glm::vec3(CT3[i + 8].x, CT3[i + 8].y, CT3[i + 8].z));
		cube3_Model_transfrom[i] = glm::rotate(cube3_Model_transfrom[i], (GLfloat)glm::radians(CR.x), glm::vec3(1.0, 0.0, 0.0));
		cube3_Model_transfrom[i] = glm::rotate(cube3_Model_transfrom[i], (GLfloat)glm::radians(CR.y), glm::vec3(0.0, 1.0, 0.0));
		cube3_Model_transfrom[i] = glm::rotate(cube3_Model_transfrom[i], (GLfloat)glm::radians(CR.z), glm::vec3(0.0, 0.0, 1.0));
		cube3_Model_transfrom[i] = glm::scale(cube3_Model_transfrom[i], glm::vec3(1.0, 2.0, 1.0));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube3_Model_transfrom[i]));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	//12-15
	glm::mat4 cube4_Model_transfrom[4] = { glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f) };
	for (int i = 0; i < 4; i++) {

		glBindVertexArray(vao_cube4[i]);

		if (stage == 1) cube4_Model_transfrom[i] = glm::translate(cube4_Model_transfrom[i], glm::vec3(CT1[i + 12].x, CT1[i + 12].y, CT1[i + 12].z));
		else if (stage == 2) cube4_Model_transfrom[i] = glm::translate(cube4_Model_transfrom[i], glm::vec3(CT2[i + 12].x, CT2[i + 12].y, CT2[i + 12].z));
		else if (stage == 3) cube4_Model_transfrom[i] = glm::translate(cube4_Model_transfrom[i], glm::vec3(CT3[i + 12].x, CT3[i + 12].y, CT3[i + 12].z));
		cube4_Model_transfrom[i] = glm::rotate(cube4_Model_transfrom[i], (GLfloat)glm::radians(CR.x), glm::vec3(1.0, 0.0, 0.0));
		cube4_Model_transfrom[i] = glm::rotate(cube4_Model_transfrom[i], (GLfloat)glm::radians(CR.y), glm::vec3(0.0, 1.0, 0.0));
		cube4_Model_transfrom[i] = glm::rotate(cube4_Model_transfrom[i], (GLfloat)glm::radians(CR.z), glm::vec3(0.0, 0.0, 1.0));
		cube4_Model_transfrom[i] = glm::scale(cube4_Model_transfrom[i], glm::vec3(1.0, 2.0, 1.0));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube4_Model_transfrom[i]));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	//16-19
	glm::mat4 cube5_Model_transfrom[4] = { glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f) };

	if (stage == 2) limit = 3;
	else limit = 4;
	for (int i = 0; i < limit; i++) {

		glBindVertexArray(vao_cube5[i]);

		if (stage == 1) cube5_Model_transfrom[i] = glm::translate(cube5_Model_transfrom[i], glm::vec3(CT1[i + 16].x, CT1[i + 16].y, CT1[i + 16].z));
		else if (stage == 2) cube5_Model_transfrom[i] = glm::translate(cube5_Model_transfrom[i], glm::vec3(CT2[i + 16].x, CT2[i + 16].y, CT2[i + 16].z));
		else if (stage == 3) cube5_Model_transfrom[i] = glm::translate(cube5_Model_transfrom[i], glm::vec3(CT3[i + 16].x, CT3[i + 16].y, CT3[i + 16].z));
		cube5_Model_transfrom[i] = glm::rotate(cube5_Model_transfrom[i], (GLfloat)glm::radians(CR.x), glm::vec3(1.0, 0.0, 0.0));
		cube5_Model_transfrom[i] = glm::rotate(cube5_Model_transfrom[i], (GLfloat)glm::radians(CR.y), glm::vec3(0.0, 1.0, 0.0));
		cube5_Model_transfrom[i] = glm::rotate(cube5_Model_transfrom[i], (GLfloat)glm::radians(CR.z), glm::vec3(0.0, 0.0, 1.0));
		cube5_Model_transfrom[i] = glm::scale(cube5_Model_transfrom[i], glm::vec3(1.0, 2.0, 1.0));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube5_Model_transfrom[i]));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	if (stage == 1 || stage == 3) {
		//20-23
		glm::mat4 cube6_Model_transfrom[4] = { glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f) };
		for (int i = 0; i < 4; i++) {

			glBindVertexArray(vao_cube6[i]);

			if (stage == 1) cube6_Model_transfrom[i] = glm::translate(cube6_Model_transfrom[i], glm::vec3(CT1[i + 20].x, CT1[i + 20].y, CT1[i + 20].z));
			else if (stage == 3) cube6_Model_transfrom[i] = glm::translate(cube6_Model_transfrom[i], glm::vec3(CT3[i + 20].x, CT3[i + 20].y, CT3[i + 20].z));
			cube6_Model_transfrom[i] = glm::rotate(cube6_Model_transfrom[i], (GLfloat)glm::radians(CR.x), glm::vec3(1.0, 0.0, 0.0));
			cube6_Model_transfrom[i] = glm::rotate(cube6_Model_transfrom[i], (GLfloat)glm::radians(CR.y), glm::vec3(0.0, 1.0, 0.0));
			cube6_Model_transfrom[i] = glm::rotate(cube6_Model_transfrom[i], (GLfloat)glm::radians(CR.z), glm::vec3(0.0, 0.0, 1.0));
			cube6_Model_transfrom[i] = glm::scale(cube6_Model_transfrom[i], glm::vec3(1.0, 2.0, 1.0));

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube6_Model_transfrom[i]));
			glUniform4f(vColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		}

		//24-27
		glm::mat4 cube7_Model_transfrom[4] = { glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f) };
		if (stage == 3) limit = 1;
		else limit = 4;
		for (int i = 0; i < limit; i++) {

			glBindVertexArray(vao_cube7[i]);

			if (stage == 1) cube7_Model_transfrom[i] = glm::translate(cube7_Model_transfrom[i], glm::vec3(CT1[i + 24].x, CT1[i + 24].y, CT1[i + 24].z));
			else if (stage == 3) cube7_Model_transfrom[i] = glm::translate(cube7_Model_transfrom[i], glm::vec3(CT3[i + 24].x, CT3[i + 24].y, CT3[i + 24].z));
			cube7_Model_transfrom[i] = glm::rotate(cube7_Model_transfrom[i], (GLfloat)glm::radians(CR.x), glm::vec3(1.0, 0.0, 0.0));
			cube7_Model_transfrom[i] = glm::rotate(cube7_Model_transfrom[i], (GLfloat)glm::radians(CR.y), glm::vec3(0.0, 1.0, 0.0));
			cube7_Model_transfrom[i] = glm::rotate(cube7_Model_transfrom[i], (GLfloat)glm::radians(CR.z), glm::vec3(0.0, 0.0, 1.0));
			cube7_Model_transfrom[i] = glm::scale(cube7_Model_transfrom[i], glm::vec3(1.0, 2.0, 1.0));

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube7_Model_transfrom[i]));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		}

		if (stage == 1) {
			//28-30
			glm::mat4 cube8_Model_transfrom[4] = { glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f) };
			for (int i = 0; i < 3; i++) {

				glBindVertexArray(vao_cube8[i]);

				cube8_Model_transfrom[i] = glm::translate(cube8_Model_transfrom[i], glm::vec3(CT1[i + 28].x, CT1[i + 28].y, CT1[i + 28].z));
				cube8_Model_transfrom[i] = glm::rotate(cube8_Model_transfrom[i], (GLfloat)glm::radians(CR.x), glm::vec3(1.0, 0.0, 0.0));
				cube8_Model_transfrom[i] = glm::rotate(cube8_Model_transfrom[i], (GLfloat)glm::radians(CR.y), glm::vec3(0.0, 1.0, 0.0));
				cube8_Model_transfrom[i] = glm::rotate(cube8_Model_transfrom[i], (GLfloat)glm::radians(CR.z), glm::vec3(0.0, 0.0, 1.0));
				cube8_Model_transfrom[i] = glm::scale(cube8_Model_transfrom[i], glm::vec3(1.0, 2.0, 1.0));

				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube8_Model_transfrom[i]));

				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

			}
		}
	}
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}

void make_vertexShader()
{
	vertexsource[0] = filetobuf("vertex_shape.glsl");
	vertexsource[1] = filetobuf("vertex_line.glsl");
	vertexsource[2] = filetobuf("vertex_floor.glsl");

	for (int i = 0; i < 3; i++)
	{
		//--- 버텍스 세이더 객체 만들기
		vertexshader[i] = glCreateShader(GL_VERTEX_SHADER);

		//--- 세이더 코드를 세이더 객체에 넣기
		glShaderSource(vertexshader[i], 1, (const GLchar**)&vertexsource[i], 0);

		//--- 버텍스 세이더 컴파일하기
		glCompileShader(vertexshader[i]);

		//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
		GLint result;
		GLchar errorLog[512];
		glGetShaderiv(vertexshader[i], GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(vertexshader[i], 512, NULL, errorLog);
			std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
			return;
		}
	}


}
void make_fragmentShader()
{
	fragmentsource[0] = filetobuf("fragment_shape.glsl");
	fragmentsource[1] = filetobuf("fragment_line.glsl");
	fragmentsource[2] = filetobuf("fragment_floor.glsl");

	for (int i = 0; i < 3; i++)
	{
		//--- 프래그먼트 세이더 객체 만들기
		fragmentshader[i] = glCreateShader(GL_FRAGMENT_SHADER);

		//--- 세이더 코드를 세이더 객체에 넣기
		glShaderSource(fragmentshader[i], 1, (const GLchar**)&fragmentsource[i], 0);

		//--- 프래그먼트 세이더 컴파일
		glCompileShader(fragmentshader[i]);

		//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
		GLint result;
		GLchar errorLog[512];
		glGetShaderiv(fragmentshader[i], GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(fragmentshader[i], 512, NULL, errorLog);
			std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
			return;
		}
	}
}

void LinkShader(GLuint &program, GLuint &vertex, GLuint &fragment)
{
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);

	// ---세이더가 잘 연결되었는지 체크하기
	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(program, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
		return;
	}
}

void InitShader()
{
	make_vertexShader(); //--- 버텍스 세이더 만들기
	make_fragmentShader(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	s_program = glCreateProgram();
	s_program_line = glCreateProgram();
	s_program_floor = glCreateProgram();


	LinkShader(s_program, vertexshader[0], fragmentshader[0]);
	LinkShader(s_program_line, vertexshader[1], fragmentshader[1]);
	LinkShader(s_program_floor, vertexshader[2], fragmentshader[2]);

	//--- 세이더 삭제하기
	for (int i = 0; i < 3; i++)
	{
		glDeleteShader(vertexshader[i]);
		glDeleteShader(fragmentshader[i]);
	}
}

void InitBuffer(){

	obj objfile[4];
	objfile[0].OpenFile("cube_18_1.obj");
	objfile[1].OpenFile("cube_18_2.obj");
	objfile[2].OpenFile("cube_18_3.obj");
	objfile[3].OpenFile("cube_18_4.obj");

	glGenVertexArrays(3, vao);
	glGenBuffers(3, vbo);
	glGenBuffers(3, vbo_color);
	glGenBuffers(3, ebo);


	//플레이어
	for (int i = 0; i < 3; i++)
	{
		objfile[i].ReadObj();

		glBindVertexArray(vao[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, objfile[i].vertexNum * 3 * sizeof(GLfloat), objfile[i].vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objfile[i].faceNum * 3 * sizeof(int), objfile[i].face_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_color[i]);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube_color[i], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
	}

	//0-3
	glGenVertexArrays(4, vao_cube1);
	glGenBuffers(4, vbo_cube1);
	glGenBuffers(4, vbo_color_cube1);
	glGenBuffers(4, ebo_cube1);

	for (int i = 0; i < 4; i++)
	{
		objfile[3].ReadObj();

		glBindVertexArray(vao_cube1[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_cube1[i]);
		glBufferData(GL_ARRAY_BUFFER, objfile[1].vertexNum * 3 * sizeof(GLfloat), objfile[3].vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_cube1[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objfile[3].faceNum * 3 * sizeof(int), objfile[3].face_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		if (i != 0) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo_color_cube1[i]);
			glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube_color[2], GL_STATIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
			glEnableVertexAttribArray(1);
			
		}
	}

	//4-7
	glGenVertexArrays(4, vao_cube2);
	glGenBuffers(4, vbo_cube2);
	glGenBuffers(4, vbo_color_cube2);
	glGenBuffers(4, ebo_cube2);

	for (int i = 0; i < 4; i++)
	{
		objfile[3].ReadObj();

		glBindVertexArray(vao_cube2[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_cube2[i]);
		glBufferData(GL_ARRAY_BUFFER, objfile[3].vertexNum * 3 * sizeof(GLfloat), objfile[3].vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_cube2[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objfile[3].faceNum * 3 * sizeof(int), objfile[3].face_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_color_cube2[i]);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube_color[0], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
	}

	//8-11
	glGenVertexArrays(4, vao_cube3);
	glGenBuffers(4, vbo_cube3);
	glGenBuffers(4, vbo_color_cube3);
	glGenBuffers(4, ebo_cube3);

	for (int i = 0; i < 4; i++)
	{
		objfile[3].ReadObj();

		glBindVertexArray(vao_cube3[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_cube3[i]);
		glBufferData(GL_ARRAY_BUFFER, objfile[3].vertexNum * 3 * sizeof(GLfloat), objfile[3].vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_cube3[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objfile[3].faceNum * 3 * sizeof(int), objfile[3].face_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_color_cube3[i]);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube_color[0], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
	}

	//12-15
	glGenVertexArrays(4, vao_cube4);
	glGenBuffers(4, vbo_cube4);
	glGenBuffers(4, vbo_color_cube4);
	glGenBuffers(4, ebo_cube4);

	for (int i = 0; i < 4; i++)
	{
		objfile[3].ReadObj();

		glBindVertexArray(vao_cube4[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_cube4[i]);
		glBufferData(GL_ARRAY_BUFFER, objfile[3].vertexNum * 3 * sizeof(GLfloat), objfile[3].vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_cube4[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objfile[3].faceNum * 3 * sizeof(int), objfile[3].face_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_color_cube4[i]);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube_color[0], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
	}

	//16-19
	glGenVertexArrays(4, vao_cube5);
	glGenBuffers(4, vbo_cube5);
	glGenBuffers(4, vbo_color_cube5);
	glGenBuffers(4, ebo_cube5);

	for (int i = 0; i < 4; i++)
	{
		objfile[3].ReadObj();

		glBindVertexArray(vao_cube5[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_cube5[i]);
		glBufferData(GL_ARRAY_BUFFER, objfile[3].vertexNum * 3 * sizeof(GLfloat), objfile[3].vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_cube5[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objfile[3].faceNum * 3 * sizeof(int), objfile[3].face_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_color_cube5[i]);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube_color[0], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
	}

	//20-23
	glGenVertexArrays(4, vao_cube6);
	glGenBuffers(4, vbo_cube6);
	glGenBuffers(4, vbo_color_cube6);
	glGenBuffers(4, ebo_cube6);

	for (int i = 0; i < 4; i++)
	{
		objfile[3].ReadObj();

		glBindVertexArray(vao_cube6[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_cube6[i]);
		glBufferData(GL_ARRAY_BUFFER, objfile[3].vertexNum * 3 * sizeof(GLfloat), objfile[3].vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_cube6[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objfile[3].faceNum * 3 * sizeof(int), objfile[3].face_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_color_cube6[i]);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube_color[0], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
	}

	//24-27
	glGenVertexArrays(4, vao_cube7);
	glGenBuffers(4, vbo_cube7);
	glGenBuffers(4, vbo_color_cube7);
	glGenBuffers(4, ebo_cube7);

	for (int i = 0; i < 4; i++)
	{
		objfile[3].ReadObj();

		glBindVertexArray(vao_cube7[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_cube7[i]);
		glBufferData(GL_ARRAY_BUFFER, objfile[3].vertexNum * 3 * sizeof(GLfloat), objfile[3].vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_cube7[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objfile[3].faceNum * 3 * sizeof(int), objfile[3].face_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_color_cube7[i]);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube_color[1], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
	}

	//28-30
	glGenVertexArrays(3, vao_cube8);
	glGenBuffers(3, vbo_cube8);
	glGenBuffers(3, vbo_color_cube8);
	glGenBuffers(3, ebo_cube8);

	for (int i = 0; i < 3; i++)
	{
		objfile[3].ReadObj();

		glBindVertexArray(vao_cube8[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_cube8[i]);
		glBufferData(GL_ARRAY_BUFFER, objfile[3].vertexNum * 3 * sizeof(GLfloat), objfile[3].vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_cube8[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objfile[3].faceNum * 3 * sizeof(int), objfile[3].face_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_color_cube8[i]);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube_color[1], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
	}

}

int isMove_x = 0;
int isMove_y = 0;
int isMove_z = 0;
int isRotate = 0;
int isRotateArm = 0;
int isCameraRotate_ori = 0;


GLvoid TimerFunction(int value)
{

	if (value == 1 && isMove_x != 0)
	{
		Cube_trans[0].x += isMove_x * 0.01;
		camera_pos.x += isMove_x  * 0.01;

		glutTimerFunc(10, TimerFunction, 1);
	}
	if (value == 3 && isMove_y != 0)
	{
		Cube_trans[0].y += isMove_y * 0.01;
		camera_pos.y += isMove_y * 0.01;

		glutTimerFunc(10, TimerFunction, 3);
	}
	if (value == 4 && isMove_z != 0)
	{
		Cube_trans[0].z += isMove_z * 0.01;
		camera_pos.z += isMove_z * 0.01;
		glutTimerFunc(10, TimerFunction, 4);
	}
	if (value == 2 && isRotate != 0)
	{
		Cube_rotate[1].y += isRotate;

		glutTimerFunc(10, TimerFunction, 2);
	}
	glutPostRedisplay();
}



GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		if (isMove_x == 0)
			glutTimerFunc(10, TimerFunction, 1);
		
		if (isMove_x == 1)
			isMove_x = 0;
		else
			isMove_x = 1;
		break;
	case 'A':
		if (isMove_x == 0)
			glutTimerFunc(10, TimerFunction, 1);

		if (isMove_x == -1)
			isMove_x = 0;
		else
			isMove_x = -1;
		break;
	case 's':
		if (isMove_y == 0)
			glutTimerFunc(10, TimerFunction, 3);

		if (isMove_y == 1)
			isMove_y = 0;
		else
			isMove_y = 1;
		break;
	case 'S':
		if (isMove_y == 0)
			glutTimerFunc(10, TimerFunction, 3);

		if (isMove_y == -1)
			isMove_y = 0;
		else
			isMove_y = -1;
		break;
	case 'd':
		if (isMove_z == 0)
			glutTimerFunc(10, TimerFunction, 4);

		if (isMove_z == 1)
			isMove_z = 0;
		else
			isMove_z = 1;
		break;
	case 'D':
		if (isMove_z == 0)
			glutTimerFunc(10, TimerFunction, 4);

		if (isMove_z == -1)
			isMove_z = 0;
		else
			isMove_z = -1;
		break;
	case 'm':
		if (isRotate == 0)
			glutTimerFunc(10, TimerFunction, 2);

		if (isRotate == 1)
			isRotate = 0;
		else
			isRotate = 1;
		break;
	case 'M':
		if (isRotate == 0)
			glutTimerFunc(10, TimerFunction, 2);

		if (isRotate == -1)
			isRotate = 0;
		else
			isRotate = -1;
		break;
	case 'z':
		rotate_camera_z += 1.0;
		break;
	case 'Z':
		rotate_camera_z -= 1.0;
		break;
	case 'x':
		rotate_camera_x += 1.0;
		break;
	case 'X':
		rotate_camera_x -= 1.0;
		break;
	case 'y':
		rotate_camera_y += 1.0;
		break;
	case 'Y':
		rotate_camera_y -= 1.0;
		break;
	case 'r':
		rotate_screen += 1.0;
		break;
	case 'R':
		rotate_screen -= 1.0;
		break;
	case 'c':
		isMove_x = 0;
		isRotate = 0;
		isRotateArm = 0;
		isCameraRotate_ori = 0;

		Cube_trans[0] = glm::vec3(0, 1, 0);
		Cube_trans[1] = glm::vec3(0, 0.5, 0);
		Cube_trans[2] = glm::vec3(-0.15, 0.3, 0);
		Cube_trans[3] = glm::vec3(0.15, 0.3, 0);
		Cube_rotate[0] = glm::vec3(0, 0, 0);
		Cube_rotate[1] = glm::vec3(0, 0, 0);
		Cube_rotate[2] = glm::vec3(0, 0, 0);
		Cube_rotate[3] = glm::vec3(0, 0, 0);


		pos_trans = glm::vec3(3.5f, 6.0f, 5.5f);
		dir_trans = glm::vec3 (0.0f, 0.0f, 0.0f);
		camera_pos = { 0, 0, 0 };
		rotate_screen = 0.0;
		rotate_camera_y = 0.0;
		break;
	case 'q':
		glutDestroyWindow(windowID);
		break;

	case'j':
		camera_pos.x += 0.1f;
		break;
	case'J':
		camera_pos.x -= 0.1f;
		break;
	case'k':
		camera_pos.y += 0.1f;
		break;
	case'K':
		camera_pos.y -= 0.1f;
		break;
	case'l':
		camera_pos.z += 0.1f;
		break;
	case'L':
		camera_pos.z -= 0.1f;
		break;
	case'1':
		stage = 1;
		break;
	case'2':
		stage = 2;
		break;
	case'3':
		stage = 3;
		break;

	}


	glutPostRedisplay();
}


char* filetobuf(const char* file)
{
	FILE* fp;
	long length;
	char* buf;

	fp = fopen(file, "rb");

	if (!fp)
		assert(fp != nullptr);

	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	buf = (char*)malloc(sizeof(char) * length + 1);
	fseek(fp, 0, SEEK_SET);
	if (buf != nullptr)
		fread(buf, 1, length + 1, fp);

	fclose(fp);
	if (buf != nullptr)
		buf[length] = 0;

	return buf;
}
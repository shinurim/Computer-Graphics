#include <GL/glut.h>
#include <math.h>

float h = 0.25;
float a = 0.01f;
float t = 0;
float walk = 0; //걷기 변수
GLUquadricObj* cyl;

void MyIdle()
{
	t = t + 1.0f;
	if (h <= 0.1) a = +0.0001f;
	if (h >= 0.6) a = -0.0001f;
	h = h + a;
	glutPostRedisplay();
}

void MyTimer(int v) {
	t = t + 1.0f;
	if (h <= 0.1) a = 0.01f;
	if (h >= 0.6) a = -0.01f;
	h = h + a;
	walk = walk + 0.001; //0.001만큼씩 이동
	glutTimerFunc(10, MyTimer, 0); // 10ms마다 MyIdle 호출
	glutPostRedisplay();
}
// 현재 좌표계에서, 높낮이는 y축으로, 앞뒤는 z축으로, 좌우는 x축으로 설정되어 있다.
void MyDisplay() {
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_LINE);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// 발판
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glScalef(8, 0.3, 8);
	glutWireCube(0.3);
	glPopMatrix(); //발판 나오기

	// 몸통
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0.0-walk, 0.0 , 0.5- walk ); // 앞으로 걸어나감
	gluCylinder(cyl, 0.1, 0.1, 0.3, 20, 5);
	
	// 목
	glPushMatrix(); //몸통을 기준으로 목 그리기
	glTranslatef(0.0, 0.0, 0.3);
	gluCylinder(cyl, 0.02, 0.02, 0.05, 20, 1);

	// 얼굴
	glPushMatrix(); //목을 기준으로 얼굴 그리기
	glTranslatef(0.0, 0.0, 0.15);
	glutWireSphere(0.1, 20, 20);
	glPopMatrix(); //얼굴 나오기
	glPopMatrix(); //목 나오기

	// 팔1
	glPushMatrix(); //몸통을 기준으로 팔1 그리기
	glTranslatef(0.15, 0.0, 0.25);
	glutWireSphere(0.05, 20, 20); //어깨 그리기
	glRotatef(180, 1, 180, 0); //반대로 움직이도록 180도 회전
	float arm_angle = 30 * sin(t * 0.005);  // -30도에서 +30도 사이로 제한
	glRotatef(arm_angle, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// 팔1-2
	glPushMatrix(); //팔1을 기준으로 팔1-2 그리기
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20); //팔꿈치 그리기
	float forearm_angle = fmax(0, 40 * sin(t * 0.005));  // 0도에서 +40도 사이로 제한
	glRotatef(forearm_angle, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.1, 20, 1);

	//손1
	glPushMatrix(); //팔1-2을 기준으로 손1그리기
	glTranslatef(0.0, 0.0, 0.13);
	glutWireSphere(0.05, 20, 20);
	glPopMatrix(); //손1 나오기

	glPopMatrix(); //팔1-2 나오기
	glPopMatrix(); //팔1 나오기

	// 팔2
	glPushMatrix(); //몸통을 기준으로 팔2 그리기
	glTranslatef(-0.15, 0.0, 0.25);
	glutWireSphere(0.05, 20, 20); //어깨 그리기
	glRotatef(180, 1, 0, 0);
	glRotatef(arm_angle, 1, 0, 0);  
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// 팔2-2
	glPushMatrix(); //팔2을 기준으로 팔2-2 그리기
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20); //팔꿈치 그리기
	forearm_angle = fmax(0, -40 * sin(t * 0.005)); // 0도에서 -40도 사이로 제한
	glRotatef(-forearm_angle, 1, 0, 0);  // 반대 방향으로 움직이게
	gluCylinder(cyl, 0.05, 0.05, 0.1, 20, 1);

	//손2
	glPushMatrix(); //팔2-2을 기준으로 손2 그리기
	glTranslatef(0.0, 0.0, 0.13);
	glutWireSphere(0.05, 20, 20);
	glPopMatrix(); //손2 나오기

	glPopMatrix(); //팔2-2 나오기
	glPopMatrix(); //팔2 나오기

	// 다리1
	glPushMatrix(); //몸통을 기준으로 다리1 그리기
	glTranslatef(0.08, 0.0, -0.05);
	glutWireSphere(0.05, 20, 20); //고관절 그리기
	glRotatef(180, 1, 0, 0);
	float thigh_angle = 30 * sin(t * 0.005); // -30도에서 +30도 사이로 제한
	glRotatef(thigh_angle, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// 다리1-2
	glPushMatrix(); //다리1을 기준으로 다리1-2 그리기
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20); //무릎 그리기
	float right_knee_angle = fmax(0, -30 * sin(t * 0.005)); // 0도에서 -30도 사이로 제한
	glRotatef(right_knee_angle, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// 발1
	glPushMatrix(); //다리1-2을 기준으로 발1 그리기
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20);
	glPopMatrix(); //발1 나오기

	glPopMatrix(); //다리1-2 나오기
	glPopMatrix(); //다리1 나오기

	// 5. 다리2
	glPushMatrix(); //몸통을 기준으로 다리2 그리기
	glTranslatef(-0.08, 0.0, -0.05);
	glutWireSphere(0.05, 20, 20); //고관절 그리기
	glRotatef(180, 1, 0, 0);
	glRotatef(-thigh_angle, 1, 0, 0); // 반대 방향으로 움직이게
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// 5. 다리2-2
	glPushMatrix(); //다리2를 기준으로 다리2-2 그리기
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20); //무릎 그리기
	float left_knee_angle = fmax(0, 30 * sin(t * 0.005)); // 0도에서 30도 사이로 제한
	glRotatef(left_knee_angle, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// 발2
	glPushMatrix(); //다리2-2을 기준으로 발2 그리기
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20);
	glPopMatrix(); //발2 나오기

	glPopMatrix(); //다리 2-2 나오기
	glPopMatrix(); //다리2 나오기


	glPopMatrix();	//몸통 나오기
	glFlush(); //그리기
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(600, 600); //윈도우 사이즈 600X600
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Walking Person"); //Walking Person
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, 1, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 1.6, 8, //각도 조정
		0, 0, 0,
		0, 1, 0);

	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyIdle); // timer를 사용하기로 한다.
	glutTimerFunc(10, MyTimer, 0); // 10ms마다 MyIdle 호출
	glutMainLoop();
	return 0;
}

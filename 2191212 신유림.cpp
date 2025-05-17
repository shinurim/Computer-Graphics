#include <GL/glut.h>
#include <math.h>

float h = 0.25;
float a = 0.01f;
float t = 0;
float walk = 0; //�ȱ� ����
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
	walk = walk + 0.001; //0.001��ŭ�� �̵�
	glutTimerFunc(10, MyTimer, 0); // 10ms���� MyIdle ȣ��
	glutPostRedisplay();
}
// ���� ��ǥ�迡��, �����̴� y������, �յڴ� z������, �¿�� x������ �����Ǿ� �ִ�.
void MyDisplay() {
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_LINE);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// ����
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glScalef(8, 0.3, 8);
	glutWireCube(0.3);
	glPopMatrix(); //���� ������

	// ����
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0.0-walk, 0.0 , 0.5- walk ); // ������ �ɾ��
	gluCylinder(cyl, 0.1, 0.1, 0.3, 20, 5);
	
	// ��
	glPushMatrix(); //������ �������� �� �׸���
	glTranslatef(0.0, 0.0, 0.3);
	gluCylinder(cyl, 0.02, 0.02, 0.05, 20, 1);

	// ��
	glPushMatrix(); //���� �������� �� �׸���
	glTranslatef(0.0, 0.0, 0.15);
	glutWireSphere(0.1, 20, 20);
	glPopMatrix(); //�� ������
	glPopMatrix(); //�� ������

	// ��1
	glPushMatrix(); //������ �������� ��1 �׸���
	glTranslatef(0.15, 0.0, 0.25);
	glutWireSphere(0.05, 20, 20); //��� �׸���
	glRotatef(180, 1, 180, 0); //�ݴ�� �����̵��� 180�� ȸ��
	float arm_angle = 30 * sin(t * 0.005);  // -30������ +30�� ���̷� ����
	glRotatef(arm_angle, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// ��1-2
	glPushMatrix(); //��1�� �������� ��1-2 �׸���
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20); //�Ȳ�ġ �׸���
	float forearm_angle = fmax(0, 40 * sin(t * 0.005));  // 0������ +40�� ���̷� ����
	glRotatef(forearm_angle, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.1, 20, 1);

	//��1
	glPushMatrix(); //��1-2�� �������� ��1�׸���
	glTranslatef(0.0, 0.0, 0.13);
	glutWireSphere(0.05, 20, 20);
	glPopMatrix(); //��1 ������

	glPopMatrix(); //��1-2 ������
	glPopMatrix(); //��1 ������

	// ��2
	glPushMatrix(); //������ �������� ��2 �׸���
	glTranslatef(-0.15, 0.0, 0.25);
	glutWireSphere(0.05, 20, 20); //��� �׸���
	glRotatef(180, 1, 0, 0);
	glRotatef(arm_angle, 1, 0, 0);  
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// ��2-2
	glPushMatrix(); //��2�� �������� ��2-2 �׸���
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20); //�Ȳ�ġ �׸���
	forearm_angle = fmax(0, -40 * sin(t * 0.005)); // 0������ -40�� ���̷� ����
	glRotatef(-forearm_angle, 1, 0, 0);  // �ݴ� �������� �����̰�
	gluCylinder(cyl, 0.05, 0.05, 0.1, 20, 1);

	//��2
	glPushMatrix(); //��2-2�� �������� ��2 �׸���
	glTranslatef(0.0, 0.0, 0.13);
	glutWireSphere(0.05, 20, 20);
	glPopMatrix(); //��2 ������

	glPopMatrix(); //��2-2 ������
	glPopMatrix(); //��2 ������

	// �ٸ�1
	glPushMatrix(); //������ �������� �ٸ�1 �׸���
	glTranslatef(0.08, 0.0, -0.05);
	glutWireSphere(0.05, 20, 20); //����� �׸���
	glRotatef(180, 1, 0, 0);
	float thigh_angle = 30 * sin(t * 0.005); // -30������ +30�� ���̷� ����
	glRotatef(thigh_angle, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// �ٸ�1-2
	glPushMatrix(); //�ٸ�1�� �������� �ٸ�1-2 �׸���
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20); //���� �׸���
	float right_knee_angle = fmax(0, -30 * sin(t * 0.005)); // 0������ -30�� ���̷� ����
	glRotatef(right_knee_angle, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// ��1
	glPushMatrix(); //�ٸ�1-2�� �������� ��1 �׸���
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20);
	glPopMatrix(); //��1 ������

	glPopMatrix(); //�ٸ�1-2 ������
	glPopMatrix(); //�ٸ�1 ������

	// 5. �ٸ�2
	glPushMatrix(); //������ �������� �ٸ�2 �׸���
	glTranslatef(-0.08, 0.0, -0.05);
	glutWireSphere(0.05, 20, 20); //����� �׸���
	glRotatef(180, 1, 0, 0);
	glRotatef(-thigh_angle, 1, 0, 0); // �ݴ� �������� �����̰�
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// 5. �ٸ�2-2
	glPushMatrix(); //�ٸ�2�� �������� �ٸ�2-2 �׸���
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20); //���� �׸���
	float left_knee_angle = fmax(0, 30 * sin(t * 0.005)); // 0������ 30�� ���̷� ����
	glRotatef(left_knee_angle, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	// ��2
	glPushMatrix(); //�ٸ�2-2�� �������� ��2 �׸���
	glTranslatef(0.0, 0.0, 0.2);
	glutWireSphere(0.05, 20, 20);
	glPopMatrix(); //��2 ������

	glPopMatrix(); //�ٸ� 2-2 ������
	glPopMatrix(); //�ٸ�2 ������


	glPopMatrix();	//���� ������
	glFlush(); //�׸���
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(600, 600); //������ ������ 600X600
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Walking Person"); //Walking Person
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, 1, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 1.6, 8, //���� ����
		0, 0, 0,
		0, 1, 0);

	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyIdle); // timer�� ����ϱ�� �Ѵ�.
	glutTimerFunc(10, MyTimer, 0); // 10ms���� MyIdle ȣ��
	glutMainLoop();
	return 0;
}
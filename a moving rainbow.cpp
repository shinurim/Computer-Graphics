#include <GL/glut.h>
#include <stdio.h>

void MyDisplay(); void MyTimer(int Value); // 디스플레이 콜백 함수와 타이머 콜백 함수 선언
bool leftRight = false; // 무지개가 좌우로 움직이는 방향 제어
int upDown = 0; //무지개가 위 아래로 움직이는 방향 제어
float Delta1 = 0; //좌우로 움직이는 값
float Delta2 = 0; //위아래로 움직이는 값
float rainbow[8][4] = { // 무지개 색상 정의
	{1,0,0,1},   //빨
	{1,0.5,0,1}, //주
	{1,1,0,1},   //노
	{0,1,0,1},   //초
	{0,0,1,0.5}, //파
	{0,0,0.5,1}, //남
	{1,0,1,1},   //보
	{1,1,1,1}    //흰
};
//main 함수
int main(int argc, char** argv) {
	glutInit(&argc, argv);     //GLUT 윈도우 함수
	glutInitWindowSize(600, 600); // 창 크기 600x600
	glutCreateWindow("OpenGL Drawing Example"); // "OpenGL Drawing Example" 창 생성
	glClearColor(1.0, 1.0, 1.0, 0.0); // 배경색 흰색 설정
	glutDisplayFunc(MyDisplay);	// 콜백함수 등록 함수 
	glutTimerFunc(50, MyTimer, 1); // 50ms 주기로 MyTimer 호출
	glutMainLoop(); // 이벤트 루프
	return 0;
}
// 타이머 콜백 함수_Delta값에 변화를 주어 무지개가 반시계방향 사각형 궤도로 움직임
void MyTimer(int Value) {
	// 오른쪽 끝 도달하면 위로 올라가기
	if (Delta1 >= 0.3) { 
		upDown = 1;
	} 
	// 왼쪽 끝 도달하면 아래로 내려가기
	else if (Delta1 <= -0.3) { 
		upDown = 2; 
	}
	//upDown == 1 위로 이동
	if (upDown == 1) {
		Delta2 = Delta2 + 0.02; //0.02씩 값 증가
		//0.2만큼 이동한 후 왼쪽으로 이동하기 위해 upDown에 0값을 주고
		//leftRight에 true값(왼쪽으로 이동)을 준 뒤 위에 조건문에 걸리지 않도록 값의 변화를 줌
		if (Delta2 >= 0.2) { 
			upDown = 0;
			leftRight = true;
			Delta1 = Delta1 - 0.01;
		}
	}
	//upDown == 1 아래로 이동
	else if (upDown == 2) {
		Delta2 = Delta2 - 0.02; //0.02씩 값 감소
		//-0.4만큼 이동한 후 오른쪽으로 이동하기 위해 upDown에 0값을 주고
		//leftRight에 false값(오른쪽으로 이동)을 준 뒤 위에 조건문에 걸리지 않도록 값의 변화를 줌
		if (Delta2 <= -0.4) {
			upDown = 0;
			leftRight = false;
			Delta1 = Delta1 + 0.01;
		}
	}
	//upDown ==0 수평 이동
	else {
		if (leftRight) {
			Delta1 = Delta1 - 0.02; // 왼쪽으로 이동
		}
		else {
			Delta1 = Delta1 + 0.02; // 오른쪽으로 이동
		}
	}
	glutPostRedisplay(); // 다시 그리기 요청
	glutTimerFunc(50, MyTimer, 1);  //타이머 반복
}
// 디스플레이 콜백 함수 _무지개 그리기
void MyDisplay() {
	float size = 0;  // 각 색깔마다 줄어드는 반지름 값
	glClear(GL_COLOR_BUFFER_BIT); // 화면 지우기

	for (int i = 0;i < 8;i++) {
		glColor4f(rainbow[i][0], rainbow[i][1], rainbow[i][2], rainbow[i][3]);
		glBegin(GL_TRIANGLE_FAN); // 삼각형 팬으로 반원 형태 무지개 그리기
		//(0,0,0)을 중심으로 왼쪽에서 오른쪽으로 반원의 무지개를 그리기
		glVertex3f(0+ Delta1, 0 + Delta2, 0);
		glVertex3f(-0.7 + Delta1, 0 + Delta2, 0);
		glVertex3f(-0.65 + Delta1, 0.2 - size +Delta2, 0);
		glVertex3f(-0.6 + Delta1, 0.35 - size + Delta2, 0);
		glVertex3f(-0.55 + Delta1, 0.43 - size + Delta2, 0);
		glVertex3f(-0.5 + Delta1, 0.50 - size + Delta2, 0);
		glVertex3f(-0.45 + Delta1, 0.56 - size + Delta2, 0);
		glVertex3f(-0.4 + Delta1, 0.61 - size + Delta2, 0);
		glVertex3f(-0.3 + Delta1, 0.65 - size + Delta2, 0);
		glVertex3f(-0.2 + Delta1, 0.69 - size + Delta2, 0);
		glVertex3f(-0.1 + Delta1, 0.695 - size + Delta2, 0);
		glVertex3f(0 + Delta1, 0.7 - size + Delta2, 0);
		glVertex3f(0.1 + Delta1, 0.695 - size + Delta2, 0);
		glVertex3f(0.2 + Delta1, 0.69 - size + Delta2, 0);
		glVertex3f(0.3 + Delta1, 0.65 - size + Delta2, 0);
		glVertex3f(0.4 + Delta1, 0.61 - size + Delta2, 0);
		glVertex3f(0.45 + Delta1, 0.56 - size + Delta2, 0);
		glVertex3f(0.5 + Delta1, 0.50 - size + Delta2, 0);
		glVertex3f(0.55 + Delta1, 0.43 - size + Delta2, 0);
		glVertex3f(0.6 + Delta1, 0.35 - size + Delta2, 0);
		glVertex3f(0.65 + Delta1, 0.2 - size + Delta2, 0);
		glVertex3f(0.7 + Delta1, 0 + Delta2, 0);
		glEnd();
		size += 0.05;
	}
	glFlush(); // 명령 실행
}


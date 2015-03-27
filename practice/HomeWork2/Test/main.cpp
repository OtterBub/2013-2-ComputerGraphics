#include <gl\glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdio.h>

/*
 * Point size의 Default 값은 1.0 이다.
 */
GLfloat size = 1.0;
GLint flag = 0;
GLint St_x=0, St_y=0, Ed_x=0, Ed_y=0;

/*
 * 파라메터로 들어온 x좌표와 y좌표를 이용하여 점을 찍는다.
 */
void RenderPoint(GLint x, GLint y)
{
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(size);

	
	glBegin(GL_POINTS);
	glVertex3f(x/300.0, (300-y)/300.0, 0.0);
	glEnd();
	glFlush();
}

/*
 * 전역 좌표인 St_x, St_y, Ed_x, Ed_y를 이용하여 선분을 그리는 함수이다.
 */
void RenderLine()
{
	int DeltaX, DeltaY;
    int X, Y;
    int D;
	
    DeltaX = Ed_x - St_x;
	DeltaY = Ed_y - St_y;

	/*
	 * RenderPoint를 이용하여 Point를 찍어줄 때 
	 * X좌표와 Y좌표의 증가량의 변수이다.
	 * 기본 Default값은 양의 1이다.
	 */
	X = 1;
	Y = 1;
	
	/*
	 * X의 증가량이 음의 수 이므로 X의 증가량의 절대값을 구하고
	 * Line을 그리면 그릴 수록 RenderPoint함수를 통해 표현할 
	 * 점의 좌표가 -값을 갖고 후퇴하며 표현해야 하므로 X값을 -1값으로 한다.
	 */
	if( DeltaX < 0 )
	{
		DeltaX = -DeltaX;
		X = -1;
	}

	/*
	 * Y의 증가량이 음의 수 이므로 Y의 증가량의 절대값을 구하고
	 * Line을 그리면 그릴 수록 RenderPoint함수를 통해 표현할 
	 * 점의 좌표가 -값을 갖고 후퇴하며 표현해야 하므로 Y값을 -1값으로 한다.
	 */
	if( DeltaY < 0 )
	{
		DeltaY = -DeltaY;
		Y = -1;
	}
	
	/*
	 * 첫 시작점을 그린다.
	 */
	RenderPoint( St_x, St_y );
	
	/*
	 * X의 증가량이 Y의 증가량보다 큰 경우이다.
	 * 기울기는 "0< 기울기 < 1"의 크기를 갖고 있다.
	 */
	if( DeltaX > DeltaY )
	{
		/*
		 * 결정변수의 값은 2DeltaY - DeltaX의 값을 갖는다. (초기화) 
		 */
		D = ( 2*DeltaY) - DeltaX;
		
		/*
		 * x좌표를 검사하여 마지막 점을 표시할 때까지 무한 반복한다.
		 */
		while( St_x != Ed_x )
		{
			/*
			 * 결정변수의 값을 검사한다.
			 * 
			 * 양의 값인 경우 X좌표와 Y좌표를 증가시키면서 
			 * 다음 래스터를 결정하게 된다.
			 * 결정변수의 연산결과는 D += 2DeltaY - 2DeltaX이다.
			 * 
			 * 음인 경우 X좌표만을 증가시키며
			 * 다음 래스터를 결정한다.
			 * 결정변수의 연산결과는 D += 2DeltaY이다. 
			 */
			if( D >= 0 )
			{
				St_y += Y;
				D -= 2*DeltaX;
			}
			St_x += X;
			D += 2*DeltaY;
			
			/*
			 * 다음 래스터로 결정된 좌표에 점 찍기
			 */
			RenderPoint( St_x, St_y );
		}
	}

	/*
	 * Y의 증가량이 X의 증가량보다 큰 경우이다.
	 * 기울기는 " 1<기울기 "의 크기를 갖고 있다.
	 * 위의 연산과 정 반대의 연산을 갖는다.
	 */
	else
	{
		/*
		 * 결정변수의 값은 2DeltaY - DeltaX의 값을 갖는다. (초기화) 
		 */
		D = ( 2*DeltaX ) - DeltaY;
		
		/*
		 * y좌표를 검사하여 마지막 점을 표시할 때까지 무한 반복한다.
		 */
		while( St_y != Ed_y )
		{
			/*
			 * 결정변수의 값을 검사한다.
			 * 
			 * 양의 값인 경우 X좌표와 Y좌표를 증가시키면서 
			 * 다음 래스터를 결정하게 된다.
			 * 결정변수의 연산결과는 D += 2DeltaX - 2DeltaY이다.
			 * 
			 * 음인 경우 Y좌표만을 증가시키며
			 * 다음 래스터를 결정한다.
			 * 결정변수의 연산결과는 D += 2DeltaX이다. 
			 */
			if( D >= 0 )
			{
				St_x += X;
				D -= 2*DeltaY;
			}
			
			St_y += Y;
			D += 2*DeltaX;
			
			/*
			 * 다음 래스터로 결정된 좌표에 점 찍기
			 */
			RenderPoint( St_x, St_y );
		}
	}
	return;
}

/*
 * 마우스 이벤트 발생시 실행되는 함수이다.
 */
void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
	/*
	 * 마우스 이벤트 발생의 상태가 클릭상태이고,(state)
	 * 버튼의 방향이 왼쪽인 경우 (button)
	 * 점을 하나 찍어준다.
	 */
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		/* 
		 * 선택한 좌표를 확인하도록 점을 찍어준다.
		 */
		RenderPoint(x,y);

		/*
		 * Flag는 이번 입력들어온 마우스의 좌표가 첫 번째 입력인지
		 * 두번째 입력인지를 구분한다.
		 * 첫번째인 경우 두번째 입력을 기다린다.
		 * 두번째인 경우 RenderLine함수를 호출하여 선분을 그린다. 
		 */
		if(flag ==1)
		{
			Ed_x = x;
			Ed_y = y;

			/* 
			 * 선분을 그리는 함수 호출 
			 */
			RenderLine();
			flag = 0;
		}
		else
		{
			St_x = x;
			St_y = y;

			/* 
			 * flag 값을 설정하여 첫번째 입력이 들어왔음을 표시한다.
			 */
			flag = 1;
		}
		/* 색은 흰색이다.*/
	}
}

/* 처음 윈도우를 만들 때 그리는 함수 */
void MyDisplay()
{
	/* Window의 색을 기본 색으로 채운다. 검은색이다. */
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

/* 윈도우를 생성하고 콜백함수를 선언하는 메인함수이다. */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300,300);
	glutInitWindowPosition(100,100);
	glutCreateWindow("CG HW#7 - Bresenham Algorithm");
	
	/* 검은색을 기본 색으로 한다.*/
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* 윈도우의 좌표계를 왼쪽 하단부를 0.0 에서 오른쪽 상단부를 1.0으로 지정한다.*/
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	/* 콜백함수를 선언한다.*/
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouse);

	/* 루프에 들어간다. */
	glutMainLoop();
	return 0;
}
#include <gl\glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdio.h>

/*
 * Point size�� Default ���� 1.0 �̴�.
 */
GLfloat size = 1.0;
GLint flag = 0;
GLint St_x=0, St_y=0, Ed_x=0, Ed_y=0;

/*
 * �Ķ���ͷ� ���� x��ǥ�� y��ǥ�� �̿��Ͽ� ���� ��´�.
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
 * ���� ��ǥ�� St_x, St_y, Ed_x, Ed_y�� �̿��Ͽ� ������ �׸��� �Լ��̴�.
 */
void RenderLine()
{
	int DeltaX, DeltaY;
    int X, Y;
    int D;
	
    DeltaX = Ed_x - St_x;
	DeltaY = Ed_y - St_y;

	/*
	 * RenderPoint�� �̿��Ͽ� Point�� ����� �� 
	 * X��ǥ�� Y��ǥ�� �������� �����̴�.
	 * �⺻ Default���� ���� 1�̴�.
	 */
	X = 1;
	Y = 1;
	
	/*
	 * X�� �������� ���� �� �̹Ƿ� X�� �������� ���밪�� ���ϰ�
	 * Line�� �׸��� �׸� ���� RenderPoint�Լ��� ���� ǥ���� 
	 * ���� ��ǥ�� -���� ���� �����ϸ� ǥ���ؾ� �ϹǷ� X���� -1������ �Ѵ�.
	 */
	if( DeltaX < 0 )
	{
		DeltaX = -DeltaX;
		X = -1;
	}

	/*
	 * Y�� �������� ���� �� �̹Ƿ� Y�� �������� ���밪�� ���ϰ�
	 * Line�� �׸��� �׸� ���� RenderPoint�Լ��� ���� ǥ���� 
	 * ���� ��ǥ�� -���� ���� �����ϸ� ǥ���ؾ� �ϹǷ� Y���� -1������ �Ѵ�.
	 */
	if( DeltaY < 0 )
	{
		DeltaY = -DeltaY;
		Y = -1;
	}
	
	/*
	 * ù �������� �׸���.
	 */
	RenderPoint( St_x, St_y );
	
	/*
	 * X�� �������� Y�� ���������� ū ����̴�.
	 * ����� "0< ���� < 1"�� ũ�⸦ ���� �ִ�.
	 */
	if( DeltaX > DeltaY )
	{
		/*
		 * ���������� ���� 2DeltaY - DeltaX�� ���� ���´�. (�ʱ�ȭ) 
		 */
		D = ( 2*DeltaY) - DeltaX;
		
		/*
		 * x��ǥ�� �˻��Ͽ� ������ ���� ǥ���� ������ ���� �ݺ��Ѵ�.
		 */
		while( St_x != Ed_x )
		{
			/*
			 * ���������� ���� �˻��Ѵ�.
			 * 
			 * ���� ���� ��� X��ǥ�� Y��ǥ�� ������Ű�鼭 
			 * ���� �����͸� �����ϰ� �ȴ�.
			 * ���������� �������� D += 2DeltaY - 2DeltaX�̴�.
			 * 
			 * ���� ��� X��ǥ���� ������Ű��
			 * ���� �����͸� �����Ѵ�.
			 * ���������� �������� D += 2DeltaY�̴�. 
			 */
			if( D >= 0 )
			{
				St_y += Y;
				D -= 2*DeltaX;
			}
			St_x += X;
			D += 2*DeltaY;
			
			/*
			 * ���� �����ͷ� ������ ��ǥ�� �� ���
			 */
			RenderPoint( St_x, St_y );
		}
	}

	/*
	 * Y�� �������� X�� ���������� ū ����̴�.
	 * ����� " 1<���� "�� ũ�⸦ ���� �ִ�.
	 * ���� ����� �� �ݴ��� ������ ���´�.
	 */
	else
	{
		/*
		 * ���������� ���� 2DeltaY - DeltaX�� ���� ���´�. (�ʱ�ȭ) 
		 */
		D = ( 2*DeltaX ) - DeltaY;
		
		/*
		 * y��ǥ�� �˻��Ͽ� ������ ���� ǥ���� ������ ���� �ݺ��Ѵ�.
		 */
		while( St_y != Ed_y )
		{
			/*
			 * ���������� ���� �˻��Ѵ�.
			 * 
			 * ���� ���� ��� X��ǥ�� Y��ǥ�� ������Ű�鼭 
			 * ���� �����͸� �����ϰ� �ȴ�.
			 * ���������� �������� D += 2DeltaX - 2DeltaY�̴�.
			 * 
			 * ���� ��� Y��ǥ���� ������Ű��
			 * ���� �����͸� �����Ѵ�.
			 * ���������� �������� D += 2DeltaX�̴�. 
			 */
			if( D >= 0 )
			{
				St_x += X;
				D -= 2*DeltaY;
			}
			
			St_y += Y;
			D += 2*DeltaX;
			
			/*
			 * ���� �����ͷ� ������ ��ǥ�� �� ���
			 */
			RenderPoint( St_x, St_y );
		}
	}
	return;
}

/*
 * ���콺 �̺�Ʈ �߻��� ����Ǵ� �Լ��̴�.
 */
void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
	/*
	 * ���콺 �̺�Ʈ �߻��� ���°� Ŭ�������̰�,(state)
	 * ��ư�� ������ ������ ��� (button)
	 * ���� �ϳ� ����ش�.
	 */
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		/* 
		 * ������ ��ǥ�� Ȯ���ϵ��� ���� ����ش�.
		 */
		RenderPoint(x,y);

		/*
		 * Flag�� �̹� �Էµ��� ���콺�� ��ǥ�� ù ��° �Է�����
		 * �ι�° �Է������� �����Ѵ�.
		 * ù��°�� ��� �ι�° �Է��� ��ٸ���.
		 * �ι�°�� ��� RenderLine�Լ��� ȣ���Ͽ� ������ �׸���. 
		 */
		if(flag ==1)
		{
			Ed_x = x;
			Ed_y = y;

			/* 
			 * ������ �׸��� �Լ� ȣ�� 
			 */
			RenderLine();
			flag = 0;
		}
		else
		{
			St_x = x;
			St_y = y;

			/* 
			 * flag ���� �����Ͽ� ù��° �Է��� �������� ǥ���Ѵ�.
			 */
			flag = 1;
		}
		/* ���� ����̴�.*/
	}
}

/* ó�� �����츦 ���� �� �׸��� �Լ� */
void MyDisplay()
{
	/* Window�� ���� �⺻ ������ ä���. �������̴�. */
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

/* �����츦 �����ϰ� �ݹ��Լ��� �����ϴ� �����Լ��̴�. */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300,300);
	glutInitWindowPosition(100,100);
	glutCreateWindow("CG HW#7 - Bresenham Algorithm");
	
	/* �������� �⺻ ������ �Ѵ�.*/
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* �������� ��ǥ�踦 ���� �ϴܺθ� 0.0 ���� ������ ��ܺθ� 1.0���� �����Ѵ�.*/
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	/* �ݹ��Լ��� �����Ѵ�.*/
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouse);

	/* ������ ����. */
	glutMainLoop();
	return 0;
}
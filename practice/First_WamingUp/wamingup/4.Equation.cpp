#include <stdio.h>
#include <math.h>

typedef struct _POINT_3D{
	double x;
	double y;
	double z;
}POINT_3D;

typedef struct _VECTOR_3D{
	double x;
	double y;
	double z;
}VECTOR_3D;

VECTOR_3D Outer_product(VECTOR_3D a, VECTOR_3D b)
{
	VECTOR_3D result;
	result.x = (a.y * b.z) - (a.z * b.y); 
	result.y = -((a.x * b.z) - (a.z * b.x));
	result.z = (a.x * b.y) - (a.y * b.x);

	return result;
}

VECTOR_3D VectorCal(POINT_3D a, POINT_3D b)
{
	VECTOR_3D result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;

	return result;
}

double GetEdgeLength(POINT_3D a, POINT_3D b)
{
	return sqrt(pow((b.x - a.x), 2.0) + pow((b.y - a.y), 2.0) + pow((b.z - a.z), 2.0));
}

void Equation_Plane_Cal(POINT_3D P, POINT_3D Q, POINT_3D R)
{
	VECTOR_3D PQ;
	VECTOR_3D PR;
	VECTOR_3D Nomal_Vector;
	
	double d;

	PQ = VectorCal(Q, P);
	PR = VectorCal(R, P);
	
	Nomal_Vector = Outer_product(PQ, PR);

	d = -(Nomal_Vector.x * P.x) - (Nomal_Vector.y * P.y) - (Nomal_Vector.z * P.z);

	printf("Equation of a Plane is %.2fx + %.2fy + %.2fz + %.2f = 0\n", Nomal_Vector.x, Nomal_Vector.y, Nomal_Vector.z, d);	
}

void Triangular_Pyramid(POINT_3D a, POINT_3D b, POINT_3D c, POINT_3D d)
{
	double e1, e2, e3, e4, e5, e6;

	printf("꼭지점 : (%.2f, %.2f, %.2f), (%.2f, %.2f, %.2f), \n(%.2f, %.2f, %.2f), (%.2f, %.2f, %.2f)\n",
		a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z, d.x, d.y, d.z);

	e1 = GetEdgeLength(a, b);
	e2 = GetEdgeLength(a, c);

	e3 = GetEdgeLength(b, c);
	e4 = GetEdgeLength(a, d);

	e5 = GetEdgeLength(b, d);
	e6 = GetEdgeLength(c, d);

	printf(" e1 : %.2f \t e2 : %.2f\n", e1, e2);
	printf(" e3 : %.2f \t e4 : %.2f\n", e3, e4);
	printf(" e5 : %.2f \t e6 : %.2f\n", e5, e6);

	printf("s1 ");Equation_Plane_Cal(a, b, c);
	printf("s2 ");Equation_Plane_Cal(a, b, d);
	printf("s3 ");Equation_Plane_Cal(a, c, d);
	printf("s4 ");Equation_Plane_Cal(b, c, d);
}

void Square_Pillar(POINT_3D a, POINT_3D b, POINT_3D c, POINT_3D d, POINT_3D e, POINT_3D f, POINT_3D g, POINT_3D h)
{
	double e1, e2, e3, e4, e5, e6, e7, e8;

	printf("꼭지점 : (%.2f, %.2f, %.2f), (%.2f, %.2f, %.2f), \n(%.2f, %.2f, %.2f), (%.2f, %.2f, %.2f)\n",
		a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z, d.x, d.y, d.z);
	printf("         (%.2f, %.2f, %.2f), (%.2f, %.2f, %.2f), \n(%.2f, %.2f, %.2f), (%.2f, %.2f, %.2f)\n",
		e.x, e.y, e.z, f.x, f.y, f.z, g.x, g.y, g.z, h.x, h.y, h.z);

	e1 = GetEdgeLength(a, b);
	e2 = GetEdgeLength(b, d);

	e3 = GetEdgeLength(d, c);
	e4 = GetEdgeLength(c, a);

	e5 = GetEdgeLength(e, f);
	e6 = GetEdgeLength(f, h);

	e7 = GetEdgeLength(h, g);
	e8 = GetEdgeLength(g, e);

	printf(" e1 : %.2f \t e2 : %.2f\n", e1, e2);
	printf(" e3 : %.2f \t e4 : %.2f\n", e3, e4);
	printf(" e5 : %.2f \t e6 : %.2f\n", e5, e6);
	printf(" e7 : %.2f \t e8 : %.2f\n", e7, e8);

	printf("s1 ");Equation_Plane_Cal(a, b, c);
	printf("s2 ");Equation_Plane_Cal(a, b, d);
	printf("s3 ");Equation_Plane_Cal(a, c, d);
	printf("s4 ");Equation_Plane_Cal(e, g, h);
	printf("s5 ");Equation_Plane_Cal(c, g, d);
	printf("s6 ");Equation_Plane_Cal(h, d, f);
}

int main()
{
	POINT_3D P = {1, 3, 2};
	POINT_3D Q = {3, -1, 6};
	POINT_3D R = {5, 2, 0};

	POINT_3D a = {0, 0, 0};
	POINT_3D b = {10, 0, 0};
	POINT_3D c = {0, 0, 10};
	POINT_3D d = {10, 0, 10};
	POINT_3D e = {0, 10, 0};
	POINT_3D f = {10, 10, 0};
	POINT_3D g = {0, 10, 10};
	POINT_3D h = {10, 10, 10};

	Equation_Plane_Cal(P, Q, R);
	printf("\n\n");

	Triangular_Pyramid(a, b, c, e);
	printf("\n\n");
	Square_Pillar(a, b, c, d, e, f, g, h);

	return 0;
}
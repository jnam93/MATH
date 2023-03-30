//
//  Simple 3d vector linear transform
//  
//
//

#include<math.h>
#include<cmath>
#include<stdio.h>
#include "tigr.h"
struct v3
{
	v3() { }
	v3(float x, float y, float z) { this->x = x; this->y = y; this->z = z;  }
	float x;
	float y;
	float z;
	
};

struct t4
{	
	t4() { }
	t4(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
	float x;
	float y;
	float z;
	float t[4][4] = { 1,0,0,x,0,1,0,y,0,0,1,z,0,0,0,1 };
};

struct Quaternion {
	Quaternion() {}
	Quaternion(float r, float x, float y, float z) { this->r = r; this->x = x; this->y = y; this->z = z; }

	float r;
	float i;
	float j;
	float k;

};

Quaternion Euler2Quaternion() {

}
v3 R(Quaternion q, v3 v) {
	
	float v_r[3] = { 0,0,0 };
	v3 vr = v3(0, 0, 0);
	float vector[3] = { v.x,v.y,v.z };
	
	float R[3][3] = {
		1 - 2 * (q.j * q.j + q.k * q.k), 2 * (q.i * q.j - q.k * q.r), 2 * (q.i * q.k + q.j * q.r),
		2 * (q.i * q.j + q.k * q.r), 1 - 2 * (q.i * q.i + q.k * q.k), 2 * (q.j * q.k - q.i * q.r),
		2 * (q.i * q.k - q.j * q.r), 2 * (q.j * q.k + q.i * q.r), 1 - 2 * (q.i * q.i + q.j * q.j) };

	for (int i = 0; i < 3; i++) {		
		for (int j = 0; j < 3; j++) {
			v_r[j] += R[i][j] * vector[j];
		}
	}
	vr.x = v_r[0];
	vr.y = v_r[1];
	vr.z = v_r[2];
	return vr;

}

v3 operator+(v3 a, v3 b) { return v3(a.x + b.x, a.y + b.y, a.z + b.z); }
v3 operator+=(v3& a, v3 b) { a = v3(a.x + b.x, a.y + b.y, a.z + b.z); return a; }
v3 operator-(v3 a, v3 b) { return v3(a.x - b.x, a.y - b.y, a.z - b.z); }
v3 operator-=(v3& a, v3 b) { a = v3(a.x - b.x, a.y - b.y, a.z - b.z); return a; }
v3 operator*(v3 a, float b) { return v3(a.x * b, a.y * b,a.z *b); }
v3 operator*=(v3& a, float b) { a = v3(a.x * b, a.y * b, a.z * b); return a; }
v3 operator/(v3 a, float b) { return v3(a.x / b, a.y / b, a.z / b); }
v3 operator/=(v3& a, float b) { a = v3(a.x / b, a.y / b, a.z / b); return a; }
float dot(v3 a, v3 b) { return a.x * b.x + a.y * b.y + a.z * b.z ; }
v3 cross(v3 a, v3 b) {
	v3 c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = -(a.x * b.z - a.z * b.x);
	c.z = a.x * b.y - a.y * b.x;
	return c;
}
v3 up = v3(0, 1, 0);
int leftright(v3 self, v3 target, v3 forward ) {
	v3 N = v3();
	N = cross(forward, target - self);
	if (dot(N, up) > 0)
		return 1;
	else if ((dot(N, up) < 0))
		return -1;
	else
		return 0;
		
}

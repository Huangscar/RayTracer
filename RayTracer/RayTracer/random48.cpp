#include "random48.h"
//double drand48(void)
//{
//	seed = (0x5DEECE66DLL * seed + 0xB16) & 0xFFFFFFFFFFFFLL;
//	unsigned int x = seed >> 16;
//	return  ((double)x / (double)0x5DEECE66DLL);
//
//}

#define rndm 0x100000000LL
#define rndc 0xB16
#define rnda 0x5DEECE66DLL
static unsigned long long seed = 1;
inline double drand48(void)
{
	seed = (rnda * seed + rndc) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return  ((double)x / (double)rndm);
}

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0f*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (p.x*p.x + p.y*p.y + p.z*p.z >= 1.0);
	return p;
}
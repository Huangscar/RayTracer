#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"



class sphere: public hitable
{
public:
	vec3 center;
	float radius;
	material *mat_ptr;
	sphere(){}
	//sphere(vec3 cen, float r) :center(cen), radius(r) {};
	sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

private:

};



#endif // !SPHEREH


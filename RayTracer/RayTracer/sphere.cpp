#include "sphere.h"

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0f*dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4*a*c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(b*b - 4*a * c)) / (2*a);
		if (temp<t_max&&temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(b*b - 4*a * c)) / (2*a);
		if (temp<t_max&&temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		
	}
	return false;
}
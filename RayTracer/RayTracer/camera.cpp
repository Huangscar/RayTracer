#define _USE_MATH_DEFINES
#include"camera.h"
#include <cmath>
#include "random48.h"

vec3 cross(const vec3 &v1, const vec3 &v2) {
	return vec3((v1.y*v2.z - v1.z*v2.y), (-(v1.x*v2.z - v1.z*v2.x)), (v1.x*v2.y - v1.y*v2.x));
}

vec3 random_in_unit_disk() {
	vec3 p;
	do {
		p = 2.0f*vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}



camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist) { // vfov is top to bottom in degrees
	lens_radius = aperture / 2;
	float theta = vfov * M_PI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	origin = lookfrom;
	w = (lookfrom - lookat)/ (float)(lookfrom - lookat).length();
	u = cross(vup, w)/(float)cross(vup, w).length();
	v = cross(w, u);
	lower_left_corner = origin - half_width * focus_dist*u - half_height * focus_dist*v - focus_dist * w;
	horizontal = 2 * half_width*focus_dist*u;
	vertical = 2 * half_height*focus_dist*v;
}

ray camera::get_ray(float s, float t) {
	vec3 rd = lens_radius * random_in_unit_disk();
	vec3 offset = u * rd.x + v * rd.y;
	return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
}

/*camera::camera() {
	lower_left_corner = vec3(-2.0f, -1.0f, -1.0f);
	horizontal = vec3(4.0f, 0.0f, 0.0f);
	vertical = vec3(0.0f, 3.0f, 0.0f);
	origin = vec3(0.0f, 0.0f, 0.0f);
}*/
/*camera::camera(float vfov, float aspect) {
	float theta = vfov * M_PI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	lower_left_corner = vec3(-half_width, -half_height, -1.0);
	horizontal = vec3(2 * half_width, 0.0, 0.0);
	vertical = vec3(0.0, 2 * half_height, 0.0);
	origin = vec3(0, 0, 0);
}*/

/*ray camera::get_ray(float s, float t) {
	return ray(origin , lower_left_corner + s * horizontal + t * vertical - origin);
}*/
#ifndef CAMERAH
#define CAMERAH
#include "ray.h"
#include <glm/glm.hpp>
using namespace glm;
class camera
{
public:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	float lens_radius;
	vec3 u, v, w;
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist);
	//camera();
	//camera(float vfov, float aspect);
	ray get_ray(float u, float v);

private:

};



#endif // !CAMERAH

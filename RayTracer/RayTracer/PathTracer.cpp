#include "PathTracer.h"
#include "ray.h"
#include <glm/glm.hpp>
#include <time.h>
#include <iostream>
#include <float.h>

using namespace glm;

hitable *list[2];
//static unsigned long long seed = 1;


vec3 getColor(const ray& r, hitable *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr != NULL &&rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * getColor(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	else {
		vec3 unit_direction = r.direction() / (float)r.direction().length();
		float t = 0.5*(unit_direction.y + 1.0);
		return (1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = drand48();
			vec3 center(a + 0.9*drand48(), 0.2, b + 0.9*drand48());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
				}
				else if (choose_mat < 0.95) { // metal
					list[i++] = new sphere(center, 0.2,
						new metal(vec3(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())), 0.5*drand48()));
				}
				else {  // glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hitable_list(list, i);
}

PathTracer::PathTracer()
	: m_channel(4), m_width(800), m_height(600), m_image(nullptr) {}


PathTracer::~PathTracer()
{
	if (m_image != nullptr)
		m_image;
	m_image = nullptr;
}

void PathTracer::initialize(int width, int height)
{
	m_width = width;
	m_height = height;
	if (m_image != nullptr)
		delete m_image;

	// allocate pixel buffer, RGBA format.
	m_image = new unsigned char[width * height * m_channel];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.3, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
}

unsigned char * PathTracer::render(double & timeConsuming)
{
	if (m_image == nullptr)
	{
		std::cout << "Must call initialize() before rendering.\n";
		return nullptr;
	}

	// record start time.
	double startFrame = clock();

	//hitable *world = random_scene();
	hitable *world = random_scene();
	vec3 lookfrom(5,4,1);
	vec3 lookat(0, 0, -1);
	float dist_to_focus = 10;
	float aperture = 0.0;

	camera cam(lookfrom, lookat, vec3(0, 1, 0), 120, float(m_width) / float(m_height), aperture, dist_to_focus);

	//camera cam;

	// render the image pixel by pixel.
	for (int row = m_height - 1; row >= 0; --row)
	{
		for (int col = 0; col < m_width; ++col)
		{
			glm::vec4 color;
			vec3 color3(0, 0, 0);
			for (int s = 0; s < 100; s++) {
				float u = static_cast<float>(col+drand48()) / static_cast<float>(m_width);
				float v = static_cast<float>(row+drand48()) / static_cast<float>(m_height);
				//color.z = 0.2;
				//color.w = 1.0f;
				
				ray r = cam.get_ray(u,v);
				//ray r(origin, lower_left_corner + color.x*horizontal + color.y*vertical);
				color3 += getColor(r, world, 0);
			}
			color3 /= float(100);
			color3 = vec3(sqrt(color3.x), sqrt(color3.y), sqrt(color3.z));
			color = vec4(color3.x, color3.y, color3.z, 1.0f);
			drawPixel(col, row, color);
		}
		//std::cout << row << std::endl;
	}

	// record end time.
	double endFrame = clock();

	// calculate time consuming.
	timeConsuming = static_cast<double>(endFrame - startFrame) / CLOCKS_PER_SEC;

	return m_image;
}

void PathTracer::drawPixel(unsigned int x, unsigned int y, const glm::vec4 & color)
{	
	// Check out 
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return;
	

	// x is column's index, y is row's index.
	unsigned int index = (y * m_width + x) * m_channel;
	// store the pixel.
	// red component.
	m_image[index + 0] = static_cast<unsigned char>(255 * color.x);
	// green component.
	m_image[index + 1] = static_cast<unsigned char>(255 * color.y);
	// blue component.
	m_image[index + 2] = static_cast<unsigned char>(255 * color.z);
	// alpha component.
	m_image[index + 3] = static_cast<unsigned char>(255 * color.w);
}

#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "PathTracer.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;



int main(int argc, char *argv[])
{
	// initialization.
	PathTracer tracer;
	tracer.initialize(800, 600);
	
	// rendering.
	double timeConsuming = 0.0f;
	unsigned char *pixels;
	pixels = tracer.render(timeConsuming);

	// save to .png file using stb_image.
	stbi_flip_vertically_on_write(1);
	stbi_write_png("./result.png",
		tracer.getWidth(),
		tracer.getHeight(),
		4,
		static_cast<void*>(tracer.getImage()),
		tracer.getWidth() * 4);

	cout << "Rendering Finished.\n";
	cout << "Time consuming: " << timeConsuming << " secs.\n";

	return 0;
}
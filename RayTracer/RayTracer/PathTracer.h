#pragma once

#include <glm/glm.hpp>
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

class PathTracer
{
private:
	// RGBA format.
	int m_channel;
	// image's size.
	int m_width, m_height;
	// image's pixel buffer.
	unsigned char *m_image;

public:
	// Ctor/Dtor.
	PathTracer();
	~PathTracer();

	// Getter.
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int getChanne() const { return m_channel; }
	unsigned char *getImage() const { return m_image; }

	// Must call it for the first of all.
	void initialize(int width, int height);

	// Render a frame.
	unsigned char *render(double &timeConsuming);

private:
	// Draw one pixel in (y,x).
	void drawPixel(unsigned int x, unsigned int y, const glm::vec4 &color);
};


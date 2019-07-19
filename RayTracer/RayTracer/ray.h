#ifndef RAYH
#define RAYH
#include <glm/glm.hpp>
using namespace glm;
class ray {
public:
	glm::vec3 A;
	glm::vec3 B;
	ray(){};
	ray(const glm::vec3& a, const glm::vec3& b);
	glm::vec3 origin() const;
	glm::vec3 direction() const;
	glm::vec3 point_at_parameter(float t) const;
};

#endif // !RAYH


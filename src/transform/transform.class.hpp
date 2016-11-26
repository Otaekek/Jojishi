#ifndef TRANSFORM_CLASS_HPP
#define TRANSFORM_CLASS_HPP

#include <glm.hpp>
#include <vec3.hpp> // glm::vec3
#include <vec4.hpp> // glm::vec4
#include <mat4x4.hpp> // glm::mat4
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <dynamicMemoryManager.class.hpp>
#include <gtc/matrix_transform.hpp>

#define GLM_FORCE_AVX2

typedef struct 		s_transform {

	glm::vec3		position;
	glm::vec3 		scale;
	glm::quat 		rotation;

}					t_transform;

class transformBuiltin {

public:

	static inline void init();
	static inline void shutdown();

	static inline uint32_t create();
	static inline void destroy(uint32_t handler);

	static inline glm::vec3 get_direction(uint32_t handler);
	static inline void rotate(uint32_t handler, glm::vec3 axis, float angle);
	static inline void rotate_model(uint32_t handler, glm::vec3 axis, float angle);
	static inline void translate(uint32_t handler, float &x, float &y, float & z);
	static inline void scale(uint32_t handler, float &x, float &y, float & z);

	static inline glm::mat4 to_mat(uint32_t handler);
	static inline t_transform get_transform(uint32_t h);


private:
	static uint32_t cluster_id;
};

#endif
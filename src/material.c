#include "minirt.h"

/**
 * @brief Creates and returns a default material.
 *
 * This function initializes a material structure with default values.
 * The default material can be used as a base for further customization.
 *
 * @return A t_material structure initialized with default values.
 */
t_material	material(void)
{
	return ((t_material){
		.color = color(1, 1, 1),
		.ambient = 0.1,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200
	});
}

#ifndef __GLLIB_H__
#define __GLLIB_H__

// opengl loader
#include <GL3/gl3.h>
#include <GL3/gl3w.h>

// window
#include <GLFW/glfw3.h>

// math
#include <glm/glm.hpp>

#ifdef _DEBUG
// console
#include "Tools/DebugConsole.h"
#endif /* _DEBUG */

#define BUFFER_OFFSET(a) ((void *)(a))

#endif /* __GLLIB_H__ */

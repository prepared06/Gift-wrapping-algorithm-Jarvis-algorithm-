// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include<iostream>
#include <string>
#include <vector>
//для openGL
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include "ReadShaders.h"
#include "FPSCamera.h"
#include "allForJarvis.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;


// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы

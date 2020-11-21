#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "shader.h"
#include "Object.h"
#include "skyBox.hpp"
//#include "./components/geometries/Geometry.h"

//class Sphere : public Geometry {
class Sphere : public Object {
    public:
        GLuint vao = 0, vbo = 0, vbo_n = 0, ebo = 0;
        glm::vec3 _minVal, _maxVal, _center;
        glm::vec3 eye;
    
        int stackCount = 40;
        int sectorCount = 40;
        int numsToDraw;
        Sphere();
        void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
        void spin(float deg);
        void update();
        void setEye(glm::vec3 eyePos) {eye = eyePos;};
        //AABB boundingBox() const override { return AABB{ _minVal, _maxVal }; }
};

#endif

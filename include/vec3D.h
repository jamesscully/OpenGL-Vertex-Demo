#ifndef VEC3D_H
#define VEC3D_H

typedef struct vec3D {

    vec3D() {}
    vec3D(float nX, float nY, float nZ){ x = nX; y = nY; z = nZ; }

    vec3D operator+(vec3D oVec3D) { return vec3D(oVec3D.x + x, oVec3D.y + y, oVec3D.z + z); }
    vec3D operator-(vec3D oVec3D) { return vec3D(x- oVec3D.x, y - oVec3D.y, z - oVec3D.z);  }
    vec3D operator/(float dValue) { return vec3D(x / dValue, y / dValue, z / dValue);       }
    vec3D operator*(float mValue) { return vec3D(x * mValue, y * mValue, z * mValue);       }

    float x, y, z;
};

#endif // VEC3D_H



//
//  math.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-27.
//
//

#ifndef __TrinityCell__math__
#define __TrinityCell__math__

#include "vec.h"
#include "matrix.h"
#include "quaternion.h"

namespace Math {
    
    inline Matrix4f mul(Matrix4f, Matrix4f)
    {
        return Matrix4f();
    }
    inline Vector4f mul(Vector4f, Matrix4f)
    {
        return Vector4f();
    }
    
    Matrix4f createLookAtLH(const Vector3f& eye, const Vector3f& at, const Vector3f& up);
    Matrix4f createPerspectiveFovLH(float fov, float aspect, float near, float far);
}

#endif /* defined(__TrinityCell__math__) */

//
//  matrix.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-27.
//
//

#ifndef __TrinityCell__matrix__
#define __TrinityCell__matrix__

#include "vec.h"

template<typename T>
class Matrix4{
private:
	T data[16];
public:
	Matrix4(){};
    
	Matrix4(T *p){
		for(int i=0; i<16; ++i){
			data[i]= p[i];
		}
	}
    
	T *ptr(){
		return data;
	}
    
	const T *ptr() const{
		return data;
	}
    
	T &operator[](int i){
		return data[i];
	}
    
	const T &operator[](int i) const{
		return data[i];
	}
    
	T &operator()(int i, int j){
		return data[i*4+j];
	}
    
	Vector4_T<T> operator * (const Vector4_T<T> &v) const{
		Vector4_T<T> rv;
		
		return Vector4_T<T>(
                     data[0]*v.x + data[1]*v.y + data[2]*v.z + data[3]*v.w,
                     data[4]*v.x + data[5]*v.y + data[6]*v.z + data[7]*v.w,
                     data[8]*v.x + data[9]*v.y + data[10]*v.z + data[11]*v.w,
                     data[12]*v.x + data[13]*v.y + data[14]*v.z + data[15]*v.w);
	}
    
	Matrix4<T> operator * (const Matrix4<T> &m) const{
		Matrix4<T> rm;
        
		for(int i=0; i<4; ++i){
			for(int j=0; j<4; ++j){
				T acum= 0.0f;
				for(int k=0; k<4; ++k){
					acum+= data[i*4+k]*m[k*4+j];
				}
				rm[i*4+j]= acum;
			}
		}
		return rm;
	}
};

typedef Matrix4<float> Matrix4f;

#endif /* defined(__TrinityCell__matrix__) */

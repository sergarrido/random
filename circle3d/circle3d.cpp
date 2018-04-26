// MIT License
//
// Copyright (c) 2018 Sergio Garrido-Jurado (sgarrido2011@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>


/**
 * @brief Basic 3D vector class
 */
class Vector3D
{
public:
    double x,y,z;

    Vector3D(double _x=0, double _y=0, double _z=0)
        : x(_x), y(_y), z(_z)
    {
    }

    double dot(Vector3D v2)
    {
        return x*v2.x + y*v2.y + z*v2.z;
    }

    Vector3D operator+(const Vector3D& v2)
    {
       return Vector3D(x+v2.x, y+v2.y, z+v2.z);
    }

    Vector3D operator-(const Vector3D& v2)
    {
       return Vector3D(x-v2.x, y-v2.y, z-v2.z);
    }

    Vector3D operator*(const double& sc)
    {
       return Vector3D(sc*x, sc*y, sc*z);
    }

    double norm()
    {
        return sqrt(dot(*this));
    }

};


/**
 * @brief just and auxiliar function to generate a random circle in 3D and provides 3 random points, its center and its radius
 */
void generateRandomCircle(Vector3D &p1, Vector3D &p2, Vector3D &p3, Vector3D &center, double &radius)
{
    // generate random radius
    radius = 100*(double(rand())/double(RAND_MAX));

    // generate random angles and 3 points
    Vector3D aux[3];
    for(int i=0; i<3; i++)
    {
        double angle = M_PI*360.*(double(rand())/double(RAND_MAX))/180.;
        aux[i].x = radius*cos(angle);
        aux[i].y = radius*sin(angle);
        aux[i].z = 0;
    }

    // rotate and translate points randomly

    Vector3D ax; // random rotation axis
    ax.x = 20.*(double(rand())/double(RAND_MAX))-10.;
    ax.y = 20.*(double(rand())/double(RAND_MAX))-10.;
    ax.z = 20.*(double(rand())/double(RAND_MAX))-10.;
    // normalize axis
    double ax_norm = ax.norm();
    ax.x /= ax_norm;
    ax.y /= ax_norm;
    ax.z /= ax_norm;

    double rotAngle = M_PI*360.*(double(rand())/double(RAND_MAX))/180.; // random rotation angle
    double rotCos = cos(rotAngle);
    double rotSin = sin(rotAngle);

    // generate totation matrix
    double R[3][3];
    R[0][0] = rotCos + ax.x*ax.x*(1.-rotCos);
    R[0][1] = ax.x*ax.y*(1.-rotCos) - ax.z*rotSin;
    R[0][2] = ax.x*ax.z*(1.-rotCos) + ax.y*rotSin;
    R[1][0] = ax.x*ax.y*(1.-rotCos) + ax.z*rotSin;
    R[1][1] = rotCos + ax.y*ax.y*(1.-rotCos);
    R[1][2] = ax.y*ax.z*(1.-rotCos) - ax.x*rotSin;
    R[2][0] = ax.x*ax.z*(1.-rotCos) - ax.y*rotSin;
    R[2][1] = ax.y*ax.z*(1.-rotCos) + ax.x*rotSin;
    R[2][2] = rotCos + ax.z*ax.z*(1-rotCos);

    // generate random traslation vector
    Vector3D T;
    T.x = 200.*(double(rand())/double(RAND_MAX))-100.;
    T.y = 200.*(double(rand())/double(RAND_MAX))-100.;
    T.z = 200.*(double(rand())/double(RAND_MAX))-100.;

    // transform the other points
    Vector3D aux_trans[3];
    for(int i=0; i<3; i++)
    {
        aux_trans[i].x = R[0][0]*aux[i].x + R[0][1]*aux[i].y + R[0][2]*aux[i].z + T.x;
        aux_trans[i].y = R[1][0]*aux[i].x + R[1][1]*aux[i].y + R[1][2]*aux[i].z + T.y;
        aux_trans[i].z = R[2][0]*aux[i].x + R[2][1]*aux[i].y + R[2][2]*aux[i].z + T.z;
    }

    // the center of the circle will be equivalent to T
    center = T;

    // the transformed points will be
    p1 = aux_trans[0];
    p2 = aux_trans[1];
    p3 = aux_trans[2];

}


/**
 * @brief estimate the center and the radious of a circle in 3D given 3 points
 * This is the relevant function
 */
void estimate3DCircle(Vector3D p1, Vector3D p2, Vector3D p3, Vector3D &c, double &radius)
{
    Vector3D v1 = p2-p1;
    Vector3D v2 = p3-p1;
    double v1v1, v2v2, v1v2;
    v1v1 = v1.dot(v1);
    v2v2 = v2.dot(v2);
    v1v2 = v1.dot(v2);

    float base = 0.5/(v1v1*v2v2-v1v2*v1v2);
    float k1 = base*v2v2*(v1v1-v1v2);
    float k2 = base*v1v1*(v2v2-v1v2);
    c = p1 + v1*k1 + v2*k2; // center

    radius = (c-p1).norm();
}



int main()
{
    const int NITERATIONS = 10;
    srand(time(NULL));

    for(int i=0; i<NITERATIONS; i++)
    {
        Vector3D p1, p2, p3; // points of the 3d circle
        Vector3D actualCenter, estimatedCenter;
        double actualRadius, estimatedRadius;

        // generate a random circle in 3D space
        generateRandomCircle(p1, p2, p3, actualCenter, actualRadius);

        // estimate the circle center and radious
        estimate3DCircle(p1, p2, p3, estimatedCenter, estimatedRadius);

        // show results
        std::cout << "Iteration: " << i << ":" << std::endl;
        std::cout << "\t p1: " << p1.x << " " << p1.y << " " << p1.z << std::endl;
        std::cout << "\t p2: " << p2.x << " " << p2.y << " " << p2.z << std::endl;
        std::cout << "\t p3: " << p3.x << " " << p3.y << " " << p3.z << std::endl;
        std::cout << "\t Actual    center: " << actualCenter.x << " " << actualCenter.y << " " << actualCenter.z << std::endl;
        std::cout << "\t Estimated center: " << estimatedCenter.x << " " << estimatedCenter.y << " " << estimatedCenter.z << std::endl;
        std::cout << "\t Actual    radius: " << actualRadius << std::endl;
        std::cout << "\t Estimated radius: " << estimatedRadius << std::endl;
        std::cout << "----------------" << std::endl << std::endl;
    }

    return 0;
}

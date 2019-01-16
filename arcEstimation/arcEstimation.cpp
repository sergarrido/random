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


/**
 * @brief Given the length of a circle arc and its corresponding chord, estimate circle radious and angle covered by arc
 */
void getRadiusNAngleFromArcNChord(double arc, double chord, double& estimatedRadius, double& estimatedAngle)
{
    // arc = radius*angle
    // chord = 2*radius*sin(angle/2)

    // radius = arc/angle
    // radius = chord/(2*sin(angle/2))
    // arc/angle = chord/(2*sin(angle/2))
    // sin(angle/2)/angle = chord/(2*arc)
    // sin(angle/2) - angle*chord/(2*arc) = 0
    // K = chord/(2*arc)
    double K = chord / (2.0*arc);

    // f(angle) = sin(angle/2) - K*angle = 0
    // f'(angle) = 0.5*cos(angle/2) - K

    estimatedAngle = M_PI;
    double temporalAngle = estimatedAngle;
    double thresh = 0.000001;
    double diff, f, ff;
    do {
	estimatedAngle = temporalAngle;
        f = sin(estimatedAngle/2) - K*estimatedAngle;
        ff = 0.5*cos(estimatedAngle/2) - K;
        temporalAngle = estimatedAngle - f/ff;
        diff = fabs(temporalAngle-estimatedAngle);
    } while(diff > thresh);

    estimatedRadius = arc/estimatedAngle;
}


int main()
{

    //// Actual values of radius and angle to compare results
    double actualRadius = 0.8;
    double actualAngle = 53;
    double actualAngleRad = actualAngle*M_PI/180.;

    //// Get arc and chord
    // arc = radius*angle
    // chord = 2*radius*sin(angle/2)
    double arc = actualRadius*actualAngleRad;
    double chord = 2*actualRadius*sin(actualAngleRad/2.0);

    //// Estimate radius and angle from arc and chord

    double estimatedRadius, estimatedAngle;
    getRadiusNAngleFromArcNChord(arc, chord, estimatedRadius, estimatedAngle);

    std::cout << "Actual Angle: " << actualAngleRad*180.0/M_PI << std::endl;
    std::cout << "Estimated Angle: " << estimatedAngle*180.0/M_PI << std::endl;
    std::cout << "Actual Radius: " << actualRadius << std::endl;
    std::cout << "Estimated Radius: " << estimatedRadius << std::endl;
  

    //// Get (x,y) coordinates of arc so that origin is on the left end of the arc and curvature pointing upwards

    // First estimate offsets to move origin
    //
    // radius^2 = (chord/2)^2 + offsetY^2
    // double offsetY = sqrt( estimatedRadius*estimatedRadius - chord*chord/4.0 );
    // simpler version:
    // double offsetY = radius * cos(angle/2)
    double offsetY = -estimatedRadius*cos(estimatedAngle/2.0);
    double offsetX = estimatedRadius*sin(estimatedAngle/2.0);

    //// Now estimate coordinates x,y using a rate for the arc angle

    // initialAngle = 90-estimatedAngle/2
    // x = radius * cos (initialAngle + estimatedAngle*i )
    // y = radius * sin (initialAngle + estimatedAngle*i )

    // Simplification
    // x = radius * cos (90-estimatedAngle/2 + estimatedAngle*i )
    // x = radius * cos (90 + estimatedAngle*(i-0.5) )
    // x = radius * ( cos90*cos(estimatedAngle*(i-0.5) ) - sin90*sin(estimatedAngle*(i-0.5) ) )
    // x = radius * (- sin( estimatedAngle*(i-0.5) ) )
    // x = radius * sin( -estimatedAngle*(i-0.5) ) )

    // y = radius * sin (90-estimatedAngle/2 + estimatedAngle*i )
    // y = radius * sin (90 + estimatedAngle*(i-0.5) )
    // y = radius * ( sin90*cos(estimatedAngle*(i-0.5)) + cos90*sin(estimatedAngle*(i-0.5)) )
    // y = radius * cos(estimatedAngle*(i-0.5))

    // rate from 0 to 1
    for(double i=0.0; i<=1.00001; i+=0.01)
    {
        double currAngle = estimatedAngle*(i-0.5);
        double x = estimatedRadius * sin(-currAngle);
        double y = estimatedRadius * cos(currAngle);

        // apply offsets and negate x to go from left to right
        x = -x + offsetX;
        y =  y + offsetY;

        std::cout << x << " " << y << std::endl;

    }

    return 1;    

}

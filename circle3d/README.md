Derivation of circle center and radius in 3D space (for any position and rotation) given 3 points
-----

Sergio Garrido-Jurado (sgarrido2011@gmail.com)

26/04/2018

I recently faced this simple problem and I was surprised I couldnt find this easy derivation on Google, so I just wanted to share it.

The problem is finding the center of a circle in the 3D space (in any position and rotation) given 3 points of its circumference. This derivation shows how it can be solved with a simple linear system of 2 equations (and 2 unknowns).

This document provides the full derivation, so if you are only interested in the final solution, just go ahead to the end of the document. A coded function in C++ is also provided in this repository.


__Input points:__

  p1(p1<sub>x</sub>, p1<sub>y</sub>, p1<sub>z</sub>)<sup>T</sup>
  
  p2(p2<sub>x</sub>, p2<sub>y</sub>, p2<sub>z</sub>)<sup>T</sup>
  
  p3(p3<sub>x</sub>, p3<sub>y</sub>, p3<sub>z</sub>)<sup>T</sup>
  
__Unknowns:__

  radius : circle radius
  
  c(c<sub>x</sub>, c<sub>y</sub>, c<sub>z</sub>)<sup>T</sup> : center of circle
  
  
   
  
-- Set of spheres passing though the 3 points p1, p2, p3 with center c:

  (p1<sub>x</sub>-c<sub>x</sub>)<sup>2</sup> + (p1<sub>y</sub>-c<sub>y</sub>)<sup>2</sup> + (p1<sub>z</sub>-c<sub>z</sub>)<sup>2</sup> - radius<sup>2</sup> = 0
  
  (p2<sub>x</sub>-c<sub>x</sub>)<sup>2</sup> + (p2<sub>y</sub>-c<sub>y</sub>)<sup>2</sup> + (p2<sub>z</sub>-c<sub>z</sub>)<sup>2</sup> - radius<sup>2</sup> = 0
  
  (p3<sub>x</sub>-c<sub>x</sub>)<sup>2</sup> + (p3<sub>y</sub>-c<sub>y</sub>)<sup>2</sup> + (p3<sub>z</sub>-c<sub>z</sub>)<sup>2</sup> - radius<sup>2</sup> = 0

==>

[Eq1]&nbsp;&nbsp;&nbsp;&nbsp;  p1<sub>x</sub><sup>2</sup> + c<sub>x</sub><sup>2</sup> - 2·p1<sub>x</sub>c<sub>x</sub> + p1<sub>y</sub><sup>2</sup> + c<sub>y</sub><sup>2</sup> - 2·p1<sub>y</sub>c<sub>y</sub> + p1<sub>z</sub><sup>2</sup> + c<sub>z</sub><sup>2</sup> - 2·p1<sub>z</sub>c<sub>z</sub> - radius<sup>2</sup> = 0
  
[Eq2]&nbsp;&nbsp;&nbsp;&nbsp;  p2<sub>x</sub><sup>2</sup> + c<sub>x</sub><sup>2</sup> - 2·p2<sub>x</sub>c<sub>x</sub> + p2<sub>y</sub><sup>2</sup> + c<sub>y</sub><sup>2</sup> - 2·p2<sub>y</sub>c<sub>y</sub> + p2<sub>z</sub><sup>2</sup> + c<sub>z</sub><sup>2</sup> - 2·p2<sub>z</sub>c<sub>z</sub> - radius<sup>2</sup> = 0
  
[Eq3]&nbsp;&nbsp;&nbsp;&nbsp;  p3<sub>x</sub><sup>2</sup> + c<sub>x</sub><sup>2</sup> - 2·p3<sub>x</sub>c<sub>x</sub> + p3<sub>y</sub><sup>2</sup> + c<sub>y</sub><sup>2</sup> - 2·p3<sub>y</sub>c<sub>y</sub> + p3<sub>z</sub><sup>2</sup> + c<sub>z</sub><sup>2</sup> - 2·p3<sub>z</sub>c<sub>z</sub> - radius<sup>2</sup> = 0


-- We have 3 equations with 4 unknowns. Lets substract Eq4=Eq1-Eq2 and Eq5=Eq1-Eq3 to remove unknown quadratic terms and radious:


[Eq4]&nbsp;&nbsp;&nbsp;&nbsp;  p1<sub>x</sub><sup>2</sup> - 2·p1<sub>x</sub>c<sub>x</sub> + p1<sub>y</sub><sup>2</sup> - 2·p1<sub>y</sub>c<sub>y</sub> + p1<sub>z</sub><sup>2</sup> - 2·p1<sub>z</sub>c<sub>z</sub> - p2<sub>x</sub><sup>2</sup> + 2·p2<sub>x</sub>c<sub>x</sub> - p2<sub>y</sub><sup>2</sup> + 2·p2<sub>y</sub>c<sub>y</sub> - p2<sub>z</sub><sup>2</sup> + 2·p2<sub>z</sub>c<sub>z</sub> = 0

[Eq5]&nbsp;&nbsp;&nbsp;&nbsp;  p1<sub>x</sub><sup>2</sup> - 2·p1<sub>x</sub>c<sub>x</sub> + p1<sub>y</sub><sup>2</sup> - 2·p1<sub>y</sub>c<sub>y</sub> + p1<sub>z</sub><sup>2</sup> - 2·p1<sub>z</sub>c<sub>z</sub> - p3<sub>x</sub><sup>2</sup> + 2·p3<sub>x</sub>c<sub>x</sub> - p3<sub>y</sub><sup>2</sup> + 2·p3<sub>y</sub>c<sub>y</sub> - p3<sub>z</sub><sup>2</sup> + 2·p3<sub>z</sub>c<sub>z</sub> = 0

==>

[Eq6]&nbsp;&nbsp;&nbsp;&nbsp; c<sub>x</sub>( 2·p2<sub>x</sub> - 2·p1<sub>x</sub> ) + c<sub>y</sub>( 2·p2<sub>y</sub> - 2·p1<sub>y</sub> ) + c<sub>z</sub>( 2·p2<sub>z</sub> - 2·p1<sub>z</sub> ) + ( p1<sub>x</sub><sup>2</sup> + p1<sub>y</sub><sup>2</sup> + p1<sub>z</sub><sup>2</sup> - p2<sub>x</sub><sup>2</sup> - p2<sub>y</sub><sup>2</sup> - p2<sub>z</sub><sup>2</sup> ) = 0

[Eq7]&nbsp;&nbsp;&nbsp;&nbsp; c<sub>x</sub>( 2·p3<sub>x</sub> - 2·p1<sub>x</sub> ) + c<sub>y</sub>( 2·p3<sub>y</sub> - 2·p1<sub>y</sub> ) + c<sub>z</sub>( 2·p3<sub>z</sub> - 2·p1<sub>z</sub> ) + ( p1<sub>x</sub><sup>2</sup> + p1<sub>y</sub><sup>2</sup> + p1<sub>z</sub><sup>2</sup> - p3<sub>x</sub><sup>2</sup> - p3<sub>y</sub><sup>2</sup> - p3<sub>z</sub><sup>2</sup> ) = 0

  
-- Even if we have removed the quadratic terms, we still have 2 equations with 3 unknowns so we cannot solve it. 

-- Now, lets define the vectors:  

  v1 = p2-p1 = (v1<sub>x</sub>, v1<sub>y</sub>, v1<sub>z</sub>)
  
  v2 = p3-p1 = (v2<sub>x</sub>, v2<sub>y</sub>, v2<sub>z</sub>)

-- And the 3x2 matrix:

  V = (v1 | v2)

-- Replacing v1 and v2 in [Eq6] and [Eq7] (and reorganizing a bit):

  c<sub>x</sub>v1<sub>x</sub> + c<sub>y</sub>v1<sub>y</sub> + c<sub>z</sub>v1<sub>z</sub> = 0.5·( p2<sub>x</sub><sup>2</sup> + p2<sub>y</sub><sup>2</sup> + p2<sub>z</sub><sup>2</sup> - p1<sub>x</sub><sup>2</sup> - p1<sub>y</sub><sup>2</sup> - p1<sub>z</sub><sup>2</sup> )

  c<sub>x</sub>v2<sub>x</sub> + c<sub>y</sub>v2<sub>y</sub> + c<sub>z</sub>v2<sub>z</sub> = 0.5·( p3<sub>x</sub><sup>2</sup> + p3<sub>y</sub><sup>2</sup> + p3<sub>z</sub><sup>2</sup> - p1<sub>x</sub><sup>2</sup> - p1<sub>y</sub><sup>2</sup> - p1<sub>z</sub><sup>2</sup> )

  ==>

  [Eq8]&nbsp;&nbsp;&nbsp;&nbsp;  c<sub>x</sub>v1<sub>x</sub> + c<sub>y</sub>v1<sub>y</sub> + c<sub>z</sub>v1<sub>z</sub> = 0.5·( p2·p2 - p1·p1 )

  [Eq9]&nbsp;&nbsp;&nbsp;&nbsp;  c<sub>x</sub>v2<sub>x</sub> + c<sub>y</sub>v2<sub>y</sub> + c<sub>z</sub>v2<sub>z</sub> = 0.5·( p3·p3 - p1·p1 )

(Note that the operator · is employed for the dot product when applied to two vectors / points (e.g. p2·p2).)

-- Now lets express the system in [Eq8] and [Eq9] in matrix notation:

  [Eq10]&nbsp;&nbsp;&nbsp;&nbsp;  V<sup>T</sup> * c = 0.5·d

where d is the vector:

  d = (p2·p2 - p1·p1, p3·p3 - p1·p1)<sup>T</sup>

-- Now, the center of the circle, c, lies in the same plane than v1 and v2, so it can be expressed as a linear combinations of these two vectors and a starting position p1.

  c = p1 + k<sub>1</sub>v1 + k<sub>2</sub>v2

-- In matrix notation:

[Eq11]&nbsp;&nbsp;&nbsp;&nbsp;  c = p1 + V·k

where k = (k<sub>1</sub>, k<sub>2</sub>)<sup>T</sup>

-- So we only need to estimate the two parameters k<sub>1</sub> and k<sub>2</sub> to determine the circle center. Now replace [Eq11] in [Eq10]:

  V<sup>T</sup> c = 0.5·d

==>

  V<sup>T</sup> (p1 + V·k) = 0.5·d

==>

  [Eq12]&nbsp;&nbsp;&nbsp;&nbsp;  (V<sup>T</sup> V)·k = 0.5·d - V<sup>T</sup>·p1

-- Analyzing in detail the right part in [Eq12] for just the first equation (first row) we have:

0.5·(p2·p2 - p1·p1) - v1·p1 =

0.5·(p2·p2 - p1·p1) - (p2-p1)·p1 =

0.5·(p2·p2 - p1·p1) - (p2·p1 - p1·p1) =

0.5·(p2·p2 - p1·p1 - 2·p2·p1 + 2·p1·p1) =

0.5·(p1·p1 + p2·p2 - 2·p2·p1) =

0.5·((p1-p2)·(p1-p2)) =

0.5·(v1·v1) =

-- A similar derivation can be done for the second equation (second row) obtaining

0.5·(v2·v2)

-- So, coming back to matrix notation in [Eq12], we have:

  [Eq13]&nbsp;&nbsp;&nbsp;&nbsp;  (V<sup>T</sup> V) k = 0.5·(v1·v1,  v2·v2)<sup>T</sup>


*************

-- **In summary**, we have to solve the following 2x2 system:

(v1·v1)k<sub>1</sub> + (v1·v2)k<sub>2</sub> = 0.5·(v1·v1)

(v1·v2)k<sub>1</sub> + (v2·v2)k<sub>2</sub> = 0.5·(v2·v2)

where

  v1 = p2-p1 = (v1<sub>x</sub>, v1<sub>y</sub>, v1<sub>z</sub>)
  
  v2 = p3-p1 = (v2<sub>x</sub>, v2<sub>y</sub>, v2<sub>z</sub>)
  
-- The direct expressions for k<sub>1</sub> and k<sub>2</sub> can be derived obtaining:

k<sub>1</sub> = 0.5·(v2·v2)·[(v1·v1) - (v1·v2)]/[(v1·v1)·(v2·v2)-(v1·v2)<sup>2</sup>]

k<sub>2</sub> = 0.5·(v1·v1)·[(v2·v2) - (v1·v2)]/[(v1·v1)·(v2·v2)-(v1·v2)<sup>2</sup>]

-- After determining k<sub>1</sub> and k<sub>2</sub>, the center of the circle is:

c<sub>x</sub> = p1<sub>x</sub> + k<sub>1</sub>v1<sub>x</sub> + k<sub>2</sub>v2<sub>x</sub>

c<sub>y</sub> = p1<sub>y</sub> + k<sub>1</sub>v1<sub>y</sub> + k<sub>2</sub>v2<sub>y</sub>

c<sub>z</sub> = p1<sub>z</sub> + k<sub>1</sub>v1<sub>z</sub> + k<sub>2</sub>v2<sub>z</sub>

-- Obviously, the circle radius can be obtained from the distance between any point p1, p2 or p3, to the center, c.

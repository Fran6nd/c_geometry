# C_GEOMETRY

It's a simple library, work in progress, made to help about 2d geomtries.
<br>
The idea is to help managing lines, segments, triangles, intersections, collisions... The final goal is to help the making of 2D games by helping about collision detection and raycasting.
<br>
There is a demo based on the SDL2 lib. Run `make demo-raycast-using-rays` (intersections between ray and segments) or `make demo-raycast-using-segments` (intersections between segments) or `make demo-raycast-using-triangles` to try it out. It will show you how the lib can find intersections between segments, rays... And how they behaves. 
<br>
For now it shows how we can perform raycasts and other things with the lib.
<br>
<br>
## #TODO
* Improve tests :)
* Use less `#define`
* Add optimization?
* Use triangles to create a polygon object by intersecting triangles.
* Add the capability to move/rotate triangles.

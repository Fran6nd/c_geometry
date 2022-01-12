# C_GEOMETRY

It's a simple library, work in progress, made to help about 2d geomtries.
<br>
The idea is to help managing lines, segments, triangles, intersections, collisions... The final goal is to help the making of 2D games by helping about collision detection, raycasting...
<br>
There is a demo based on the SDL2 lib. Run `make demo` to try it out.
<br>
For now it shows how we can perform raycasts and other things with the lib.
<br>
## #TODO
* Improve tests :)
* Make more demos.
* Get angle between segs/lines if intersections.
* Use triangles to create a polygon object by intersecting triangles.

## Questions
Feel free to answer :)
* Is it better to include the intersection type into the instersection struct or to return it?
* I want to make triangles interoperables with segments... Maybe using vector[] instead of struct for both could do the trick?

# C_GEOMETRY

It's a simple library, work in progress, made to help about 2d geomtries.
<br>
The idea is to help managing lines, segments, triangles, intersections, collisions... The final goal is to help the making of 2D games by helping about collision detection, raycasting...
<br>
There is a demo based on the SDL2 lib. Run `make demo` to try it out. It will show you how the lib can find intersections between segments.
<br>
For now it shows how we can perform raycasts and other things with the lib.
<br>
## #TODO
* Improve tests :)
* Make more demos. We need demos of triangles capabilities and when it will work, we need a demo of ray reflecting on surfaces.
* Get angle between segs/lines if intersections.
* Use triangles to create a polygon object by intersecting triangles.
* Add a `ray` struct defines by a `vector` as origin and a `float` "theta" or another `vector` as a direction.

## Questions
Feel free to answer :)
* Is it better to include the intersection type into the instersection struct or to return it?
* I want to make triangles interoperables with segments... Maybe using vector[] instead of struct for both could do the trick? Cause I would like to have triangles made of 3 segments sharing points to keep the struct small... Looks unpossible? Or should I write kind of `triangle_intersect_segment()` and `triangle_intersect_triangle()`?

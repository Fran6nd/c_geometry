UNAME := $(shell uname)
SDL2_INCLUDE := "-lSDL2"
ifeq ($(UNAME), Darwin)
	SDL2_INCLUDE :=  -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2
endif

test:
	gcc test.c -o tmp-test line.c vector.c segment.c triangle.c
	./tmp-test
	rm tmp-test
demo-raycast-using-rays:
	gcc demo-raycast-using-rays.c -o tmp-demo line.c vector.c segment.c triangle.c ray.c draw.c intersection.c raycast.c  $(SDL2_INCLUDE)
	./tmp-demo
	rm tmp-demo
demo-raycast-using-segments:
	gcc demo-raycast-using-segments.c -o tmp-demo line.c vector.c segment.c ray.c draw.c intersection.c  $(SDL2_INCLUDE)
	./tmp-demo
	rm tmp-demo
demo-raycast-using-triangles:
	gcc demo-raycast-using-triangles.c -o tmp-demo line.c raycast.c vector.c segment.c ray.c draw.c intersection.c triangle.c  $(SDL2_INCLUDE)
	./tmp-demo
	rm tmp-demo
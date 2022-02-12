UNAME := $(shell uname)
SDL2_INCLUDE := "-lSDL2"
ifeq ($(UNAME), Darwin)
	SDL2_INCLUDE :=  -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2
endif

test:
	gcc test.c -o tmp-test line.c vector.c segment.c triangle.c
	./tmp-test
	rm tmp-test
demo-line:
	gcc demo-line.c -o tmp-demo-line line.c vector.c segment.c  $(SDL2_INCLUDE)
	./tmp-demo-line
	rm tmp-demo-line
demo-raycast:
	gcc demo-raycast.c -o tmp-demo-raycast line.c vector.c segment.c ray.c draw.c  $(SDL2_INCLUDE)
	./tmp-demo-raycast
	rm tmp-demo-raycast
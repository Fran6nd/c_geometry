UNAME := $(shell uname)
SDL2_INCLUDE := "-lSDL2"
ifeq ($(UNAME), Darwin)
	SDL2_INCLUDE :=  -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2
endif

test:
	gcc test.c -o tmp-test line.c vector.c segment.c
	./tmp-test
	rm tmp-test
demo:
	gcc demo.c -o tmp-demo-line line.c vector.c segment.c  $(SDL2_INCLUDE)
	./tmp-demo-line
	rm tmp-demo-line
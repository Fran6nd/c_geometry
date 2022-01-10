test:
	gcc test.c -o tmp-test line.c vector.c
	./tmp-test
	rm tmp-test
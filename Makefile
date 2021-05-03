
EXECS:=args sha512

sha512: sha512.c
	cc -o sha512 sha512.c 
	

test: sha512 abc.txt empty.txt G00343624.txt Hamlet.txt
	./tests.sh

clean:
	rm -f $(EXECS)
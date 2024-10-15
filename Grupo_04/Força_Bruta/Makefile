all: item.o lista.o deque.o
	gcc item.o lista.o deque.o caixeiro.c -o caixeiro -std=c99 -Wall -Werror -lm
run:
	./caixeiro
item.o:
	gcc -c item.c -o item.o
lista.o:
	gcc -c lista.c -o lista.o
deque.o:
	gcc -c deque.c -o deque.o
clean:
	rm *.o caixeiro caixa.zip
zip:
	zip -r caixa.zip *
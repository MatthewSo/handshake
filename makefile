compile: server.c server.c
	gcc server.c -o server
	gcc client.c -o client

clean:
	rm -f rsctrl
	rm -f writing
	rm -rf *~ *out

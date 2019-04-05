cc = g++
LD = -lwiringPi

server:server.o car.o carmer.o
		$(cc) -o server server.o car.o carmer.o $(LD)

server.o:server.cpp
	$(cc) -c server.cpp $(LD)

car.o:car.h car.cpp
	$(cc) -c car.cpp $(LD)

carmer.o:carmer.h carmer.cpp
	$(cc) -c carmer.cpp $(LD)

#################################
#客户端控制

clinet: client.o
	$(cc) -o client client.o

client.o: client.cpp
	$(cc) -c client.cpp

#################################

clean:
	rm -f *.o server client

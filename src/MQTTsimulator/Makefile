dataFeeder: main.o Sensor.o
	g++ -o ../ParallaxDataFeeder build/main.o build/Sensor.o

Sensor.o: mkdirBuild
	g++ -o build/Sensor.o -c sensors/Sensor.cpp

main.o: mkdirBuild
	g++ -o build/main.o -c main.cpp

mkdirBuild:
	mkdir -p build
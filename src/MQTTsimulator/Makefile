include_mqtt = -lpaho-mqtt3c -lpaho-mqtt3a -lpaho-mqttpp3
dataFeeder: main.o Sensor.o
	g++ -o ../../ParallaxDataFeeder.exe build/main.o build/Sensor.o ${include_mqtt}

Sensor.o: mkdirBuild
	g++ -o build/Sensor.o -c sensors/Sensor.cpp

main.o: mkdirBuild
	g++ -o build/main.o -c main.cpp

mkdirBuild:
	mkdir -p build

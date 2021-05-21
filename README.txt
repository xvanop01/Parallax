Projekt do semináru C++ - MQTT explorer
2020/2021 FIT VUT Brno

Názov projektu: Parallax
Členovia tímu: 
	Peter Vaňo xvanop01
		xvanop01@stud.fit.vutbr.cz
	Adriana Jurkechová xjurke02
		xjurke02@stud.fit.vutb.cz

Jazyk: C++17
UI: QT
Preklad a spustenie: Makefile
	make / make all - preklad aplikácie
	make run - spustenie aplikacie Parallax Explorer (ParallaxExplorer.exe)
		(Parallax Simulator potrebné spustiť osobitne)
	make doxygen - vygenerovanie programovej dokumentácie
	make clean - vymaže generované súbory
	make pack - vygeneruje .tar.gz súbor so zdrojovými kódmi

Štruktúra:
+--+src
|  +--+config
|  |  +---simDefault.config
|  +--+MQTTsimulator
|  |  +--+sensors
|  |  |  +---Sensor.cpp
|  |  |  +---Sensor.h
|  |  +---main.cpp
|  |  +---Makefile
|  +--+ParallaxExplorer
|     +--+mqttMsgStruct
|     |  +---Messages.cpp
|     |  +---Messages.h
|     +---main.cpp      GENEROVANÉ
|     +---Parallax.pro  KOSTRA GENEROVANÁ
|     +---widget.cpp    KOSTRA GENEROVANÁ
|     +---widget.h      KOSTRA GENEROVANÁ
|     +---widget.ui
+---Doxyfile            KOSTRA GENEROVANÁ
+---Makefile
+---README.txt

Implementácia:
	Projekt pozostáva z 2 častí - Parallax Explorer a Parallax Simulator
(ParallaxDataFeeder). Hlavnou časťou je explorer, ktorý vykonáva a zobrazuje
MQTT komunikáciu s localhostom na MQTT default porte. Simulátor simuluje
pravidelné posielanie správ niekoľkých meracích senzorov (taktiež posiela 
správy na localhost).

Neimplementované zo zadania:
	- prijímanie a odosielanie binárnych súborov
	- farebné odlíšenie odoslaných správ od prijatých
	- ukladanie aktuálneho stavu
	- rôzny náhlad na sledované témy v dashboarde
	- zadávanie dát z dashboardu (posielať je možné len z Explorer záložky)
	- konfigurácia dashboardu užívateľa
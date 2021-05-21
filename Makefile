all:
	$(MAKE) -C src/MQTTsimulator dataFeeder;
	qmake -o src/ParallaxExplorer/Makefile src/ParallaxExplorer/Parallax.pro;
	$(MAKE) -C src/ParallaxExplorer;

run: all
	./ParallaxExplorer.exe

clean:
	rm -f *.exe
	rm -rf src/MQTTsimulator/build
	rm -f src/ParallaxExplorer/*.o
	rm -f src/ParallaxExplorer/Makefile
	rm -f src/ParallaxExplorer/moc*
	rm -f src/ParallaxExplorer/ui_widget.h
	rm -rf doc
	rm -f 1-xvanop01-xjurke02.tar.gz

doxygen:
	doxygen $<

pack:
	tar czfv 1-xvanop01-xjurke02.tar.gz src Doxyfile Makefile README.txt

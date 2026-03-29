app:
	g++ main.cpp -o app.exe
	./app.exe

debug:
	-rm ./output.png
	-rm  ./output.jpg
	g++ main.cpp -o app.exe -DLOGGING -Wall
	./app.exe


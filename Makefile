app:
	g++ main.cpp -o app.exe
	./app.exe
debug:
	g++ main.cpp -o app.exe -DLOGGING
	./app.exe

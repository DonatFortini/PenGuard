g++ -c manager.cc `pkg-config --libs --cflags  gtkmm-3.0`
g++ -o main main.cc manager.o `pkg-config --libs --cflags gtkmm-3.0`
./main
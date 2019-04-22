echo "Begin Compiling"
g++ -std=c++11 main.cpp City.cpp PriorityQueue.cpp -o run.exe -static-libgcc -static-libstdc++
echo "finished compiling"
./run.exe
read -n 2 -s
echo "terminate"

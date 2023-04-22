FROM gcc:12.2.0

RUN apt-get update && apt-get install -y libomp-dev

COPY prog.cpp .

RUN g++ -std=c++17 -O2 -fopenmp prog.cpp -o prog

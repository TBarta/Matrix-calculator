CC=g++
FL=-pedantic -Wall -Wextra -Wno-long-long -O0 -ggdb -std=c++11 -o bartat20

all: compile doc
compile: Matrix.o SparseMatrix.o DenseMatrix.o MatrixCalc.o Utility.o UserInterface.o main.o
	$(CC) $(FL) Matrix.o SparseMatrix.o DenseMatrix.o MatrixCalc.o Utility.o UserInterface.o main.o -o bartat20

run:
	./bartat20

clean:
	rm -rf *.o bartat20 doc

doc:
	doxygen Doxyfile

Matrix.o:
	$(CC) $(FL) -c src/Matrix.cpp -o Matrix.o
SparseMatrix.o:
	$(CC) $(FL) -c src/SparseMatrix.cpp -o SparseMatrix.o
DenseMatrix.o:
	$(CC) $(FL) -c src/DenseMatrix.cpp -o DenseMatrix.o
MatrixCalc.o:
	$(CC) $(FL) -c src/MatrixCalc.cpp -o MatrixCalc.o
Utility.o:
	$(CC) $(FL) -c src/Utility.cpp -o Utility.o
UserInterface.o:
	$(CC) $(FL) -c src/UserInterface.cpp -o UserInterface.o
main.o:
	$(CC) $(FL) -c src/main.cpp -o main.o

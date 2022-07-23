#include <iostream>

int main(){

    int x = 7;
    int y = 9;

    int matrix[x*y] = {};
    int index = 0;
    for( int i = 0; i < x; i++){
        for( int j = 0; j < y; j ++){
            index = i*y + j;
                matrix[index] = index + 1;
            std::cout << matrix[index] << " ";
            if(j==y-1) std::cout << "\n";
        }
    }

    std::cout << "hello there" << "\n";
}
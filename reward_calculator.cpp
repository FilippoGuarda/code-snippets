#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include <cmath>
#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/io.hpp"
#define SS 40

using namespace boost::numeric::ublas;


//returns the signum of the assigned value
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void print(std::vector<int> const &input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' \n';
    }
}


std::vector<int> get_coords(){
    int V;
    std::vector<int> coords;
    std::cout << "insert x coordinate";
    std::cin >> V;
    coords.push_back(V);
    std::cout << "insert y coordinate";
    std::cin >> V;
    coords.push_back(V);
    return coords;
}

matrix<bool> update_matrix(matrix<bool> m, std::vector<int> coord, int radius){
    
    /* -- variables
    - Matrix m: original matrix to modify with illumination
    - Vector coord: vector containing x, y coordinates of the illumination centre
    - int d: maximum distance after which illumination is negligible

    -- Scope
    - this function calculates 'shadow points' in a boolean matrix, it is possible to add
    an irradiation function that takes in the distance as an input and outputs  */
    //create ancyllary matrix to return
    matrix<bool> n (SS, SS);
    int x = coord[0];
    int y = coord[1];
    float direction, distance, modulo;

    //iterate trough the matrix doing raycasting
    
    for (unsigned i = 0; i < m.size1 (); ++ i){
        for (unsigned j = 0; j < m.size2 (); ++ j){
            //raycast from point i,j to point x,y 
            //if collisions are found, set point i,j value to false
            float x1, y1;
            distance = 0;
            direction = atan2((y-j),(x-i));
            modulo = sqrt((y-j)^2 + (x-i)^2);
            if(modulo > radius){
                n(i,j) = 0;
                continue;
            }
            //walk along direction until the i,j point is reached or a zero tile
            while(distance < modulo){
                distance += 0.25;
                x1 = x + distance*cos(direction);
                y1 = y + distance*sin(direction);
                if(m(x1, y1) == 0){
                    n(i,j) = 0;
                    break;
                }
            }
        }
    }

    return n;
}

void show_matrix(matrix<bool> m){
    for (unsigned i=0; i< m.size1(); ++i){
        for (unsigned j=0; j< m.size2(); ++j){
            std::cout << m(i,j);
        }
        std::cout << std::endl;
    }
}

int main () {

    // generate random bool function

    auto gen = std::bind(std::uniform_real_distribution<>(0,1), std::default_random_engine(time(0)));
    float prob = 0.95;
    int d = 0;
    int x, y;

    //create a nxn matrix
    matrix<bool> m (SS, SS);
    //populate matrix with random boolean values
    for (unsigned i = 0; i < m.size1 (); ++ i){
        for (unsigned j = 0; j < m.size2 (); ++ j){
            //randomize bool at element i,j between true and false with probability prob
            m(i,j) = (gen() <= prob)? true : false;
        }
    }
    
    show_matrix(m);

    while(true){

        std::vector<int> coords = get_coords();
        print(coords);
        matrix<bool> n = update_matrix(m, coords, 30);
        show_matrix(n);
    }

    
}
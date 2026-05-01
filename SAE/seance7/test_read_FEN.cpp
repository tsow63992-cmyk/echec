#include <iostream>
using namespace std ;
#include "view.hpp"

int main () {
    square *T ;
    T = empty() ;
    read_FEN( T , "FEN2.txt") ;
    print_board(T) ;
    delete[] T ;
    return 0 ;
}
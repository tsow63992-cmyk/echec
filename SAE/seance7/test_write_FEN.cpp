#include <iostream>
using namespace std ;
#include "view.hpp"
#include <fstream>

int main () {
    square *T ;
    T = empty() ;
    start(T) ;
    write_FEN ( T , "FEN1.txt" ) ;
    delete[] T ;
    return 0 ;
}
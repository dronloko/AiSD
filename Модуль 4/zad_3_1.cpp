#include <iostream>
#include <vector>
#include <stdint.h>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

void Count( int n, int64_t& counter ) {
    int64_t** d = new int64_t*[n + 1];
    
    for ( int i = 1; i < n + 1; ++i ) {
        d[i] = new int64_t[n + 1];
    }

    for ( int i = 1; i < n + 1; ++i ) {
        for ( int j = i + 1; j < n; ++j ) {
            d[i][j] = 0;
        }
    }
    
    for ( int i = 1; i < n + 1; ++i ) {
        d[i][i] = 1;
    }
    
    for ( int i = 1; i < n + 1; ++i ) {
        for ( int j = i - 1; j >= 1; --j ) {
            d[i][j] = d[i - j][j] /* есть столбик k */
            + d[i][j + 1] /* нет столбика k */;
            // d[i][j] = d[i - j][j + 1] /* есть столбик k */
            // + d[i][j + 1] /* нет столбика k */;
        }
    }
    
    counter = d[n][1];
    
    for ( int i = 0; i < n; ++i )
        delete d[i];
    delete[] d;
}

int main() {
           
    int n = 0;
    std::cin >> n;
    int64_t counter = 0;
    Count(n, counter);
    std::cout << counter << std::endl;
    
    return 0;
}

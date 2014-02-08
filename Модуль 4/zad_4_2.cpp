#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Call {
    int Start;
    int Finish;
    Call( int start, int finish ) : Start(start), Finish(finish) {};
};

bool less_Finish( const Call &left, const Call &right ) {
    if ( left.Finish < right.Finish ) return true;
    return false;
}

void qSort_Finish( Call* data, int low, int high ) {
    int i = low;
    int j = high;
    Call x = data[(low + high) / 2];

    do {
        while ( less_Finish( data[i], x ) ) ++i;
        while ( less_Finish( x, data[j] ) ) --j;
        if (i <= j) {
            std::swap(data[i], data[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (low < j) qSort_Finish(data, low, j);
    if (i < high) qSort_Finish(data, i, high);
}

void Count( vector <Call> calls, int& counter ) {
    qSort_Finish( &calls[0], 0, calls.size() - 1 );
    ++counter;
    int j = 0; 
    for ( int i = 1; i < calls.size(); ++i ) {
        if ( calls[i].Start >= calls[j].Finish ) {
            ++counter;
            j = i;
        }
    }
}

int main() {
    vector <Call> calls;
    while ( true ) {
        int start = 0, finish = 0;
        cin >> start >> finish;
        if ( cin.eof() )
            break;
        Call call( start, finish );
        calls.push_back( call );
    }
    int counter = 0;
    Count( calls, counter );
    cout << counter << endl;
    return 0;
}

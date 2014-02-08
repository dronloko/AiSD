// Copyright 2013 <DronLoko>

#include <iostream>

struct Rectangle {
    int Start;
    int Height;
    
    Rectangle() : Start(0), Height(0) {}
};

struct Stack {
    int Top;
    int bufferSize;
    int maxSquare;
    Rectangle* buffer;
    Rectangle lastRectangle;

    Stack();
    ~Stack();
    
    void resizeBuffer();
    void push( Rectangle rect );    
    Rectangle pop();
    void fixMaxSquare( Rectangle& rect );
    int getmaxSquare();
};

Stack::Stack() {
    bufferSize = 5;
    Top = -1;
    buffer = new Rectangle[bufferSize];
    maxSquare = 0;
}

Stack::~Stack() {
     delete[] buffer;
}

void Stack::resizeBuffer() {
    Rectangle* newBuffer = new Rectangle[bufferSize + 5];
    for ( int i = 0; i <= Top; ++i ) {
        newBuffer[i] = buffer[i];
    }
    bufferSize += 5;
    delete[] buffer;
    buffer = newBuffer;
}

void Stack::push( Rectangle rect ) {
    if ( Top == bufferSize - 1 )
        resizeBuffer();
    if ( rect.Height < lastRectangle.Height )
        fixMaxSquare( rect );
    lastRectangle = rect;
    buffer[++Top] = rect;
}

Rectangle Stack::pop() {
    if ( Top != -1 ) {
        lastRectangle = buffer[Top - 1];
        return buffer[Top--];
    }
}

void Stack::fixMaxSquare( Rectangle& rect ) {
    Rectangle temp;
    while ( lastRectangle.Height > rect.Height ) {
        temp = pop();
        int square = (rect.Start - temp.Start) * temp.Height;
        if ( square > maxSquare ) {
            maxSquare = square;
        }
    }
    rect.Start = temp.Start;
}

int Stack::getmaxSquare() {
    return maxSquare;
}

int main() {
    int n = 0;
    std::cin >> n;
    
    Rectangle rectangle;
    Stack st;
    st.push(rectangle);
    
    for ( int i = 0; i < n; ++i ) {
        int height = 0;
        int width = 0;
        std::cin >> width >> rectangle.Height;
        st.push(rectangle);
        rectangle.Start += width;
    }
    rectangle.Height = 0;
    st.push(rectangle);
    std::cout << st.getmaxSquare() << std::endl;
    return 0;
}

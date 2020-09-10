#include <iostream>

using namespace std;

const int maxSize = 100;

class Queue {
    char q[maxSize];
    int size; //maximum elements in queue
    int putloc, getloc; //indexes of elements that put in or get out of queue
public:
    Queue(int len) {
        if(len > maxSize) len = maxSize;
        else if(len <= 0) len = 1;

        size = len;
        putloc = getloc = 0;
    }

    void put(char ch) {
        if(putloc == size) {
            cout << "---Queue is full.\n";
            return;
        }

        putloc++;
        q[putloc] = ch;
    }

    char get() {
        if(getloc == putloc) {
            cout << "---Queue is empty.\n";
            return 0;
        }

        getloc++;
        return q[getloc];
    }
};

int main() {
    Queue bigQ(100);
    Queue smallQ(4);
    char ch;
    int i;

    cout << "BigQ is for alphabet.\n";
    for(i = 0; i < 26; i++) {
        bigQ.put('A' + i);
    }

    cout << "BigQ have this elements: " << "\n";
    for(i = 0; i < 26; i++) {
        ch = bigQ.get();
        if (ch != 0) cout << ch;
    }

    cout << "\n\n";

    cout << "SmallQ is for showing mistakes.\n";

    for(i = 0; i < 5; i++) {
        cout << "Trying to put " << (char) ('Z' - i);
        smallQ.put('Z' - i);
        cout << "\n";
    }

    cout << "\n";
    cout << "Elements in smallQ: ";
    for(i = 0; i < 5; i++) {
        ch = smallQ.get();

        if(ch != 0) cout << ch;
    }

    cout << "\n";
}
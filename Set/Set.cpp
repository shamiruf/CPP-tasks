#include <iostream>

using namespace std;

const int maxSize = 100;

class Set {
    int len; // number of elements
    char members[maxSize]; // array that contains set
    
    int find(char ch); // find element
public:
    // Сonstructor
    Set() { len = 0; }

    // return number of elements in set
    int getLength() { return len; }

    void showSet(); 
    bool isMember(char ch);

    Set operator+(char ch); // add element 
    Set operator-(char ch); // delete element

    Set operator+(Set ob2); // forms a union   
    Set operator-(Set ob2); // forms a difference
};

int Set::find(char ch) {
    int i;

    for (i = 0; i < len; i++) {
        if (members[i] == ch) return i;
    }

    return -1;
}

void Set::showSet() {
    int i;
    cout << "{ ";
    for(i = 0; i < len; i++) {
        cout << members[i] << " ";
    }
    cout << "}\n";
}

bool Set::isMember(char ch) {
    if(find(ch) != -1) return true;
    return false;
}

Set Set::operator+(char ch) {
    Set newSet;

    if (len == maxSize) {
        cout << "Set is full.\n";
        return *this;
    }

    newSet = *this;

    if (find(ch) == -1) {
        newSet.members[newSet.len] = ch;
        newSet.len++;
    }
    return newSet;
}

Set Set::operator-(char ch) {
    Set newSet;
    int i = find(ch);

    for (int j = 0; j < len; j++) 
        if(j != i) newSet = newSet + members[j];

    return newSet;
}

Set Set::operator+(Set ob2) {
    Set newSet = *this;

    for (int i = 0; i < ob2.len; i++) 
        newSet = newSet + ob2.members[i];
    
    return newSet;
}

Set Set::operator-(Set ob2) {
    Set newSet = *this;

    for (int i = 0; i < ob2.len; i++) 
        newSet = newSet - ob2.members[i];

    return newSet;
}

int main() {
    Set s1;
    Set s2;
    Set s3;

    s1 = s1 + 'A';
    s1 = s1 + 'B';
    s1 = s1 + 'C';

    cout << "s1 after adding A B C: ";
    s1.showSet();

    cout << "\n";

    cout << "Check function isMember().\n";
    if(s1.isMember('B')) 
        cout << "B is member of s1.\n";
    else
        cout << "B isn't member of s1.\n";

    if(s1.isMember('T')) 
        cout << "T is member of s1.\n";
    else
        cout << "T isn't member of s1.\n";

    cout << "\n";

    s1 = s1 - 'B';
    cout << "s1 after s1 = s1 - 'B': ";
    s1.showSet();

    cout << "\n";

    s1 = s1 + 'B';
    cout << "s1 after adding 'B': ";
    s1.showSet();

    cout << "\n";

    s2 = s2 + 'A';
    s2 = s2 + 'X';
    s2 = s2 + 'W';

    cout << "s2 after adding A X W: ";
    s2.showSet();

    cout << "\n";

    s3 = s1 + s2;
    cout << "s3 after s3 = s1 + s2: ";
    s3.showSet();

    s3 = s3 - s1;
    cout << "s3 after s3 = s3 - s1: ";
    s3.showSet();

    cout << "\n";

    s2 = s2 - s2;
    cout << "s2 after s2 = s2 - s2: ";
    s2.showSet();

    return 0;
}
#include <iostream>
#include <map>
#include <set>

using namespace std;

int main(){
    map<char, int> mymap;
    mymap.insert ( std::pair<char,int>('a',100) );
    mymap.insert ( std::pair<char,int>('b',20) );
    mymap.insert ( std::pair<char,int>('c',0) );

    for (auto it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

    set<char> myset;
    myset.insert('A');
    myset.insert('C');
    myset.insert('B');

    for (auto it=myset.begin(); it!=myset.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}

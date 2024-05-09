#include <cstdlib>
#include<iostream>
#include<string>
#include<queue>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::queue;

int main(int argc, char* argv[])
{
    queue<int> myque;
    for (int i = 0; i<10; i++) 
    {
        myque.push(i);
    }
    while(!myque.empty())
    {
        int num = myque.front();
        cout<<num<<",";
        myque.pop();
    }
    cout<<endl;
    return EXIT_SUCCESS;
}

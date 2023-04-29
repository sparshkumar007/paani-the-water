#include <iostream>
#include <vector>
using namespace std;

class TIME
{
public:
    int hr, min;
    TIME()
    {
        hr = 0;
        min = 0;
    }
    TIME(int _hr, int _min)
    {
        hr = _hr;
        min = _min;
    }
};

class drivers
{
public:
    string name;
    int age;
    vector<int> schedule;
    drivers() {}
    drivers(string _name, int _age, vector<int> _schedule) {}
};

int main()
{
    vector<vector<int>> cities;
    int dst = 2;
    int requiredFlow = 35;
    TIME req;
    req.hr = 3;
    req.min = 53;
    bool pref = 1;
    int choice;
    // 1->pipes;
    // 2->tankers;
    choice = 1;
    if (choice == 1)
    {
        network_flow(cities, dst, requiredFlow, req);
    }
    return 0;
    dfdffd
}
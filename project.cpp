#include <iostream>
#include <vector>
#include <queue>
#include <climits> //for INT_MAX
#include <math.h>  //for Ceil
using namespace std;

// Structures,Classes,Variables used...
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

class driver
{
public:
    string name;
    int age;
    vector<int> schedule;
    driver() {}
    driver(string _name, int _age, vector<int> _schedule) {}
} drivers[10];

vector<vector<int>> cities; // stores flow per minute
vector<int> srcs;
int no_of_cities;

// Helper functions
void assign()
{
    no_of_cities = 10;
    cout << "assigned";
}

int to_minutes(TIME t)
{
    return t.hr * 60 + t.min;
}

// Algorithms
int Edmond_Karp(int dst)
{
    // assigning a dummy graph
    // we'll make changes in dummy graph by changing reverse edges and forward edges
    vector<vector<int>> dummy = cities;
    int n = no_of_cities;

    // algorithm
    int ans = 0;
    bool f = 1;
    while (f)
    {
        f = 0;
        // taken a temparory source having infinite flow to all the given sources.
        // all our sources have parent=-2.
        int flow = INT_MAX;
        queue<pair<int, int>> q;
        vector<int> parent(n, -1);
        vector<bool> visited(n, 0);
        for (auto it : srcs)
        {
            q.push(make_pair(it, -2));
            visited[it] = 1;
        }
        while (!q.empty())
        {
            pair<int, int> x = q.front();
            q.pop();
            int y = x.first;
            parent[y] = x.second;
            for (int i = 0; i < n; i++)
            {
                if (dummy[y][i] && !visited[i])
                {
                    q.push(make_pair(y, i));
                    visited[i] = 1;
                }
            }
        }
        if (parent[dst] != -1)
        {
            // as we have reached our destination so set f=1.
            f = 1;
            vector<int> path;
            int x = 0;
            int y = dst;
            while (x != -2)
            {
                path.push_back(x);
                x = parent[y];
            }

            // calculating flow from the path.
            int flow = INT_MAX;
            for (int i = 0; i < path.size() - 1; i++)
            {
                flow = min(flow, dummy[path[i + 1]][path[i]]);
            }

            // making changes in forward and revrse map.
            for (int i = 0; i < path.size() - 1; i++)
            {
                // forward edge
                dummy[path[i + 1]][path[i]] -= flow;
                // reverse edge
                dummy[path[i]][path[i + 1]] += flow;
            }
            ans += flow;
        }
    }
    return ans;
}

int Dijkistra(int dst)
{
    // code remaining
    return 0;
}
bool check_availability(int a, int b)
{
    // code remaining
    return true;
}

// So_called operations....
int pipeflow(int dst, int requiredflow)
{
    int flow_per_minute = Edmond_Karp(dst);
    int time_taken = ceil(1.0 * requiredflow / flow_per_minute);
    return time_taken;
}

int travel_by_road(int dst, TIME required_at_time)
{
    int time_taken = 0;
    time_taken = Dijkistra(dst);
    int _from = to_minutes(required_at_time);
    int _to = time_taken + _from;
    bool is_available = true;
    is_available = check_availability(_from, _to);
    if (is_available)
        return time_taken;
    return INT_MAX;
}

// Our Job
int supply_water(int choice, int dst, int required_amount, TIME required_at_time)
{
    int time_by_pipes = pipeflow(dst, required_amount);
    int time_by_tanker = travel_by_road(dst, required_at_time);
    if (choice == 1)
        time_by_tanker = INT_MAX;
    if (choice == 2)
        time_by_pipes = INT_MAX;
    return min(time_by_pipes, time_by_tanker);
}
int main()
{
    assign();
    int dst = 2;
    int required_amount = 35;
    TIME required_at_time;
    required_at_time.hr = 3;
    required_at_time.min = 53;
    int choice = 3;
    // 1->pipes;
    // 2->tankers;
    int ans = supply_water(choice, dst, required_amount, required_at_time);
    if (ans == INT_MAX)
        cout << "Sorry!!!" << endl
             << "We cant supply water to you with your preffered choice currenty...";
    else
        cout << "Total time required to supply water to your dst is: " << ans;
    cout << endl;
    return 0;
}
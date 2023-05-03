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

vector<vector<int>> cities;   // stores flow per minute
vector<vector<int>> road_map; // stores time taken to travel between two cities using tanker
vector<int> srcs;
int no_of_cities;

// Helper functions
void assign()
{
    // code remaining
    no_of_cities = 10;
}

int to_minutes(TIME t)
{
    return t.hr * 60 + t.min;
}

class cmp
{
public:
    bool operator()(pair<int, int> *a, pair<int, int> *b)
    {
        return a->second > b->second;
    }
};

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

int DIJKISTRA(int src, int dst)
{
    // declaring required things
    int n = no_of_cities;
    vector<bool> visited(n, 0);

    // in below heap:
    // pair's first value is node
    // second value is curent distance of that node from src
    priority_queue<pair<int, int> *, vector<pair<int, int> *>, cmp> q;

    // hash table
    vector<pair<int, int> *> hash(n, NULL);

    // distance vector
    vector<int> dis(n, INT_MAX);
    dis[src] = 0;

    // giving values in heap and hash table
    for (int i = 0; i < n; i++)
    {
        pair<int, int> *x = new pair<int, int>;
        *x = make_pair(i, dis[i]);
        q.push(x);
        hash[i] = x;
    }
    //

    // starting operation
    for (int k = 1; k <= n; k++)
    {
        // finding minimum element in heap
        pair<int, int> *x = q.top();
        int i = x->first;
        int d = x->second;
        if (d == INT_MAX)
            return dis[dst];
        dis[i] = d;
        visited[i] = 1;

        // applying algorithm
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && road_map[i][j] != 0)
            {
                pair<int, int> *p = hash[j];
                if (d + road_map[i][j] < p->second)
                {
                    p->second = road_map[i][j] + d;
                }
            }
        }
        q.pop();
    }
    return dis[dst];
}

int Dijkistra(int dst)
{
    int time_taken = INT_MAX;
    for (auto it : srcs)
        time_taken = min(time_taken, DIJKISTRA(it, dst));
    return time_taken;
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
    int _to = (time_taken + _from) % 1440;
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

    // name searching part is remaning

    int choice = 3;
    cout << "1.)Pipeline" << endl
         << "2.)Tanker" << endl
         << "3.)we just need water" << endl;
    cout << "enter your preffered choice for supply..." << endl;
    cin >> choice;
    int ans = supply_water(choice, dst, required_amount, required_at_time);
    if (ans == INT_MAX)
        cout << "Sorry!!!" << endl
             << "We cant supply water to you with your preffered choice currenty...";
    else
        cout << "Total time required to supply water to your dst is: " << ans;
    cout << endl;
    return 0;
}
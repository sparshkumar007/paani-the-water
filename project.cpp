#include <iostream>
#include <vector>
#include <queue>
#include <climits>
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

vector<vector<int>> cities;
vector<int> srcs;
int no_of_cities;

void assign()
{
    cout << "assigned";
}

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

int networkflow(int dst, int requiredflow)
{
    int flow_per_hour = Edmond_Karp(dst);
    cout << flow_per_hour << endl;
}

int main()
{
    assign();
    int dst = 2;
    int requiredamount = 35;
    TIME req;
    req.hr = 3;
    req.min = 53;
    bool pref = 1;
    int choice;
    // 1->pipes;
    // 2->tankers;
    choice = 1;
    int time_by_pipes = networkflow(dst, requiredamount);
    int time_by_tanker = 0;
    return 0;
}
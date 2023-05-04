#include <iostream>
#include <vector>
#include <queue>
#include <climits>  //INT_MAX
#include <math.h>   //CEIL
#include <stdlib.h> //CLEAR
using namespace std;

// Structures,Classes,Variables used...
class node
{
public:
    bool terminal;
    int data;
    node **next;
    node()
    {
        terminal = 0;
        data = -1;
        next = new node *[26];
        for (int i = 0; i < 26; i++)
            next[i] = NULL;
    }
};

class TRIE
{
public:
    node *root;
    int data;
    int count;
    TRIE()
    {
        root = new node();
        count = 0;
    }
    void insert(string word, int _data)
    {
        int i = 0;
        node *it = root;
        while (i < word.size())
        {
            if (it->next[word[i] - 'a'] == NULL)
            {
                it->next[word[i] - 'a'] = new node();
            }
            it = it->next[word[i] - 'a'];
            i++;
        }
        it->terminal = true;
        it->data = _data;
        count++;
    }
    int search(string word)
    {
        node *it = root;
        int i = 0;
        while (i < word.size())
        {
            if (it->next[word[i] - 'a'] == NULL)
            {
                return -1;
            }
            it = it->next[word[i] - 'a'];
            i++;
        }
        if (it->terminal == true)
            return it->data;
        return -1;
    }
};

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
    void insert(string _name, int _age, vector<int> _schedule)
    {
        name = _name;
        age = _age;
        schedule = _schedule;
    }
    void print()
    {
        cout << name << endl;
        cout << "Age: " << age << endl;
        cout << endl;
    }
} drivers[10];

vector<vector<int>> cities;   // stores flow per minute
vector<vector<int>> road_map; // stores time taken to travel between two cities using tanker
TRIE city_names;
vector<int> srcs;
int no_of_cities;

// Helper functions
void city()
{
    city_names.insert("noida", 0);
    city_names.insert("ghaziabad", 1);
    city_names.insert("delhi", 2);
    city_names.insert("faridabad", 3);
    city_names.insert("gurugram", 4);
    city_names.insert("meerut", 5);
    city_names.insert("saharanpur", 6);
    city_names.insert("muzzafarnagar", 7);
    city_names.insert("bijnor", 8);
    city_names.insert("chennai", 9);
    city_names.insert("lahore", 10);
    no_of_cities = city_names.count;
    srcs.push_back(0);
    srcs.push_back(5);
    srcs.push_back(9);
}
void roads()
{
    int n = no_of_cities;
    vector<int> temp;
    for (int j = 0; j < n; j++)
        temp.push_back(0);
    for (int i = 0; i < n; i++)
    {
        road_map.push_back(temp);
    }
    road_map[0][7] = 54;
    road_map[0][8] = 43;
    road_map[1][2] = 53;
    road_map[1][8] = 98;
    road_map[2][1] = 53;
    road_map[2][3] = 43;
    road_map[2][8] = 70;
    road_map[2][9] = 149;
    road_map[3][2] = 43;
    road_map[3][4] = 45;
    road_map[4][3] = 45;
    road_map[4][5] = 72;
    road_map[4][9] = 173;
    road_map[4][10] = 51;
    road_map[5][4] = 72;
    road_map[5][10] = 59;
    road_map[6][7] = 48;
    road_map[6][10] = 68;
    road_map[7][0] = 54;
    road_map[7][6] = 48;
    road_map[7][8] = 59;
    road_map[8][0] = 43;
    road_map[8][1] = 98;
    road_map[8][2] = 70;
    road_map[8][7] = 59;
    road_map[8][9] = 152;
    road_map[8][10] = 47;
    road_map[9][2] = 149;
    road_map[9][4] = 173;
    road_map[9][8] = 152;
    road_map[10][4] = 51;
    road_map[10][5] = 59;
    road_map[10][6] = 68;
    road_map[10][8] = 47;
}
void pipes()
{
    int n = no_of_cities;
    vector<int> temp;
    for (int j = 0; j < n; j++)
        temp.push_back(0);
    for (int i = 0; i < n; i++)
    {
        cities.push_back(temp);
    }
    cities[0][1] = 150;
    cities[0][7] = 100;
    cities[0][8] = 176;
    cities[1][2] = 78;
    cities[2][3] = 52;
    cities[2][8] = 43;
    cities[3][4] = 89;
    cities[5][6] = 200;
    cities[5][8] = 80;
    cities[5][10] = 340;
    cities[7][8] = 160;
    cities[8][6] = 76;
    cities[8][10] = 97;
    cities[9][2] = 200;
    cities[9][3] = 300;
    cities[9][8] = 190;
    cities[9][10] = 210;
    cities[10][4] = 275;
}

void drivers_details()
{
    vector<int> temp(24, 0);
    vector<vector<int>> s(10, temp);
    s[0][0] = 1;
    s[0][3] = 1;
    s[0][6] = 1;
    s[0][7] = 1;
    s[0][8] = 1;
    s[0][9] = 1;
    s[0][20] = 1;
    s[0][23] = 1;
    s[1][1] = 1;
    s[1][4] = 1;
    s[1][5] = 1;
    s[1][13] = 1;
    s[1][14] = 1;
    s[1][15] = 1;
    s[1][16] = 1;
    s[2][1] = 1;
    s[2][2] = 1;
    s[2][3] = 1;
    s[2][4] = 1;
    s[2][23] = 1;
    s[2][0] = 1;
    s[3][11] = 1;
    s[3][12] = 1;
    s[3][13] = 1;
    s[3][14] = 1;
    s[4][20] = 1;
    s[4][21] = 1;
    s[4][22] = 1;
    s[4][23] = 1;
    s[5][5] = 1;
    s[5][6] = 1;
    s[5][15] = 1;
    s[5][16] = 1;
    s[6][17] = 1;
    s[7][15] = 1;
    s[8][10] = 1;
    s[9][16] = 1;
    s[9][17] = 1;
    s[9][18] = 1;
    s[9][19] = 1;
    s[9][20] = 1;
    drivers[0].insert("RAHUL KALRA", 29, s[0]);
    drivers[1].insert("ADI", 19, s[1]);
    drivers[2].insert("ANOOBIE", 69, s[2]);
    drivers[3].insert("NORMIE", 98, s[3]);
    drivers[4].insert("AKASHI", 35, s[4]);
    drivers[5].insert("BARBARIQ ALI KHAN", 19, s[5]);
    drivers[6].insert("AKSHIT: THE LAST AIR BENDER", 2, s[6]);
    drivers[7].insert("BALMUKUND MEENA", 11, s[7]);
    drivers[8].insert("DEVANSH", 33, s[8]);
    drivers[9].insert("PANDIT GANGADHAR VIDHYADHAR MAYADHAR OMKARNATH SHASTRI", 298, s[9]);
}
void assign()
{
    city();
    pipes();
    roads();
    drivers_details();
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
                    q.push(make_pair(i, y));
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
            while (y != -2)
            {
                path.push_back(y);
                y = parent[y];
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
    int n = no_of_cities;
    vector<bool> visited(n, 0);
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    for (int i = 0; i < n; i++)
    {
        int x = -1;
        int m = INT_MAX;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && m > dist[j])
            {
                m = dist[j];
                x = j;
            }
        }
        if (x == -1)
            return INT_MAX;
        if (x == dst)
            return dist[dst];
        visited[x] = 1;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && dist[j] > dist[x] + road_map[x][j] && road_map[x][j] != 0)
            {
                dist[j] = road_map[x][j] + dist[x];
            }
        }
    }
    return dist[dst];
}

int Dijkistra(int dst)
{
    int time_taken = INT_MAX;
    for (auto it : srcs)
    {
        time_taken = min(time_taken, DIJKISTRA(it, dst));
    }
    return time_taken;
}

bool check_availability(int a, int b)
{
    int from = a / 60;
    int to = b / 60;
    vector<int> times;
    if (from < to)
    {
        while (from != to)
            times.push_back(from++);
        times.push_back(to);
    }
    else
    {
        while (from != to)
            times.push_back((from++) % 24);
        times.push_back(to);
    }
    for (int i = 0; i < 10; i++)
    {
        int k = 1;
        for (int j = 0; j < times.size(); j++)
        {
            if (drivers[i].schedule[times[j]] == 0)
            {
                k = 0;
                break;
            }
        }
        if (k)
            return true;
        else
            k = 1;
    }
    return false;
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
    int _from = (to_minutes(required_at_time) - time_taken) % 1440;
    int _to = (to_minutes(required_at_time) + time_taken) % 1440;
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
    int dst;
    int required_amount;
    TIME required_at_time;
    string s;
    cout << "Enter name of city you want water supply: ";
    cin >> s;
    dst = city_names.search(s);
    while (dst == -1)
    {
        cout << "Sorry!!!" << endl
             << "I guess you have entered wrong name." << endl
             << "Please reEnter the city name: ";
        cin >> s;
        dst = city_names.search(s);
    }
    system("CLS");
    cout << "OK...Got it" << endl
         << "Now how much PANI do you need" << endl
         << "(please enter in Litre)" << endl
         << "Amount: ";
    cin >> required_amount;
    system("CLS");
    cout << "OK..." << endl
         << "Now just tell us when do you need your supply.." << endl
         << "Hour: ";
    cin >> required_at_time.hr;
    while (required_at_time.hr > 23 || required_at_time.hr < 0)
    {
        cout << "Please enter valid hrs(0 to 23)" << endl;
        cout << "Hour: ";
        cin >> required_at_time.hr;
    }
    cout << "Minute: ";
    cin >> required_at_time.min;
    while (required_at_time.min > 59 || required_at_time.min < 0)
    {
        cout << "Please enter valid mins(0 to 59)" << endl;
        cout << "Minute: ";
        cin >> required_at_time.min;
    }
    system("CLS");
    int choice = 3;
    cout << "1.)Pipeline" << endl
         << "2.)Tanker" << endl
         << "3.)we just need water" << endl;
    cout << "enter your preffered choice for supply..." << endl;
    cin >> choice;
    while (choice > 3 || choice < 1)
    {
        cout << "Please enter right choice: ";
        cin >> choice;
    }
    system("CLS");
    cout << "Ok we got your request." << endl;
    cout << "Please wait for few seconds...." << endl;
    for (int k = 1; k <= 3; k++)
    {
        cout << ".";
        for (int i = 1; i <= 10000; i++)
        {
            for (int j = 1; j <= 10000; j++)
            {
            }
        }
    }
    system("CLS");
    cout << "OK Done." << endl;
    int ans = supply_water(choice, dst, required_amount * 1000, required_at_time);
    if (ans == INT_MAX)
        cout << "Sorry!!!" << endl
             << "We cant supply water to you with your preffered choice currenty...";
    else
        cout << "Total time required to supply water to your dst is: " << ans;
    cout << endl;
    return 0;
}
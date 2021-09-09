#include <bits/stdc++.h>
using namespace std;

class meetings
{
public:
    int startTime, endTime, duration;
    string clientName, date, host;

    meetings(string date, int startTime, int endTime, int duration, string clientName, string host)
    {
        this->date = date;
        this->startTime = startTime;
        this->endTime = endTime;
        this->duration = duration;
        this->clientName = clientName;
        this->host = host;
    }
};

class MeetingScheduler
{
private:
    unordered_map<string, vector<meetings>> user_meetings;

    bool isAvailable(string user, string day, int start, int endi)
    {
        if (user_meetings.count(user) <= 0)
        {
            return false;
        }
        for (int i = 1; i < user_meetings[user].size(); i++)
        { //because 0th contains ("",-1,-1,-1,"")
            if (user_meetings[user][i].date == day)
            {
                int stt = user_meetings[user][i].startTime;
                int entt = user_meetings[user][i].endTime;
                if (stt <= start && entt >= endi)
                {
                    return false;
                }
                else if (endi > stt && endi <= entt)
                {
                    return false;
                }
                else if (start >= stt && start < entt)
                {
                    return false;
                }
            }
        }

        return true;
    }

public:
    bool addUser(string userName)
    {
        if (user_meetings.count(userName) > 0)
        {
            return false;
        }
        meetings newMeet("", -1, -1, -1, "", "");
        user_meetings[userName].push_back(newMeet);
        return true;
    }

    bool createEvent(string day, int startTime, int duration, int num, vector<string> &users)
    {
        for (int i = 0; i < num - 1; i++)
        {
            for (int j = i + 1; j < num; j++)
            {
                if (isAvailable(users[i], day, startTime, startTime + duration) && isAvailable(users[j], day, startTime, startTime + duration))
                {
                    meetings newMeet1(day, startTime, startTime + duration, duration, users[j], users[i]);
                    meetings newMeet2(day, startTime, startTime + duration, duration, users[j], users[i]);
                    user_meetings[users[i]].push_back(newMeet1);
                    user_meetings[users[j]].push_back(newMeet2);
                }
                else
                {
                    return false;
                }
            }
        }

        return true;
    }

    void showEvents(string day, string userName)
    {
        unordered_map<string, vector<string>> schedule;
        bool printed = false;
        for (int i = 1; i < user_meetings[userName].size(); i++)
        {
            printed = true;
            cout << user_meetings[userName][i].startTime << "-" << user_meetings[userName][i].endTime << " ";
            cout << user_meetings[userName][i].host << " " << user_meetings[userName][i].clientName << "\n";
        }

        if (!printed)
        {
            cout << "none\n";
        }
    }

    void suggestSlot(string day, int start, int endi, int duration, int num, vector<string> &users)
    {
        for (int i = 0; i < num; i++)
        {
            for (int j = 1; j < user_meetings[users[i]].size(); j++)
            {
                meetings temp = user_meetings[users[i]][j];
                if (temp.startTime <= start && temp.endTime >= endi)
                {
                    cout << "none\n";
                    return;
                }
                else if (temp.startTime > start && (temp.endTime >= endi && endi > temp.startTime))
                {
                    endi = temp.startTime;
                }
                else if ((temp.startTime <= start && temp.endTime > start) && (temp.endTime < endi))
                {
                    start = temp.endTime;
                }
            }
        }

        if (endi - start >= duration)
        {
            cout << start << "\n";
        }
        else
        {
            cout << "none\n";
        }
    }
};

void addUser(MeetingScheduler &cs)
{
    string name;
    cin >> name;
    bool res = cs.addUser(name);
    if (res)
    {
        cout << "success\n";
    }
    else
    {
        cout << "failure\n";
    }
}

void createEvent(MeetingScheduler &cs)
{
    string date;
    int startTime, duration;
    cin >> date >> startTime >> duration;
    int counts, num;
    cin >> counts;
    num = counts;
    vector<string> users;
    while (counts--)
    {
        string name;
        cin >> name;
        users.push_back(name);
    }
    bool res = cs.createEvent(date, startTime, duration, num, users);
    if (res)
    {
        cout << "success\n";
    }
    else
    {
        cout << "failure\n";
    }
}

void showEvents(MeetingScheduler &cs)
{
    string day;
    string user;
    cin >> day >> user;
    cs.showEvents(day, user);
}

void suggestSlot(MeetingScheduler &cs)
{
    string day;
    int start, endi, duration;
    cin >> day >> start >> endi >> duration;
    int counts, num;
    cin >> counts;
    num = counts;
    vector<string> users;
    while (counts--)
    {
        string name;
        cin >> name;
        users.push_back(name);
    }

    cs.suggestSlot(day, start, endi, duration, num, users);
}

int main()
{
    MeetingScheduler cs;
    while (1)
    {
        string command;
        cin >> command;
        if (command == "add-user")
        {
            addUser(cs);
        }
        else if (command == "create-event")
        {
            createEvent(cs);
        }
        else if (command == "show-events")
        {
            showEvents(cs);
        }
        else if (command == "suggest-slot")
        {
            suggestSlot(cs);
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            cout << "Invalid Command\n";
        }
    }
    return 0;
}
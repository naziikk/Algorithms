class UserStatistics {
private:
    int K;
    int Limit;
    queue<pair<int, int>> q;
    unordered_map<int, int> mp;
    int counter;
public:
    UserStatistics(int k, int limit) : K(k), Limit(limit), counter(0) {

    }

    void event(int now, int userId) {
        q.push({now, userId});
        mp[userId]++;
        if (mp[userId] >= Limit) {
            counter++;
        }
        while (!q.empty() && q.front().first < now-K) {
            int du = q.front().second;
            mp[du] -= 1;
            if (mp[du] < Limit) {
                counter--;
            }
            q.pop();
        }
    }

    int robotCount(int now) {
        while (!q.empty() && q.front().first < now - K) {
            int du = q.front().second;
            mp[du] -= 1;
            if (mp[du] < Limit) {
                counter--;
            }
            q.pop();
        }
        return counter;
    }
};
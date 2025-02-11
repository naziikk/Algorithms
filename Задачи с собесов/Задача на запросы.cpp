#include <iostream>
#include <queue>
#include <unordered_map>

class UserStatistics {
public:
    UserStatistics(int k, int limit) : k(k), limit(limit), current(0){};

    void event(int time, int user_id) {
       request_queue.push({time, user_id});
       mp[user_id]++;
       if (mp[user_id] == limit) {
           current++;
       }
       while (!request_queue.empty() && request_queue.front().first < time - k) {
           int user_id_to_delete = request_queue.front().second;
           request_queue.pop();
           if (mp[user_id_to_delete] == limit) {
               current--;
           }
           mp[user_id_to_delete]--;
       }
    }

    int getNumberOfUsers(int time) {
        while (!request_queue.empty() && request_queue.front().first < time - k) {
            int user_id_to_delete = request_queue.front().second;
            request_queue.pop();
            if (mp[user_id_to_delete] == limit) {
                current--;
            }
            mp[user_id_to_delete]--;
        }
        return current;
    }

private:
    int k;
    int limit;
    std::queue<std::pair<int, int>> request_queue;
    std::unordered_map<int, int> mp;
    int current;
};
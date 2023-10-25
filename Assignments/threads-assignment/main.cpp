Simple Optimizing a Search Engine solution


#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <unordered_map>

using namespace std;

unordered_map<string, string> dataRepository = {
    {"query1", "result1"},
    {"query2", "result2"},
    {"query3", "result3"},
    // ... other data
};

mutex mtx;  // Mutex for controlling access to shared resources

void processQuery(const string& query) {
    // Acquire the lock
    lock_guard<mutex> lock(mtx);

    // Get the ID of the current thread
    thread::id this_id = this_thread::get_id();

    // Print the thread ID and the query it's processing
    cout << "Thread " << this_id << " processing " << query << endl;

    if (dataRepository.find(query) != dataRepository.end()) {
        cout << "Result for " << query << ": " << dataRepository[query] << endl;
    } else {
        cout << "No result found for " << query << endl;
    }
}

int main() {
    vector<string> queries = {"query1", "query2", "query3"};
    vector<thread> threads;

    for (const string& query : queries) {
        threads.emplace_back(thread(processQuery, query));
    }

    for (thread& th : threads) {
        th.join();
    }

    return 0;
}
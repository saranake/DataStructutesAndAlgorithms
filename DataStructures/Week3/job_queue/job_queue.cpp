#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

using std::vector;
using std::cin;
using std::cout;


  

class PriorityCompare {

  public:

  PriorityCompare() { }

  ~PriorityCompare() { }

  bool operator() (std::pair<int, long long> &lhs, std::pair<int, long long> &rhs) const {
    if(lhs.second == rhs.second) {
      return lhs.first > rhs.first;
    } else {
      return lhs.second > rhs.second;
    }
  }
};

 

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    assigned_workers_.resize(m);
    start_times_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    typedef std::pair<int, long long> thread;
    typedef std::priority_queue <thread,std::vector<thread>, PriorityCompare> myq;
    myq scheduler;

    for(int i = 0; i < num_workers_; i++) {
      scheduler.push(std::make_pair(i, 0));
    }

    for(int i = 0; i < jobs_.size(); i++) {
      thread t = scheduler.top();
      scheduler.pop();
      assigned_workers_[i] = t.first;
      start_times_[i] = t.second;
      t.second += jobs_[i];
      scheduler.push(t);
    }
  }
 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}

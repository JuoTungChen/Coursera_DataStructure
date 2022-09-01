#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;

using namespace std;

typedef pair<int, long long> mypair;

class MyCompare{
	public:
		bool operator()(const mypair &a, const mypair &b){
			if(a.second == b.second)
				return a.first > b.first;
			else
				return a.second > b.second;
		}
};


class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;     //which thread to use for each job
  vector<long long> start_times_;    //the start time for each thread to process each job

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs_Naive() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
  }

  void AssignJobs(){
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size()); 
    priority_queue<mypair, vector<mypair>, MyCompare> next_free_time;

    for(int i = 0; i < num_workers_; i++){
   	    next_free_time.push(make_pair(i, 0));
    }
    for(int j = 0; j < jobs_.size(); j++){
    	pair<int, long long> next_worker = next_free_time.top();
	    assigned_workers_[j] = next_worker.first;
	    start_times_[j] = next_worker.second;
	    next_free_time.pop();
	    next_free_time.push(make_pair(next_worker.first, next_worker.second+jobs_[j]));
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

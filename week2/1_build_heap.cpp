#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
	 vector<int> data_;
	 vector< pair<int, int> > swaps_;

	 void WriteResponse() const {
	    	cout << swaps_.size() << "\n";
	    	for (int i = 0; i < swaps_.size(); ++i) {
	  		cout << swaps_[i].first << " " << swaps_[i].second << "\n";
	    	}
	  }

	void ReadData() {
		int n;
		cin >> n;
	    	data_.resize(n);
	    	for(int i = 0; i < n; ++i)
	      		cin >> data_[i];
	  }
	
	// SiftDown Operation
	void SiftDown(int i){
		int min_index = i;
		int l = 2*i+1;
		int r = 2*i+2;
		// should be data_.size()-1 instead of data_.size() 
		if((l <= data_.size()-1) && (data_[l] < data_[min_index]))
				min_index = l;

		if((r <= data_.size()-1) && (data_[r] < data_[min_index]))
				min_index = r;
		if(i != min_index){
			swap(data_[i], data_[min_index]);
			swaps_.push_back(make_pair(i, min_index));
			SiftDown(min_index);
		}
	}

  void GenerateSwaps_naive() {
    swaps_.clear();   //clear the vector (make sure it is empty)
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }

  //my solution
  void GenerateSwaps(){
	  swaps_.clear();
	  for(int i = ((data_.size()/2) - 1); i>=0; i--){
		SiftDown(i);
	  }
  }
 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}

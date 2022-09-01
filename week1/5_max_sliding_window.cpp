#include <iostream>
#include <vector>
#include <deque>
using std::cin;
using std::cout;
using std::vector;
using std::max;

void max_sliding_window_naive(vector<int> const & A, int w) {
    for (size_t i = 0; i < A.size() - w + 1; ++i) {
        int window_max = A.at(i);
        for (size_t j = i + 1; j < i + w; ++j)
            window_max = max(window_max, A.at(j));

        cout << window_max << " ";
    }

    return;
}

void max_sliding_window(vector<int> const & A, int w){
    std::deque<int> q(w);
    for(int i = 0; i < w; i++){
        while(!q.empty() && A[i] >= A[q.back()]){
            q.pop_back();
        }
        q.push_back(i);
    }

    for(int i = w; i < A.size(); i++){
        cout << A[q.front()] << " ";
        while(!q.empty() && q.front() <= i - w){
            q.pop_front();
        }

        while(!q.empty() && A[i] >= A[q.back()]){
            q.pop_back();
        }
        q.push_back(i);
    
    }
    cout << A[q.front()];
}

int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window(A, w);

    return 0;
}

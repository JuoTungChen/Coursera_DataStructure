#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::cout;
struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;  //m
    // store all strings in one vector
    vector<string> elems;
    vector<vector<string>> hash_table;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;    //x
        static const size_t prime = 1000000007;  //p
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = ((((hash * multiplier + s[i]) % prime )+ prime) % prime);
        return (((hash % bucket_count) + bucket_count) % bucket_count);
    }

public:
    QueryProcessor(int n){ 
            this -> bucket_count = n;
            this -> elems.resize(n);
            this -> hash_table.resize(n);
    };

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")   //query = add / del / find
            cin >> query.s;
        else
            cin >> query.ind;        //query = check
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery_mine(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            /*for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
                    */
            cout << elems[query.ind];
            std::cout << "\n";        //output blank line
        } else {
            //vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            long H = hash_func(query.s);
            size_t found = elems[H].find(query.s);
            if (query.type == "find")
                //writeSearchResult(it != elems.end());
                writeSearchResult(found != elems[H].npos);
            else if (query.type == "add") {
                if (found  == elems[H].npos){      //string currently not in chain
                    elems[H].insert(0, query.s+" ");
                    //cout<<"H = "<<H<<std::endl;
                }
                    //elems.push_back(query.s);
            } else if (query.type == "del") {
                if (found != elems[H].npos){      //string currently in chain
                //if (elems[H] != "")      //if string is in the chain -> erase it
                    //elems.erase(elems.begin() + H);
                    elems[H].erase(found, found + query.s.size() + 1);
                }
            }
        }
    }

    void processQuery(const Query &query){
        if(query.type == "check"){
            for(long long i = static_cast<long long>(hash_table[query.ind].size())-1; i>=0; i--){
            if(hash_func(hash_table[query.ind][i]) == query.ind)
                    cout<< hash_table[query.ind][i] << " ";
            }
            cout<<"\n";
        
        }
        else{
                int H = hash_func(query.s);
                vector<string>::iterator it = std::find(hash_table[H].begin(), hash_table[H].end(), query.s);
                if(query.type == "find"){
                    writeSearchResult(it != hash_table[H].end());
                }
                else if(query.type == "add"){
                    if(it == hash_table[H].end())
                        hash_table[H].push_back(query.s);
                }
                else if(query.type == "del"){
                    if(it != hash_table[H].end())
                            hash_table[H].erase(it);
                }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}

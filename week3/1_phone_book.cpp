#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::string;
using std::vector;
using std::cin;
using std::unordered_map;


struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries_naive(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts[j].name = queries[i].name;
                    was_founded = true;
                    break;
                }
            // otherwise, just add it
            if (!was_founded)
                contacts.push_back(queries[i]);
        } else if (queries[i].type == "del") {
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts.erase(contacts.begin() + j);
                    break;
                }
        } else {
            string response = "not found";
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    response = contacts[j].name;
                    break;
                }
            result.push_back(response);
        }
    return result;
}


vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    unordered_map<int, string> contacts;
     for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            // if we already have contact with such number,
            // we should rewrite contact's name
            auto it = contacts.find(queries[i].number);
            if (it != contacts.end()){
                it->second = queries[i].name;
            }
            // otherwise, just add it
            else{
                contacts[queries[i].number] = queries[i].name;
            }

        } else if (queries[i].type == "del") {
            contacts.erase(queries[i].number);   //delete the number in the contacts
                   
        } else {
            string response = "not found";
            auto it = contacts.find(queries[i].number);
                if (it != contacts.end()){
                    response = it->second;
                }
            result.push_back(response);
        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}

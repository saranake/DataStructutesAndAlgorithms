#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::string;
using std::vector;
using std::cin;

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

void process_queries(const vector<Query>& queries) {
    std::map<int, Query> phoneBook;
    for (size_t i = 0; i < queries.size(); ++i) {
      if(queries[i].type == "add") {
        std::map<int, Query>::iterator it = phoneBook.find(queries[i].number);
        if(it == phoneBook.end()) {
          phoneBook[queries[i].number] = queries[i];
        } else {
          Query &q = phoneBook[queries[i].number]; 
          q.name = queries[i].name;
        }
      } else if (queries[i].type == "del") {
        phoneBook.erase(queries[i].number);
      } else if (queries[i].type == "find") {
        std::map<int, Query>::iterator it = phoneBook.find(queries[i].number);
        if(it == phoneBook.end()) {
          std::cout << "not found\n";
        } else {
          Query &q = phoneBook[queries[i].number];
          std::cout << q.name << "\n";
        }
      }
    }
}

int main() {
    process_queries(read_queries());
    return 0;
}

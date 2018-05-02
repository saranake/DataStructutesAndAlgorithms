#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <math.h>

using std::string;
using std::list;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};


class QueryProcessor {
    vector<list<string> > hashTable;
    int bucket_count;
    // store all strings in one vector
    // Allocate an empty list

    unsigned long long longMod(int i) {
      static const size_t multiplier = 263;
      static const size_t prime = 1000000007;

      unsigned long long mod = 1;
      while (i != 0) {
        mod = (mod * multiplier) % prime;
        i--;
      }
      return mod;
    }

    size_t hash_func(const string& s) {
        unsigned long long hash = 0;
        for (int i  = 0; i <  static_cast<int> (s.size()) ; i++) {
            unsigned long long t = s[i] * longMod(i) ;
            hash += t;
        }
        hash = hash % 1000000007;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count), hashTable(bucket_count) {
       for(int i = 0; i < bucket_count; i++) {
         list<string> l;
         hashTable[i] = l;
       }
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {

        if (query.type == "check") {
            list<string> &l = hashTable[query.ind];
            for (list<string >::iterator i = l.begin(); i != l.end(); i++ )
                    std::cout << *i << " ";
            std::cout << "\n";
        } else {
            list<string> &l = hashTable[hash_func(query.s)];
            if (query.type == "find") {
               bool found = false;
               for (list<string >::iterator i = l.begin(); i != l.end(); i++ ) {
                 if(query.s == *i) {
                    found = true; 
                    break;
                 }
               }
               writeSearchResult(found);
            } else if (query.type == "add") {
               bool found = false;
               for (list<string >::iterator i = l.begin(); i != l.end(); i++ ) {
                 if(query.s == *i) {
                    found = true; 
                    break;
                 }
               }
               if(!found) {
                 l.push_front(query.s);
               }
            } else if (query.type == "del") {
              for (list<string >::iterator i = l.begin(); i != l.end(); i++ ) {
                  if (*i == query.s) {
                    l.erase(i);
                    break;
                  }
              }
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

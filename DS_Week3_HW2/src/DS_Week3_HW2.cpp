//============================================================================
// Name        : DS_Week3_HW2.cpp
// Author      : Daniel Ramirez
// Version     :
// Copyright   : HW2_Week3
// Description :  Hashing with chains, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

#define Constraints   ((number_queries >=1 && number_queries <= 1e5) && (bucket_count <= number_queries && bucket_count>=(number_queries/5)))
#define latinLetters  ( ( ((int)*it)>=65 && ((int)*it)<=90 ) || (((int)*it)>=97 && ((int)*it)<=122 ) )

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::list;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    list <Query> queries_storage;
    vector < list<string> > chain_vector;
    int number_queries;

  public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {chain_vector.resize(bucket_count);}

    void readQuery(){
        Query query;
        cin >> query.type;
        if (query.type != "check"){
            cin >> query.s;
            queries_storage.push_back(query);
        }
        else{
            cin >> query.ind;
            queries_storage.push_back(query);
        }
  }

    void processQuery(){
        Query aux;
        while(!queries_storage.empty()){
           aux=queries_storage.front();
           if (aux.type == "check") {
             check_processing(aux.ind);
           } else {
               if (aux.type == "find"){
                  if(string_val(aux.s))
                    find_processing(aux.s);
               }
               else if (aux.type == "add") {
                 if(string_val(aux.s))
                   add_processing(aux.s);
               } else if (aux.type == "del") {
                 if(string_val(aux.s))
                   del_processing(aux.s);
               }
            }
            queries_storage.pop_front();
        }
    }

  bool string_val(const string & s){
     bool result=false;
     if(s.size()<=15){
        for(string::const_iterator it=s.begin();it!=s.end();++it){
            if(latinLetters)
               result=true;
            else
               return false;
        }
     }
     else
        return result;
     return result;
  }

  void add_processing(const string &s){
    unsigned long long hash_value;
    bool string_found=false;
    hash_value=hash_func(s);
    if(!chain_vector[hash_value].empty()){
       list<string>::iterator it=chain_vector[hash_value].begin();
       list<string>::iterator end=chain_vector[hash_value].end();
       while(it!=end && string_found==false){
          if(*it==s)
             string_found=true;
          it++;
        }
        if(string_found==false)
            chain_vector[hash_value].push_front(s);
    }
    else
       chain_vector[hash_value].push_front(s);
  }

  void find_processing(const string &s){
     unsigned long long hash_value;
     bool key_found=false;
     hash_value=hash_func(s);
     if(chain_vector[hash_value].empty()){
              cout<<"no\n";
     }
     else{
           list<string>::iterator it=chain_vector[hash_value].begin();
           list<string>::iterator end=chain_vector[hash_value].end();
           while(it!=end && key_found==false){
              if(*it==s){
                  cout<<"yes\n";
                 key_found=true;
              }
              it++;
           }
           if(key_found==false){
               cout<<"no\n";
           }
     }
  }

  void del_processing(const string&s){
     unsigned long long hash_value;
     bool key_found=false;
     hash_value=hash_func(s);
     if(!chain_vector[hash_value].empty()){
        list<string>::iterator it=chain_vector[hash_value].begin();
        list<string>::iterator end=chain_vector[hash_value].end();
        while(it!=end && key_found==false){
           if(*it==s){
             chain_vector[hash_value].remove(*it);
              key_found=true;
           }
           it++;
        }
     }
  }

  void check_processing(const int addr){
       if(!chain_vector[addr].empty()){
          for (list<string>::const_iterator iterator= chain_vector[addr].begin(); iterator != chain_vector[addr].end(); ++iterator) {
              cout<<*iterator<<" ";
          }
       }
       cout<<"\n";
  }

  void processQueries() {
        cin >> number_queries;
        for (int i = 0; i < number_queries; ++i)
          if(Constraints)
            readQuery();
        processQuery();
        destroy_mem();
  }

  size_t hash_func(const string& s)  {
    static const size_t multiplier = 263;
    static const size_t prime = 1000000007;
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return hash % bucket_count;
  }

  void destroy_mem(){
     chain_vector.clear();
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

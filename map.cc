#include <map>
#include <string>
#include <iostream>

using namespace std;

int main() {
  map<string, int> M;
  string name;
  int score;
  while(cin >> name >> score){
    M[name] = score;
  }

  for(auto it = M.begin(); it != M.end(); it++){
    cout << it->first << ": " << it->second << endl;
  }
  
  return 0;
}

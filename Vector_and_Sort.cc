#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main (){
  vector<string> S;
  
  string s;
  while(cin >> s) S.push_back(s);

  sort(S.begin(), S.end(), [](const string& l, const string& r) { return l > r; });

  for (auto it = S.begin(); it != S.end(); it++) cout << *it << endl;
  
  return 0;
}

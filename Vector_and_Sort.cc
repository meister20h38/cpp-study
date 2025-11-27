#include <iostream>
#include <string>
#include <vector>
#include <algorith>

using namespace std;

int main (){
  vector<string> S;
  
  string s;
  while(cin >> s) S.push_back(s);

  S.sort(S.begin(), S.end(), [](const string& l, const string& r {return l > r; });

  for (const auto& e : S) cout << *e << endl;
  
  return 0;
}

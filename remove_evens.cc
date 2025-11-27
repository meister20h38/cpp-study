void remove_evens(std::vector<int>& v) {
  for (auto it = v.begin(); it != v.end();) {
    if (*it % 2 == 0) it = v.erase(it);
    else ++it;
  }
}

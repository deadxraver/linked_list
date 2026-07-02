#include "linked_list.hpp"

int main(void) {
  linked_list<int> ll;
  std::cout << ll << std::endl;
  ll.push_back(11);
  ll.push_back(42);
  std::cout << ll << std::endl;
  std::cout << ll[0] << ' ' << ll[1] << std::endl;
  std::cout << ll.size() << std::endl;
  ll.push(1111);
  std::cout << ll.top() << ", " << ll << std::endl;
  ll.pop();
  ll.remove(42);
  std::cout << ll << std::endl;
  try {
    ll.remove(42);
  } catch (std::logic_error e) {
    std::cerr << e.what() << std::endl;
  }
  try {
    std::cout << ll[3] << std::endl;
  } catch (std::logic_error e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}

#include "linked_list.hpp"

int main(void) {
  linked_list<int> ll;
  std::cout << ll << std::endl;
  ll.push_back(11);
  ll.push_back(42);
  std::cout << ll << std::endl;
  std::cout << ll[0] << ' ' << ll[1] << std::endl;
  std::cout << ll.size() << std::endl;
  std::cout << ll[3] << std::endl;
  return 0;
}

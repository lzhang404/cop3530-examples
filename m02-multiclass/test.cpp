#include "store.hpp"
#include "store-item.hpp"
#include <iostream>
#include <cassert>
using namespace std;

#ifndef HEADER_GUARD
#define HEADER_GUARD
// header file content
#endif
#include "catch.hpp"
#include "store-item.hpp"
TEST_CASE("store item equality and priting", "[storeItem]")
{
  SECTION("case-insensitive comparison"{
    storeItem item1("Apple");
    storeItem item2("apple");
    CHECK(item1.equals(item2));
  }
}
void testStoreItem() {
  StoreItem item1("Apple");
  item1.print();
  StoreItem item2("apple");
  item2.print();
  assert(item1.equals(item2));
}

void testStore() {
  Store myStore("Test Store");
  myStore.addItem(StoreItem("Apple"));
  myStore.addItem(StoreItem("Banana"));
  myStore.print();
}

int main() {
  testStoreItem();
  testStore();
  return 0;
}
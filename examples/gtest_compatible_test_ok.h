#pragma once

// gtest or simple_test shall be included prior to this one.

#include <cassert>
#include <vector>

TEST(simple_test, vector_capacity) {
  std::vector<int> xs;
  xs.reserve(100500);
  xs.clear();
  EXPECT_NE(0, xs.capacity());
}

TEST(DISABLED_simple_test, some_disabled) {
  assert(false);  // unreachable
}

TEST(simple_test, DISABLED_something) {
  assert(false);  // unreachable
}

TEST(simple_test, some_correct) {
  const char h1[] = "hello";
  const char h2[] = "hello";
  EXPECT_NE(h1, h2);  // different addresses
  EXPECT_STREQ(h1, h2);  // equal content

  EXPECT_STRNE("hello", "world");

  EXPECT_STREQ("hello\0one", "hello\0two");  // difference beyond trailing zero

  std::cout << "all right!" << std::endl;
}

TEST(simple_test, do_not_eval_twice) {
  int counter = 0;
  ASSERT_EQ(counter++, 0);
  ASSERT_EQ(++counter, 2);
  ASSERT_EQ(2, counter++);
  ASSERT_EQ(4, ++counter);
}

struct D {
  static const int TRASH = 123456789;
  static int g_x;
  explicit D(int x) { g_x = x; }
  D(const D&) = delete;
  void operator=(const D&) = delete;
  ~D() { g_x = TRASH; }
  const int& cref() const { return g_x; }
};
int D::g_x = D::TRASH;

TEST(simple_test, do_not_make_dangling_references) {
  EXPECT_EQ(D(123).cref(), 123);

  const int& d = D(456).cref();
  EXPECT_NE(d, 456);
}

TEST(simple_test, compare_floats_implicitly) {
  const auto pivot = 123.4;
  const auto epsilon = 0.1;

  EXPECT_NEAR(pivot, pivot - epsilon, epsilon);
  EXPECT_NEAR(pivot, pivot + epsilon, epsilon);
}

TEST(simple_test, compare_types) {
  EXPECT_EQ(typeid(int), typeid(int));
}

TEST(simple_test, exceptions) {
  EXPECT_THROW(throw std::out_of_range("ahaha"), std::logic_error);
  EXPECT_ANY_THROW(throw std::out_of_range("ahaha"));
  EXPECT_NO_THROW({});

  ASSERT_THROW(throw std::out_of_range("ahaha"), std::logic_error);
  ASSERT_ANY_THROW(throw std::out_of_range("ahaha"));
  ASSERT_NO_THROW({});
}

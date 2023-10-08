# simple_test
simple unittest (GTest-like)

Original repository: https://github.com/nickolaym/simple_test

## Usage

- add `simple_test.h` to your project
- include
- write set of `TEST(suite, name) {body}` functions
- add `TESTING_MAIN()`
- voila

## Macros

### TEST

```c++
TEST(suite, name, [enabled]) {
  test body goes here;
}
```
- `suite` is valid C identifier (not decorated)
- `name` is valid C identifier (not decorated)
- `enabled` is optional bool expression (runtime constant, evaluated before main())

introduces auxillary object test_name and function

```c++
void func_name() {
  test body goes here;
}
```
which shall throw an exception if some test assertion fails.

Please don't catch(...) inside it without special need.

GTest compatibility: if suite or name starts with `DISABLED`, the test will skip.

### ASSERT_..., EXPECT_...

```c++
ASSERT_CMP(a, op, b)
EXPECT_CMP(a, op, b)
ASSERT_EQ, ASSERT_LT, ASSERT_LE, ... as in GTest

ASSERT_STRCMP(a, op, b)
EXPECT_STRCMP(a, op, b)
ASSERT_STREQ, ASSERT_STRNE, ... as in GTest

ASSERT_FLOATCMP(a, op, b, eps)
EXPECT_FLOATCMP(a, op, b, eps)
ASSERT_NEAR, EXPECT_NEAR as in GTest

ASSERT_BOOL(a, b)
EXPECT_BOOL(a, b)
ASSERT_TRUE, ASSERT_FALSE, ... as in GTest
```
where args
- `a`, `b` - arbitrary expressions
- `op` - arbitrary comparison operator (except `<=>`)

macro suffices
- `_CMP` compares a and b directly, `a op b`, so they should be comparable
- `_STRCMP` uses C string comparison `strcmp(a, b) op 0`
- `_FLOATCMP` uses inaccurate float comparison, `(a ± eps) op b`
- `_BOOL` matches boolean `(bool)a == (bool)b`

So, GTest's `ASSERT_TRUE(a)` is our `ASSERT_BOOL(a, true)` or `ASSERT_BOOL(true, a)`

If a comparison failed, compared values are printed `std::cout << a`.
So, they should be printable.

### Extra output

To print extra messages if an assetion fails, use following syntax:

```c++
ASSERT_BLABLABLA() << common << C++ << stream << args;

ASSERTION_FAULT(common, C++, stream, args);
```

Note that if the assertion passes, nothing will evaluate.

### Show green assertions

```c++
SHOW_GREEN_ASSERTIONS(flag)
```
where `flag` is boolean

If true, all positive assertions will print their values, too.

(TODO: print trailing messages).

See examples in just_simple_test.cpp


### TESTING_MAIN
Just implementation of `int main()`

Feel free to call a subsequent function from your `main()` with your fixtures:

```c++
int main(int argc, char** argv) {
  ...
  int result = simple_test::testing_main(argc, argv);
  ...
  return result;
}
```

#### Arguments

```c++
your_test_application [-h] [--help] [-l] [--list] {patterns}
```

* -h | --help - print help
* -l | --list - print list of matched tests, instead of run them
* pattens are glob-like patterns to match to suite.test names

If no patterns are specified, all tests match to run/list.

Pattern syntax:
* `?` for any single char,
* `*` for any substring,
* `.` for separator between suite and name
* other chars are a-z, A-Z, 0-9, _

### TODO:
- test throwing / nothrowing exceptions

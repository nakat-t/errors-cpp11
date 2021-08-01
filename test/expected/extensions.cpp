#include "catch.hpp"
#include <errors_cpp11/errors.hpp>

#define TOKENPASTE(x, y) x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
// In catch2 v2.13.7, STATIC_REQUIRE is already defined.
#ifndef STATIC_REQUIRE
#define STATIC_REQUIRE(e)                                                      \
  constexpr bool TOKENPASTE2(rqure, __LINE__) = e;                             \
  REQUIRE(e);
#endif

TEST_CASE("Map extensions", "[extensions.map]") {
  auto mul2 = [](int a) { return a * 2; };
  auto ret_void = [](int a) {};

  {
    errors::expected<int, int> e = 21;
    auto ret = e.map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = e.map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = std::move(e).map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = std::move(e).map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = e.map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), errors::expected<void, int>>::value));
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = e.map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), errors::expected<void, int>>::value));
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = std::move(e).map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), errors::expected<void, int>>::value));
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = std::move(e).map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), errors::expected<void, int>>::value));
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), errors::expected<void, int>>::value));
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), errors::expected<void, int>>::value));
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), errors::expected<void, int>>::value));
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), errors::expected<void, int>>::value));
  }


  // mapping functions which return references
  {
    errors::expected<int, int> e(42);
    auto ret = e.map([](int& i) -> int& { return i; });
    REQUIRE(ret);
    REQUIRE(ret == 42);
  }
}

TEST_CASE("Map error extensions", "[extensions.map_error]") {
  auto mul2 = [](int a) { return a * 2; };
  auto ret_void = [](int a) {};

  {
    errors::expected<int, int> e = 21;
    auto ret = e.map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = e.map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = e.map_error(ret_void);
    REQUIRE(ret);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = e.map_error(ret_void);
    REQUIRE(ret);
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(ret);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(ret);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.map_error(ret_void);
    REQUIRE(!ret);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.map_error(ret_void);
    REQUIRE(!ret);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(!ret);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(!ret);
  }

}

TEST_CASE("And then extensions", "[extensions.and_then]") {
  auto succeed = [](int a) { return errors::expected<int, int>(21 * 2); };
  auto fail = [](int a) { return errors::expected<int, int>(errors::unexpect, 17); };

  {
    errors::expected<int, int> e = 21;
    auto ret = e.and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = e.and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }
}

TEST_CASE("or_else", "[extensions.or_else]") {
  using eptr = std::unique_ptr<int>;
  auto succeed = [](int a) { return errors::expected<int, int>(21 * 2); };
  auto succeedptr = [](eptr e) { return errors::expected<int,eptr>(21*2);};
  auto fail =    [](int a) { return errors::expected<int,int>(errors::unexpect, 17);};
  auto efail =   [](eptr e) { *e = 17;return errors::expected<int,eptr>(errors::unexpect, std::move(e));};
  auto failptr = [](eptr e) { return errors::expected<int,eptr>(errors::unexpect, std::move(e));};
  auto failvoid = [](int) {};
  auto failvoidptr = [](const eptr&) { /* don't consume */};
  auto consumeptr = [](eptr) {};
  auto make_u_int = [](int n) { return std::unique_ptr<int>(new int(n));};

  {
    errors::expected<int, int> e = 21;
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    errors::expected<int, eptr> e = 21;
    auto ret = std::move(e).or_else(succeedptr);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = e.or_else(fail);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = e.or_else(fail);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    errors::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(fail);
    REQUIRE(ret);
    REQUIRE(ret == 21);
  }


  {
    errors::expected<int, eptr> e = 21;
    auto ret = std::move(e).or_else(efail);
    REQUIRE(ret);
    REQUIRE(ret == 21);
  }

  {
    const errors::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(fail);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    errors::expected<int, eptr> e(errors::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else(succeedptr);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = e.or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    errors::expected<int, eptr> e(errors::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else(failvoidptr);
    REQUIRE(!ret);
    REQUIRE(*ret.error() == 21);
  }

  {
    errors::expected<int, eptr> e(errors::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else(consumeptr);
    REQUIRE(!ret);
    REQUIRE(ret.error() == nullptr);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const errors::expected<int, int> e(errors::unexpect, 21);
    auto ret = std::move(e).or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

}
struct S {
    int x;
};

struct F {
    int x;
};

TEST_CASE("14", "[issue.14]") {
    auto res = errors::expected<S,F>{errors::unexpect, F{}};

    res.map_error([](F f) {

    });
}

TEST_CASE("32", "[issue.32]") {
    int i = 0;
    errors::expected<void, int> a;
    a.map([&i]{i = 42;});
    REQUIRE(i == 42);

    auto x = a.map([]{return 42;});
    REQUIRE(*x == 42);
}

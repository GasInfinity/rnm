## 📏 Rena::Mathematics (rnm)

Small, simple C++26 math library for game development and such. Use it by adding the headers in your project and including `rnm/rnm.hpp` (or each header individually).

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
  
## 🔍 Usage

```cpp
#include <rnm/rnm.hpp>

typedef rnm::vec<float, 2> vec2f; // a.k.a: rnm::vec2<float>
typedef rnm::vec<float, 3> vec3f; // a.k.a: rnm::vec2<float>
typedef rnm::mat<float, 3, 3> mat3f; // a.k.a: rnm::mat3<float>

vec2f xy = {100.f, 20.f};
mat3f translation = rnm::translate(xy);

vec2f translated = (translation * vec3f(xy, 1.f)).xy;

std::print("{:.2f}", translated / 4.f); // Prints: "(50.00, 10.00)"
```


## ❓ FAQ

#### Why don't you use SIMD?

SIMD is overrated for this, you won't get any kind of performance improvement by using it naively. You must think about the data you'll be handling and [put it in optimal ways for SIMD](https://www.reedbeta.com/blog/on-vector-math-libraries/#how-to-simd-and-how-not-to).

## 📜 License

[MIT](https://choosealicense.com/licenses/mit/)


## 📝 TODO

- [ ]  Document the entire library.
- [ ]  Add support for C++20 modules.

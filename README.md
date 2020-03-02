# Corsicana
[![Build Status](https://travis-ci.org/kurt-nj/corsicana.svg?branch=master)](https://travis-ci.org/kurt-nj/corsicana)
[![codecov](https://codecov.io/gh/kurt-nj/corsicana/branch/master/graph/badge.svg)](https://codecov.io/gh/kurt-nj/corsicana)
[![Github Releases](https://img.shields.io/github/release/kurt-nj/corsicana.svg)](https://github.com/kurt-nj/corsicana/releases)

A header only C++ implementation of the [Aho-Corasick](https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm)
algorithm. It aims to be reasonably fast and thread safe.

## Usage

### Trie Construction

Construct a match trie in one of the following manners. New patterns cannot be added to a trie once it is built.
```c++
corsicana::trie_builder my_trie_builder;
auto my_trie = my_trie_builder.insert("pattern one")
                              .insert("pattern two")
                              .build();
```
```c++
corsicana::trie_builder my_trie_builder;
auto my_trie = my_trie_builder.insert(container.begin(), container.end()).build();
```
```c++
corsicana::trie_builder my_trie_builder(container.begin(), container.end());
auto my_trie = my_trie_builder.build();
```
```c++
corsicana::trie_builder my_trie_builder = { "one", "two", "three" };
auto my_trie = my_trie_builder.build();
```

### Matching

There are a number of different ways to search on a frozen trie

```c++
auto match = my_trie.match("Input Text");
// get all matches at once
vector<corsicana::result> all = match.all();
```
```c++
auto match = my_trie.match("Input Text");
// get the count of matches
int total = match.count();
```
```c++
auto match = my_trie.match("Input Text");
// return true if we can find any matches
bool any_there = match.any();
```
```c++
auto match = my_trie.match("Input Text");
// or iterate over them one at a time
for (auto const& m : match) {
    // iteration will search one at a time and can be stopped at any time
}
```

## Testing

Tests are written using [Catch2](https://github.com/catchorg/Catch2) and can be executed by
running `ctest` after building

Testing can be disabled by setting BUILD_TESTING to OFF in cmake

## Benchmark

Benchmarks and a harness to write additional benchmarks is included in the benchmark directory. 

Benchmarks can be disabled by setting BUILD_BENCHMARK to OFF in cmake

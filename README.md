# Corsicana
[![Build Status](https://travis-ci.org/kurt-nj/corsicana.svg?branch=master)](https://travis-ci.org/kurt-nj/corsicana)
[![codecov](https://codecov.io/gh/kurt-nj/corsicana/branch/master/graph/badge.svg)](https://codecov.io/gh/kurt-nj/corsicana)

A header only C++ implementation of the [Aho-Corasick](https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm)
algorithm. It aims to be reasonably fast and thread safe.

## Usage

### Trie Construction

Construct a match trie in the following manner. The trie needs to be frozen before it can be searched.
Once frozen, new patterns cannot be added and is now read only.
```
corsicana::trie my_trie;
my_trie.insert("pattern one")
       .insert("pattern two")
       .freeze();
```

### Matching

There are a number of different ways to search on a frozen trie

```
auto match = my_trie.match("Input Text");
// get all matches at once
vector<string> all = match.all();
// get the count of matches
int total = match.count();
// or iterate over them one at a time
for (auto const& m : match) {
    // iteration will search one at a time and can be stopped at any time
}
```

## Testing

Tests are written using [Catch2](https://github.com/catchorg/Catch2) and can be executed by
running `ctest` after building

## Benchmark

A simple benchmark is included the test directory that compares against a simple naive text search.

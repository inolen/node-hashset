node-hashset
============

Provides a native hashset implementation for node.

Often, when you need to use a set in JavaScript, you may instead use a JavaScript object like so:
```javascript
var cache = {};

cache['foobar'] = true;

if (!cache['foobar']) {
  ...
}
```

This works good for up to a million items, but it starts to grind down to a halt in v8 around the 10,000,000 mark.

node-hashset implements a stricly typed hashset with [std::unsorted_map](http://en.cppreference.com/w/cpp/container/unordered_map) to enable high-volume sets.

## Installation

```bash
$ npm install hashset
```

## Quick start

```javascript
var HashSet = require('hashset');
var set = new HashSet.string();
set.add('foobar');
```

Checkout [the tests](https://github.com/inolen/node-hashset/blob/master/test/test-hashset.js) for more examples.

## HashSet

There are currently two HashSet constructors, `HashSet.int32` and `HashSet.string`.

### add(value)

Adds `value` to the set.

### contains(value)

Returns a boolean value indicating if the set contains `value`.

### remove(value)

Removes `value` from the set.

### clear()

Removes all values from the set.

### size()

Returns the numbers of values in the set.

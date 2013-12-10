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

This works well for up to a few million items, but after that it starts to grind v8 down to a halt.

node-hashset implements a stricly typed hashset with [std::unsorted_set](http://en.cppreference.com/w/cpp/container/unordered_set) to enable working with extremely large sets.

## Installation

```bash
$ npm install hashset-native
```

## Quick start

```javascript
var HashSet = require('hashset-native');
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

### iterator()

Returns an iterator to iterate over the values in the set.

```javascript
var it = set.iterator();

while (it.hasNext()) {
  console.log(it.next());
}
```

### remove(value)

Removes `value` from the set.

### clear()

Removes all values from the set.

### size()

Returns the numbers of values in the set.

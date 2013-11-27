'use strict';

var assert = require('assert');
var HashSet = require('../index');

[
  { type: 'string', key1: 'key1', key2: 'key2', missing: 'invalid' },
  { type: 'int32', key1: -13, key2: 79, missing: 42 }
].forEach(function (it) {
  var type = it.type;
  var key1 = it.key1;
  var key2 = it.key2;
  var missing = it.missing;

  suite('hashset-' + type, function() {
    var set;

    setup(function() {
      set = new HashSet[type]();
    });

    test('add()', function () {
      set.add(key1);
      assert(set.contains(key1));
      assert(!set.contains(missing));
    });

    test('remove()', function () {
      set.add(key1);
      assert(set.contains(key1));
      set.remove(key1);
      assert(!set.contains(key1));
    });

    test('size()', function () {
      assert(set.size() === 0);
      set.add(key1);
      assert(set.size() === 1);
      set.add(key2);
      assert(set.size() === 2);
    });

    test('clear()', function () {
      assert(set.size() === 0);
      set.add(key1);
      assert(set.size() === 1);
      set.clear();
      assert(set.size() === 0);
    });

    test('empty()', function () {
      assert(set.empty());
      set.add(key1);
      assert(!set.empty());
    });
  });
});

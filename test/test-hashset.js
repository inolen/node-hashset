'use strict';

var assert = require('assert');
var HashSet = require('../index');

[
  { type: 'string', keys: ['key1', 'key2', 'invalid'] },
  { type: 'int32', keys: [-13, 79, 42] }
].forEach(function (it) {
  var type = it.type;
  var keys = it.keys;
  var key1 = it.keys[0];
  var key2 = it.keys[1];
  var missing = it.keys[2];

  suite('hashset-' + type, function() {
    var set;

    setup(function() {
      set = new HashSet[type]();
    });

    test('add(), contains()', function () {
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

    test('iterator()', function () {
      set.add(key1);
      set.add(key2);

      var it = set.iterator();

      assert(it.hasNext());
      assert(keys.indexOf(it.next()) !== -1);

      assert(it.hasNext());
      assert(keys.indexOf(it.next()) !== -1);

      assert(!it.hasNext());
    });
  });
});

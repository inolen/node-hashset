'use strict';

var assert = require('assert');
var HashSet = require('../index');

suite('hashset', function() {
  var set;

  setup(function() {
    set = new HashSet();
  });

  test('add() and contains()', function () {
    set.add('key');
    assert(set.contains('key'));
    assert(!set.contains('invalid'));
  });

  test('size() and clear()', function () {
    assert(set.size() === 0);
    set.add('key');
    assert(set.size() === 1);
    set.clear();
    assert(set.size() === 0);
  });

  test('empty()', function () {
    assert(set.empty());
    set.add('key');
    assert(!set.empty());
  });

  test('remove()', function () {
    set.add('key');
    assert(set.contains('key'));
    set.remove('key');
    assert(!set.contains('key'));
  });
});

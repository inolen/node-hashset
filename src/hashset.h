#ifndef __HashSet_H__
#define __HashSet_H__

#include <node.h>
#include <string>
#include <unordered_set>

class HashSet : public node::ObjectWrap {
 private:
  HashSet();
  ~HashSet();

  std::unordered_set<std::string> set;

  static v8::Handle<v8::Value> New(const v8::Arguments &args);

  static v8::Handle<v8::Value> Add(const v8::Arguments &args);
  static v8::Handle<v8::Value> Clear(const v8::Arguments &args);
  static v8::Handle<v8::Value> Contains(const v8::Arguments &args);
  static v8::Handle<v8::Value> Empty(const v8::Arguments &args);
  static v8::Handle<v8::Value> Remove(const v8::Arguments &args);
  static v8::Handle<v8::Value> Size(const v8::Arguments &args);

 public:
  static void Init(v8::Handle<v8::Object> exports);
};

#endif

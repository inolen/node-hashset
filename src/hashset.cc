#include <iostream>
#include <sstream>
#include <node.h>
#include <node_internals.h>
#include "HashSet.h"

using namespace v8;
using namespace node;

HashSet::HashSet() {
}

HashSet::~HashSet() {
}

Handle<Value> HashSet::New(const Arguments& args) {
  HashSet *obj = new HashSet();
  obj->Wrap(args.This());
  return args.This();
}

Handle<Value> HashSet::Add(const Arguments &args) {
  HandleScope scope;
  HashSet *obj = ObjectWrap::Unwrap<HashSet>(args.This());

  if (args.Length() < 1 || !args[0]->IsString()) {
    std::ostringstream err;
    err << "Argument 0 must be a string";
    return ThrowTypeError(err.str().c_str());
  }

  Local<String> keyLocal = Local<String>::Cast(args[0]);
  String::AsciiValue keyAscii(keyLocal);

  obj->set.insert(*keyAscii);

  return scope.Close(Undefined());
}

Handle<Value> HashSet::Clear(const Arguments &args) {
  HandleScope scope;
  HashSet *obj = ObjectWrap::Unwrap<HashSet>(args.This());

  obj->set.clear();

  return scope.Close(Undefined());
}

Handle<Value> HashSet::Contains(const Arguments &args) {
  HandleScope scope;
  HashSet *obj = ObjectWrap::Unwrap<HashSet>(args.This());

  if (args.Length() < 1 || !args[0]->IsString()) {
    std::ostringstream err;
    err << "Argument 0 must be a string";
    return ThrowTypeError(err.str().c_str());
  }

  Local<String> keyLocal = Local<String>::Cast(args[0]);
  String::AsciiValue keyAscii(keyLocal);
  std::string key = *keyAscii;

  return scope.Close(Boolean::New(obj->set.count(key) > 0));
}

Handle<Value> HashSet::Empty(const Arguments &args) {
  HandleScope scope;
  HashSet *obj = ObjectWrap::Unwrap<HashSet>(args.This());

  return scope.Close(Boolean::New(obj->set.empty()));
}

Handle<Value> HashSet::Remove(const Arguments &args) {
  HandleScope scope;
  HashSet *obj = ObjectWrap::Unwrap<HashSet>(args.This());

  if (args.Length() < 1 || !args[0]->IsString()) {
    std::ostringstream err;
    err << "Argument 0 must be a string";
    return ThrowTypeError(err.str().c_str());
  }

  Local<String> keyLocal = Local<String>::Cast(args[0]);
  String::AsciiValue keyAscii(keyLocal);
  std::string key = *keyAscii;

  obj->set.erase(key);

  return scope.Close(Undefined());
}

Handle<Value> HashSet::Size(const Arguments &args) {
  HandleScope scope;
  HashSet *obj = ObjectWrap::Unwrap<HashSet>(args.This());

  return scope.Close(Number::New(obj->set.size()));
}

void HashSet::Init(Handle<Object> exports) {
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("HashSet"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  auto prototype = tpl->PrototypeTemplate();
  prototype->Set("add", FunctionTemplate::New(Add)->GetFunction());
  prototype->Set("clear", FunctionTemplate::New(Clear)->GetFunction());
  prototype->Set("contains", FunctionTemplate::New(Contains)->GetFunction());
  prototype->Set("empty", FunctionTemplate::New(Empty)->GetFunction());
  prototype->Set("remove", FunctionTemplate::New(Remove)->GetFunction());
  prototype->Set("size", FunctionTemplate::New(Size)->GetFunction());

  exports->Set(String::NewSymbol("HashSet"), Persistent<Function>::New(tpl->GetFunction()));
}

#ifndef __HASHSET_H__
#define __HASHSET_H__

#include <node.h>
#include <node_internals.h>
#include <v8.h>
#include <unordered_set>

template <typename T>
class HashSet : public node::ObjectWrap {
private:
	std::unordered_set<T> set;

	static v8::Handle<v8::Value> New(const v8::Arguments &args) {
		HashSet *obj = new HashSet();
		obj->Wrap(args.This());
		return args.This();
	}

	static v8::Handle<v8::Value> Add(const v8::Arguments &args);
	static v8::Handle<v8::Value> Contains(const v8::Arguments &args);
	static v8::Handle<v8::Value> Remove(const v8::Arguments &args);

	static v8::Handle<v8::Value> Clear(const v8::Arguments &args) {
		v8::HandleScope scope;
		HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

		obj->set.clear();

		return scope.Close(v8::Undefined());
	}

	static v8::Handle<v8::Value> Empty(const v8::Arguments &args) {
		v8::HandleScope scope;
		HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

		return scope.Close(v8::Boolean::New(obj->set.empty()));
	}

	static v8::Handle<v8::Value> Size(const v8::Arguments &args) {
		v8::HandleScope scope;
		HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

		return scope.Close(v8::Number::New(obj->set.size()));
	}

public:
	static v8::Persistent<v8::Value> Init() {
		v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
		tpl->SetClassName(v8::String::NewSymbol("HashSet"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		auto prototype = tpl->PrototypeTemplate();
		prototype->Set("add", v8::FunctionTemplate::New(Add)->GetFunction());
		prototype->Set("clear", v8::FunctionTemplate::New(Clear)->GetFunction());
		prototype->Set("contains", v8::FunctionTemplate::New(Contains)->GetFunction());
		prototype->Set("empty", v8::FunctionTemplate::New(Empty)->GetFunction());
		prototype->Set("remove", v8::FunctionTemplate::New(Remove)->GetFunction());
		prototype->Set("size", v8::FunctionTemplate::New(Size)->GetFunction());

		return v8::Persistent<v8::Function>::New(tpl->GetFunction());
	}
};

// int32_t specialization
template <>
v8::Handle<v8::Value> HashSet<int32_t>::Add(const v8::Arguments &args) {
	v8::HandleScope scope;
	HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

	if (!args[0]->IsInt32()) {
		return node::ThrowTypeError("argument 0 must be an integer");
	}

	int32_t key = args[0]->Int32Value();

	obj->set.insert(key);

	return scope.Close(v8::Undefined());
}

template <>
v8::Handle<v8::Value> HashSet<int32_t>::Contains(const v8::Arguments &args) {
	v8::HandleScope scope;
	HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

	if (!args[0]->IsInt32()) {
		return node::ThrowTypeError("argument 0 must be an integer");
	}

	int32_t key = args[0]->Int32Value();

	return scope.Close(v8::Boolean::New(obj->set.count(key) > 0));
}

template <>
v8::Handle<v8::Value> HashSet<int32_t>::Remove(const v8::Arguments &args) {
	v8::HandleScope scope;
	HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

	if (!args[0]->IsInt32()) {
		return node::ThrowTypeError("argument 0 must be an integer");
	}

	int32_t key = args[0]->Int32Value();

	obj->set.erase(key);

	return scope.Close(v8::Undefined());
}

// std::string specialization
template <>
v8::Handle<v8::Value> HashSet<std::string>::Add(const v8::Arguments &args) {
	v8::HandleScope scope;
	HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

	if (!args[0]->IsString()) {
		return node::ThrowTypeError("argument 0 must be a string");
	}

	v8::Local<v8::String> keyLocal = v8::Local<v8::String>::Cast(args[0]);
	v8::String::Utf8Value keyUtf(keyLocal);
	std::string key = *keyUtf;

	obj->set.insert(key);

	return scope.Close(v8::Undefined());
}

template <>
v8::Handle<v8::Value> HashSet<std::string>::Contains(const v8::Arguments &args) {
	v8::HandleScope scope;
	HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

	if (!args[0]->IsString()) {
		return node::ThrowTypeError("argument 0 must be a string");
	}

	v8::Local<v8::String> keyLocal = v8::Local<v8::String>::Cast(args[0]);
	v8::String::Utf8Value keyUtf(keyLocal);
	std::string key = *keyUtf;

	return scope.Close(v8::Boolean::New(obj->set.count(key) > 0));
}

template <>
v8::Handle<v8::Value> HashSet<std::string>::Remove(const v8::Arguments &args) {
	v8::HandleScope scope;
	HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

	if (!args[0]->IsString()) {
		return node::ThrowTypeError("argument 0 must be a string");
	}

	v8::Local<v8::String> keyLocal = v8::Local<v8::String>::Cast(args[0]);
	v8::String::Utf8Value keyUtf(keyLocal);
	std::string key = *keyUtf;

	obj->set.erase(key);

	return scope.Close(v8::Undefined());
}

#endif

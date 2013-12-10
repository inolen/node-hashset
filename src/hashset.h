#ifndef __HASHSET_H__
#define __HASHSET_H__

#include <node.h>
#include <node_internals.h>
#include <v8.h>
#include <unordered_set>

template <typename T> bool IsA(const v8::Local<v8::Value> &arg);
template <typename T> T UnwrapValue(const v8::Local<v8::Value> &arg);
template <typename T> v8::Handle<v8::Value> WrapValue(const T &value);

template <typename K>
class HashSet : public node::ObjectWrap {
private:
	std::unordered_set<K> set;

	class It : public node::ObjectWrap {
	private:
		const std::unordered_set<K> *set;
		typename std::unordered_set<K>::const_iterator it;

	public:
		It(const std::unordered_set<K> *set) : set(set) {
			it = set->begin();
		}

		static v8::Handle<v8::Value> New(const std::unordered_set<K> *set) {
			v8::Local<v8::Object> obj = GetCtor()->NewInstance();
			It *it = new It(set);

			it->Wrap(obj);

			return obj;
		}

		static v8::Handle<v8::Value> HasNext(const v8::Arguments &args) {
			v8::HandleScope scope;
			It *obj = node::ObjectWrap::Unwrap<It>(args.This());

			return v8::Boolean::New(obj->it != obj->set->end());
		}

		static v8::Handle<v8::Value> Next(const v8::Arguments &args) {
			v8::HandleScope scope;
			It *obj = node::ObjectWrap::Unwrap<It>(args.This());

			K value = *obj->it;
			obj->it++;

			return WrapValue(value);
		}

		static v8::Persistent<v8::Function> GetCtor() {
			static v8::Persistent<v8::Function> persistentCtor;

			if (persistentCtor.IsEmpty()) {
				auto tpl = v8::FunctionTemplate::New();
				tpl->SetClassName(v8::String::NewSymbol("HashSetIt"));
				tpl->InstanceTemplate()->SetInternalFieldCount(1);

				auto prototype = tpl->PrototypeTemplate();
				prototype->Set("hasNext", v8::FunctionTemplate::New(HasNext)->GetFunction());
				prototype->Set("next", v8::FunctionTemplate::New(Next)->GetFunction());

				persistentCtor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
			}

			return persistentCtor;
		}
	};

	static v8::Handle<v8::Value> New(const v8::Arguments &args) {
		HashSet *obj = new HashSet();

		obj->Wrap(args.This());

		return args.This();
	}

	static v8::Handle<v8::Value> Add(const v8::Arguments &args) {
		v8::HandleScope scope;
		HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

		if (args.Length() < 1 || !IsA<K>(args[0])) {
			return node::ThrowTypeError("invalid type for argument 0");
		}

		K key = UnwrapValue<K>(args[0]);

		obj->set.insert(key);

		return scope.Close(v8::Undefined());
	}

	static v8::Handle<v8::Value> Contains(const v8::Arguments &args) {
		v8::HandleScope scope;
		HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

		if (args.Length() < 1 || !IsA<K>(args[0])) {
			return node::ThrowTypeError("invalid type for argument 0");
		}

		K key = UnwrapValue<K>(args[0]);

		return scope.Close(v8::Boolean::New(obj->set.count(key) > 0));
	}

	static v8::Handle<v8::Value> Remove(const v8::Arguments &args) {
		v8::HandleScope scope;
		HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

		if (args.Length() < 1 || !IsA<K>(args[0])) {
			return node::ThrowTypeError("invalid type for argument 0");
		}

		K key = UnwrapValue<K>(args[0]);

		obj->set.erase(key);

		return scope.Close(v8::Undefined());
	}

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

	static v8::Handle<v8::Value> Iterator(const v8::Arguments &args) {
		v8::HandleScope scope;
		HashSet *obj = node::ObjectWrap::Unwrap<HashSet>(args.This());

		return scope.Close(It::New(&obj->set));
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
		prototype->Set("iterator", v8::FunctionTemplate::New(Iterator)->GetFunction());
		prototype->Set("remove", v8::FunctionTemplate::New(Remove)->GetFunction());
		prototype->Set("size", v8::FunctionTemplate::New(Size)->GetFunction());

		return v8::Persistent<v8::Function>::New(tpl->GetFunction());
	}
};

// int32_t specialization
template <>
bool IsA<int32_t>(const v8::Local<v8::Value> &arg) {
	return arg->IsInt32();
}

template <>
int32_t UnwrapValue<int32_t>(const v8::Local<v8::Value> &arg) {
	return arg->Int32Value();
}

template <>
v8::Handle<v8::Value> WrapValue<int32_t>(const int32_t &value) {
	return v8::Integer::New(value);
}

// std::string specialization
template <>
bool IsA<std::string>(const v8::Local<v8::Value> &arg) {
	return arg->IsString();
}

template <>
std::string UnwrapValue<std::string>(const v8::Local<v8::Value> &arg) {
	v8::Local<v8::String> local = v8::Local<v8::String>::Cast(arg);
	v8::String::Utf8Value utf(local);
	return *utf;
}

template <>
v8::Handle<v8::Value> WrapValue<std::string>(const std::string &value) {
	return v8::String::New(value.c_str());
}

#endif

#include <node.h>
#include <v8.h>
#include <string>
#include "hashset.h"

using namespace v8;

void Init(Handle<Object> exports) {
	exports->Set(String::NewSymbol("int32"), HashSet<int32_t>::Init());
	exports->Set(String::NewSymbol("string"), HashSet<std::string>::Init());
}

NODE_MODULE(addon, Init);

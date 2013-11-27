#include <node.h>
#include <v8.h>
#include "hashset.h"

using namespace v8;

void Init(Handle<Object> exports) {
  HashSet::Init(exports);
}

NODE_MODULE(addon, Init);

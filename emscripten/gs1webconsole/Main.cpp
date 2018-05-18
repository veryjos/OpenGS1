#include <gs1/compiler/CompileVisitor.hpp>
#include <gs1/parse/Parser.hpp>

#include <gs1/vm/Device.hpp>

#include "GFlagLibrary.hpp"
#include "GOutputLibrary.hpp"
#include "GStringLibrary.hpp"
#include "GArrayLibrary.hpp"

#include <iostream>

#include "/usr/lib/emscripten/system/include/emscripten.h"

using namespace gs1;

extern "C" {

char *returnValue;

void free_string() { free(returnValue); }

char *eval_string(char *sourceString)
{
  // Prototypes for commands/functions are necessary for correct parsing
  PrototypeMap cmds = {
      {"message", {true}},
      {"print", {true}},

      {"set", {true}},
      {"unset", {true}},

      {"setstring", {true, true}},
      {"addstring", {true, true}},
  };

  PrototypeMap funcs = {
      {"strtofloat", {true}},
  };

  std::string output;

  Log::Get().SetLogCallback([&](LogLevel logLevel, char *message) {
    switch (logLevel) {
    case LOGLEVEL_ERROR:
    case LOGLEVEL_INFO:
    case LOGLEVEL_WARNING:
      output += message;
      break;

    default:
      break;
    }
  });

  try {
    Device device;

    // Create variable store
    auto primaryVarStore = device.CreateVarStore();

    // Create context
    auto context = device.CreateContext(primaryVarStore);

    // Compile source string to bytecode
    auto bytecodeBytes =
        device.CompileSourceFromString(sourceString, cmds, funcs);

    // Load bytecode to device and link to context
    auto bytecode = device.LoadBytecode(bytecodeBytes.GetBytes(),
                                        bytecodeBytes.GetLength());
    context->LinkBytecode(bytecode);

    // Load and link the flag library (set, unset)
    auto flagLibrary = device.LoadLibrary<GFlagLibrary>();
    context->LinkLibrary(flagLibrary);

    // Load and link the string library (setstring, addstring..)
    auto stringLibrary = device.LoadLibrary<GStringLibrary>();
    context->LinkLibrary(stringLibrary);

    // Load and link the output library (message, print)
    auto outputLibrary = device.LoadLibrary<GOutputLibrary>();
    context->LinkLibrary(outputLibrary);

    // Load and link the array library (arraylen)
    auto arrayLibrary = device.LoadLibrary<GArrayLibrary>();
    context->LinkLibrary(arrayLibrary);

    context->Run();
  }

  catch (Exception &e) {
    output += "Exception:\n%s\n";
    output += e.what();
  }

  returnValue = (char *)malloc(output.length() + 1);
  memcpy(returnValue, output.c_str(), output.length());
  returnValue[output.length()] = '\0';

  return returnValue;
}
}

int main(int argc, const char *argv[]) { return 0; }

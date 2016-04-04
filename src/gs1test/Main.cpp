#include <gs1/compiler/CompileVisitor.hpp>
#include <gs1/parse/Parser.hpp>

#include <gs1/vm/Device.hpp>

#include "GFlagLibrary.hpp"
#include "GStringLibrary.hpp"

using namespace gs1;

int main(int argc, const char *argv[])
{
  // Prototypes for commands/functions are necessary for correct parsing
  PrototypeMap cmds = {
      {"setarray", {false, false}},
      {"freezeplayer", {false}},
      {"hideplayer", {false}},
      {"addstring", {false, true}},
      {"showimg", {false, true, false, false}},
      {"changeimgcolors", {false, false, false, false, false}},
      {"addstring", {false, true}},
      {"hideimg", {false}},
      {"showtext", {false, false, false, true, true, true}},
      {"play", {true}},
      {"stopmidi", {}},
      {"changeimgvis", {false, false}},
      {"debug", {false}},
      {"debugstr", {true}},
      {"setplayerprop", {true, true}},

      {"set", {true}},
      {"unset", {true}},

      {"setstring", {true, true}},
      {"addstring", {true, true}},
  };

  PrototypeMap funcs = {
      {"strtofloat", {true}},
  };

  try {
    const char *path;
    if (argc > 1)
      path = argv[1];
    else
      path = "../example/test.gs";

    Device device;

    // Create variable store
    auto primaryVarStore = device.CreateVarStore();

    // Create context
    auto context = device.CreateContext(primaryVarStore);

    // Compile source file to bytecode
    auto bytecodeBytes = device.CompileSourceFromFile(path, cmds, funcs);

    // Load bytecode to device and link to context
    auto bytecode = device.LoadBytecode(bytecodeBytes.GetBytes(),
                                        bytecodeBytes.GetLength());
    context->LinkBytecode(bytecode);

    // Create "this." varstore for context-local variables
    auto thisVarStore = device.CreateVarStore();
    context->LinkVarStore(thisVarStore, "this.");

    // Load and link the flag library (set, unset)
    auto flagLibrary = device.LoadLibrary<GFlagLibrary>();
    context->LinkLibrary(flagLibrary);

    // Load and link the string library (setstring, addstring..)
    auto stringLibrary = device.LoadLibrary<GStringLibrary>();
    context->LinkLibrary(stringLibrary);

    // Set event flags for running the context
    GVarStore eventflags;
    eventflags.SetValue("created", GVARTYPE_FLAG, true);

    context->Run(&eventflags);
  }

  catch (Exception &e) {
    printf("Exception:\n%s\n", e.what());
  }

  return 0;
}

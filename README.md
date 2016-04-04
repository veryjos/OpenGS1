# OpenGS1

OpenGS1 is a C++11-based lexer, parser, compiler, and VM for GraalScript 1 (MIT license)

GraalScript 1, or GS1, is the original scripting language that powers [Graal Online](http://graalonline.com/). This is a reverse engineering and reimplementation project in an effort to archive the hundreds of legacy Graal Online servers and dozens of thousands of scripts that have since been abandoned and are no longer supported in the official client. See [Graal Reborn](http://www.graal.in/).

#### Basic Example:

```c++
#include <gs1/vm/Device.hpp>

#include "GFlagLibrary.hpp"
#include "GStringLibrary.hpp"

using namespace gs1;

int main(int argc, const char *argv[])
{
  // Prototypes for commands/functions are necessary for correct parsing
  PrototypeMap cmds = {
      {"set", {true}},
      {"unset", {true}},

      {"setstring", {true, true}},
      {"addstring", {true, true}},
  };

  PrototypeMap funcs = {
      {"strtofloat", {true}},
  };

  try {
    Device device;

    // Create variable store
    auto primaryVarStore = device.CreateVarStore();

    // Create context with the primary var store we created earlier
    auto context = device.CreateContext(primaryVarStore);

    // Compile source file to bytecode
    auto bytecodeBytes = device.CompileSourceFromString(
	"if (created) { \
		setstring foo, bar; \
	}",
	cmds, funcs
    );

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

    // Get and print the string that we set in GS1
    std::string fooValue = ((GStringVariable*)primaryVarStore->GetVariable("foo", GVARTYPE_STRING))->string;

    printf("Foo: %s\n", fooValue.c_str());
  }

  catch (Exception &e) {
    printf("Exception:\n%s\n", e.what());
  }

  return 0;
}

```

OpenGS1 currently implements the majority of the GS1 language but is missing some features:

#### Implemented Features:

* Literals (dec hex bin str list)
* Math Operators (+ -/*^%)
* Comparison (< <= > >=)
* Binary Logical (\|\| && == !=)
* Unary Logical (!)
* Ternary Operator (? :)
* Postcrement (++ --)
* If-else-statement
* For loop
* While loop
* Dot-operator ID's (this., level., etc)
* Command calls
* Builtin Function calls
* Array Getter/Setter

#### Incomplete Implementation

* Array Objects (player[]., npcs[]., etc) - Bytecode is generated, no VM support
* Function Definitions - No bytecode generation or VM support, lexer/parser only

#### String Interpolators:

* #v: Partial, No expression parsing, just variable lookup
* #s: Fully supported
* #e: Fully supported

These are the only built-in interpolators planned to be supported. Other interpolators should be client-defined using the interpolator callback.

#### Building:

OpenGS1 currently has no dependencies. Simply build with CMake.

Special thanks to [Daniel Lindberg](https://github.com/dajoh) for bootstrapping the lexer and parser.

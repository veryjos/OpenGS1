#include "GFlagLibrary.hpp"
#include "GStringLibrary.hpp"
#include <gs1/compiler/CompileVisitor.hpp>
#include <gs1/parse/Parser.hpp>

#include <gs1/vm/Device.hpp>

using namespace gs1;

void observer(const Diag &d)
{
  switch (d.severity) {
  case Diag::Info:
    printf("info: %d@%d: %s\n", d.pos.line + 1, d.pos.offset,
           d.message.c_str());
    break;
  case Diag::Warning:
    printf("warning: %d@%d: %s\n", d.pos.line + 1, d.pos.offset,
           d.message.c_str());
    break;
  case Diag::Error:
    printf("error: %d@%d: %s\n", d.pos.line + 1, d.pos.offset,
           d.message.c_str());
    break;
  }
}

int main(int argc, const char *argv[])
{
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

  PrototypeMap funs = {
      {"strtofloat", {true}},
  };

  try {
    const char *path;
    if (argc > 1)
      path = argv[1];
    else
      path = "../example/test.gs";

    FileSource source(path);
    DiagBuilder diag(observer);
    CompileVisitor visitor(source);
    Lexer lexer(diag, source);
    Parser parser(diag, lexer, cmds, funs);

    auto tree = parser.Parse();
    tree->Accept(&visitor);
    ByteBuffer bytecodeBytes = visitor.GetBytecode();

    Device device;

    auto flagLibrary = device.LoadLibrary<GFlagLibrary>();
    auto stringLibrary = device.LoadLibrary<GStringLibrary>();

    auto primaryVarStore = device.CreateVarStore();
    auto context = device.CreateContext(primaryVarStore);

    auto bytecode = device.LoadBytecode(bytecodeBytes.GetBytes(),
                                        bytecodeBytes.GetLength());
    context->LinkBytecode(bytecode);

    auto thisVarStore = device.CreateVarStore();
    context->LinkVarStore(thisVarStore, "this.");

    context->LinkLibrary(flagLibrary);
    context->LinkLibrary(stringLibrary);

    GVarStore eventflags;
    eventflags.SetValue("created", GVARTYPE_FLAG, true);

    context->Run(&eventflags);
  }

  catch (Exception &e) {
    printf("Exception:\n%s\n", e.what());
  }

  return 0;
}

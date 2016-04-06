#include <gs1/vm/Context.hpp>

namespace gs1
{
class GStringLibrary : public GLibrary
{
public:
  GStringLibrary()
  {

    RegisterCommand("setstring", [&](Context *context) {
      std::string strValue =
          context->InterpolateString(context->stack.Pop().GetString());
      std::string strName = context->stack.Pop().GetString();

      context->SetVariable(strName, GVARTYPE_STRING, GStringVariable(strValue));

      printf("setstring %s=%s\n", strName.c_str(), strValue.c_str());
    });

    RegisterCommand("addstring", [&](Context *context) {
      std::string strValue =
          context->InterpolateString(context->stack.Pop().GetString());
      std::string strName = context->stack.Pop().GetString();

      GStringVariable *strVariable =
          (GStringVariable *)context->GetVariable(strName, GVARTYPE_STRING);

      if (strVariable == nullptr) {
        context->SetVariable(strName, GVARTYPE_STRING,
                             GStringVariable(strValue));

        printf("addstring %s=%s\n", strName.c_str(), strValue.c_str());
      } else {
        context->SetVariable(strName, GVARTYPE_STRING,
                             GStringVariable(strVariable->string + strValue));

        printf("addstring %s=%s\n", strName.c_str(),
               (strVariable->string + strValue).c_str());
      }
    });

    RegisterFunction("strtofloat", [&](Context *context) {
      std::string strValue =
          context->InterpolateString(context->stack.Pop().GetString());

      try {
        context->stack.Push(std::stof(strValue));
      }

      catch (...) {
        context->stack.Push(0.0f);
      }
    });
  };

  ~GStringLibrary(){};

  static std::string GetName() { return "GStringLibrary"; }
};
};
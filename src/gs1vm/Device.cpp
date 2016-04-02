#include <gs1/vm/Device.hpp>

using namespace gs1;

Device::Device() {}

Device::~Device() {}

std::shared_ptr<Context>
Device::CreateContext(std::shared_ptr<GVarStore> primaryVarStore)
{
  return std::make_shared<Context>(this, primaryVarStore);
}

std::shared_ptr<GVarStore> Device::CreateVarStore()
{
  return std::make_shared<GVarStore>();
}

std::shared_ptr<Bytecode> Device::LoadBytecode(const char *data,
                                               unsigned int length)
{
  return std::make_shared<Bytecode>(data, length);
}
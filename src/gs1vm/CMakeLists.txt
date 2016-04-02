add_library(
        gs1vm
        Device.cpp                  ../../include/gs1/vm/Device.hpp
        Context.cpp                 ../../include/gs1/vm/Context.hpp
        GVarStore.cpp               ../../include/gs1/vm/GVarStore.hpp
        OperationDispatcher.cpp     ../../include/gs1/vm/OperationDispatcher.hpp
        Bytecode.cpp                ../../include/gs1/vm/Bytecode.hpp
        GLibrary.cpp                ../../include/gs1/vm/GLibrary.hpp
        GStringFormatter.cpp        ../../include/gs1/vm/GStringFormatter.hpp
        ../../include/gs1/vm/Stack.hpp
)

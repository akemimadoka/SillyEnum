add_executable(SillyEnum.Test Main.cpp Tests.cpp)

target_link_libraries(SillyEnum.Test PRIVATE
    SillyEnum CONAN_PKG::Catch2)

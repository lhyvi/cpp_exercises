# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(gallowTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(gallow_test source/gallow_test.cpp)
target_link_libraries(
    gallow_test PRIVATE
    gallow_lib
    Catch2::Catch2WithMain
)
target_compile_features(gallow_test PRIVATE cxx_std_17)

catch_discover_tests(gallow_test)

# ---- End-of-file commands ----

add_folders(Test)

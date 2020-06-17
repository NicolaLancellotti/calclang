add_executable(calclang main.cpp)

target_include_directories(calclang PUBLIC ${Headers}/Driver)

target_link_libraries(calclang PUBLIC
        calclangBasic
        calclangDriver
        calclangParseLex
        calclangSema
        calclangAST
        calclangEvaluator
        calclangASTDump
)



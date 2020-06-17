set(LibHeaders ${Headers}/Basic)

add_library(calclangBasic STATIC
        ${LibHeaders}/Unreachable.h
        ${LibHeaders}/PrettyPrint.h
        PrettyPrint.cpp
        ${LibHeaders}/Error.h
        Error.cpp
        ${LibHeaders}/Action.h
        Action.cpp
        ${LibHeaders}/InputStream.h
        ${LibHeaders}/OutputStream.h
)

target_include_directories(calclangBasic PUBLIC
        ${LibHeaders}
        ${Headers}/ParseLex
)

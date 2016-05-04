cmake_minimum_required(VERSION 3.3)
project(MTProject)

find_program(LLVM_CONFIG NAMES llvm-config-3.5 /usr/bin)

if(NOT EXISTS ${LLVM_CONFIG})
    message(FATAL_ERROR ${LLVM_CONFIG})
endif()

execute_process(COMMAND ${LLVM_CONFIG} --cppflags
        OUTPUT_VARIABLE LLVM_FLAGS)

execute_process(COMMAND ${LLVM_CONFIG} --ldflags
        OUTPUT_STRIP_TRAILING_WHITESPACE
        OUTPUT_VARIABLE LLVM_LD_FLAGS)

execute_process(COMMAND ${LLVM_CONFIG} --libs engine jit
        OUTPUT_STRIP_TRAILING_WHITESPACE
        OUTPUT_VARIABLE LLVM_EXECENGINE_LD_FLAGS)

execute_process(COMMAND ${LLVM_CONFIG} --libs
        OUTPUT_STRIP_TRAILING_WHITESPACE
        OUTPUT_VARIABLE LLVM_LIBS)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_LINKER llvm-link)
add_definitions("${LLVM_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Tokens.h Scanner.cpp Scanner.h AST/ExprAST.cpp AST/ExprAST.h AST/NumberExprAST.cpp AST/NumberExprAST.h AST/VariableExprAST.cpp AST/VariableExprAST.h AST/CallExprAST.cpp AST/CallExprAST.h AST/PrototypeAST.cpp AST/PrototypeAST.h AST/FunctionAST.cpp AST/FunctionAST.h Parser.cpp Parser.h AST/BinaryExprAST.cpp AST/BinaryExprAST.h AST/IdentifierExprAST.cpp AST/IdentifierExprAST.h Emit.cpp Emit.h AST/PrintExprAST.cpp AST/PrintExprAST.h AST/ReturnExprAST.cpp AST/ReturnExprAST.h AST/WhileExprAST.cpp AST/WhileExprAST.h AST/IfExprAST.cpp AST/IfExprAST.h)
add_executable(MTProject ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LLVM_LD_FLAGS} ${LLVM_LIBS} ${LLVM_EXECENGINE_LD_FLAGS} -lpthread -ldl -ltinfo -lz)

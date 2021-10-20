#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<"ADD 2\n"
                  "ADD 3\n"
                  "ADD 2\n"
                  "SEARCH 2\n"
                  "ADD 5\n"
                  "PRINTTREE\n"
                  "SEARCH 7";
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();
    
    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str() == "DONE\n"
                            "DONE\n"
                            "ALREADY\n"
                            "YES\n"
                            "DONE\n"
                            "2\n"
                            ".3\n"
                            "..5\n"
                            "NO\n");
}

TEST_CASE("both trees", ""){
    std::stringstream input, output;
    input<<"ADD 0\n"
           "ADD -1\n"
           "ADD 1\n"
           "ADD 1\n"
           "SEARCH 2\n"
           "SEARCH 0\n"
           "SEARCH -1\n"
           "SEARCH 1\n"
           "PRINTTREE\n";
    parseFile(input,output);
    REQUIRE(output.str() ==
            "DONE\n"
            "DONE\n"
            "DONE\n"
            "ALREADY\n"
            "NO\n"
            "YES\n"
            "YES\n"
            "YES\n"
            ".-1\n"
            "0\n"
            ".1\n");
}

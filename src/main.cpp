
#include "iolib.hpp"

#include <iostream>

void test_extract_tok_XL();
void test_extract_tok_X();
void test_extract_tok();

int main()
{
    test_extract_tok_XL();
    test_extract_tok_X();
    test_extract_tok();



}

void test_extract_tok_XL()
{
    std::string text = {".abI.have.abseen--things.you--wouldn't.believe.ab"};
    std::string tokens[3] = {".ab", ".", "--"};
    std::vector<std::string> result(0);

    extract_tok_XL(result, text, tokens, 3, true);
    for(size_t i = 0; i < result.size(); ++i) std::cout << result[i] << ' ';
    std::cout << std::endl;
}

void test_extract_tok_X()
{
    std::string text = {"XYZTheXYZanswer toXYZlife, theXYZuniverse,XYZandXYZeverythingXYZ"};
    std::string token = "XYZ";
    std::vector<std::string> result(0);

    extract_tok_X(result, text, token);
    for(size_t i = 0; i < result.size(); ++i) std::cout << result[i] << ' ';
    std::cout << std::endl;
}

void test_extract_tok()
{
    std::string str = ",221,,B,Baker,,street,";
    std::vector<std::string> result(0);

    extract_tok(result, str, ',');
    for(size_t i = 0; i < result.size(); ++i) std::cout << result[i] << ' ';
    std::cout << std::endl;
}












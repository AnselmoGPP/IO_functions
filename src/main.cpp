
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
    std::string text = {".abNow.split.abthis--if.you--can.ab"};
    std::string tokens[3] = {".ab", ".", "--"};
    std::vector<std::string> result(0);

    result = extract_tok_XL(text, tokens, 3, true);
    for(int i = 0; i < result.size(); ++i) std::cout << result[i] << ' ';
    std::cout << std::endl;
}

void test_extract_tok_X()
{

}

void test_extract_tok()
{
    std::string str = ",221,B,Baker,street,";
    std::vector<std::string> result;

    result = extract_tok(str, ',');
    for(int i = 0; i < result.size(); ++i) std::cout << result[i] << ' ';
    std::cout << std::endl;
}












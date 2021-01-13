/*
 * Origin at upper left corner of the screen
 * Bounding boxes coordinates: x (upper left), y (upper left), x2 (lower right), y2 (lower right)
 * ROI: x (upper left), y (upper left), width (to the right), height (downwards)
 */

#ifndef IOLIB_HPP
#define IOLIB_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include <iterator>
//#include <array>
#include <fstream>
#include <sstream>

// Declarations ---------------------------------------------------------------

// Given a string (text), extract all the substrings that exist between certain tokens (tokens) (one char size or bigger)
void extract_tok_XL(std::vector<std::string> &result, const std::string &text, std::string *tokens, unsigned long num_tokens, bool sort_tokens);

// Given a string, extract all the substrings that exist between certain token (one char size or bigger)
void extract_tok_X(std::vector<std::string> &result, const std::string &text, const std::string &token);

// Given a string, extract all the substrings that exist between certain token (one char size)
void extract_tok(std::vector<std::string> &result, const std::string &text, char token);

// Given a number, extract its digits and return them in a vector
std::vector<unsigned int> extract_digits(unsigned int n);

// Extract all the data from a file to a string
void extract_file(std::string &result, std::string &path);

// Extract all the data from a file to a vector<string>, where each string is a line (\n)
void extract_file_lines(std::vector<std::string> &result, std::string &path);


// Definitions ----------------------------------------------------------------

bool is_bigger(const std::string &a, const std::string &b) { return a.size() > b.size(); }

struct { bool operator()(const std::string a, const std::string b) { return a.size() > b.size(); } } customBigger;

void extract_tok_XL(std::vector<std::string> &result, const std::string &text, std::string *tokens, unsigned long num_tokens, bool sort_tokens = false)
{
    // The tokens list should be ordered in descending order (for checking firt the longer tokens and avoid mistakes between similar tokens)
    if(sort_tokens)     // 3 ways of sorting
    {
        //std::sort(tokensX, tokensX + num_tokens, is_bigger);
        //std::sort(tokensX, tokensX + num_tokens, customBigger);
        std::sort(tokens, tokens + num_tokens, [](const std::string a, const std::string b) { return a.size() > b.size(); });
    }

    std::string found_str;
    int first_pos = 0;

    for(size_t i = 0; i < text.size(); ++i)                 // For each text character
    {
        for(size_t j = 0; j < num_tokens; ++j)              // For each token
        {
            // Check end of text
            if(tokens[j].size() > text.size() - i) continue;

            // We have a token identification
            if( tokens[j] == text.substr(i, tokens[j].size()) )
            {
                found_str = text.substr(first_pos, i - first_pos);
                if(found_str.size() > 0) result.push_back(found_str);
                first_pos = i + tokens[j].size();
                i += (tokens[j].size() - 1);
                break;
            }
        }
    }

    // Check last string (when the tokens are larger than the text remaining)
    if((text.size() - first_pos) > 0) result.push_back(text.substr(first_pos, text.size()));
}

void extract_tok_X(std::vector<std::string> &result, const std::string &text, const std::string &token)
{
    std::string found_str;
    int first_pos = 0;

    for(size_t i = 0; i < text.size(); ++i)
    {
        if(token.size() > text.size() - i) break;

        if( token == text.substr(i, token.size()) )
        {
            found_str = text.substr(first_pos, i - first_pos);
            if(found_str.size() > 0) result.push_back(found_str);
            first_pos = i + token.size();
            i += (token.size() - 1);
            continue;
        }
    }

    if((text.size() - first_pos) > 0) result.push_back(text.substr(first_pos, text.size()));
}

void extract_tok(std::vector<std::string> &result, const std::string &text, char token)
{
    std::string found_str;
    int first_pos = 0;

    for(size_t i = 0; i < text.size(); ++i)
    {
        if( text[i] == token )
        {
            found_str = text.substr(first_pos, i - first_pos);
            if(found_str.size() > 0) result.push_back(found_str);
            first_pos = i + 1;
            continue;
        }
    }

    if((text.size() - first_pos) > 0) result.push_back(text.substr(first_pos, text.size()));
}

std::vector<unsigned int> extract_digits(unsigned int n)
{
    std::vector<unsigned int> result;

    do
    {
        result.push_back(n % 10);
        n /= 10;
    }
    while (n > 0);

    return result;
}

void extract_file(std::string &result, std::string &path)
{
    std::ifstream ifile(path);

    if(ifile.is_open())
    {
        std::stringstream sstr;
        sstr << ifile.rdbuf();
        result = sstr.str();
        ifile.close();
    }
    else std::cout << "Cannot open file " << path << std::endl;
}

void extract_file_lines(std::vector<std::string> &result, std::string &path)
{
    std::ifstream ifile(path);

    if(ifile.is_open())
    {
        std::string line;
        while(std::getline(ifile, line))
            result.push_back(line);

        ifile.close();
    }
    else std::cout << "Cannot open file " << path << std::endl;
}

std::string getCurrentDirectory(){

    std::string dir = "";

    #if defined(_WIN64) || (_WIN32)
	dir = system("cd");
    
    #elif __unix__
        dir = system("pwd");
	std::string test = dir.substr(0, dir.size() - 10);
	dir = test;
	//std::cout << dir.substr(0, dir.size() - 10) << std::endl;
	//std::cout << dir.size() << std::endl;
    #endif

    return dir;
}

#endif


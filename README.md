# iolib

Simple library with useful functions for I/O operations and parsing.

- Parsing functions:

// Given a string (text), extract all the substrings that exist between certain tokens (tokens) (one char size or bigger)
std::vector<std::string> extract_tok_XL(std::string &text, const std::string *tokens, int num_tokens, bool sort_tokens);

// Given a string, extract all the substrings that exist between certain token (one char size or bigger)
std::vector<std::string> extract_tok_X(std::string &text, const std::string *tokens);

// Given a string, extract all the substrings that exist between certain token (one char size)
std::vector<std::string> extract_tok(std::string &text, char token);

- I/O functions:

// Extract all the data from a file to a string
std::string extract_file(std::string &text);

// Extract all the data from a file to a vector<string>, where each string is a line (\n)
std::string extract_file_lines(std::string &text);

/*
 * Origin at upper left corner of the screen
 * Bounding boxes coordinates: x (upper left), y (upper left), x2 (lower right), y2 (lower right)
 * ROI: x (upper left), y (upper left), width (to the right), height (downwards)
 */

#ifndef IOLIB_HPP
#define IOLIB_HPP

#include <iostream>
//#include <fstream>
#include <string>
//#include <sstream>
#include <vector>
//#include <iterator>
#include <algorithm>
//#include <array>

// Declarations ---------------------------------------------------------------

// Given a string (text), extract all the substrings that exist between certain tokens (tokens) (one char size or bigger)
std::vector<std::string> extract_tok_XL(std::string &text, const std::string *tokens, int num_tokens, bool sort_tokens);

// Given a string, extract all the substrings that exist between certain token (one char size or bigger)
std::vector<std::string> extract_tok_X(std::string &text, const std::string *tokens);

// Given a string, extract all the substrings that exist between certain token (one char size)
std::vector<std::string> extract_tok(std::string &text, char token);


// Extract all the data from a file to a string
std::string extract_file(std::string &text);

// Extract all the data from a file to a vector<string>, where each string is a line (\n)
std::string extract_file_lines(std::string &text);


// Definitions ----------------------------------------------------------------

bool is_bigger(const std::string &a, const std::string &b) { return a.size() > b.size(); }

struct {
    bool operator()(const std::string a, const std::string b) { return a.size() > b.size(); }
} customMore;

std::vector<std::string> extract_tok_XL(std::string &text, std::string *tokens, int num_tokens, bool sort_tokens = false)
{
    // The tokens list should be ordered in descending order (for checking firt the longer tokens and avoid mistakes between similar tokens)
    if(sort_tokens)     // 3 ways of sorting
    {
        //std::sort(tokensX, tokensX + num_tokens, is_bigger);
        //std::sort(tokensX, tokensX + num_tokens, customMore);
        std::sort(tokens, tokens + num_tokens, [](const std::string a, const std::string b) { return a.size() > b.size(); });
    }

    std::vector<std::string> substrings;
    std::string found_str;
    int first_pos = 0;

    for(int i = 0; i < text.size(); ++i)                    // For each text character
    {
        for(size_t j = 0; j < num_tokens; ++j)              // For each token
        {
            // Check end of text
            if(tokens[j].size() > text.size() - i) continue;

            // We have a token identification
            if( tokens[j] == text.substr(i, tokens[j].size()) )
            {
                found_str = text.substr(first_pos, i - first_pos);
                if(found_str.size() > 0) substrings.push_back(found_str);
                first_pos = i + tokens[j].size();
                i += (tokens[j].size() - 1);
                break;
            }
        }
    }

    // Check last string (when the tokens are larger than the text remaining)
    if((text.size() - first_pos) > 0) substrings.push_back(text.substr(first_pos, text.size()));

    return substrings;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
std::vector<std::string> extract_tok_X(std::string &text, const std::string *tokens)
{
    std::vector<std::string> substrings;
    /*
    std::string found_str;
    int first_pos = 0;

    for(int i = 0; i < text.size(); ++i)                            // For each text character
    {
        for(size_t j = 0; j < num_tokens; ++j)                      // For each token
        {
            // Check end of text
            if(tokens[j].size() > text.size() - i) continue;

            // We have a token identification
            if( tokens[j] == text.substr(i, tokens[j].size()) )
            {
                found_str = text.substr(first_pos, i - first_pos);
                if(found_str.size() > 0) substrings.push_back(found_str);
                first_pos = i + tokens[j].size();
                i += (tokens[j].size() - 1);
                break;
            }
        }
    }

    // Check last string (when the tokens are larger than the text remaining)
    if((text.size() - first_pos) > 0) substrings.push_back(text.substr(first_pos, text.size()));
*/
    return substrings;
}

std::vector<std::string> extract_tok(std::string &text, char token)
{
    std::vector<std::string> substrings;
    std::string found_str;
    int first_pos = 0;

    for(int i = 0; i < text.size(); ++i)
    {
        if( text[i] == token )
        {
            found_str = text.substr(first_pos, i - first_pos);
            if(found_str.size() > 0) substrings.push_back(found_str);
            first_pos = i + 1;
            continue;
        }
    }

    if((text.size() - first_pos) > 0) substrings.push_back(text.substr(first_pos, text.size()));

    return substrings;
}

std::string extract_file(std::string &text)
{

}

std::string extract_file_lines(std::string &text)
{

}








// Check whether one point (x,y) is inside a box (bx, by, bx2, by2)
bool is_inside(float x, float y, float bx, float by, float bx2, float by2)
{
    if( x > bx  &&  x < bx2  &&  y > by  &&  y < by2 ) return true;
    else return false;
}

/*
int main1()
{
	std::ifstream ROI_file("/opt/samples/04.ROAD/01.ADAS/04.RAW/metrics_detector/metrics_clips_Econsystem_enero2020/Otros/ROIs.txt");
	std::ifstream ifile("/opt/samples/04.ROAD/01.ADAS/04.RAW/metrics_detector/metrics_clips_Econsystem_enero2020/labels_full.json");
	std::ofstream ofile("/opt/samples/04.ROAD/01.ADAS/04.RAW/metrics_detector/metrics_clips_Econsystem_enero2020/labels_ROI.json");

	if(ROI_file.is_open() && ifile.is_open() && ofile.is_open())
	{
        // Get the extracted ROI ----------------------------------
        std::vector<std::vector<int>> ROIs;
        std::string tokens[3] = { " ", "\n", "," };
        std::vector<std::string> temp;

        std::string line;
        while(std::getline(ROI_file, line))
        {
            temp = extract_between_tokens(line, tokens, 2);
            ROIs.push_back( std::vector<int>{stoi(temp[0]), stoi(temp[1]), stoi(temp[2]), stoi(temp[3])} );
        }
        ROI_file.close();
        //std::cout << ROIs.size() << std::endl;
        //for(int i = 0; i < 10; ++i) std::cout << ROIs[i][0] << " " << ROIs[i][1] << " " << ROIs[i][2] << " " << ROIs[i][3] << std::endl;

        // Labels/Predictions -------------------------------------
        int roiIndex = 0;
        float x, y, x2, y2;                         // ROI coordinates
        float bx, by, bx2, by2;                     // Bounding box coordinates
        bool corners_inside_ROI[4] = {0,0,0,0};     // up left, up right, low right, low left
        std::string str_to_output;

        while(std::getline(ifile, line))
        {
            bool is_labels = true;      // <<<<<<<<<<<<<<

            if ((roiIndex + 1) > ROIs.size()) break;
            std::cout << "Progress: " << roiIndex + 1 << " / " << ROIs.size() << '\r';

            std::string regist;
            bool box_outside = false;

            regist.append(line + '\n');
            if(std::getline(ifile, line)) regist.append(line + '\n');

            if(is_labels)
            {
                if (std::getline(ifile, line)) regist.append(line + '\n');
                if (std::getline(ifile, line)) regist.append(line + '\n');
                if (std::getline(ifile, line)) regist.append(line + '\n');
            }

            //if(std::getline(ifile, line)) std::cout << "XXX: " << std::stof(extract_between_tokens(line, tokens, 3)[0]) << std::endl;

            if(std::getline(ifile, line)) x  = std::stof(extract_between_tokens(line, tokens, 3)[0]);
            if(std::getline(ifile, line)) y  = std::stof(extract_between_tokens(line, tokens, 3)[0]);
            if(std::getline(ifile, line)) x2 = std::stof(extract_between_tokens(line, tokens, 3)[0]);
            if(std::getline(ifile, line)) y2 = std::stof(extract_between_tokens(line, tokens, 3)[0]);

            // Check box position with respect to the ROI
            bx  = ROIs[roiIndex][0];
            by  = ROIs[roiIndex][1];
            bx2 = ROIs[roiIndex][0]+ROIs[roiIndex][2];
            by2 = ROIs[roiIndex][1]+ROIs[roiIndex][3];

            corners_inside_ROI[0] = is_inside(bx,  by,  x, y, x2, y2);
            corners_inside_ROI[1] = is_inside(bx2, by,  x, y, x2, y2);
            corners_inside_ROI[2] = is_inside(bx2, by2, x, y, x2, y2);
            corners_inside_ROI[3] = is_inside(bx,  by2, x, y, x2, y2);

            if(corners_inside_ROI[0] && corners_inside_ROI[1] && corners_inside_ROI[2] && corners_inside_ROI[3]) { }
            else if(corners_inside_ROI[0] && corners_inside_ROI[1]) { by2 = y2; }
            else if(corners_inside_ROI[2] && corners_inside_ROI[3]) { by  = y;  }
            else if(corners_inside_ROI[1] && corners_inside_ROI[2]) { bx  = x;  }
            else if(corners_inside_ROI[0] && corners_inside_ROI[3]) { bx2 = x2; }
            else if(corners_inside_ROI[0]) { bx2 = x2;  by2 = y2; }
            else if(corners_inside_ROI[1]) { bx  = x;   by2 = y2; }
            else if(corners_inside_ROI[2]) { bx  = x;   by  = y;  }
            else if(corners_inside_ROI[3]) { bx2 = x2;  by  = y;  }
            else if(bx < x  &&  by < y   &&  bx2 > x   &&  bx2 < x2  &&  by2 > y2) { bx = x;  by  = y;   by2 = y2; }
            else if(bx > x  &&  bx < x2  &&  by < y    &&  bx2 > x2  &&  by2 > y2) { by = y;  bx2 = x2;  by2 = y2; }
            else if(bx < x  &&  by < y   &&  bx2 > x2  &&  by2 > y   &&  by2 < y2) { bx = x;  by  = y;   bx2 = x2; }
            else if(bx < x  &&  by > y   &&  by < y2   &&  bx2 > x2  &&  by2 > y2) { bx = x;  bx2 = x2;  by2 = y2; }
            else if(bx < x  &&  by < y   &&  bx2 > x2  &&  by2 > y2) { bx = x;  by = y;  bx2 = x2;  by2 = y2; }
            else box_outside = true;

            std::string space;
            if(is_labels) space = "            ";
            else space = "        ";

            // Uncomment for labels
            std::stringstream sstream;
            sstream << space << bx  << ",\n"
                    << space << by  << ",\n"
                    << space << bx2 << ",\n"
                    << space << by2 << "\n";
            regist.append(sstream.str());

            if(std::getline(ifile, line)) regist.append(line + '\n');
            if(std::getline(ifile, line)) regist.append(line + '\n');
            if(std::getline(ifile, line)) regist.append(line + '\n');
            if(std::getline(ifile, line)) regist.append(line + '\n');
            if(std::getline(ifile, line)) regist.append(line + '\n');

            if(!box_outside) str_to_output.append(regist);
            roiIndex++;
        }
        ifile.close();
        std::cout << std::endl;

        ofile << str_to_output;
        ofile.close();
	}
    else std::cout << "A file could not be opened" << std::endl;
}
*/
#endif


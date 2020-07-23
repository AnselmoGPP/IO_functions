/*
 * Origin at upper left corner of the screen
 * Bounding boxes coordinates: x (upper left), y (upper left), x2 (lower right), y2 (lower right)
 * ROI: x (upper left), y (upper left), width (to the right), height (downwards)
 */
#include "header.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>

// Given a string ("text"), extract all the substrings that exist between certain tokens ("tokens")
std::vector<std::string> extract_between_tokens(std::string &text, const std::string *tokens, int num_tokens)
{
    //std::sort(tokens, tokens + num_tokens, [](std::string &str_1, std::string &str_2)->bool{return str_1.size() > str_2.size();});
    //for(int i = 0; i < num_tokens; ++i) std::cout << tokens[i] << " ";
    //std::cout << std::endl;

    std::vector<std::string> substrings;
    int first_pos = 0;

    for(int i = 0; i < text.size(); ++i)                            // For each text character
    {
        for(size_t j = 0; j < num_tokens; ++j)                      // For each token
        {
            if(tokens[j].size() > text.size() - i) continue;
            if( tokens[j] == text.substr(i, tokens[j].size()) )     // We have a token identification
            {
                std::string found_str = text.substr(first_pos, i - first_pos);
                if(found_str.size() > 0) substrings.push_back(found_str);
                first_pos = i + tokens[j].size();
                i += (tokens[j].size() - 1);
                break;
            }
        }
    }
    if((text.size() - first_pos) > 0) substrings.push_back(text.substr(first_pos, text.size()));
    return substrings;
}

// Check whether one point (x,y) is inside a box (bx, by, bx2, by2)
bool is_inside(float x, float y, float bx, float by, float bx2, float by2)
{
    if( x > bx  &&  x < bx2  &&  y > by  &&  y < by2 ) return true;
    else return false;
}

int main()
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

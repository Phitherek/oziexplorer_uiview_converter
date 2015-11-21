//
// Created by phitherek on 19.11.15.
//

#include "Converter.h"
#include "ConversionError.h"

#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>

void Converter::convert() {
    if(_infilename == "") {
        throw ConversionError("Input file name cannot be empty!");
    } else if(_outfilename == "") {
        throw ConversionError("Output file name cannot be empty!");
    }
    std::ifstream in(_infilename.c_str());
    if(!in) {
        throw ConversionError("Could not open input file: " + _infilename + "!");
    }
    std::string line = "";
    std::vector<std::string> filecontent;
    while(!in.eof()) {
        char c;
        c = in.get();
        if(in) {
            if(c == '\n' || c == '\r') {
                if(line != "") {
                    filecontent.push_back(line);
                }
                line = "";
            } else {
                line += c;
            }
        }
    }
    in.close();
    std::vector<std::string> convertcontent;
    for(unsigned int i = 0; i < filecontent.size(); i++) {
        if(filecontent[i].find("MMPLL") != std::string::npos) {
            convertcontent.push_back(filecontent[i]);
        }
    }
    filecontent.erase(filecontent.begin(), filecontent.end());
    std::string upperleftlat = "";
    std::string upperleftlon = "";
    std::string lowerrightlat = "";
    std::string lowerrightlon = "";
    std::vector<std::string> brokenline;
    for(unsigned int i = 0; i < convertcontent.size(); i++) {
        std::string tmp = "";
        for(int j = 0; j < convertcontent[i].length(); j++) {
            if(convertcontent[i][j] == ',' && tmp != "") {
                brokenline.push_back(tmp);
                tmp = "";
            } else if(convertcontent[i][j] != ' ' && convertcontent[i][j] != '\n' && convertcontent[i][j] != '\r') {
                tmp += convertcontent[i][j];
            }
        }
        brokenline.push_back(tmp);
        tmp = "";
        if(brokenline.size() == 4) {
            if(brokenline[1][0] == '1') {
                upperleftlon = brokenline[2];
                upperleftlat = brokenline[3];
            } else if(brokenline[1][0] == '3') {
                lowerrightlon = brokenline[2];
                lowerrightlat = brokenline[3];
            }
        }
        brokenline.erase(brokenline.begin(), brokenline.end());
    }
    convertcontent.erase(convertcontent.begin(), convertcontent.end());
    if(upperleftlat == "" || upperleftlon == "" || lowerrightlat == "" || lowerrightlon == "") {
        throw ConversionError("Could not read coordinates from file: " + _infilename + "!");
    }
    double fullat;
    double fullon;
    double flrlat;
    double flrlon;
    fullat = std::atof(upperleftlat.c_str());
    fullon = std::atof(upperleftlon.c_str());
    flrlat = std::atof(lowerrightlat.c_str());
    flrlon = std::atof(lowerrightlon.c_str());
    char fullatdir;
    char fullondir;
    char flrlatdir;
    char flrlondir;
    if(fullat < 0) {
        fullatdir = 'S';
        fullat -= 2*fullat;
    } else {
        fullatdir = 'N';
    }
    if(fullon < 0) {
        fullondir = 'W';
        fullon -= 2*fullon;
    } else {
        fullondir = 'E';
    }
    if(flrlat < 0) {
        flrlatdir = 'S';
        flrlat -= 2*flrlat;
    } else {
        flrlatdir = 'N';
    }
    if(flrlon < 0) {
        flrlondir = 'W';
        flrlon -= 2*flrlon;
    } else {
        flrlondir = 'E';
    }
    int fullat_deg;
    int fullat_min;
    int fullat_sec;
    int fullon_deg;
    int fullon_min;
    int fullon_sec;
    int flrlat_deg;
    int flrlat_min;
    int flrlat_sec;
    int flrlon_deg;
    int flrlon_min;
    int flrlon_sec;
    fullat_deg = static_cast<int>(trunc(fullat));
    fullat_min = static_cast<int>(trunc(fullat*60))%60;
    fullat_sec = static_cast<int>(trunc(fullat*3600))%60;
    fullon_deg = static_cast<int>(trunc(fullon));
    fullon_min = static_cast<int>(trunc(fullon*60))%60;
    fullon_sec = static_cast<int>(trunc(fullon*3600))%60;
    flrlat_deg = static_cast<int>(trunc(flrlat));
    flrlat_min = static_cast<int>(trunc(flrlat*60))%60;
    flrlat_sec = static_cast<int>(trunc(flrlat*3600))%60;
    flrlon_deg = static_cast<int>(trunc(flrlon));
    flrlon_min = static_cast<int>(trunc(flrlon*60))%60;
    flrlon_sec = static_cast<int>(trunc(flrlon*3600))%60;
    std::ofstream out(_outfilename.c_str());
    if(!out) {
        throw ConversionError("Could not open output file: " + _outfilename + "!");
    }
    char buffer[10];
    for(int i = 0; i < 10; i++) {
        buffer[i] = '\000';
    }
    sprintf(buffer, "%02d.%02d.%02d%c", fullat_deg, fullat_min, fullat_sec, fullatdir);
    out << buffer << ", ";
    for(int i = 0; i < 10; i++) {
        buffer[i] = '\000';
    }
    sprintf(buffer, "%03d.%02d.%02d%c", fullon_deg, fullon_min, fullon_sec, fullondir);
    out << buffer << std::endl;
    for(int i = 0; i < 10; i++) {
        buffer[i] = '\000';
    }
    sprintf(buffer, "%02d.%02d.%02d%c", flrlat_deg, flrlat_min, flrlat_sec, flrlatdir);
    out << buffer << ", ";
    for(int i = 0; i < 10; i++) {
        buffer[i] = '\000';
    }
    sprintf(buffer, "%03d.%02d.%02d%c", flrlon_deg, flrlon_min, flrlon_sec, flrlondir);
    out << buffer << std::endl;
    out << "OziExplorer to UI-View(C)SO9PH" << std::endl;
    out.close();
}

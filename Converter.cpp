//
// Created by phitherek on 19.11.15.
//

#include "Converter.h"
#include "ConversionError.h"

#include <fstream>

void Converter::convert() {
    if(_infilename == "") {
        throw ConversionError("Input filename cannot be empty!");
    } else if(_outfilename == "") {
        throw ConversionError("Output filename cannot be empty!");
    }

}

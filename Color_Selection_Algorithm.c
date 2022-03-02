#include "Color_Selection_Algorithm.h"

const int MAX_COLORPAIR_NAME_CHARS = 16;

const char* majorColorNames[] = {"White", "Red", "Black", "Yellow", "Violet"};
const char* minorColorNames[] = {"Blue", "Orange", "Green", "Brown", "Slate"};

int numberOfMajorColors = sizeof(majorColorNames) / sizeof(majorColorNames[0]);
int numberOfMinorColors = sizeof(minorColorNames) / sizeof(minorColorNames[0]);
    
void colorPairToString(const ColorPair* colorPair, char* buffer) {
    sprintf(buffer, "%s %s",
        majorColorNames[colorPair->majorColor],
        minorColorNames[colorPair->minorColor]);
}

ColorPair getColorFromPairNumber(int pairNumber) {
    ColorPair colorPair;
    int zeroBasedPairNumber = pairNumber - 1;
    colorPair.majorColor = 
        (enum MajorColor)(zeroBasedPairNumber / numberOfMinorColors);
    colorPair.minorColor =
        (enum MinorColor)(zeroBasedPairNumber % numberOfMinorColors);
    return colorPair;
}

int getPairNumberFromColor(const ColorPair* colorPair) {
    return colorPair->majorColor * numberOfMinorColors +
            colorPair->minorColor + 1;
}

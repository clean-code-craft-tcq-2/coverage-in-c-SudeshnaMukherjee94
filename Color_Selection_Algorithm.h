#include <stdio.h>
#include <assert.h>
#define MAJOR_AND_MINOR_COLORS (5u)

enum MajorColor {WHITE, RED, BLACK, YELLOW, VIOLET};
enum MinorColor {BLUE, ORANGE, GREEN, BROWN, SLATE};

int numberOfMajorColors;
int numberOfMinorColors;

const int MAX_COLORPAIR_NAME_CHARS;

typedef struct {
    enum MajorColor majorColor;
    enum MinorColor minorColor;
} ColorPair;

//Method definitions

ColorPair getColorFromPairNumber(int pairNumber);
void colorPairToString(const ColorPair* colorPair, char* buffer);
int getPairNumberFromColor(const ColorPair* colorPair);

extern const char* majorColorNames[];
extern const char* minorColorNames[];

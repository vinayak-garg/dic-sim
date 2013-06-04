#ifndef CONSTANTS_H
#define CONSTANTS_H

const char VERSION[] = "1.3.2";

const int IO_COUNT = 10;

const int kTop = 70;
const int kLeft = 30;
const int kWidth = 620;
const int kHeight = 480;
const int kRadius = 15;
const int kBorder = 4;
const int kSquare = 6;
const int kBox = kBorder + kSquare;
const int kOuterBorder = 16;
const int kCols = 59;
const int kNotchGap = 2*kBox;
const int kBusBorder = 2*kBox;
const int kBusGap = kBox;
const int kBusCols = 10;

const int ktR1 = kTop + kOuterBorder;
const int ktR2 = 5*kBox - kBorder + kNotchGap + ktR1;
const int ktR3 = 12*kBox - 3*kBorder + kNotchGap + 2*kBusBorder + ktR1;
const int ktR4 = 17*kBox - 4*kBorder + 2*kNotchGap + 2*kBusBorder + ktR1;
const int ktR5 = 24*kBox - 6*kBorder + 2*kNotchGap + 4*kBusBorder + ktR1;
const int ktR6 = 29*kBox - 7*kBorder + 3*kNotchGap + 4*kBusBorder + ktR1;

const int kbR1 = ktR1 + 10*kBox + kNotchGap + kBusBorder - 2*kBorder;
const int kbR2 = kbR1 + 2*kBusBorder + 12*kBox + kNotchGap - 3*kBorder;

const int BUS_ROW_HIGH = 30;
const int BUS_ROW_LOW = 31;
const int BUS_COL = kCols + 10;

const int HIGH_OFFSET = -1;
const int LOW_OFFSET = -2;

const int MAX_INPUTS = 128;
const int MAX_OUTPUTS = 128;

const int kMaxTerminals = kCols*6
        + 10 /* Input points */
        + 10 /* Output points */;
const int INPUT_OFFSET = kCols*6;
const int OUTPUT_OFFSET = INPUT_OFFSET + 10;

const int INTERNAL_PIN_OFFSET = 1000;

#endif // CONSTANTS_H

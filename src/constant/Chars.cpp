#include "Chars.h"

const std::map<std::string, uint8_t> Chars::KEY_MAP = {
	{ "0", 0 },
	{ "1", 1 },
	{ "2", 2 },
	{ "3", 3 },
	{ "4", 4 },
	{ "5", 5 },
	{ "6", 6 },
	{ "7", 7 },
	{ "8", 8 },
	{ "9", 9 },
	{ "A", 10 },
	{ "B", 11 },
	{ "C", 12 },
	{ "D", 13 },
	{ "E", 14 },
	{ "F", 15 },
	{ "G", 16 },
	{ "H", 17 },
	{ "I", 18 },
	{ "J", 19 },
	{ "K", 20 },
	{ "L", 21 },
	{ "M", 22 },
	{ "N", 23 },
	{ "O", 24 },
	{ "P", 25 },
	{ "Q", 26 },
	{ "R", 27 },
	{ "S", 28 },
	{ "T", 29 },
	{ "U", 30 },
	{ "V", 31 },
	{ "W", 32 },
	{ "X", 33 },
	{ "Y", 34 },
	{ "Z", 35 },
	{ "AE", 36 },
	{ "UE", 37 },
	{ "OE", 38 },
	{ "SS", 39 },
	{ "a", 40 },
	{ "b", 41 },
	{ "c", 42 },
	{ "d", 43 },
	{ "e", 44 },
	{ "f", 45 },
	{ "g", 46 },
	{ "h", 47 },
	{ "i", 48 },
	{ "j", 49 },
	{ "k", 50 },
	{ "l", 51 },
	{ "m", 52 },
	{ "n", 53 },
	{ "o", 54 },
	{ "p", 55 },
	{ "q", 56 },
	{ "r", 57 },
	{ "s", 58 },
	{ "t", 59 },
	{ "u", 60 },
	{ "v", 61 },
	{ "w", 62 },
	{ "x", 63 },
	{ "y", 64 },
	{ "z", 65 },
	{ "ae", 66 },
	{ "ue", 67 },
	{ "oe", 68 },
	{ "+", 69 },
	{ "-", 70 },
	{ "multiply", 71 },
	{ "divide", 72 },
	{ "=", 73 },
	{ "(", 74 },
	{ ")", 75 },
	{ "[", 76 },
	{ "]", 77 },
	{ "{", 78 },
	{ "}", 79 },
	{ " ", 80 },
	{ ".", 81 },
	{ ",", 82 },
	{ ";", 83 },
	{ ":", 84 },
	{ "!", 85 },
	{ "?", 86 },
	{ "_", 87 },
	{ "<", 88 },
	{ ">", 89 },
	{ "|", 90 },
	{ "#", 91 },
	{ "'", 92 },
	{ "\"", 93 },
	{ "^", 94 },
	{ "empty", 95 },
	{ "euro", 96 },
	{ "$", 97 },
	{ "%", 98 },
	{ "&", 99 },
	{ "\\", 100 },
	{ "@", 101 },
	{ "time", 102 },
	{ "SHIFT", 103 },
	{ "ALPHA", 104 },
	{ "MODE", 105 },
	{ "Abs", 106 },
	{ "x^3", 107 },
	{ "x^-1", 108 },
	{ "logn", 109 },
	{ "fraction", 110 },
	{ "root2", 111 },
	{ "x^2", 112 },
	{ "x^n", 113 },
	{ "log10", 114 },
	{ "ln", 115 },
	{ "(-)", 116 },
	{ "hyp", 117 },
	{ "sin", 118 },
	{ "cos", 119 },
	{ "tan", 120 },
	{ "RCL", 121 },
	{ "ENG", 122 },
	{ "S<>D", 123 },
	{ "M+", 124 },
	{ "DEL", 125 },
	{ "AC", 126 },
	{ "*10^n", 127 },
	{ "Ans", 128 },
	{ "SETUP", 129 },
	{ "/R", 130 },
	{ "mixedfraction", 131 },
	{ "root3", 132 },
	{ "periodic", 133 },
	{ "rootn", 134 },
	{ "10^n", 135 },
	{ "e^n", 136 },
	{ "FACT", 137 },
	{ "sin^-1", 138 },
	{ "cos^-1", 139 },
	{ "tan^-1", 140 },
	{ "STO", 141 },
	{ "<-", 142 },
	{ "mf<>f", 143 },
	{ "M-", 144 },
	{ "CONST", 145 },
	{ "CONV", 146 },
	{ "CLR", 147 },
	{ "INS", 148 },
	{ "OFF", 149 },
	{ "nPr", 150 },
	{ "nCr", 151 },
	{ "Pol", 152 },
	{ "Rec", 153 },
	{ "Rnd", 154 },
	{ "Ran#", 155 },
	{ "pi", 156 },
	{ "DRG", 157 },
	{ "wav=", 158 },
	{ "Conv", 159 },
	{ "GCD", 160 },
	{ "LCM", 161 },
	{ "Int", 162 },
	{ "Intg", 163 },
	{ "RanInt", 164 },
	{ "euler", 165 },
	{ "up", 167 },
	{ "down", 168 },
	{ "left", 169 },
	{ "right", 170 },
	{ "VERIFY", 171 },
	{ "BASE", 172 },
	{ "STAT/DIST", 173 },
	{ "*", 174 },
	{ "/", 175 },
	{ ">=", 176 },
	{ "<=", 177 },
	{ "=/", 178 },
	{ "cursor", 179 },
	{ "~", 180 },
	{ "bigarrowleft", 181 },
	{ "bigarrowright", 182 },
	{ "smallarrowleft", 183 },
	{ "smallarrowright", 184 },
	{ "liter", 185 },
	{ "gradian", 186 },
	{ "degree", 187 },
	{ "radian", 188 },
	{ "unknown", 189 },
	{ "sinh", 190 },
	{ "cosh", 191 },
	{ "tanh", 192 },
	{ "sinh^-1", 193 },
	{ "cosh^-1", 194 },
	{ "tanh^-1", 195 },
	{ "CONV1", 196 },
	{ "CONV2", 197 },
	{ "CONV3", 198 },
	{ "CONV4", 199 },
	{ "CONV5", 200 },
	{ "CONV6", 201 },
	{ "CONV7", 202 },
	{ "CONV8", 203 },
	{ "CONV9", 204 },
	{ "CONV10", 205 },
	{ "CONV11", 206 },
	{ "CONV12", 207 },
	{ "CONV13", 208 },
	{ "CONV14", 209 },
	{ "CONV15", 210 },
	{ "CONV16", 211 },
	{ "CONV17", 212 },
	{ "CONV18", 213 },
	{ "CONV19", 214 },
	{ "CONV20", 215 },
	{ "CONV21", 216 },
	{ "CONV22", 217 },
	{ "CONV23", 218 },
	{ "CONV24", 219 },
	{ "CONV25", 220 },
	{ "CONV26", 221 },
	{ "CONV27", 222 },
	{ "CONV28", 223 },
	{ "CONV29", 224 },
	{ "CONV30", 225 },
	{ "CONV31", 226 },
	{ "CONV32", 227 },
	{ "CONV33", 228 },
	{ "CONV34", 229 },
	{ "CONV35", 230 },
	{ "CONV36", 231 },
	{ "CONV37", 232 },
	{ "CONV38", 233 },
	{ "CONV39", 234 },
	{ "CONV40", 235 },
	{ "ON", 236 },
};

const std::map<uint8_t, uint8_t> Chars::KEY_MAP_SHIFT = {
	{ KEY_MAP.at("Abs"), KEY_MAP.at("/R") },
	{ KEY_MAP.at("fraction"), KEY_MAP.at("mixedfraction") },
	{ KEY_MAP.at("RCL"), KEY_MAP.at("STO") },
	{ KEY_MAP.at("7"), KEY_MAP.at("CONST") },
	{ KEY_MAP.at("1"), KEY_MAP.at("STAT/DIST") },
	{ KEY_MAP.at("0"), KEY_MAP.at("Rnd") },
	{ KEY_MAP.at("root2"), KEY_MAP.at("root3") },
	{ KEY_MAP.at("time"), KEY_MAP.at("FACT") },
	{ KEY_MAP.at("ENG"), KEY_MAP.at("<-") },
	{ KEY_MAP.at("8"), KEY_MAP.at("CONV") },
	{ KEY_MAP.at(","), KEY_MAP.at("Ran#") },
	{ KEY_MAP.at("x^2"), KEY_MAP.at("periodic") },
	{ KEY_MAP.at("("), KEY_MAP.at("%") },
	{ KEY_MAP.at("9"), KEY_MAP.at("CLR") },
	{ KEY_MAP.at("6"), KEY_MAP.at("VERIFY") },
	{ KEY_MAP.at("3"), KEY_MAP.at("BASE") },
	{ KEY_MAP.at("*10^n"), KEY_MAP.at("pi") },
	{ KEY_MAP.at("x^-1"), KEY_MAP.at("!") },
	{ KEY_MAP.at("x^n"), KEY_MAP.at("rootn") },
	{ KEY_MAP.at("sin"), KEY_MAP.at("sin^-1") },
	{ KEY_MAP.at(")"), KEY_MAP.at(";") },
	{ KEY_MAP.at("DEL"), KEY_MAP.at("INS") },
	{ KEY_MAP.at("multiply"), KEY_MAP.at("nPr") },
	{ KEY_MAP.at("+"), KEY_MAP.at("Pol") },
	{ KEY_MAP.at("Ans"), KEY_MAP.at("DRG") },
	{ KEY_MAP.at("log10"), KEY_MAP.at("10^n") },
	{ KEY_MAP.at("cos"), KEY_MAP.at("cos^-1") },
	{ KEY_MAP.at("S<>D"), KEY_MAP.at("mf<>f") },
	{ KEY_MAP.at("AC"), KEY_MAP.at("OFF") },
	{ KEY_MAP.at("divide"), KEY_MAP.at("nCr") },
	{ KEY_MAP.at("-"), KEY_MAP.at("Rec") },
	{ KEY_MAP.at("="), KEY_MAP.at("wav=") },
	{ KEY_MAP.at("MODE"), KEY_MAP.at("SETUP") },
	{ KEY_MAP.at("ln"), KEY_MAP.at("e^n") },
	{ KEY_MAP.at("tan"), KEY_MAP.at("tan^-1") },
	{ KEY_MAP.at("M+"), KEY_MAP.at("M-") },
	{ KEY_MAP.at("unknown"), KEY_MAP.at("unknown") },
};

const std::map<uint8_t, uint8_t> Chars::KEY_MAP_ALPHA = {
	{ KEY_MAP.at("(-)"), KEY_MAP.at("A") },
	{ KEY_MAP.at("x^3"), KEY_MAP.at(":") },
	{ KEY_MAP.at("time"), KEY_MAP.at("B") },
	{ KEY_MAP.at("8"), KEY_MAP.at("Conv") },
	{ KEY_MAP.at(","), KEY_MAP.at("RanInt") },
	{ KEY_MAP.at("hyp"), KEY_MAP.at("C") },
	{ KEY_MAP.at("*10^n"), KEY_MAP.at("euler") },
	{ KEY_MAP.at("sin"), KEY_MAP.at("D") },
	{ KEY_MAP.at(")"), KEY_MAP.at("X") },
	{ KEY_MAP.at("multiply"), KEY_MAP.at("GCD") },
	{ KEY_MAP.at("+"), KEY_MAP.at("Int") },
	{ KEY_MAP.at("cos"), KEY_MAP.at("E") },
	{ KEY_MAP.at("S<>D"), KEY_MAP.at("Y") },
	{ KEY_MAP.at("divide"), KEY_MAP.at("LCM") },
	{ KEY_MAP.at("-"), KEY_MAP.at("Intg") },
	{ KEY_MAP.at("tan"), KEY_MAP.at("F") },
	{ KEY_MAP.at("M+"), KEY_MAP.at("M") },
	{ KEY_MAP.at("unknown"), KEY_MAP.at("unknown") },
};
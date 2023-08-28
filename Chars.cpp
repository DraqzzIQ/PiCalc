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
	{ "unknown", 189},
};
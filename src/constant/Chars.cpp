#include "Chars.h"

const std::map<std::string, KEY> Chars::CHAR_TO_KEYCODE = {
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
	{ "nextVal", 237 },
	{ "symbolEnd", 238 },
	{ "newline", 239 },
	{ "dark0", 240 },
	{ "dark1", 241 },
	{ "dark2", 242 },
	{ "dark3", 243 },
	{ "dark4", 244 },
	{ "dark5", 245 },
	{ "dark6", 246 },
	{ "dark7", 247 },
	{ "dark8", 248 },
	{ "dark9", 249 },
	{ "RETURN", 250 },
	{ "ceil", 251 }
};

const std::vector<std::string> Chars::KEY_MAP = {
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"AE",
	"UE",
	"OE",
	"SS",
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"g",
	"h",
	"i",
	"j",
	"k",
	"l",
	"m",
	"n",
	"o",
	"p",
	"q",
	"r",
	"s",
	"t",
	"u",
	"v",
	"w",
	"x",
	"y",
	"z",
	"ae",
	"ue",
	"oe",
	"+",
	"-",
	"multiply",
	"divide",
	"=",
	"(",
	")",
	"[",
	"]",
	"{",
	"}",
	" ",
	".",
	",",
	";",
	":",
	"!",
	"?",
	"_",
	"<",
	">",
	"|",
	"#",
	"'",
	"\"",
	"^",
	"empty",
	"euro",
	"$",
	"%",
	"&",
	"\\",
	"@",
	"time",
	"SHIFT",
	"ALPHA",
	"MODE",
	"Abs",
	"x^3",
	"x^-1",
	"logn",
	"fraction",
	"root2",
	"x^2",
	"x^n",
	"log10",
	"ln",
	"(-)",
	"hyp",
	"sin",
	"cos",
	"tan",
	"RCL",
	"ENG",
	"S<>D",
	"M+",
	"DEL",
	"AC",
	"*10^n",
	"Ans",
	"SETUP",
	"/R",
	"mixedfraction",
	"root3",
	"periodic",
	"rootn",
	"10^n",
	"e^n",
	"FACT",
	"sin^-1",
	"cos^-1",
	"tan^-1",
	"STO",
	"<-",
	"mf<>f",
	"M-",
	"CONST",
	"CONV",
	"CLR",
	"INS",
	"OFF",
	"nPr",
	"nCr",
	"Pol",
	"Rec",
	"Rnd",
	"Ran#",
	"pi",
	"DRG",
	"wav=",
	"Conv",
	"GCD",
	"LCM",
	"Int",
	"Intg",
	"RanInt",
	"euler",
	"",
	"up",
	"down",
	"left",
	"right",
	"VERIFY",
	"BASE",
	"STAT/DIST",
	"*",
	"/",
	">=",
	"<=",
	"=/",
	"cursor",
	"~",
	"bigarrowleft",
	"bigarrowright",
	"smallarrowleft",
	"smallarrowright",
	"liter",
	"gradian",
	"degree",
	"radian",
	"unknown",
	"sinh",
	"cosh",
	"tanh",
	"sinh^-1",
	"cosh^-1",
	"tanh^-1",
	"CONV1",
	"CONV2",
	"CONV3",
	"CONV4",
	"CONV5",
	"CONV6",
	"CONV7",
	"CONV8",
	"CONV9",
	"CONV10",
	"CONV11",
	"CONV12",
	"CONV13",
	"CONV14",
	"CONV15",
	"CONV16",
	"CONV17",
	"CONV18",
	"CONV19",
	"CONV20",
	"CONV21",
	"CONV22",
	"CONV23",
	"CONV24",
	"CONV25",
	"CONV26",
	"CONV27",
	"CONV28",
	"CONV29",
	"CONV30",
	"CONV31",
	"CONV32",
	"CONV33",
	"CONV34",
	"CONV35",
	"CONV36",
	"CONV37",
	"CONV38",
	"CONV39",
	"CONV40",
	"ON",
	"nextVal",
	"symbolEnd"
	"newline",
	"dark0",
	"dark1",
	"dark2",
	"dark3",
	"dark4",
	"dark5",
	"dark6",
	"dark7",
	"dark8",
	"dark9",
	"RETURN",
	"ceil",
};

const std::map<KEY, KEY> Chars::KEY_MAP_SHIFT = {
	{ CHAR_TO_KEYCODE.at("Abs"), CHAR_TO_KEYCODE.at("/R") },
	{ CHAR_TO_KEYCODE.at("fraction"), CHAR_TO_KEYCODE.at("mixedfraction") },
	{ CHAR_TO_KEYCODE.at("RCL"), CHAR_TO_KEYCODE.at("STO") },
	{ CHAR_TO_KEYCODE.at("7"), CHAR_TO_KEYCODE.at("CONST") },
	{ CHAR_TO_KEYCODE.at("1"), CHAR_TO_KEYCODE.at("STAT/DIST") },
	{ CHAR_TO_KEYCODE.at("0"), CHAR_TO_KEYCODE.at("Rnd") },
	{ CHAR_TO_KEYCODE.at("root2"), CHAR_TO_KEYCODE.at("root3") },
	{ CHAR_TO_KEYCODE.at("time"), CHAR_TO_KEYCODE.at("FACT") },
	{ CHAR_TO_KEYCODE.at("ENG"), CHAR_TO_KEYCODE.at("<-") },
	{ CHAR_TO_KEYCODE.at("8"), CHAR_TO_KEYCODE.at("CONV") },
	{ CHAR_TO_KEYCODE.at(","), CHAR_TO_KEYCODE.at("Ran#") },
	{ CHAR_TO_KEYCODE.at("x^2"), CHAR_TO_KEYCODE.at("periodic") },
	{ CHAR_TO_KEYCODE.at("("), CHAR_TO_KEYCODE.at("%") },
	{ CHAR_TO_KEYCODE.at("9"), CHAR_TO_KEYCODE.at("CLR") },
	{ CHAR_TO_KEYCODE.at("6"), CHAR_TO_KEYCODE.at("VERIFY") },
	{ CHAR_TO_KEYCODE.at("3"), CHAR_TO_KEYCODE.at("BASE") },
	{ CHAR_TO_KEYCODE.at("*10^n"), CHAR_TO_KEYCODE.at("pi") },
	{ CHAR_TO_KEYCODE.at("x^-1"), CHAR_TO_KEYCODE.at("!") },
	{ CHAR_TO_KEYCODE.at("x^n"), CHAR_TO_KEYCODE.at("rootn") },
	{ CHAR_TO_KEYCODE.at("sin"), CHAR_TO_KEYCODE.at("sin^-1") },
	{ CHAR_TO_KEYCODE.at(")"), CHAR_TO_KEYCODE.at(";") },
	{ CHAR_TO_KEYCODE.at("DEL"), CHAR_TO_KEYCODE.at("INS") },
	{ CHAR_TO_KEYCODE.at("multiply"), CHAR_TO_KEYCODE.at("nPr") },
	{ CHAR_TO_KEYCODE.at("+"), CHAR_TO_KEYCODE.at("Pol") },
	{ CHAR_TO_KEYCODE.at("Ans"), CHAR_TO_KEYCODE.at("DRG") },
	{ CHAR_TO_KEYCODE.at("log10"), CHAR_TO_KEYCODE.at("10^n") },
	{ CHAR_TO_KEYCODE.at("cos"), CHAR_TO_KEYCODE.at("cos^-1") },
	{ CHAR_TO_KEYCODE.at("S<>D"), CHAR_TO_KEYCODE.at("mf<>f") },
	{ CHAR_TO_KEYCODE.at("AC"), CHAR_TO_KEYCODE.at("OFF") },
	{ CHAR_TO_KEYCODE.at("divide"), CHAR_TO_KEYCODE.at("nCr") },
	{ CHAR_TO_KEYCODE.at("-"), CHAR_TO_KEYCODE.at("Rec") },
	{ CHAR_TO_KEYCODE.at("="), CHAR_TO_KEYCODE.at("wav=") },
	{ CHAR_TO_KEYCODE.at("MODE"), CHAR_TO_KEYCODE.at("SETUP") },
	{ CHAR_TO_KEYCODE.at("ln"), CHAR_TO_KEYCODE.at("e^n") },
	{ CHAR_TO_KEYCODE.at("tan"), CHAR_TO_KEYCODE.at("tan^-1") },
	{ CHAR_TO_KEYCODE.at("M+"), CHAR_TO_KEYCODE.at("M-") },
	{ CHAR_TO_KEYCODE.at("unknown"), CHAR_TO_KEYCODE.at("unknown") },
};


const std::map<KEY, KEY> Chars::KEY_MAP_ALPHA = {
	{ CHAR_TO_KEYCODE.at("(-)"), CHAR_TO_KEYCODE.at("A") },
	{ CHAR_TO_KEYCODE.at("x^3"), CHAR_TO_KEYCODE.at(":") },
	{ CHAR_TO_KEYCODE.at("time"), CHAR_TO_KEYCODE.at("B") },
	{ CHAR_TO_KEYCODE.at("8"), CHAR_TO_KEYCODE.at("Conv") },
	{ CHAR_TO_KEYCODE.at(","), CHAR_TO_KEYCODE.at("RanInt") },
	{ CHAR_TO_KEYCODE.at("hyp"), CHAR_TO_KEYCODE.at("C") },
	{ CHAR_TO_KEYCODE.at("*10^n"), CHAR_TO_KEYCODE.at("euler") },
	{ CHAR_TO_KEYCODE.at("sin"), CHAR_TO_KEYCODE.at("D") },
	{ CHAR_TO_KEYCODE.at(")"), CHAR_TO_KEYCODE.at("X") },
	{ CHAR_TO_KEYCODE.at("multiply"), CHAR_TO_KEYCODE.at("GCD") },
	{ CHAR_TO_KEYCODE.at("+"), CHAR_TO_KEYCODE.at("Int") },
	{ CHAR_TO_KEYCODE.at("cos"), CHAR_TO_KEYCODE.at("E") },
	{ CHAR_TO_KEYCODE.at("S<>D"), CHAR_TO_KEYCODE.at("Y") },
	{ CHAR_TO_KEYCODE.at("divide"), CHAR_TO_KEYCODE.at("LCM") },
	{ CHAR_TO_KEYCODE.at("-"), CHAR_TO_KEYCODE.at("Intg") },
	{ CHAR_TO_KEYCODE.at("tan"), CHAR_TO_KEYCODE.at("F") },
	{ CHAR_TO_KEYCODE.at("M+"), CHAR_TO_KEYCODE.at("M") },
	{ CHAR_TO_KEYCODE.at("unknown"), CHAR_TO_KEYCODE.at("unknown") },
};

bool Chars::in_key_set(KEY value, const KEY_SET& vector)
{
	return std::count(vector.begin(), vector.end(), value);
}
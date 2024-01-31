/*
New map:
CAPITAL: control characters, can't be in Files
lowercase (and uppercase single characters): normal characters
0	unknown
1	SHIFT
2	ALPHA
3	UP
4	DOWN
5	LEFT
6	RIGHT
7	MODE
8	SETUP
9	ON
10	newline
11	ABS
12	MOD (/R)
13	cubed (x^3)
14	reciprocal (x^-1)
15	LOGN
16	FRACTION
17	MIXED_FRACTION
18	SQRT
19	ROOT3
20	squared (x^2)
21	PERIODIC
22	POWER (x^n)
23	ROOTN
24	LOG
25	POWER10 (10^n)
26	LN
27	EXP (e^n)
28	negate (-)
29	TIME (°,,,)
30	FACT
31	HYP
32	space
33	!
34	"
35	#
36	$
37	%
38	&
39	'
40	(
41	)
42	*
43	+
44	,
45	-
46	.
47	/
48	0
49	1
50	2
51	3
52	4
53	5
54	6
55	7
56	8
57	9
58	:
59	;
60	<
61	=
62	>
63	?
64	@
65	A
66	B
67	C
68	D
69	E
70	F
71	G
72	H
73	I
74	J
75	K
76	L
77	M
78	N
79	O
80	P
81	Q
82	R
83	S
84	T
85	U
86	V
87	W
88	X
89	Y
90	Z
91	[
92	\
93	]
94	^
95	_
96	`
97	a
98	b
99	c
100	d
101	e
102	f
103	g
104	h
105	i
106	j
107	k
108	l
109	m
110	n
111	o
112	p
113	q
114	r
115	s
116	t
117	u
118	v
119	w
120	x
121	y
122	z
123	{
124	|
125	}
126	~
127 empty
128	euro
129 SIN
130	COS
131	TAN
132	ASIN
133	ACOS
134	ATAN
135	SINH
136	COSH
137	TANH
138	ASINH
139	ACOSH
140	ATANH
141	RCL
142	STO
143	ENG
144	BACK_ENG (<-)
145	S<>D
146	MF<>F
147	M+
148	M-
149	CONST
150	SHIFT_CONV
151	ALPHA_CONV
152	CLR
153	DEL
154	INS
155	AC
156	OFF
157	VERIFY
158	NPR
159	GCD
160	NCR
161	LCM
162	STAT/DIST
163	BASE
164	POL
165	INT
166 REC
167	INTG
168	RND
169	RAN#
170	RAN_INT
171	*10^n
172	PI
173	EULER
174	RADIAN
175	GRADIAN
176	degree
177	plus_minus
178	ANS
179	DRG
180	WAV=
181	CEIL
182	>=
183	<=
184	!=
185	CURSOR
186	BIG_ARROW_LEFT
187	BIG_ARROW_RIGHT
188	SMALL_ARROW_LEFT
189	SMALL_ARROW_RIGHT
190	NEXT_VAL
191	SYMBOL_END
192
193
194
195
196	AE
197 DARK0
198	DARK1
199	DARK2
200	DARK3
201	DARK4
202	DARK5
203	DARK6
204	DARK7
205	DARK8
206	DARK9
207
208
209
210
211
212
213
214	OE
215	multiply
216
217
218
219
220	UE
221
222
223	SS
224
225
226
227
228	ae
229
230
231
232
233
234
235
236
237
238
239
240
241
242
243
244
245
246	oe
247	divide
248
249
250
251
252	ue
253
254
255

Old map:
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
{ "ceil", 166 },
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
};

TODO: change KEYs,
      Equation: tostring / Notes / chat,
      Decimal::sin,
      cos,
      tan,
      Number simplify,
      implement convert calculator,
      function drawer,
      TIME handling
          change map to switch case
*/
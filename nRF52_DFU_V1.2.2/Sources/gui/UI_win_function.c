
#include "OSAL.h"
#include "OSAL_Timer.h"

#include "Task_GUI.h"
#include "Task_Step.h"
#include "LCD_ST7735.h"

#include "string.h"
#include "Window.h"
#include "UserSetting.h"
#include "UI_Draw.h"

#include "UI_function_icon.h"
#include "UI_win_function.h"
#include "UI_comm_icon.h"
#include "UI_Comm_Draw.h"

const unsigned char jpeg_ui_bg_red[]={255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
0,100,0,0,255,236,0,17,68,117,99,107,121,0,1,0,
4,0,0,0,100,0,0,255,238,0,14,65,100,111,98,101,
0,100,192,0,0,0,1,255,219,0,132,0,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,
2,2,3,3,3,3,3,3,3,3,3,3,1,1,1,1,
1,1,1,2,1,1,2,2,2,1,2,2,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,255,192,0,
17,8,0,34,0,80,3,1,17,0,2,17,1,3,17,1,
255,196,0,145,0,1,1,0,2,3,1,0,0,0,0,0,
0,0,0,0,0,0,7,1,5,4,6,8,11,1,1,0,
3,1,1,1,1,0,0,0,0,0,0,0,0,0,0,5,
6,8,7,2,4,9,16,0,1,2,4,3,6,6,3,0,
0,0,0,0,0,0,0,1,2,5,0,17,3,4,81,161,
6,33,145,18,82,20,21,65,114,19,83,22,7,49,34,50,
17,0,1,2,4,2,6,8,4,7,0,0,0,0,0,0,
0,1,0,2,17,3,4,5,81,6,33,161,82,19,21,7,
49,65,97,129,18,50,20,22,145,162,23,8,34,66,98,114,
130,146,163,255,218,0,12,3,1,0,2,17,3,17,0,63,
0,249,255,0,193,22,245,167,76,106,23,197,36,52,179,56,
223,37,70,94,181,27,90,189,50,124,247,74,74,109,169,143,
50,196,71,214,93,173,150,240,77,108,249,82,200,234,46,30,
46,230,249,143,112,87,28,183,203,236,241,155,222,214,229,171,
85,117,99,28,124,236,148,253,208,253,211,136,18,155,252,158,
21,85,147,232,77,84,224,80,183,123,230,150,26,38,92,104,
171,92,184,222,164,29,179,77,11,46,43,69,75,198,119,9,
49,79,175,230,45,158,154,45,162,151,58,165,253,68,15,3,
126,47,252,95,33,90,59,41,125,153,115,30,244,91,55,51,
86,91,108,212,167,204,215,204,53,51,199,104,151,34,50,79,
108,106,90,123,15,85,145,135,232,63,175,91,202,42,62,56,
187,106,26,169,35,142,151,170,134,155,10,128,74,96,209,180,
43,190,76,206,23,95,141,241,70,184,243,27,50,212,197,182,
249,82,105,152,122,12,55,143,29,238,131,63,205,106,108,153,
246,95,201,27,33,100,252,223,93,115,189,212,180,136,179,198,
40,233,221,216,101,201,46,168,17,236,171,232,237,210,174,26,
117,191,66,233,62,5,105,237,50,198,217,89,18,225,188,165,
99,70,163,135,235,252,205,198,224,86,190,84,188,39,80,237,
138,5,206,167,48,222,98,46,117,117,19,101,159,202,94,67,
63,160,131,62,85,175,50,61,151,147,252,182,45,153,146,44,
22,139,125,91,33,9,204,167,99,170,116,116,70,166,96,125,
65,135,84,102,157,58,122,74,106,38,253,11,171,56,213,168,
116,203,27,157,101,207,138,242,173,141,26,110,31,183,245,39,
27,113,70,249,51,241,149,65,182,22,202,156,195,102,128,182,
85,212,74,150,63,40,121,44,254,134,44,249,83,60,89,121,
63,204,146,233,153,222,193,104,184,85,190,49,156,250,118,54,
167,79,76,42,101,134,84,8,245,194,104,211,167,164,40,123,
247,208,127,94,184,21,212,99,113,118,211,213,84,79,5,47,
85,14,214,20,193,156,128,163,118,81,124,169,28,110,191,27,
226,255,0,110,230,54,101,166,131,110,18,164,212,176,116,152,
110,222,123,219,22,127,154,200,121,207,236,191,146,55,178,249,
249,66,186,231,100,169,113,48,103,140,86,83,183,176,75,156,
91,80,97,219,87,209,219,165,70,222,254,132,213,77,229,107,
104,190,105,126,162,39,192,138,85,203,117,234,128,219,53,80,
189,225,180,76,252,37,112,163,23,154,14,98,217,234,96,218,
217,115,169,159,214,72,241,183,226,207,197,242,5,150,115,111,
217,151,49,236,165,211,114,205,101,182,243,74,60,173,100,195,
77,60,246,153,115,225,36,118,66,165,199,176,117,202,157,180,
198,161,99,82,131,179,51,141,138,82,101,235,86,181,171,211,
43,201,116,148,170,218,160,242,172,197,194,142,237,108,184,0,
104,167,202,152,79,80,112,241,119,183,204,59,194,206,57,147,
151,217,227,40,61,205,204,182,170,234,54,52,249,223,41,251,
163,251,103,0,101,59,248,188,173,20,72,42,114,244,251,99,
126,146,104,225,85,147,45,135,170,153,74,189,205,51,123,92,
43,197,105,171,120,107,170,154,137,229,225,24,108,142,75,87,
83,121,173,136,159,62,103,128,245,52,248,7,193,176,143,124,
87,232,86,95,178,242,211,44,22,190,213,105,163,245,13,232,
153,53,187,249,145,196,62,126,240,180,159,209,225,29,64,1,
161,118,193,170,138,64,1,96,0,0,0,108,0,13,128,0,
4,128,2,33,141,158,38,36,105,93,41,188,199,44,104,107,
93,6,129,0,7,64,24,5,159,150,43,220,206,28,24,96,
189,125,73,126,222,180,249,98,189,204,225,193,134,9,245,37,
251,122,211,229,138,247,51,135,6,24,39,212,151,237,235,79,
150,43,220,206,28,24,96,159,82,95,183,173,62,88,175,115,
56,112,97,130,125,73,126,222,180,249,98,189,204,225,193,134,
9,245,37,251,122,214,14,170,42,4,21,130,8,32,131,180,
16,118,16,65,18,32,136,11,60,12,64,210,188,187,152,229,
237,45,115,162,210,32,65,232,35,2,186,155,155,126,146,119,
226,85,235,45,135,170,169,206,189,181,51,101,92,171,193,106,
171,102,104,42,162,129,230,226,24,236,137,154,74,155,205,20,
4,137,243,60,3,169,199,198,62,14,140,59,160,185,174,96,
178,242,211,51,151,62,235,105,163,245,14,233,153,41,187,137,
145,196,190,70,236,184,143,215,226,29,68,17,161,75,251,218,
249,243,49,110,244,3,5,158,125,219,51,107,90,119,181,243,
230,97,232,6,9,238,217,155,90,211,189,175,159,51,15,64,
48,79,118,204,218,214,157,237,124,249,152,122,1,130,123,182,
102,214,180,239,107,231,204,195,208,12,19,221,179,54,181,167,
123,95,62,102,30,128,96,158,237,153,181,173,59,218,249,243,
48,244,3,4,247,108,205,173,105,222,215,207,153,135,160,24,
39,187,102,109,107,78,246,190,124,204,61,0,193,61,219,51,
107,90,119,181,243,230,97,232,6,9,238,217,155,90,212,251,
170,86,39,124,89,55,65,113,62,33,51,18,157,82,177,59,
225,186,9,196,38,98,83,170,86,39,124,55,65,56,132,204,
74,117,74,196,239,134,232,39,16,153,137,78,169,88,157,240,
221,4,226,19,49,41,213,43,19,190,27,160,156,66,102,37,
58,165,98,119,195,116,19,136,76,196,167,84,172,78,248,110,
130,113,9,152,148,234,149,137,223,13,208,78,33,51,18,157,
82,177,59,225,186,9,196,38,98,87,6,62,133,14,144,68,
130,36,17,32,137,4,72,34,65,18,8,144,69,255,217};

const unsigned char jpeg_ui_bg_yellow[] = {255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
0,100,0,0,255,236,0,17,68,117,99,107,121,0,1,0,
4,0,0,0,100,0,0,255,238,0,14,65,100,111,98,101,
0,100,192,0,0,0,1,255,219,0,132,0,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,
2,2,3,3,3,3,3,3,3,3,3,3,1,1,1,1,
1,1,1,2,1,1,2,2,2,1,2,2,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,255,192,0,
17,8,0,34,0,80,3,1,17,0,2,17,1,3,17,1,
255,196,0,146,0,1,0,2,3,1,0,0,0,0,0,0,
0,0,0,0,0,0,8,9,2,6,7,11,1,1,0,2,
2,3,1,1,0,0,0,0,0,0,0,0,0,0,4,8,
5,7,1,3,6,2,9,16,0,1,2,5,1,5,9,1,
1,1,0,0,0,0,0,0,1,2,3,0,4,5,6,7,
17,19,147,84,21,8,33,65,145,225,18,82,226,23,24,9,
51,22,17,0,0,4,2,5,10,4,7,1,0,0,0,0,
0,0,0,0,1,2,3,17,4,33,81,161,5,6,49,65,
97,18,82,19,20,21,22,7,113,145,50,23,129,177,66,98,
114,51,8,130,255,218,0,12,3,1,0,2,17,3,17,0,
63,0,243,255,0,128,14,177,143,176,78,101,202,174,178,222,
60,198,87,157,214,203,202,244,166,163,76,161,79,26,35,103,
184,205,87,166,26,98,137,38,146,123,222,152,64,215,190,60,
118,36,238,22,6,193,232,82,177,53,237,35,38,180,253,11,
117,27,211,252,89,35,55,85,254,80,99,181,182,30,119,245,
165,71,240,163,207,32,176,28,93,252,140,234,2,239,84,188,
214,68,186,177,238,36,166,44,129,51,45,61,85,93,231,116,
50,149,0,66,216,164,218,251,107,121,240,158,208,160,186,203,
42,7,77,1,237,34,183,226,223,236,254,219,220,164,166,176,
204,157,229,124,205,23,165,72,108,165,152,63,23,31,131,197,
162,18,202,45,37,158,123,87,75,235,165,195,74,11,198,39,
101,22,139,42,196,159,200,142,142,172,243,43,57,149,47,44,
133,152,234,12,173,6,98,67,152,177,143,109,41,180,39,210,
84,133,211,45,197,77,93,76,237,20,8,37,21,208,66,78,
131,66,61,81,86,49,159,246,151,123,239,178,91,24,66,70,
236,184,229,148,71,5,234,28,228,194,116,239,30,213,151,56,
105,148,203,150,138,6,73,171,166,77,20,186,165,44,252,96,
86,83,104,181,44,53,103,244,165,211,225,151,127,13,224,204,
87,99,84,229,118,123,27,142,159,108,83,231,110,241,177,255,
0,45,165,231,88,110,163,117,191,179,36,148,237,39,21,162,
137,35,180,147,21,7,28,223,93,225,238,81,41,188,113,136,
47,123,194,81,113,139,11,125,105,150,167,44,37,155,52,75,
148,115,193,162,162,5,144,136,101,25,68,172,191,233,66,18,
117,194,159,60,182,134,101,179,250,82,234,12,204,63,153,48,
102,43,190,106,115,91,77,181,199,80,182,41,242,87,121,219,
127,174,206,243,163,183,78,186,216,218,16,10,182,115,137,213,
64,19,218,1,134,6,190,187,195,219,82,75,120,31,16,94,
247,124,162,33,6,16,250,213,45,70,72,203,56,107,151,56,
102,139,71,68,75,33,152,60,137,89,143,220,132,40,235,133,
62,121,109,21,91,150,255,0,145,29,29,94,6,106,115,21,
222,89,11,14,84,30,90,204,188,135,49,99,33,90,82,136,
87,168,165,8,166,92,106,149,186,158,217,168,128,10,235,164,
148,141,14,164,250,162,223,96,207,237,46,247,220,132,134,49,
124,141,217,126,75,36,138,43,212,57,57,133,105,222,51,173,
46,81,209,41,151,37,20,12,91,183,76,154,233,105,74,65,
248,196,173,166,209,90,185,71,249,25,212,5,160,169,137,172,
119,117,99,220,183,76,65,34,90,90,70,170,187,50,232,121,
41,4,149,191,73,186,54,54,243,1,93,129,33,21,151,148,
78,186,129,216,77,167,194,95,217,253,183,190,137,45,98,105,
59,202,230,154,63,82,150,217,76,176,94,14,49,23,143,76,
101,146,90,79,54,53,219,165,244,82,217,165,101,227,3,182,
139,69,127,100,28,19,153,113,83,175,55,144,241,149,231,106,
50,202,189,42,168,212,232,83,194,136,225,239,50,181,233,118,
159,162,78,36,30,246,102,22,53,239,139,33,134,251,133,129,
177,130,18,172,51,123,72,206,45,95,66,29,70,244,191,38,
76,201,212,255,0,164,16,128,227,15,53,251,18,162,248,81,
231,144,114,120,246,35,168,94,245,139,104,116,243,142,75,47,
91,56,198,211,19,204,4,150,234,181,201,95,250,138,170,29,
26,21,76,51,63,114,46,168,252,155,203,80,212,150,11,73,
26,232,144,19,217,31,158,88,134,250,238,102,39,37,34,245,
189,167,56,117,101,109,165,112,237,153,84,104,96,155,37,17,
125,250,199,156,204,206,145,156,66,101,155,244,164,163,166,159,
152,144,200,234,5,109,33,13,53,53,179,109,180,37,13,182,
133,37,8,66,16,2,80,132,33,32,37,40,74,70,128,14,
192,35,89,171,182,228,181,26,214,136,168,206,38,103,73,153,
158,115,18,56,130,25,254,132,127,141,86,243,202,56,246,213,
27,22,7,16,85,135,232,71,248,213,111,60,161,237,170,54,
44,14,32,171,15,208,143,241,170,222,121,67,219,84,108,88,
28,65,86,31,161,31,227,85,188,242,135,182,168,216,176,56,
130,172,63,66,63,198,171,121,229,15,109,81,177,96,113,5,
88,126,132,127,141,86,243,202,30,218,163,98,192,226,10,177,
130,250,129,91,168,91,78,205,109,27,113,10,67,141,173,73,
90,22,133,130,149,161,104,80,41,82,20,147,161,7,176,136,
229,61,183,36,40,150,132,65,68,113,35,42,12,140,179,144,
113,4,35,205,245,104,116,243,145,139,207,92,216,198,211,51,
207,133,23,42,180,57,95,249,122,170,221,58,148,204,61,63,
109,174,150,252,227,200,81,212,23,203,169,58,104,160,83,217,
27,51,15,95,93,204,195,4,148,93,87,180,231,14,156,141,
186,174,33,178,42,137,15,147,132,146,63,179,84,243,145,145,
210,35,173,50,206,122,146,81,209,71,200,64,223,180,38,120,
131,188,249,69,136,233,38,182,108,16,119,129,246,132,207,16,
119,159,40,116,147,91,54,6,240,62,208,153,226,14,243,229,
14,146,107,102,192,222,7,218,19,60,65,222,124,161,210,77,
108,216,27,192,251,66,103,136,59,207,148,58,73,173,155,3,
120,31,104,76,241,7,121,242,135,73,53,179,96,111,3,237,
9,158,32,239,62,80,233,38,182,108,13,224,125,161,51,196,
29,231,202,29,36,214,205,129,188,15,180,38,120,131,188,249,
67,164,154,217,176,55,129,246,132,207,16,119,159,40,116,147,
91,54,6,240,67,238,122,247,188,248,152,221,188,189,21,8,
122,196,28,245,239,121,241,48,229,232,168,53,136,57,235,222,
243,226,97,203,209,80,107,16,115,215,189,231,196,195,151,162,
160,214,32,231,175,123,207,137,135,47,69,65,172,65,207,94,
247,159,19,14,94,138,131,88,131,158,189,239,62,38,28,189,
21,6,177,7,61,123,222,124,76,57,122,42,13,98,14,122,
247,188,248,152,114,244,84,26,196,28,245,239,121,241,48,229,
232,168,53,136,106,145,152,31,33,0,8,0,64,2,0,16,
0,128,4,0,32,1,0,31,255,217};

const unsigned char jpeg_ui_bg_blue[]={255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
0,100,0,0,255,236,0,17,68,117,99,107,121,0,1,0,
4,0,0,0,100,0,0,255,238,0,14,65,100,111,98,101,
0,100,192,0,0,0,1,255,219,0,132,0,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,
2,2,3,3,3,3,3,3,3,3,3,3,1,1,1,1,
1,1,1,2,1,1,2,2,2,1,2,2,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,255,192,0,
17,8,0,34,0,80,3,1,17,0,2,17,1,3,17,1,
255,196,0,148,0,1,0,3,1,1,1,0,0,0,0,0,
0,0,0,0,0,0,7,8,9,2,6,11,1,1,0,2,
3,1,1,0,0,0,0,0,0,0,0,0,0,0,6,8,
1,5,7,4,9,16,0,1,2,4,2,9,3,4,3,0,
0,0,0,0,0,0,1,2,3,0,4,5,6,17,7,33,
145,18,82,146,19,83,21,23,49,226,84,65,20,8,9,35,
51,22,17,0,1,2,4,3,4,7,6,7,1,0,0,0,
0,0,0,1,0,2,17,3,4,5,81,21,6,161,18,19,
7,33,49,65,97,129,82,22,113,50,162,83,20,23,145,34,
66,98,114,146,8,163,255,218,0,12,3,1,0,2,17,3,
17,0,63,0,249,255,0,193,20,143,101,228,254,105,102,43,
141,34,201,176,110,155,137,167,78,200,158,144,163,205,154,82,
15,166,51,21,151,155,106,149,42,146,126,174,60,129,140,108,
104,173,23,75,137,2,138,68,217,128,246,134,157,223,23,123,
163,196,168,102,165,230,38,133,209,204,115,181,61,218,130,141,
237,30,228,201,204,226,159,227,36,19,53,222,198,176,149,116,
50,247,245,169,156,247,49,98,98,247,184,236,172,181,144,81,
28,246,38,234,11,186,110,6,194,128,33,76,211,173,224,237,
17,224,61,8,93,81,165,3,232,14,146,38,86,254,91,222,
106,96,234,217,146,105,165,246,130,119,223,248,51,242,252,97,
86,189,95,254,214,229,181,144,58,78,152,163,185,222,170,199,
186,230,75,20,180,231,184,204,168,132,225,221,10,103,14,241,
219,124,178,215,245,161,248,189,108,25,121,172,196,186,111,108,
208,157,105,72,47,201,253,235,54,77,181,50,148,224,84,149,
83,232,106,152,184,154,219,32,130,81,87,24,36,232,211,166,
39,86,222,91,105,138,104,58,225,54,125,83,199,88,143,13,
135,193,177,127,253,21,82,214,191,237,142,121,223,3,228,104,
234,11,101,138,153,192,238,191,112,214,212,183,2,38,79,221,
167,48,239,164,235,238,232,90,35,149,182,207,227,150,74,22,
29,202,236,163,203,203,66,161,47,177,202,174,73,91,210,51,
87,55,241,127,95,50,233,169,183,61,113,189,203,56,145,183,
52,172,9,39,212,152,232,86,186,109,59,101,129,182,82,83,
201,152,63,80,96,47,254,238,139,254,37,79,53,221,239,156,
188,204,14,151,174,181,13,226,227,72,248,198,67,234,30,218,
110,158,184,82,202,44,167,17,237,132,161,17,1,212,19,52,
173,159,199,44,235,47,187,154,57,71,151,151,125,66,99,111,
155,92,157,183,164,101,110,111,229,254,206,93,211,76,110,70,
227,103,152,112,39,98,105,56,144,15,168,16,186,83,105,219,
212,77,206,146,158,116,195,250,139,0,127,247,108,31,241,38,
132,189,243,151,150,97,178,244,46,161,188,91,169,25,8,72,
101,67,221,77,209,213,26,89,165,244,230,29,145,148,96,34,
58,138,206,236,202,253,104,126,47,92,230,98,107,46,238,155,
219,43,231,93,82,203,18,127,122,205,237,109,75,37,88,148,
165,52,250,226,165,238,39,118,9,0,21,213,206,41,26,116,
233,142,123,114,229,182,152,169,139,173,243,103,210,188,245,8,
241,24,60,29,7,255,0,209,92,61,21,254,216,231,157,140,
50,70,177,160,182,95,105,154,6,243,247,13,21,75,177,38,
100,141,234,113,30,234,78,190,238,133,67,115,11,245,169,156,
246,201,126,98,200,184,236,172,202,144,73,60,134,37,42,11,
181,174,7,2,65,37,79,83,174,16,213,17,144,125,0,69,
81,213,19,234,6,130,96,183,14,91,222,105,162,234,41,146,
106,101,246,0,119,31,248,63,242,252,101,90,221,33,254,214,
229,181,236,54,78,167,163,185,217,106,207,188,231,203,21,84,
227,184,76,167,140,227,223,26,102,142,243,217,75,239,76,159,
205,44,186,113,212,94,214,13,211,110,180,209,217,51,211,244,
121,177,74,89,244,198,94,178,203,110,210,166,146,15,213,183,
150,49,136,109,109,162,233,110,36,86,200,155,44,14,210,211,
187,224,239,116,248,21,101,52,215,49,52,46,177,99,93,166,
46,212,21,143,112,247,37,206,103,20,127,41,36,137,173,246,
57,128,168,226,53,202,102,182,14,208,182,114,74,198,45,57,
64,176,45,191,187,100,39,98,163,87,150,255,0,65,81,75,
131,2,94,106,114,186,237,65,217,87,86,161,137,228,150,192,
199,0,2,116,71,93,164,166,178,208,192,200,167,151,190,59,
92,55,207,182,46,140,60,32,190,117,234,43,223,51,181,64,
115,46,215,122,223,167,119,92,185,78,250,121,100,121,75,36,
9,97,192,126,253,226,122,201,39,165,77,168,206,133,54,132,
182,220,192,66,16,148,161,8,65,9,66,16,144,18,148,165,
41,32,37,41,3,0,6,128,35,116,47,48,16,7,161,115,
23,114,212,61,197,239,100,92,76,73,61,36,147,218,87,94,
107,115,229,30,63,116,103,58,56,172,125,179,103,203,216,158,
107,115,229,30,63,116,51,163,138,125,179,103,203,216,158,107,
115,229,30,63,116,51,163,138,125,179,103,203,216,158,107,115,
229,30,63,116,51,163,138,125,179,103,203,216,158,107,115,229,
30,63,116,51,163,138,125,179,103,203,216,158,107,115,229,30,
63,116,51,163,138,125,179,103,203,216,185,94,116,41,196,41,
183,38,2,208,180,169,11,66,200,82,22,133,2,149,37,73,
81,33,73,80,56,16,116,17,24,55,152,136,19,208,178,222,
90,134,56,61,140,131,129,136,35,160,130,59,66,132,174,251,
103,36,175,146,235,149,251,2,219,251,183,130,182,234,52,137,
111,243,245,21,56,113,33,231,103,40,78,211,221,154,117,10,
56,142,113,112,28,48,32,167,68,105,106,233,172,181,209,51,
233,229,239,158,214,141,195,237,139,97,31,24,174,157,167,111,
124,206,210,225,172,180,221,235,126,157,189,82,230,187,234,37,
129,229,12,158,38,6,131,251,55,72,235,4,30,149,79,60,
130,247,92,241,196,67,48,118,42,197,250,70,95,151,98,121,
5,238,185,227,134,96,236,83,210,50,252,187,19,200,47,117,
207,28,51,7,98,158,145,151,229,216,158,65,123,174,120,225,
152,59,20,244,140,191,46,196,242,11,221,115,199,12,193,216,
167,164,101,249,118,39,144,94,235,158,56,102,14,197,61,35,
47,203,177,60,130,247,92,241,195,48,118,41,233,25,126,93,
137,228,23,186,231,142,25,131,177,79,72,203,242,236,79,32,
189,215,60,112,204,29,138,122,70,95,151,98,121,5,238,185,
227,134,96,236,83,210,50,252,187,21,97,238,238,239,157,113,
25,227,21,220,50,233,120,39,119,119,124,235,135,24,166,93,
47,4,238,238,239,157,112,227,20,203,165,224,157,221,221,243,
174,28,98,153,116,188,19,187,187,190,117,195,140,83,46,151,
130,119,119,119,206,184,113,138,101,210,240,78,238,238,249,215,
14,49,76,186,94,9,221,221,223,58,225,198,41,151,75,193,
59,187,187,231,92,56,197,50,233,120,39,119,119,124,235,135,
24,166,93,47,5,231,99,206,183,41,4,72,34,65,18,8,
144,68,130,36,17,32,137,4,95,255,217};

int selected = 0;

int window_cnt = 0;

extern void DrawBackGroud(void);

#include "UI_Flash_Lib.h"
#include "jpeg_decode.h"

void show_function(int x, int y, int counter )
{		
    if ( selected == 0 )                  		// 骑行
    {
        DrawUI_Bitmap_Ex((80-32)/2,8-4,32,32,bmp_function_back,0X42cc);	
        #if 0
        DrawUI_Bitmap(0,40,80,80,BMP_function_bycle,BMP_FUNCTION_BYCLE_RGB_F,BMP_FUNCTION_BYCLE_RGB_B);	
        #else
        draw_bitmap_from_flash( (80-64)/2, (160-64)/2, 64, 64, FLASH_BASE_ADDR+0x0000);
        #endif
        
        DrawUI_JPEG( 0, 160-34, jpeg_ui_bg_yellow );
        
        // 双色
        #if 0
        DrawUI_Bitmap((80-32)/2,120,32,32,bmp_hr_1, 0X3000,0x00); 
        DrawUI_Bitmap_Ex((80-32)/2,120+4,32,32,bmp_hr_2, 0X3000);
        #else
        DrawUI_Bitmap_Ex((80-32)/2,120+4,32,32, bmp_hr_hr, 0xFFFF);
        #endif
    }else if ( selected == 1 )                 	// 心率
    {	
        DrawUI_Bitmap_Ex((80-32)/2,8-4,32,32,bmp_function_bycle,0X42cc);		
        
        #if 0
        // 双色
        DrawUI_Bitmap(0,40,80,80,BMP_hr_1, 0x1F<<11,0x00); 
        DrawUI_Bitmap_Ex(0,40,80,80,BMP_hr_2, 0xFFFF);	
        #else
        draw_bitmap_from_flash( (80-64)/2, (160-64)/2, 64, 64, FLASH_BASE_ADDR+0x2000);
        #endif
        
        DrawUI_JPEG( 0, 160-34, jpeg_ui_bg_red );
        
        DrawUI_Bitmap_Ex((80-32)/2,120+4,32,32,bmp_function_sleep,0xFFFF);	
    }else if ( selected == 2 )                  // 睡眠
    {
        // 双色
        #if 0
        DrawUI_Bitmap_Ex((80-32)/2,8-4,32,32,bmp_hr_1, 0X42cc); 
        DrawUI_Bitmap_Ex((80-32)/2,8,32,32,bmp_hr_2, 0X3000);
        #endif
        DrawUI_Bitmap_Ex((80-32)/2,8-4,32,32, bmp_hr_hr, 0X42cc);
        #if 0
        DrawUI_Bitmap(0,40,80,80,BMP_function_sleep,0XF81F,BMP_FUNCTION_SLEEP_RGB_B);
        #else
        draw_bitmap_from_flash( (80-64)/2, (160-64)/2, 64, 64, FLASH_BASE_ADDR+0x4000);
        #endif
        
        DrawUI_JPEG( 0, 160-34, jpeg_ui_bg_blue );
        
        DrawUI_Bitmap_Ex((80-32)/2,120+4,32,32,bmp_function_alarm,0xFFFF);		
    } else if ( selected == 3 )					// 闹钟
    {
        DrawUI_Bitmap_Ex((80-32)/2,8-4,32,32,bmp_function_sleep,0X42cc);	
        #if 0
        DrawUI_Bitmap(0,40,80,80,BMP_function_alarm,BMP_FUNCTION_ALARM_RGB_F,BMP_FUNCTION_ALARM_RGB_B);
        #else
        draw_bitmap_from_flash( (80-64)/2, (160-64)/2, 64, 64, FLASH_BASE_ADDR+0x6000);
        #endif 
        DrawUI_JPEG( 0, 160-34, jpeg_ui_bg_yellow );
        
        DrawUI_Bitmap_Ex((80-32)/2+3,120+4,32,32,bmp_function_findphone,0xFFFF);			
    } else if ( selected == 4 )               	// 手机
    {
        DrawUI_Bitmap_Ex((80-32)/2,8-4,32,32,bmp_function_alarm,0X42cc);	
        #if 0
        DrawUI_Bitmap(0,40,80,80,BMP_function_findphone,BMP_FUNCTION_FINDPHONE_RGB_F,BMP_FUNCTION_FINDPHONE_RGB_B);
        #else
        draw_bitmap_from_flash( (80-64)/2+8, (160-64)/2, 64, 64, FLASH_BASE_ADDR+0x8000);
        #endif  
        DrawUI_JPEG( 0, 160-34, jpeg_ui_bg_blue ); 
        
        DrawUI_Bitmap_Ex((80-32)/2,120+4,32,32,bmp_function_info,0xFFFF);		
    } else if ( selected == 5 )                 // 信息
    {
        DrawUI_Bitmap_Ex((80-32)/2+3,8-4,32,32,bmp_function_findphone,0X42cc);
        #if 0
        DrawUI_Bitmap(0,40,80,80,BMP_function_info,BMP_FUNCTION_INFO_RGB_F,BMP_FUNCTION_INFO_RGB_B);
        #else
        draw_bitmap_from_flash( (80-64)/2, (160-64)/2, 64, 64, FLASH_BASE_ADDR+0xa000);
        #endif   
        DrawUI_JPEG( 0, 160-34, jpeg_ui_bg_yellow );
        DrawUI_Bitmap_Ex((80-32)/2,120+4,32,32,bmp_function_shutdown,0xFFFF);	
    } else if ( selected == 6 )					// 关机
    {
        DrawUI_Bitmap_Ex((80-32)/2,8-4,32,32,bmp_function_info,0x42cc);
        #if 0
        DrawUI_Bitmap(0,40,80,80,BMP_function_shutdown,BMP_FUNCTION_SHUTDOWN_RGB_F,BMP_FUNCTION_SHUTDOWN_RGB_B);
        #else
        draw_bitmap_from_flash( (80-64)/2, (160-64)/2, 64, 64, FLASH_BASE_ADDR+0xc000);
        #endif        
        DrawUI_JPEG( 0, 160-34, jpeg_ui_bg_red );        
        DrawUI_Bitmap_Ex((80-32)/2,120+4,32,32,bmp_function_back,0xFFFF);
    }else if ( selected == 7 )					// 返回
    {
        DrawUI_Bitmap_Ex((80-32)/2,8-4,32,32,bmp_function_shutdown,0X42cc);
        #if 0
        DrawUI_Bitmap(0,40,80,80,BMP_function_back,BMP_FUNCTION_BACK_RGB_F,BMP_FUNCTION_BACK_RGB_B); 
        #else
        draw_bitmap_from_flash( (80-64)/2, (160-64)/2, 64, 64, FLASH_BASE_ADDR+0xe000);
        #endif      
        DrawUI_JPEG( 0, 160-34, jpeg_ui_bg_blue );
        DrawUI_Bitmap_Ex((80-32)/2,120+4,32,32,bmp_function_bycle,0xFFFF);		
    }else{
        selected = 0;
    }
}

unsigned long win_function_proc(unsigned long wid, unsigned long msg_type, 
                            unsigned long msg_param, unsigned long *p)
{
	if ( msg_type & WINDOW_CREATE )
	{
		win_ticks = 0; // selected = 0;

		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);
		}		

		osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
		
		return ( msg_type ^ WINDOW_CREATE );
	}
	
	if ( msg_type & WINDOW_UPDATE )
	{
		win_ticks++;
		
		if ( win_ticks > 5 )
		{
			lcd_display(0);
			
			return ( msg_type ^ WINDOW_UPDATE );
		}

		/**
		 *  增加以下语句,2秒内自动跳转选中的功能界面
		 */
		// if ( win_ticks > 3 )
		// {
		//	msg_type |= WINDOW_SWITCH;
		//	return ( msg_type ^ WINDOW_UPDATE );
		// }		
		
		// memset(frame_buffer, 0x00, sizeof(frame_buffer));
        
		DrawBackGroud();
		show_function( 28, 20, pedometer.calorie);
		sync_frame();
		
		osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 500);
		
		return ( msg_type ^ WINDOW_UPDATE );
	}
	
	if ( msg_type & WINDOW_TOUCH )
	{		
		win_ticks = 0;
		
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);			
		}else{	

			if ( selected == 7 )
			{
				window_push(WIN_ID_TIMER); 	 // back window
				msg_type |= WINDOW_DISTORY;
				return ( msg_type ^ WINDOW_TOUCH );
			} else {
				selected++; selected %= 8;
			}
		}
		
		msg_type |= WINDOW_UPDATE;
		
		return ( msg_type ^ WINDOW_TOUCH );
	}
	
	if ( msg_type & WINDOW_SWITCH )
	{
		win_ticks = 0;
		
		window_push(win_current);	
		
		switch ( selected )
		{
		case 0:	
			window_push(WIN_ID_SPORT); 	 // bycle window
			break;
		case 1:
			window_push(WIN_ID_HR); 	 // hr window
			break;
		case 2:
			window_push(WIN_ID_SLEEP); 	 // sleep window
			break;
		case 3:
			window_push(WIN_ID_ALARM); 	 // alarm window
			break;
		case 4:
			window_push(WIN_ID_FIND); 	 // findphone window
			break;
		case 5:
			window_push(WIN_ID_INFO);  	 // info window
			break;
		case 6:
			window_push(WIN_ID_SHUTDOWN);// shutdown window
			break;	
		case 7:
			window_push(WIN_ID_TIMER); 	 // back window
			break;
		default:
			break;
		}
		
		msg_type |= WINDOW_DISTORY;
		
		// lcd_display(0);
			
		return ( msg_type ^ WINDOW_SWITCH );
	}
	
	if ( msg_type & WINDOW_PRESS )
	{		
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);
			msg_type |= WINDOW_UPDATE;
		}else{
			msg_type |= WINDOW_SWITCH;
		}
		
		win_ticks = 0;
		
		return ( msg_type ^ WINDOW_PRESS );
	}
	
	if ( msg_type & WINDOW_NOTIFY )
	{   
        /* 当前窗体入栈 */
        window_push( win_current );
        
        /* 通知界面作为当前界面 */
        win_current = NOTIFY_WIN_ID_GET();
        
        /* 调用窗体回调函数以便创建窗体  */
        window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0);
		
		return ( msg_type ^ WINDOW_NOTIFY );
	}	
	
	if ( msg_type & WINDOW_DISTORY )
	{
		window_pop(&win_current);
		
		return window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0 );
	}	
	
	return 0;
}


#include "OSAL.h"
#include "OSAL_Timer.h"

#include "Task_GUI.h"
#include "Task_Step.h"
#include "LCD_ST7735.h"

#include "string.h"
#include "Window.h"
#include "UserSetting.h"
#include "UI_Draw.h"

#include "UI_pedometer_icon.h"
#include "UI_comm_icon.h"
#include "UI_Comm_Draw.h"
#include "QR_Utils.h"
#include "UI_main_icon.h"
#include "UI_function_icon.h"

const unsigned char jpeg_ui_Font_16x16_0[] = 
{255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
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
17,8,0,16,0,16,3,1,17,0,2,17,1,3,17,1,
255,196,0,101,0,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,2,0,9,1,1,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,6,9,16,0,1,
5,1,1,1,1,0,0,0,0,0,0,0,0,0,4,3,
5,6,7,8,2,9,1,18,17,0,2,2,3,0,2,3,
1,1,0,0,0,0,0,0,0,2,3,1,4,5,6,7,
0,17,193,34,8,18,145,255,218,0,12,3,1,0,2,17,
3,17,0,63,0,206,251,171,72,208,254,69,227,31,49,163,
85,54,3,200,87,172,195,83,228,88,78,151,183,44,157,33,
92,139,97,74,156,166,19,216,204,65,248,224,194,114,235,145,
29,81,110,9,201,248,164,198,67,178,187,20,80,248,69,20,
81,79,239,42,40,175,22,116,62,93,208,255,0,104,247,78,
177,149,220,186,62,235,175,97,53,13,210,214,15,29,71,9,
116,169,215,10,213,31,101,32,68,31,101,201,144,37,114,101,
11,134,49,178,195,54,20,72,8,107,93,97,24,154,117,133,
85,210,102,213,65,148,156,123,159,115,17,63,62,84,174,145,
161,253,116,198,62,156,198,173,156,7,144,168,169,134,88,200,
179,109,47,81,217,57,190,185,22,189,149,54,204,32,81,153,
123,240,33,154,229,207,37,186,172,220,107,147,8,169,146,135,
5,112,41,65,246,178,43,34,167,222,147,81,38,249,203,186,
31,226,238,233,201,242,186,111,71,221,118,28,38,223,186,85,
193,228,104,230,238,149,202,231,90,219,235,36,200,67,234,184,
49,7,50,64,165,114,197,182,22,96,193,136,49,50,108,35,
45,78,200,182,186,64,212,169,49,144,143,83,238,34,103,227,
197,118,102,202,35,215,44,97,230,36,158,166,223,153,2,138,
151,229,172,135,9,205,86,213,107,163,236,128,235,249,91,100,
190,5,27,137,71,206,48,86,207,170,24,237,211,121,174,113,
242,148,25,85,68,76,98,129,237,5,209,89,79,218,156,39,
52,62,167,208,255,0,23,247,78,179,137,220,185,198,237,176,
225,118,237,214,214,115,29,123,9,72,174,87,101,107,111,176,
224,18,103,161,95,246,43,114,197,130,44,35,91,97,139,96,
15,242,36,71,86,70,90,157,98,85,132,129,169,48,5,7,
62,167,220,68,71,199,249,225,165,115,117,15,228,94,49,244,
230,75,108,239,204,133,122,204,53,62,69,155,102,138,142,182,
205,246,48,182,20,169,202,97,61,140,203,216,65,48,214,222,
122,17,213,22,224,156,159,133,80,149,248,23,177,69,15,133,
150,89,100,254,242,154,106,221,243,168,244,63,218,61,211,147,
226,180,222,113,186,235,216,77,67,116,171,156,200,222,205,210,
42,117,194,181,71,214,113,136,159,217,114,100,9,100,0,203,
33,140,108,172,1,101,18,100,4,215,70,38,157,146,109,132,
153,181,82,3,1,62,231,220,196,199,207,159,255,217};

const unsigned char jpeg_ui_Font_16x16_1[] = {255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
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
17,8,0,16,0,16,3,1,17,0,2,17,1,3,17,1,
255,196,0,95,0,1,1,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,10,1,1,1,1,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,4,8,16,0,1,5,0,
3,1,0,0,0,0,0,0,0,0,0,0,5,1,2,3,
4,6,0,8,9,7,17,0,2,2,2,3,1,0,0,0,
0,0,0,0,0,0,0,1,2,3,5,33,4,0,6,8,
17,255,218,0,12,3,1,0,2,17,3,17,0,63,0,143,
159,43,179,121,221,135,164,61,34,203,107,64,133,212,230,52,
29,150,249,64,163,217,205,24,186,38,192,155,23,115,86,62,
27,131,75,136,39,5,161,228,168,91,133,202,201,97,154,55,
199,35,85,81,200,169,204,229,235,219,75,58,79,46,247,235,
122,109,153,245,45,181,186,173,132,144,207,4,143,20,209,72,
186,238,85,227,146,50,174,142,167,42,202,193,129,200,60,190,
173,85,236,96,87,0,169,145,126,131,144,115,199,170,57,188,
238,63,210,30,238,229,178,64,66,229,179,25,254,203,125,92,
80,28,230,112,93,16,128,66,11,167,171,33,13,49,162,4,
12,130,168,241,180,42,66,212,100,80,195,27,35,141,168,136,
212,68,227,200,86,150,119,126,93,232,54,247,59,51,237,219,
108,245,90,249,38,158,121,30,89,165,145,181,208,179,201,36,
133,157,221,142,89,153,139,19,146,120,180,85,75,25,213,0,
10,36,111,128,96,12,241,229,118,147,59,143,244,135,164,90,
157,105,224,185,108,198,127,178,223,40,42,123,71,163,41,68,
32,16,130,233,234,199,205,112,145,114,228,231,170,60,109,10,
144,181,95,44,211,72,200,227,106,42,185,81,56,245,237,93,
157,223,151,123,245,69,54,180,251,118,219,61,86,194,56,96,
130,55,150,105,100,109,119,10,145,199,24,103,119,99,133,85,
82,196,224,14,42,217,82,198,6,114,2,137,23,233,56,3,
60,122,163,164,206,236,61,33,238,238,167,36,120,46,167,49,
160,236,183,213,202,129,209,231,10,81,54,4,216,187,154,178,
19,83,36,32,184,201,237,15,37,66,220,46,71,197,52,50,
62,57,26,168,173,85,78,60,133,87,103,73,229,222,131,81,
115,173,62,165,182,183,85,175,142,104,39,141,226,154,41,23,
93,3,36,145,200,21,209,212,225,149,148,48,56,35,139,70,
87,177,157,144,130,166,70,248,70,65,207,63,255,217};

const unsigned char jpeg_ui_Font_16x16_2[] ={255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
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
17,8,0,16,0,16,3,1,17,0,2,17,1,3,17,1,
255,196,0,120,0,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,9,7,10,1,0,2,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,5,8,3,6,9,16,0,
0,6,2,2,2,2,3,1,0,0,0,0,0,0,0,3,
4,5,6,7,8,1,2,21,9,19,22,0,23,17,18,34,
25,17,0,1,3,3,2,5,3,4,3,0,0,0,0,0,
0,0,1,2,3,4,17,5,7,18,6,0,33,81,19,8,
49,65,20,129,225,34,36,21,22,23,255,218,0,12,3,1,
0,2,17,3,17,0,63,0,206,140,23,221,223,210,48,220,
103,16,127,155,157,116,73,31,91,50,208,89,222,253,34,193,
156,235,237,225,193,16,4,143,176,59,150,121,64,185,53,245,
63,23,148,200,223,174,190,65,54,206,127,31,51,231,32,248,
13,253,251,124,93,119,175,250,150,78,181,255,0,41,61,233,
63,14,21,215,181,18,55,117,101,125,152,205,118,207,109,150,
235,165,9,169,162,64,28,27,98,245,216,101,44,252,104,234,
210,0,169,77,73,167,185,61,120,107,226,253,202,246,11,65,
110,252,149,121,186,183,171,180,142,10,98,87,87,60,141,5,
217,168,254,34,2,18,117,143,41,35,38,31,56,213,17,154,
10,246,224,187,221,73,199,84,48,91,80,6,79,223,68,197,
97,179,197,109,131,123,157,192,90,33,187,181,47,120,217,228,
110,192,218,222,63,101,205,219,191,178,21,199,115,177,10,237,
98,153,113,55,72,226,3,174,33,50,4,146,205,99,71,90,
81,172,173,47,2,252,116,254,224,44,165,130,181,26,106,151,
8,15,185,58,43,76,48,150,201,74,194,116,157,67,210,149,
230,126,156,143,167,58,241,102,169,212,195,175,154,137,92,98,
23,237,89,148,122,199,146,110,187,137,140,213,114,186,230,235,
215,97,209,215,210,227,103,90,203,125,57,81,72,22,20,74,
213,220,233,84,145,82,84,78,152,42,95,33,154,69,86,42,
30,152,193,147,135,51,157,131,197,27,50,103,79,36,243,78,
80,189,109,220,187,104,202,246,172,15,22,225,33,136,246,173,
167,102,113,151,39,71,105,229,182,131,46,227,32,37,78,7,
16,132,56,189,77,202,142,226,141,90,97,138,5,25,162,195,
183,196,142,133,197,84,101,77,41,4,169,213,214,132,143,100,
143,177,234,79,7,15,96,52,210,230,218,70,195,254,87,179,
125,218,80,153,185,49,128,215,117,63,146,33,150,141,135,9,
53,177,184,173,116,69,5,144,16,99,184,153,182,136,142,206,
246,181,32,9,106,68,160,249,43,178,137,209,114,22,163,153,
23,127,239,227,65,227,126,114,193,152,142,237,109,217,216,163,
2,228,91,4,171,148,184,240,220,185,201,179,21,190,3,238,
161,162,244,219,139,238,185,39,227,160,168,186,226,59,129,150,
147,172,182,210,19,248,240,58,124,57,146,146,167,100,205,97,
97,32,157,33,124,185,10,208,36,10,87,219,169,235,199,255,
217};

const unsigned char jpeg_ui_Font_16x16_3[] ={255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
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
17,8,0,16,0,16,3,1,17,0,2,17,1,3,17,1,
255,196,0,109,0,1,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,8,1,1,1,1,1,0,0,0,0,0,
0,0,0,0,0,0,0,4,7,6,9,16,0,1,4,3,
1,0,2,2,3,0,0,0,0,0,0,0,5,3,4,6,
7,1,2,9,8,0,17,33,10,34,20,22,17,0,1,4,
1,3,4,3,1,1,0,0,0,0,0,0,0,2,1,3,
4,5,17,33,6,7,0,49,18,8,65,81,19,20,97,255,
218,0,12,3,1,0,2,17,3,17,0,63,0,16,81,150,
143,79,25,210,116,243,72,151,235,237,227,123,46,40,214,172,
175,155,198,108,99,190,113,16,80,220,254,60,132,72,66,65,
102,198,9,239,46,67,114,37,101,67,117,77,251,133,243,166,
153,89,101,246,223,58,227,239,235,231,15,121,3,104,250,156,
254,253,187,122,231,217,45,241,85,112,118,243,9,248,77,93,
184,219,80,222,89,14,43,177,91,109,35,170,3,113,207,201,
160,12,175,136,130,38,87,29,107,216,114,205,25,4,8,12,
144,120,166,21,65,50,169,141,21,117,249,239,210,10,213,164,
142,122,127,154,189,7,156,116,55,150,158,110,231,164,179,207,
21,75,139,35,205,119,5,93,10,139,86,82,41,37,132,204,
41,210,12,33,73,53,106,236,129,253,218,158,149,6,14,21,
198,23,121,150,5,127,208,36,138,77,178,241,174,139,105,54,
217,251,246,191,137,189,167,227,90,15,90,57,119,116,242,93,
54,230,184,24,87,149,179,229,72,156,203,16,201,214,128,229,
41,16,131,40,76,199,118,76,160,240,107,246,143,252,102,225,
186,140,186,64,72,117,130,147,91,32,236,34,183,28,219,12,
129,10,34,42,174,186,125,234,168,137,244,185,237,148,232,151,
73,249,211,164,37,41,170,144,156,91,246,22,243,77,103,24,
35,88,192,159,71,43,114,190,211,149,129,41,95,1,119,21,
20,224,68,32,144,52,81,202,33,95,197,7,168,155,5,154,
105,252,91,40,223,41,227,241,175,203,46,252,228,239,87,98,
111,155,168,150,254,180,238,171,91,102,173,165,131,243,91,219,
17,222,110,99,195,33,196,114,80,58,171,151,66,65,161,60,
46,46,166,38,132,189,250,35,49,236,85,144,81,176,108,69,
69,48,159,162,166,19,29,177,241,142,221,43,202,217,187,248,
227,159,189,1,143,116,79,171,212,127,68,201,250,18,153,47,
90,208,180,36,34,220,66,236,52,222,120,230,61,32,96,42,
68,196,145,37,87,152,0,213,180,148,232,215,78,92,183,104,
139,0,250,13,77,246,87,221,231,245,83,214,57,15,106,15,
56,123,35,198,246,126,178,240,237,255,0,25,68,219,87,173,
206,183,183,149,92,181,109,44,65,121,147,113,147,0,68,140,
247,147,13,62,216,1,184,79,73,87,202,58,54,44,126,164,
171,87,127,142,4,129,176,148,18,21,192,84,17,66,242,92,
225,117,251,77,85,63,196,198,123,227,175,255,217};

const unsigned char jpeg_ui_Font_16x16_4[]={255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
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
17,8,0,16,0,16,3,1,17,0,2,17,1,3,17,1,
255,196,0,108,0,0,3,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,6,9,10,1,0,3,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,2,6,9,5,16,0,1,
4,3,1,1,1,1,0,0,0,0,0,0,0,0,4,2,
3,5,6,1,7,8,9,0,17,33,17,0,2,2,1,2,
6,3,0,3,0,0,0,0,0,0,0,1,2,3,4,5,
6,7,0,17,33,49,18,8,65,97,19,81,161,241,255,218,
0,12,3,1,0,2,17,3,17,0,63,0,93,30,162,121,
111,186,187,70,173,231,246,251,243,111,152,233,119,253,63,99,
226,157,116,37,190,119,76,61,167,233,35,21,177,135,36,195,
166,223,182,71,170,114,174,233,214,100,181,38,216,197,16,234,
31,33,178,196,124,103,148,151,71,90,19,23,61,73,246,227,
65,236,86,95,114,54,235,218,77,89,123,27,173,170,235,203,
173,90,28,152,201,90,101,164,202,169,16,174,255,0,149,128,
144,115,140,201,26,41,84,49,201,28,168,10,74,172,91,50,
152,201,174,45,121,241,209,6,132,194,57,149,241,29,126,251,
117,255,0,56,35,242,15,200,126,150,231,121,46,221,186,119,
95,30,195,195,82,31,226,173,166,38,188,146,218,2,106,125,
136,8,91,20,87,226,165,66,42,0,49,38,173,164,66,207,
141,16,1,78,54,106,26,97,72,66,84,156,59,140,171,24,
206,103,186,190,233,237,94,230,85,208,56,47,94,245,180,243,
231,215,94,99,218,234,80,108,133,39,106,76,36,141,150,102,
104,171,172,176,180,143,24,104,139,48,36,130,83,144,230,11,
17,137,179,92,204,247,161,1,63,22,229,229,226,122,253,119,
235,247,196,190,234,142,191,235,77,13,4,245,91,70,245,23,
69,105,154,201,5,58,115,245,205,81,187,54,94,187,130,124,
231,243,140,190,99,209,21,11,52,60,123,133,61,148,227,43,
115,45,229,106,252,254,231,234,211,172,118,83,102,183,19,34,
185,125,192,210,58,99,59,150,84,8,38,200,98,232,221,152,
32,236,162,75,48,72,225,71,194,134,228,62,7,11,49,91,
183,2,248,193,44,136,191,194,177,3,250,60,81,7,135,158,
130,238,27,173,155,186,224,251,23,183,118,85,182,166,87,13,
109,70,40,144,253,47,210,150,137,234,233,55,210,228,33,3,
13,154,148,126,210,186,21,26,245,184,152,215,200,105,164,134,
140,154,182,22,226,83,250,140,171,31,76,223,127,125,109,209,
56,28,86,222,228,54,71,64,226,169,102,83,112,49,230,220,
152,60,29,120,102,90,138,146,179,27,15,66,170,184,172,174,
17,152,202,127,32,225,73,234,7,12,24,76,132,206,243,173,
201,216,167,224,220,188,220,145,207,167,111,35,223,143,255,217,
};

const unsigned char jpeg_ui_Font_16x16_5[] ={255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
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
17,8,0,16,0,16,3,1,17,0,2,17,1,3,17,1,
255,196,0,114,0,0,3,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,5,7,8,9,1,0,2,3,1,0,0,
0,0,0,0,0,0,0,0,0,0,4,7,1,5,8,10,
16,0,1,4,3,1,0,3,1,1,0,0,0,0,0,0,
0,4,2,5,6,7,1,3,8,9,17,19,20,0,10,17,
0,2,2,1,2,6,2,2,3,0,0,0,0,0,0,0,
2,3,1,4,5,17,6,0,33,18,19,7,8,49,65,81,
20,97,129,145,255,218,0,12,3,1,0,2,17,3,17,0,
63,0,106,116,133,127,210,213,60,59,148,67,225,79,28,56,
143,171,97,18,110,93,171,164,214,28,242,123,81,212,226,189,
183,88,166,53,227,81,173,43,218,92,162,14,65,223,161,163,
72,166,236,220,189,4,41,123,137,86,115,183,57,249,74,121,
145,241,118,228,241,94,242,206,111,23,251,9,231,13,253,179,
179,245,55,117,244,83,169,83,35,144,37,29,33,102,162,200,
129,69,161,14,150,75,21,3,4,17,2,17,160,68,115,150,
13,149,217,80,42,40,211,75,66,84,51,51,34,58,235,254,
199,25,1,223,183,71,161,149,247,49,218,173,151,247,134,28,
105,207,117,236,234,30,239,10,117,188,171,122,29,137,193,222,
178,204,159,66,153,69,146,9,47,132,75,165,65,194,94,6,
48,180,96,18,206,250,117,254,165,107,74,115,149,41,41,206,
215,245,199,98,250,209,185,60,177,135,183,227,143,96,183,206,
229,220,184,251,203,180,188,85,220,179,65,119,187,19,221,36,
21,107,85,171,149,165,144,140,247,86,174,169,237,193,76,233,
17,51,21,55,221,144,93,99,135,209,74,214,81,167,84,12,
106,58,253,235,19,58,127,124,14,169,57,11,208,233,85,83,
89,73,217,191,209,101,69,94,52,72,235,232,99,243,84,1,
227,209,235,194,60,237,6,109,120,142,54,184,3,15,116,96,
22,70,145,88,220,99,34,144,144,183,135,175,24,214,54,221,
10,214,156,124,39,31,196,239,63,53,122,207,136,222,25,108,
77,239,88,243,89,59,181,114,86,146,203,139,217,88,167,46,
217,173,230,7,101,110,36,117,52,30,67,45,22,23,51,19,
130,158,115,196,42,166,64,212,37,25,0,24,145,137,211,188,
81,167,47,141,53,229,167,199,22,188,34,97,187,128,120,227,
189,220,61,1,245,246,174,244,40,123,202,129,148,84,149,15,
57,176,116,100,151,164,28,157,230,114,40,228,129,160,83,2,
84,186,66,231,49,142,234,52,199,157,2,157,185,188,93,13,
193,134,165,24,89,31,110,161,146,148,62,127,8,30,199,249,
195,199,85,189,110,240,166,95,198,140,219,251,141,25,28,150,
105,216,84,97,1,117,82,244,176,132,191,89,43,172,233,17,
81,177,66,230,19,154,200,132,37,93,6,217,147,64,255,0,
66,155,230,253,177,177,6,185,17,8,57,62,115,19,249,157,
99,249,211,151,220,253,113,255,217};

const unsigned char jpeg_ui_Font_16x16_6[] ={255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
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
17,8,0,16,0,16,3,1,17,0,2,17,1,3,17,1,
255,196,0,117,0,0,3,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,2,5,8,9,1,0,1,5,1,0,0,
0,0,0,0,0,0,0,0,0,0,4,2,5,6,7,8,
10,16,0,1,5,1,1,0,1,4,3,0,0,0,0,0,
0,0,4,2,3,5,6,7,8,9,1,0,17,34,19,20,
21,22,17,0,2,2,1,3,3,4,2,3,0,0,0,0,
0,0,0,2,3,1,4,5,17,6,7,0,33,8,65,81,
18,20,113,19,97,145,193,255,218,0,12,3,1,0,2,17,
3,17,0,63,0,43,23,47,109,60,105,207,156,117,155,121,
241,228,23,44,118,156,61,147,157,233,154,30,221,185,238,149,
28,238,193,110,153,214,45,96,12,100,184,207,191,106,182,214,
231,210,167,191,35,80,143,146,11,8,65,75,96,65,82,203,
99,125,149,205,246,51,150,182,39,57,114,86,247,221,62,74,
115,94,239,216,151,106,238,107,84,177,88,156,77,155,169,172,
172,125,115,33,89,68,87,174,244,246,236,169,159,130,218,198,
45,142,108,153,55,88,158,149,87,83,174,149,208,168,167,68,
174,36,136,162,38,126,83,249,152,159,243,210,58,205,126,252,
216,125,16,160,114,246,174,30,249,225,127,25,115,230,117,119,
168,75,82,38,55,44,219,11,175,72,205,230,31,234,25,254,
144,75,56,214,170,61,198,212,197,30,76,115,142,105,0,156,
127,195,12,127,49,109,161,42,83,139,74,126,117,63,142,59,
35,198,109,199,203,120,103,241,207,144,91,231,114,238,122,23,
87,105,88,171,217,103,2,175,253,121,253,164,130,175,106,181,
121,180,178,0,41,106,147,38,95,170,12,166,32,98,102,27,
111,187,32,21,78,31,69,43,89,70,159,40,24,212,117,245,
214,38,116,252,207,86,190,177,167,159,233,159,45,113,46,139,
196,126,197,211,248,42,237,148,226,144,57,118,253,134,92,122,
126,237,206,171,85,186,42,10,12,71,228,203,141,168,218,98,
165,37,202,139,152,136,48,112,77,126,56,129,36,163,29,105,
230,10,109,77,184,202,232,109,157,180,235,248,167,203,187,247,
108,115,231,8,93,228,92,14,99,60,235,248,124,181,108,13,
92,212,125,102,53,165,11,19,179,93,139,88,177,108,89,181,
64,224,98,30,38,12,81,65,11,4,214,182,114,85,82,202,
87,5,6,33,2,67,39,33,223,72,246,159,235,183,120,245,
233,61,34,230,87,159,188,119,222,114,157,253,235,222,91,232,
104,219,134,7,102,201,114,46,111,129,232,139,15,74,73,204,
93,108,80,19,145,1,158,26,174,150,73,43,101,120,82,10,
153,104,105,21,128,27,81,194,132,165,24,81,31,181,145,145,
244,118,127,4,159,36,121,187,142,234,120,225,194,185,126,52,
110,3,113,163,35,146,205,187,12,156,26,215,85,46,83,8,
11,234,160,43,184,132,84,70,152,107,9,204,108,66,82,191,
129,180,186,72,28,208,166,249,191,108,108,65,174,68,66,14,
79,188,196,251,206,177,252,233,219,78,243,233,215,255,217};

const unsigned char jpeg_ui_Font_16x16_7[] ={255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
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
17,8,0,16,0,16,3,1,17,0,2,17,1,3,17,1,
255,196,0,116,0,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,8,9,10,1,0,2,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,4,5,7,8,9,16,0,
0,7,1,0,3,0,3,0,0,0,0,0,0,0,0,1,
2,3,4,5,6,7,8,0,17,9,18,21,10,17,0,1,
3,3,2,4,5,5,1,0,0,0,0,0,0,0,1,2,
3,4,17,5,6,0,7,33,65,18,8,81,97,113,19,20,
49,129,145,34,50,9,255,218,0,12,3,1,0,2,17,3,
17,0,63,0,206,143,4,125,70,186,230,89,246,29,198,185,
199,205,174,25,233,203,242,214,105,10,125,58,213,169,226,99,
115,215,180,59,22,145,162,78,79,196,198,205,206,126,205,177,
95,158,57,229,168,177,172,204,98,144,141,163,90,34,83,136,
21,49,55,153,243,220,95,104,246,28,175,37,200,55,203,40,
221,45,193,196,241,196,196,68,153,49,237,247,79,139,109,132,
204,40,77,50,226,218,107,161,93,1,105,142,95,112,2,74,
223,113,100,2,84,6,157,192,185,173,166,209,13,184,204,58,
229,104,10,147,85,18,73,60,79,222,158,154,121,255,0,70,
29,15,136,103,209,89,103,4,229,184,87,42,210,183,88,90,
245,46,255,0,217,55,220,19,30,167,84,227,225,110,238,97,
24,75,66,228,116,121,176,135,11,108,124,16,187,116,51,111,
65,119,0,233,70,103,139,77,67,128,157,226,62,87,127,243,
19,108,243,236,146,101,223,184,172,187,33,204,39,237,235,242,
101,67,198,98,93,238,82,100,45,216,169,117,109,187,113,150,
215,185,241,214,239,74,126,43,93,8,246,210,232,150,164,138,
6,92,209,249,12,134,27,9,128,211,109,37,240,1,112,165,
32,113,167,242,57,211,159,227,207,70,79,145,18,220,243,192,
252,249,187,125,93,217,109,25,141,187,123,165,199,205,100,252,
65,206,207,45,85,247,247,121,61,58,202,193,212,20,174,167,
59,74,109,46,141,158,58,174,192,174,213,98,15,63,4,76,
72,148,38,20,39,181,142,192,199,149,251,211,135,185,125,198,
110,86,61,217,222,13,18,237,11,110,167,56,213,199,42,189,
38,59,200,138,220,6,22,151,91,183,181,41,77,150,22,250,
250,82,239,183,85,3,33,112,82,175,208,72,0,107,73,143,
2,58,238,175,20,151,211,84,182,138,138,212,240,234,35,235,
78,94,149,242,212,9,209,180,59,174,185,126,185,234,58,61,
138,70,219,126,208,108,211,87,11,141,154,89,97,94,70,114,
197,96,126,188,156,180,147,165,61,1,64,238,94,56,49,128,
165,2,145,50,250,41,0,165,0,0,209,172,95,25,176,225,
152,228,28,75,23,138,212,44,114,219,17,168,209,152,108,81,
13,50,202,2,27,66,71,130,82,144,42,106,73,226,73,36,
157,33,113,197,186,225,117,194,75,138,53,39,196,157,127,255,
217};

const unsigned char jpeg_ui_Font_16x16_8[] ={255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
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
17,8,0,16,0,16,3,1,17,0,2,17,1,3,17,1,
255,196,0,109,0,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,3,7,1,1,0,3,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,2,6,10,16,0,
1,4,3,1,0,3,0,0,0,0,0,0,0,0,0,5,
3,4,6,7,2,8,9,1,17,19,21,17,0,2,2,1,
3,2,7,1,1,0,0,0,0,0,0,0,2,3,1,4,
5,17,6,7,49,8,0,33,81,97,18,19,20,35,21,255,
218,0,12,3,1,0,2,17,3,17,0,63,0,201,235,170,
70,69,171,188,231,231,188,199,157,92,180,214,222,131,151,216,
26,117,149,151,178,86,245,171,11,140,90,82,112,214,105,80,
17,130,47,162,255,0,67,162,34,207,48,96,26,72,76,208,
164,145,73,124,153,11,252,111,91,42,142,15,51,85,85,185,
241,220,251,251,25,203,125,206,242,86,19,185,190,93,221,60,
107,75,109,231,10,142,19,27,143,180,250,8,109,21,185,224,
15,212,65,137,51,106,2,173,130,34,8,107,255,0,76,52,
12,144,32,11,220,45,5,91,31,92,241,245,87,98,88,31,
35,34,136,41,215,72,242,245,235,172,123,105,167,95,11,22,
145,145,109,23,57,250,17,49,232,175,45,53,183,159,5,245,
250,157,123,101,235,109,189,85,66,227,21,108,156,205,154,40,
4,156,139,24,191,208,212,137,67,207,216,25,146,12,10,41,
84,85,95,22,69,63,103,198,201,35,155,204,18,85,22,216,
223,216,206,36,238,119,141,112,157,178,114,238,233,228,170,91,
147,56,52,115,120,220,133,167,223,66,168,177,200,3,126,164,
11,72,26,144,118,172,9,8,75,81,249,165,166,98,130,48,
97,136,43,56,251,7,144,170,186,242,176,249,1,12,64,206,
186,79,151,175,93,35,223,93,58,248,154,86,51,189,200,209,
30,127,13,231,111,91,41,30,125,173,66,81,81,218,190,243,
161,231,22,223,148,97,156,172,17,209,200,243,3,70,223,186,
26,229,57,65,223,153,8,103,249,182,89,118,121,176,36,147,
188,159,36,227,197,212,93,63,110,123,97,60,29,220,55,36,
90,238,107,134,115,252,146,27,143,112,186,254,39,45,83,29,
254,170,191,25,189,198,165,0,152,202,21,252,90,168,49,22,
195,144,75,138,230,191,172,86,81,31,100,220,163,94,49,246,
194,191,214,184,18,25,47,140,235,164,107,62,179,231,175,180,
245,240,86,198,119,166,250,35,208,17,189,18,235,101,35,208,
69,175,186,42,69,87,209,148,60,30,219,242,243,51,141,130,
70,57,33,96,20,219,7,68,156,169,40,5,241,33,50,195,
55,43,32,207,6,3,82,105,139,229,92,122,186,104,39,224,
54,194,121,199,184,110,55,181,219,47,12,231,248,216,54,230,
225,77,252,182,90,222,59,252,165,126,48,122,77,170,49,1,
132,55,248,169,176,2,77,151,60,153,53,193,127,89,48,165,
246,77,58,54,35,33,108,44,125,139,145,17,130,249,78,186,
78,147,235,30,122,123,71,95,31,255,217};

const unsigned char jpeg_ui_Font_16x16_9[]={255,216,255,224,0,16,74,70,73,70,0,1,2,0,0,100,
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
17,8,0,16,0,16,3,1,17,0,2,17,1,3,17,1,
255,196,0,114,0,0,3,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,5,7,8,9,1,0,2,3,1,0,0,
0,0,0,0,0,0,0,0,0,0,5,8,2,4,6,10,
16,0,1,5,1,1,1,1,1,1,0,0,0,0,0,0,
0,4,2,3,5,6,7,8,9,1,18,19,21,17,0,2,
2,1,3,3,3,3,5,0,0,0,0,0,0,0,2,3,
1,4,5,17,6,7,0,33,8,49,65,18,240,81,20,97,
113,145,34,19,255,218,0,12,3,1,0,2,17,3,17,0,
63,0,74,221,105,197,240,7,29,240,68,119,159,254,66,229,
190,134,5,185,96,21,157,115,94,232,219,15,57,89,58,70,
94,98,239,101,128,128,152,32,19,19,78,174,31,110,173,10,
241,19,15,18,3,82,4,180,0,161,173,33,138,63,199,88,
41,127,121,252,193,103,19,228,135,55,114,45,159,36,57,171,
47,198,143,219,251,145,248,236,110,21,57,164,97,22,170,168,
115,148,38,63,146,224,174,242,136,80,131,137,32,78,99,98,
94,214,72,49,35,214,216,194,104,83,68,80,168,54,32,215,
4,71,33,39,222,98,62,209,172,122,246,215,183,180,123,244,
111,39,204,15,244,207,150,187,107,58,237,207,29,41,252,21,
118,202,113,73,237,71,1,220,233,220,193,118,231,85,170,221,
21,5,56,91,17,130,73,91,170,209,82,146,229,69,204,68,
6,65,193,49,34,64,146,81,142,186,203,226,182,166,219,121,
99,247,142,236,175,226,159,46,236,45,207,192,124,223,119,145,
112,57,140,242,104,102,49,54,115,213,115,81,248,204,106,134,
88,65,90,195,22,177,98,216,192,83,77,32,196,60,64,214,
210,130,37,140,148,169,201,85,114,238,211,20,24,132,144,148,
4,135,125,39,239,31,207,126,241,237,212,25,195,92,251,232,
5,111,151,114,50,240,255,0,117,121,43,157,51,171,149,82,
50,247,13,135,219,250,95,252,201,236,209,118,193,155,151,54,
181,39,89,151,130,150,69,78,76,82,136,90,140,4,85,54,
194,75,83,171,252,255,0,69,173,74,98,60,128,228,159,27,
242,156,183,154,78,255,0,241,239,121,238,125,207,70,227,42,
55,43,91,7,254,137,189,21,202,86,47,7,173,171,155,11,
33,136,133,181,145,39,43,128,29,126,34,49,20,104,162,248,
213,9,69,229,45,115,26,252,100,251,198,190,218,105,219,246,
235,73,40,219,222,175,195,24,31,101,106,61,245,236,55,60,
246,212,93,167,156,174,121,182,41,133,100,122,228,54,131,103,
152,213,109,97,190,52,65,65,199,137,25,29,44,51,239,41,
8,9,111,182,33,34,136,25,100,20,83,140,180,63,223,218,
185,184,56,235,103,121,5,200,219,27,105,120,231,194,59,155,
97,91,167,186,42,222,202,101,178,56,230,211,66,241,245,202,
9,130,70,70,107,40,142,237,128,150,3,24,197,173,42,19,
54,127,82,33,97,180,80,230,223,184,183,196,174,96,68,74,
38,126,83,245,167,233,235,61,127,255,217};

const unsigned char *Font_p_16x16[] = 
{
    jpeg_ui_Font_16x16_0,
    jpeg_ui_Font_16x16_1,
    jpeg_ui_Font_16x16_2,
    jpeg_ui_Font_16x16_3,
    jpeg_ui_Font_16x16_4,
    jpeg_ui_Font_16x16_5,
    jpeg_ui_Font_16x16_6,
    jpeg_ui_Font_16x16_7,
    jpeg_ui_Font_16x16_8,
    jpeg_ui_Font_16x16_9,    
};

const unsigned char Font_17x17[][52] = 
{
{0x00,0x00,0x00,0xF8,0x3F,0x00,0xFC,0x7F,0x00,0xFE,0xFF,0x00,0x1E,0xF0,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x1E,0xF0,0x00,0xFE,0xFF,0x00,0xFE,0xFF,0x00,0xFC,0x7F,0x00,0xF8,0x3F,0x00,0x00,0x00,0x00},/*"E:\BandAll\HB045_GIT\UI\HB045其它修改切图_6.25\计步\0.BMP",0*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"E:\BandAll\HB045_GIT\UI\HB045其它修改切图_6.25\计步\1.BMP",0*/




{0x00,0x00,0x00,0x0E,0xF8,0x00,0x0E,0xF8,0x00,0x0E,0xFC,0x00,0x0E,0xFC,0x00,0x0E,0xFE,0x00,0x0E,0xFE,0x00,0x0E,0xEF,0x00,0x0E,0xEF,0x00,0x8E,0xE7,0x00,0x8E,0xE7,0x00,0xCE,0xE3,0x00,0xDE,0xE3,0x00,0xFE,0xE1,0x00,0xFC,0xE1,0x00,0xF8,0xE0,0x00,0x00,0x00,0x00},/*"E:\BandAll\HB045_GIT\UI\HB045其它修改切图_6.25\计步\2.BMP",0*/

    
{0x00,0x00,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0xCE,0xF3,0x00,0xFE,0xFF,0x00,0xFE,0xFF,0x00,0xFC,0x7F,0x00,0xF0,0x3E,0x00,0x00,0x00,0x00},/*"E:\BandAll\HB045_GIT\UI\HB045其它修改切图_6.25\计步\3.BMP",0*/




{0x00,0x00,0x00,0xFE,0x00,0x00,0xFE,0x01,0x00,0xFE,0x03,0x00,0xC0,0x03,0x00,0xC0,0x03,0x00,0xC0,0x03,0x00,0xC0,0x03,0x00,0xC0,0x03,0x00,0xC0,0x03,0x00,0xC0,0x03,0x00,0xC0,0x03,0x00,0xC0,0x03,0x00,0xFE,0xFF,0x00,0xFE,0xFF,0x00,0xFE,0xFF,0x00,0x00,0x00,0x00},/*"E:\BandAll\HB045_GIT\UI\HB045其它修改切图_6.25\计步\4.BMP",0*/


{0xFE,0x03,0x00,0xFE,0xE3,0x00,0xFE,0xE3,0x00,0xFE,0xE3,0x00,0xCE,0xE3,0x00,0xCE,0xE3,0x00,0xCE,0xE3,0x00,0xCE,0xE3,0x00,0xCE,0xE3,0x00,0xCE,0xE3,0x00,0xCE,0xE3,0x00,0xCE,0xF3,0x00,0xCE,0xFF,0x00,0x8E,0xFF,0x00,0x8E,0x7F,0x00,0x00,0x3E,0x00,0x00,0x00,0x00},/*"E:\BandAll\HB045_GIT\UI\HB045其它修改切图_6.25\计步\5.BMP",0*/




{0xF0,0x1F,0x00,0xFC,0x7F,0x00,0xFE,0x7F,0x00,0xFE,0xFF,0x00,0xCE,0xF3,0x00,0xCE,0xF3,0x00,0xCE,0xE3,0x00,0xCE,0xE3,0x00,0xCE,0xE3,0x00,0xCE,0xE3,0x00,0xCE,0xE3,0x00,0xCE,0xF3,0x00,0xCE,0xFF,0x00,0x8E,0xFF,0x00,0x8E,0x7F,0x00,0x00,0x3E,0x00,0x00,0x00,0x00},/*"E:\BandAll\HB045_GIT\UI\HB045其它修改切图_6.25\计步\6.BMP",0*/




{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0xC0,0x00,0x0E,0xF0,0x00,0x0E,0xF8,0x00,0x0E,0xFE,0x00,0x8E,0x3F,0x00,0xCE,0x1F,0x00,0xFE,0x07,0x00,0xFE,0x01,0x00,0xFE,0x00,0x00,0x3E,0x00,0x00,0x1E,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"E:\BandAll\HB045_GIT\UI\HB045其它修改切图_6.25\计步\7.BMP",0*/




{0x00,0x00,0x00,0x78,0x3C,0x00,0xFC,0x7F,0x00,0xFC,0xFF,0x00,0xFE,0xFF,0x00,0xDE,0xF7,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0x8E,0xE3,0x00,0xDE,0xF7,0x00,0xFC,0xFF,0x00,0xFC,0x7F,0x00,0x78,0x3C,0x00,0x00,0x00,0x00},/*"E:\BandAll\HB045_GIT\UI\HB045其它修改切图_6.25\计步\8.BMP",0*/




{0x00,0x00,0x00,0x78,0x00,0x00,0xFC,0xE1,0x00,0xFE,0xE3,0x00,0xFF,0xE3,0x00,0xCF,0xE3,0x00,0x8F,0xE3,0x00,0x8F,0xE3,0x00,0x8F,0xE3,0x00,0x8F,0xE3,0x00,0x8F,0xE3,0x00,0x8F,0xE3,0x00,0x8F,0xE3,0x00,0xFE,0xFF,0x00,0xFE,0x7F,0x00,0xFC,0x3F,0x00,0x00,0x00,0x00},/*"E:\BandAll\HB045_GIT\UI\HB045其它修改切图_6.25\计步\9.BMP",0*/




};

void show_Degree( int x, int y, int w, int h, int level )
{
	for ( int j = y; j < y + h; j++ )
	{
		for ( int i = x; i < x + w; i++ )
		{
			if ( !(i%2) )
			{
				set_pixel(i, j, 0xFFFF);
			}
		}
	}
	
	for ( int j = y; j < y + h; j++ )
	{
		for ( int i = x; i < x + w; i++ )
		{
			if ( !(i%2) )
			{
				set_pixel(i, j, 0xFFFF);
			}
		}
	}	
}

#include "jpeg_decode.h"

void show_pedometer_val( int x,int y, int counter)
{
	int width = 0;
	int val = counter;
	
	do{
		width++;
		val /= 10;
	}while(val>0);
	
	val = counter;
	
    #if 0
	int sx = x+((80-x) - width*16)/2;
	
	int ex = sx + (width-1) * 16;
	do
	{  
		DrawUI_JPEG(ex, y, Font_p_16x16[val%10]);
		val /= 10; ex -= 16;
	}while( val > 0 );	
	#else
	int sx = x+((80-x) - width*17)/2;
	
	int ex = sx + (width-1) * 17;
	do
	{  
		DrawUI_Bitmap_Ex(ex, y, 17,24, Font_17x17[val%10], 0x1F<<11|0x3F<<5);
		val /= 10; ex -= 17;
	}while( val > 0 );    
    #endif
}

#define COLOR_F 0xFFFF
#define COLOR_B 0x0000

void show_distance_val( int x, int y, int distance )
{
	float value;
	
	if ( config.unit == 0 )
	{
		value = distance / 1000.0 + 0.05;
	}else{
		value = distance * 0.0006214 + 0.05;
	}	
	
	int vh = (int)value;
	int vl = (int)((value - vh)*10);
	
	if ( vh > 99 ){
		vh = 99;
	}
	
	if ( vh > 9 )
	{
		DrawUI_Bitmap_Ex( x, y, 7, 16,Font_7x16[vh/10], COLOR_F);
	}
	DrawUI_Bitmap_Ex(x+7, y, 7, 16,Font_7x16[vh%10], COLOR_F);
	DrawUI_Bitmap_Ex(x+14,y, 7, 16,Font_7x16[10], COLOR_F);	
	DrawUI_Bitmap_Ex(x+14+5,y, 7, 16,Font_7x16[vl], COLOR_F);	
}

void show_calorie_val( int x, int y, int calorie )
{
	int val =  calorie;
	int count = 0, width = 0;
	
	do{	
		count++;
		val /= 10;
	}while(val>0);
	
	width = x + (61- x - count*7)/2;
	x = width + (count-1)*7;
	val = calorie;
	do{
		DrawUI_Bitmap_Ex(x, y, 7, 16,Font_7x16[val%10], COLOR_F);
		val /= 10;
		x -= 7;
	}while(val > 0 );
}

extern void DrawBackGroud(void);

void show_pedometer(int x, int y, int counter )
{	
    DrawBackGroud();	
	
	show_pedometer_val(0,24, counter);
	
	draw_bitmap( 0,56-8,20,22, gImage_running);
	DrawUI_Bitmap_Ex(48,61,32,16,bmp_steps_pedometer, 0x07EC);
	
	draw_bitmap( 0, 90+6, 16, 16, gImage_distance);
	draw_bitmap( 0, 126+4, 16, 16, gImage_calurie_ss);
	
	// show distance and calorie 

	if ( config.unit == 0 )
	{
		show_distance_val(31, 96, pedometer.distance);
	}else
	{
		show_distance_val(28, 96, pedometer.distance);
	}
	show_calorie_val(22, 131, pedometer.calorie);
	
	if ( config.unit == 0 )
	{	
		DrawUI_Bitmap_Ex(62,96,32,16,bmp_km_pedometer, COLOR_F);
	} else {	
		DrawUI_Bitmap_Ex(62-5,96,32,16,bmp_mile_pedometer, COLOR_F);
	}		
	
	DrawUI_Bitmap_Ex(62-6,131,32,16,bmp_kc_pedometer, COLOR_F);
	
	show_Degree( 0,86-8, 80, 1, 100);
}

void show_qr(void)
{
	QR_Copy_Image(frame_buffer);
}

unsigned long show_qr_flag = 0;
unsigned long win_pedometer_proc(unsigned long wid, unsigned long msg_type, 
                            unsigned long msg_param, unsigned long *p)
{
	if ( msg_type & WINDOW_CREATE )
	{
		win_ticks = 0;

		osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
		
		return ( msg_type ^ WINDOW_CREATE );
	}
	
	if ( msg_type & WINDOW_UPDATE )
	{
		win_ticks++;
		
		if (( (win_ticks > 5) && (show_qr_flag == 0) )
			|| ( win_ticks > 60 ) )
		{
			lcd_display(0);
			
			return ( msg_type ^ WINDOW_UPDATE );
		}
				
		memset( frame_buffer, 0, sizeof(frame_buffer));
		
		if ( (show_qr_flag == 1) && (ble.isConnected == 0))
		{ 
			show_qr();
		}else{
			show_pedometer( 28, 20, pedometer.counter);
            if ( show_qr_flag == 1 )
            {
                show_qr_flag = 0;
            }
		}        
		
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);
		}		
		sync_frame();
		
		osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 500);		
				
		return ( msg_type ^ WINDOW_UPDATE );
	}
	
	if ( msg_type & WINDOW_TOUCH )
	{		
		if ( config.lcdEnable == 0 )
		{
			win_ticks = 0;
			msg_type |= WINDOW_UPDATE;
		}else{
			
			if ( show_qr_flag == 1 && ble.isConnected == 1)
			{
				win_ticks = 0;
				show_qr_flag = 0;
				msg_type |= WINDOW_UPDATE;
				
				return ( msg_type ^ WINDOW_TOUCH );
			}
			window_push(window_get(win_current));
			msg_type |= WINDOW_DISTORY;
		}
		
		return ( msg_type ^ WINDOW_TOUCH );
	}
	
	if ( msg_type & WINDOW_PRESS )
	{	
		win_ticks = 0;
		
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);
			msg_type |= WINDOW_UPDATE;
			
			return ( msg_type ^ WINDOW_PRESS );
		}
		if ( (show_qr_flag == 0) &&
			(ble.isConnected == 0) ){
			show_qr();
			show_qr_flag = 1;
		}else{
			show_qr_flag = 0;
		}
		
		msg_type |= WINDOW_UPDATE;
		
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
		show_qr_flag = 0;		
		window_pop(&win_current);
		
		return window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0 );
	}	
	
	return 0;
}

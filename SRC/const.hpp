//global
constexpr auto RES_FOLDER = "RES/";
constexpr auto ROMS_FOLDER = "ROMS/";
constexpr auto SOUND_FILE = "sound.wav";

//intructions type
constexpr auto ASSIGN = "ASSIGN";
constexpr auto BCD = "BCD";
constexpr auto BITOP = "BITOP";
constexpr auto CALL = "CALL";
constexpr auto COND = "COND";
constexpr auto CONS = "CONS";
constexpr auto DISPLAY = "DISPLAY";
constexpr auto FLOW = "FLOW";
constexpr auto KEYOP = "KEYOP";
constexpr auto MATH = "MATH";
constexpr auto MEMORY = "MEMORY";
constexpr auto RAND = "RAND";
constexpr auto SOUND = "SOUND";
constexpr auto TIMER = "TIMER";
constexpr auto UNKNOW = "UNKNOW";
constexpr auto NO_DESC = "no_desc"; 

//chip8
constexpr auto BYTE_SIZE = 8;
constexpr auto MAX_MEMORY = 4096;
constexpr auto BASE_LOAD = 0x200;
constexpr auto BASE_STACK = 0xEA0;
constexpr auto BASE_DISP = 0xF00;
constexpr auto NUM_REGISTERS = 16;
constexpr auto NUM_KEYS = 16;

//charset
constexpr auto BASE_CHARSET = 0x000;
constexpr auto CHARSET_SIZE = 0xF;
constexpr auto CHARSET_CHAR_DIM = 5;

//pixel
constexpr auto ON = 1;
constexpr auto OFF = 0;
constexpr auto PIXEL_W = 16.0f;
constexpr auto PIXEL_H = 16.0f;

//display
constexpr auto DISPLAY_W = 64;
constexpr auto DISPLAY_H = 32;

//display window
constexpr auto WINDOW_W = DISPLAY_W * PIXEL_W;
constexpr auto WINDOW_H = DISPLAY_H * PIXEL_H;
constexpr auto WINDOW_BITS = 32;
constexpr auto WINDOW_TITLE = "Chip8 Emulator       Esc: Exit       F1: Reset       F2: Next";

//frequancies
constexpr auto CPU_FREQ = 568; // 1760 Hz
constexpr auto TIME_FREQ = 16666; // 60 Hz



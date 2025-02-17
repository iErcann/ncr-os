 // Azerty keyboard car c'est mieux quand même.
/*
 * 
D'après http://www.brokenthorn.com/Resources/OSDev19.html : 
Keyboard Controller Ports
Port	Read/Write	Descripton
Keyboard Encoder
0x60	Read	Read Input Buffer <-------------
0x60	Write	Send Command
Onboard Keyboard Controller
0x64	Read	Status Register
0x64	Write	Send Command
 * 
 * 
 * */
 
 
static enum PORT {
	PORT_A = 0x10,
	PORT_B = 0x30,
	PORT_C = 0x2E,
	PORT_D = 0x20,
	PORT_E = 0x12,
	PORT_F = 0x21,
	PORT_G = 0x22,
	PORT_H = 0x23,
	PORT_I = 0x17,
	PORT_J = 0x24,
	PORT_K = 0x25,
	PORT_L = 0x26,
	PORT_M = 0x27,
	PORT_N = 0x31,
	PORT_O = 0x18,
	PORT_P = 0x19,
	PORT_Q = 0x1E,
	PORT_R = 0x13,
	PORT_S = 0x1F,
	PORT_T = 0x14,
	PORT_U = 0x16,
	PORT_V = 0x2F,
	PORT_W = 0x2C,
	PORT_X = 0x2D,
	PORT_Y = 0x15,
	PORT_Z = 0x11,

	PORT_ONE = 0x02, // AH
	PORT_TWO = 0x03,
	PORT_THREE = 0x04,
	PORT_FOUR = 0x05,
	PORT_FIVE = 0x06,
	PORT_SIX = 0x07,
	PORT_SEVEN = 0x08,
	PORT_HEIGHT = 0x09,
	PORT_NINE = 0x0A,
	PORT_ZERO = 0x0B,

	PORT_F1 = 0x3B,
	PORT_F2 = 0x3C,
	PORT_F3 = 0x3D,
	PORT_F4 = 0x3E,
	PORT_F5 = 0x3F,
	PORT_F6 = 0x40,
	PORT_F7 = 0x41,
	PORT_F8 = 0x42,
	PORT_F9 = 0x43,
	PORT_F10 = 0x44,
	PORT_F11 = 0x57,
	PORT_F12 = 0x58,

	PORT_ESC = 0x01,
	PORT_ENTER = 0x1C,
	PORT_SPACE = 0x39,
	PORT_TAB = 0x0F,
	PORT_BACKSPACE = 0x0E,
	PORT_CAPSLOCK = 0x3A,
	PORT_ESCAPE = 0x01,

	PORT_UP = 0x48,
	PORT_DOWN = 0x50,
	PORT_LEFT = 0x4B,
	PORT_RIGHT = 0x4D,

	PORT_LEFT_SHIFT = 0x2A,
	PORT_LEFT_CTRL = 0x1D,
	PORT_RIGHT_SHIFT = 0x36,
	PORT_NUMBER_LOCK = 0x45,
	PORT_SCROLL_LOCK = 0x46,

	PORT_KEYPAD_1 = 0x4F,
	PORT_KEYPAD_2 = 0x50,
	PORT_KEYPAD_3 = 0x51,
	PORT_KEYPAD_4 = 0x4B,
	PORT_KEYPAD_5 = 0x4C,
	PORT_KEYPAD_6 = 0x4D,
	PORT_KEYPAD_7 = 0x47,
	PORT_KEYPAD_8 = 0x48,
	PORT_KEYPAD_9 = 0x49,
	PORT_KEYPAD_0 = 0x52,
	PORT_KEYPAD_PLUS = 0x4E,
	PORT_KEYPAD_MINUS = 0x4A
};

 
 
 
typedef struct Key{
	char *name;
	uint8_t port;
} Key;

 
static uint8_t k_readPort(){
	return inportb(0x60);
}

static bool k_newPort(){
	 static uint8_t currentPressedPort = 0x00;
	 static uint8_t lastPressedPort = 0x00;
	 
	 lastPressedPort = currentPressedPort;
	 currentPressedPort = k_readPort();
	 
	 if (lastPressedPort != currentPressedPort){
		return true;
	 }	
	 return false;
	
}
static bool k_portExist(uint8_t ports[]){
	if (getIndex(k_readPort(), ports) == -1) {
		return false;
	}
	return true;

}
static char *k_getChar(Key keys[], uint8_t  ports[]) {
	 size_t ind = getIndex(k_readPort(), ports); 
	 return keys[ind].name;
} 

Key keys[26]; // Global variable. 
uint8_t ports[] = {PORT_A,  PORT_B, PORT_C,  PORT_D,  PORT_E,  PORT_F,  PORT_G,  PORT_H,  PORT_I,  PORT_J,  PORT_K,  PORT_L,  PORT_M,  PORT_N,  PORT_O,  PORT_P,  PORT_Q,  PORT_R,  PORT_S,  PORT_T,  PORT_U,  PORT_V,  PORT_W,  PORT_X,  PORT_Y,  PORT_Z};

void k_printKeyAt(size_t x, size_t y){
	if (k_newPort() == true && k_portExist(ports)){
			terminal_writestring_at(k_getChar(keys, ports), 10, VGA_COLOR_WHITE, VGA_COLOR_BLACK, x, y);
	}
}
    
 
void k_initialize(){
	printf("Keyboard Initialization..\n");
	
	char *names[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
	//uint8_t ports[] = {PORT_A,  PORT_B, PORT_C,  PORT_D,  PORT_E,  PORT_F,  PORT_G,  PORT_H,  PORT_I,  PORT_J,  PORT_K,  PORT_L,  PORT_M,  PORT_N,  PORT_O,  PORT_P,  PORT_Q,  PORT_R,  PORT_S,  PORT_T,  PORT_U,  PORT_V,  PORT_W,  PORT_X,  PORT_Y,  PORT_Z};

	for (size_t i = 0; i < 26; i++){
		keys[i].name = names[i];
		keys[i].port = ports[i];
	}
 
	
	
	/*
	terminal_output_prompt();
	terminal_updateCursor();
 	
 	uint8_t ret = 0x0;  
	while (true){
		terminal_updateCursor();
		
		uint8_t currentret = k_readInput();
		
		if (currentret != ret){ 
				const char keyPressed = k_getChar(keys, ports);
			    if (keyPressed != '}') {  	 
					currentLine[lineI] = keyPressed;
					lineI++;
					printfc(  keyPressed  );
				}	
			}
				ret = currentret;
		} */		 
}

 

 

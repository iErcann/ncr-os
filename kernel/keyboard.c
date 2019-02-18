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
uint8_t readInput(){
	return inportb(0x60);
}

char readInput(){
	return inportb(0x60);
}


 

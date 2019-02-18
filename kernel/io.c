
/* Input a byte from a port */
inline uint8_t inportb(unsigned int port)
{
   uint8_t ret;
   asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
   return ret;
}

/* Output a byte to a port */
/* July 6, 2001 added space between :: to make code compatible with gpp */

inline void outportb(unsigned int port,unsigned char value)
{
   asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value));
}

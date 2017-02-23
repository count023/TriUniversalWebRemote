struct LED_REMOTE {
  unsigned long bright;   unsigned long dim;        unsigned long next;     unsigned long power;
  unsigned long red1;     unsigned long green1;     unsigned long blue1;     unsigned long white1; 
  unsigned long red2;     unsigned long green2;     unsigned long blue2;     unsigned long white2; 
  unsigned long red3;     unsigned long green3;     unsigned long blue3;     unsigned long white3; 
  unsigned long red4;     unsigned long green4;     unsigned long blue4;     unsigned long white4; 
  unsigned long red5;     unsigned long green5;     unsigned long blue5;     unsigned long white5; 
  unsigned long red_up;   unsigned long green_up;   unsigned long blue_up;   unsigned long quick; 
  unsigned long red_down; unsigned long green_down; unsigned long blue_down; unsigned long slow; 
  unsigned long diy1;     unsigned long diy2;       unsigned long diy3;      unsigned long autom; 
  unsigned long diy4;     unsigned long diy5;       unsigned long diy6;      unsigned long flash; 
  unsigned long jump3;    unsigned long jump7;      unsigned long fade3;     unsigned long fade7;
};

const LED_REMOTE ledRemote = {
  0xFF3AC5,0xFFBA45,0xFF827D,0xFF02FD,
  0xFF1AE5,0xFF9A65,0xFFA25D,0xFF22DD,
  0xFF2AD5,0xFFAA55,0xFF0000,0xFF12ED,
  0xFF0AF5,0xFF8A75,0xFFB24D,0xFF32CD,
  0xFF38C7,0xFFB847,0xFF7887,0xFFF807,
  0xFF18E7,0xFF9867,0xFF58A7,0xFFD827,
  0xFF28D7,0xFFA857,0xFF6897,0xFFE817,
  0xFF08F7,0xFF8877,0xFF48B7,0xFFC837,
  0xFF30CF,0xFFB04F,0xFF708F,0xFFF00F,
  0xFF10EF,0xFF906F,0xFF50AF,0xFFD02F,
  0xFF20DF,0xFFA05F,0xFF609F,0xFFE01F
};

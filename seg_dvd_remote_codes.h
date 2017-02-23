struct SEG_DVD_REMOTE {
  unsigned long power;        unsigned long pcb;        unsigned long displaying;    unsigned long eject;
  unsigned long subtitle;     unsigned long search;     unsigned long angle;         unsigned long language;
  unsigned long setuping;     unsigned long title;      unsigned long menu;          unsigned long zoom;
  unsigned long pscan;        unsigned long up;         unsigned long pause;
  unsigned long left;         unsigned long play;       unsigned long right;
  unsigned long slow;         unsigned long down;       unsigned long stopping;
  unsigned long previous;     unsigned long next;       unsigned long fastReward;    unsigned long fastForward;
  unsigned long all;          unsigned long aToB;       unsigned long volumePlus;    unsigned long volumeMinus;
  unsigned long one;          unsigned long two;        unsigned long three;         unsigned long mute;
  unsigned long four;         unsigned long five;       unsigned long six;           unsigned long plusTen;
  unsigned long seven;        unsigned long eight;      unsigned long nine;          unsigned long zero;
  unsigned long audio;                                                               unsigned long program;
};

const SEG_DVD_REMOTE segDvdRemote = {
  0x4FB708F, 0x4FB32CD, 0x4FB1AE5, 0x4FB58A7,
  0x4FB48B7, 0x4FB0AF5, 0x4FB2AD5, 0x4FB6897,
  0x4FB40BF, 0x4FB02FD, 0x4FB42BD, 0x4FB50AF,
  0x4FB609F, 0x4FB22DD, 0x4FB7887,
  0x4FB38C7, 0x4FB3AC5, 0x4FB12ED,
  0x4FBF807, 0x4FBB847, 0x4FBBA45,
  0x4FBD827, 0x4FB18E7, 0x4FB9867, 0x4FB9A65,
  0x4FBE817, 0x4FB28D7, 0x4FBA857, 0x4FBAA55,
  0x4FBC837, 0x4FB08F7, 0x4FB8877, 0x4FB8A75,
  0x4FBF00F, 0x4FB30CF, 0x4FBB04F, 0x4FBB24D,
  0x4FBD02F, 0x4FB10EF, 0x4FB906F, 0x4FB926D,
  0x4FBE21D,                       0x4FBC23D
};

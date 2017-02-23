/**
 * infrared commands of a standard samsung tv remote control
 */

struct SAMSUNG_TV_REMOTE {
  unsigned long power;                                   unsigned long source;
  unsigned long one;          unsigned long two;         unsigned long three;
  unsigned long four;         unsigned long five;        unsigned long six;
  unsigned long seven;        unsigned long eight;       unsigned long nine;
  unsigned long ttx;          unsigned long zero;        unsigned long previous;
  unsigned long volumePlus;   unsigned long mute;        unsigned long channelUp;
  unsigned long volumeMinus;  unsigned long channelList; unsigned long channelDown;
  unsigned long menu;         unsigned long smartHub;    unsigned long guide;
  unsigned long tools;        unsigned long up;          unsigned long info;
  unsigned long left;         unsigned long enter;       unsigned long right;
  unsigned long returning;    unsigned long down;        unsigned long exiting;
};

const SAMSUNG_TV_REMOTE samsungTvRemote = {
  0xE0E040BF,             0xE0E0807F,
  0xE0E020DF, 0xE0E0A05F, 0xE0E0609F,
  0xE0E010EF, 0xE0E0906F, 0xE0E050AF,
  0xE0E030CF, 0xE0E0B04F, 0xE0E0708F,
  0xE0E034CB, 0xE0E08877, 0xE0E0C837,
  0xE0E0E01F, 0xE0E0F00F, 0xE0E048B7,
  0xE0E0D02F, 0xE0E0D629, 0xE0E008F7,
  0xE0E058A7, 0xE0E09E61, 0xE0E0F20D,
  0xE0E0D22D, 0xE0E006F9, 0xE0E0F807,
  0xE0E0A659, 0xE0E016E9, 0xE0E046B9,
  0xE0E01AE5, 0xE0E08679, 0xE0E0B44B
};

void initSamsunTvRemote();



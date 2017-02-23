struct KENWOOD_RECEIVER_REMOTE {
  unsigned long power;
  unsigned long mute;
  unsigned long volumePlus;
  unsigned long volumeMinus;
};

const KENWOOD_RECEIVER_REMOTE kenwoodReceiverRemote = {
  0x1D00B946,
  0x1D0039C6,
  0x1D00D926,
  0x1D0059A6
};

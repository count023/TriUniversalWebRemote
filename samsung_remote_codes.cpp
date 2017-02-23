#include <map>

#include "samsung_remote_codes.h"


#ifndef deviceCommands
    std::map<std::string, std::map<std::string, long> > deviceCommands;
#endif
std::map<std::string, long> samsungTvDeviceCommands;

void initSamsunTvRemote() {
 
  samsungTvDeviceCommands.emplace("power", samsungTvRemote.power);
  samsungTvDeviceCommands.emplace("source", samsungTvRemote.source);
  samsungTvDeviceCommands.emplace("one", samsungTvRemote.one);
  samsungTvDeviceCommands.emplace("two", samsungTvRemote.two);
  samsungTvDeviceCommands.emplace("three", samsungTvRemote.three);
  samsungTvDeviceCommands.emplace("fourr", samsungTvRemote.four);
  samsungTvDeviceCommands.emplace("five", samsungTvRemote.five);
  samsungTvDeviceCommands.emplace("six", samsungTvRemote.six);
  samsungTvDeviceCommands.emplace("seven", samsungTvRemote.seven);
  samsungTvDeviceCommands.emplace("eight", samsungTvRemote.eight);
  samsungTvDeviceCommands.emplace("nine", samsungTvRemote.nine);
  samsungTvDeviceCommands.emplace("ttx", samsungTvRemote.ttx);
  samsungTvDeviceCommands.emplace("zero", samsungTvRemote.zero);
  samsungTvDeviceCommands.emplace("previous", samsungTvRemote.previous);
  samsungTvDeviceCommands.emplace("volumePlus", samsungTvRemote.volumePlus);
  samsungTvDeviceCommands.emplace("mute", samsungTvRemote.mute);
  samsungTvDeviceCommands.emplace("channelUp", samsungTvRemote.channelUp);
  samsungTvDeviceCommands.emplace("volumeMinus", samsungTvRemote.volumeMinus);
  samsungTvDeviceCommands.emplace("channelList", samsungTvRemote.channelList);
  samsungTvDeviceCommands.emplace("channelDown", samsungTvRemote.channelDown);
  samsungTvDeviceCommands.emplace("menu", samsungTvRemote.menu);
  samsungTvDeviceCommands.emplace("smartHub", samsungTvRemote.smartHub);
  samsungTvDeviceCommands.emplace("guide", samsungTvRemote.guide);
  samsungTvDeviceCommands.emplace("tools", samsungTvRemote.tools);
  samsungTvDeviceCommands.emplace("up", samsungTvRemote.up);
  samsungTvDeviceCommands.emplace("info", samsungTvRemote.info);
  samsungTvDeviceCommands.emplace("left", samsungTvRemote.left);
  samsungTvDeviceCommands.emplace("enter", samsungTvRemote.enter);
  samsungTvDeviceCommands.emplace("right", samsungTvRemote.right);
  samsungTvDeviceCommands.emplace("returning", samsungTvRemote.returning);
  samsungTvDeviceCommands.emplace("down", samsungTvRemote.down);
  samsungTvDeviceCommands.emplace("exiting", samsungTvRemote.exiting);

  deviceCommands.emplace("samsung-tv", samsungTvDeviceCommands);
}


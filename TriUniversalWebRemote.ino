/**
 *  2017-01-23
 *  @author: taquma
 *  @author: count023
 *
 *  An IR LED must be connected to ESP8266 pin 1 (D5).
 *  @desc ir remote control for different devices via http-get-requests
 *  a call to /<device>/<command> is translated to the appropriate ir command
 *  
 *  Basically it's a proxy for http-get-reuqests to ir-commands
 *  
 *  currently implemented:
 *  - samsung tv (with standard ir control)
 *  - kenwood receiver
 *  - paulmann led ir control
 *  - somewhat cheap SEG dvd player
 *  - gigablue-receiver
 *  
 *  intended to be build on a nodeMcu V3 (esp8266)
*/
#include <regex> // needed for std::set
#include <RCSwitch.h>
#include <IRremoteESP8266.h>


#include "passwords.h"
#include "InitMultiWifi.h"
#include "GpioneersHttpUpdate.h"


#include "led_remote_codes.h"
#include "samsung_remote_codes.h"
#include "kenwood_receiver_remote_codes.h"
#include "gigablue_receiver_remote_codes.h"
#include "seg_dvd_remote_codes.h"

struct DeviceCommand {
  String device;
  String command;
};

const int MAX_CLIENT_AVAILABLE = 200;
const int IR_LED_PIN = 3;
const int RC_SWITCH_PIN = 2;

RCSwitch mySwitch = RCSwitch();
// an IR led is connected to GPIO pin ?
IRsend irsend(IR_LED_PIN);

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {

  Serial.begin(9600);

  initSamsunTvRemote();
  irsend.begin();
  delay(10);

  // Connect to WiFi network
  wifiInitiated = setupWifi();
  if (wifiInitiated) {
    httpUpdate();
  }

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
  Serial.println("");
}

void loop() {

  int statusCode = 200;
  String device = "unknown";

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  int clientAvailable = 0;
  while (!client.available()) {
    if (clientAvailable < MAX_CLIENT_AVAILABLE) {
      Serial.print(".");
      delay(3);
      clientAvailable++;
    } else {
      Serial.println();
      Serial.println("Aborting request");
      delay(10);
      return;
    }
  }
  Serial.println();

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println("req: '" + req + "'");

  // currently not used ... 
  // parseRequestPath(req);
  
  client.flush();

  String val;
  // Match the request
  if (req.indexOf("/led/") != -1) {
    val = handleLed(req);
    device = "led";
  } else if (req.indexOf("/tv/") != -1) {
    val = handleTv(req);
    device = "tv";
  } else if (req.indexOf("/recv/") != -1) {
    val = handleReceiver(req);
    device = "receiver";
  } else if (req.indexOf("/gigablue/") != -1) {
    val = handleGigablue(req);
    device = "gigablue";
  } else if (req.indexOf("/dvd/") != -1) {
    val = handleDvd(req);
    device = "dvd";
  } else {
    Serial.println("invalid request");
    val = "invalid request";
    statusCode = 400;
  }

  // Send the response to the client
  sendResponse(client, val, device, statusCode);

  delay(10);
}

void sendResponse(WiFiClient &client, String val, String device, int statusCode) {

  // Prepare the response
  String responseBody = "HTTP/1.1 " + String(statusCode) + " OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Type: application/json\r\n\r\n{\"status\":\"";
  responseBody += val;
  responseBody += "\";\"device\":\"";
  responseBody += device;
  responseBody += "\"}\r\n";

  client.print(responseBody);
  client.flush();
  delay(1);
  client.stop();
  Serial.println("Client disonnected");
  Serial.println();
}

String handleLed(String req) {
  
  String val = "";
  unsigned int irCode = 0xFFFFFFFF;
  unsigned int exceutionTimes = 1;
  
  if (req.indexOf("/led/power") != -1) { 
    val = "power";
    irCode = ledRemote.power;
  } else if (req.indexOf("/led/dim-max") != -1) {
    val = "dim-max";
    irCode = ledRemote.dim;
    exceutionTimes = 5;
  } else if (req.indexOf("/led/dim") != -1) {
    val = "dim";
    irCode = ledRemote.dim;
  } else if (req.indexOf("/led/bright-max") != -1) {
    val = "bright-max";
    irCode = ledRemote.bright;
    exceutionTimes = 5;
  } else if (req.indexOf("/led/bright") != -1) {
    val = "bright";
    irCode = ledRemote.bright;
  } else if (req.indexOf("/led/red1") != -1) {
    val = "red1";
    irCode = ledRemote.red1;
  } else if (req.indexOf("/led/green1") != -1) {
    val = "green1";
    irCode = ledRemote.green1;
  } else if (req.indexOf("/led/blue1") != -1) {
    val = "blue1";
    irCode = ledRemote.blue1;
  } else if (req.indexOf("/led/white1") != -1) {
    val = "white1";
    irCode = ledRemote.white1;
  }

  for (unsigned int i = 0; i < exceutionTimes; i++) {
    irsend.sendNEC(irCode, 36);
    Serial.println("handleLed: send " + val + " irCode " + String(irCode));
    delay(50);  
  }

  return val;
}

String handleTv(String req) {

  String val = "";
  std::set<unsigned long> irCode;

  if (req.indexOf("/tv/power") != -1) { 
    val = "power";
    irCode.insert(samsungTvRemote.power);
  } else if (req.indexOf("/tv/source") != -1) {
    val = "source";
    irCode.insert(samsungTvRemote.source);
  } else if (req.indexOf("/tv/one") != -1) {
    val = "one";
    irCode.insert(samsungTvRemote.one);
  } else if (req.indexOf("/tv/two") != -1) {
    val = "two";
    irCode.insert(samsungTvRemote.two);
  } else if (req.indexOf("/tv/three") != -1) {
    val = "three";
    irCode.insert(samsungTvRemote.three);
  } else if (req.indexOf("/tv/four") != -1) {
    val = "four";
    irCode.insert(samsungTvRemote.four);
  } else if (req.indexOf("/tv/five") != -1) {
    val = "five";
    irCode.insert(samsungTvRemote.five);
  } else if (req.indexOf("/tv/six") != -1) {
    val = "six";
    irCode.insert(samsungTvRemote.six);
  } else if (req.indexOf("/tv/seven") != -1) {
    val = "seven";
    irCode.insert(samsungTvRemote.seven);
  } else if (req.indexOf("/tv/eight") != -1) {
    val = "eight";
    irCode.insert(samsungTvRemote.eight);
  } else if (req.indexOf("/tv/nine") != -1) {
    val = "nine";
    irCode.insert(samsungTvRemote.nine);
  } else if (req.indexOf("/tv/zero") != -1) {
    val = "zero";
    irCode.insert(samsungTvRemote.zero);
  } else if (req.indexOf("/tv/ard") != -1) {
    val = "ard";
    irCode.insert(samsungTvRemote.one);
  } else if (req.indexOf("/tv/zdf") != -1) {
    val = "zdf";
    irCode.insert(samsungTvRemote.two);
  } else if (req.indexOf("/tv/3sat") != -1) {
    val = "3sat";
    irCode.insert(samsungTvRemote.three);
  } else if (req.indexOf("/tv/sat1") != -1) {
    val = "sat1";
    irCode.insert(samsungTvRemote.four);
  } else if (req.indexOf("/tv/rtl") != -1) {
    val = "rtl";
    irCode.insert(samsungTvRemote.five);
  } else if (req.indexOf("/tv/vox") != -1) {
    val = "vox";
    irCode.insert(samsungTvRemote.six);
  } else if (req.indexOf("/tv/prosieben") != -1) {
    val = "prosieben";
    irCode.insert(samsungTvRemote.seven);
  } else if (req.indexOf("/tv/kabel1") != -1) {
    val = "kabel1";
    irCode.insert(samsungTvRemote.eight);
  } else if (req.indexOf("/tv/rtl2") != -1) {
    val = "rtl2";
    irCode.insert(samsungTvRemote.nine);
  } else if (req.indexOf("/tv/srtl") != -1) {
    val = "srtl";
    irCode.insert(samsungTvRemote.one);
    irCode.insert(samsungTvRemote.zero);
  } else if (req.indexOf("/tv/einsfestival") != -1) {
    val = "einsfestival";
    irCode.insert(samsungTvRemote.one);
    irCode.insert(samsungTvRemote.two);
  } else if (req.indexOf("/tv/neo") != -1) {
    val = "zdf_neo";
    irCode.insert(samsungTvRemote.one);
    irCode.insert(samsungTvRemote.three);
  } else if (req.indexOf("/tv/alex") != -1) {
    val = "alex";
    irCode.insert(samsungTvRemote.one);
    irCode.insert(samsungTvRemote.one);
  } else if (req.indexOf("/tv/gold") != -1) {
    val = "Sat.1 Gold";
    irCode.insert(samsungTvRemote.one);
    irCode.insert(samsungTvRemote.five);
  } else if (req.indexOf("/tv/maxx") != -1) {
    val = "ProSieben MAXX";
    irCode.insert(samsungTvRemote.one);
    irCode.insert(samsungTvRemote.seven);
  } else if (req.indexOf("/tv/ttx") != -1) {
    val = "ttx";
    irCode.insert(samsungTvRemote.ttx);
  } else if (req.indexOf("/tv/previous") != -1) {
    val = "previous";
    irCode.insert(samsungTvRemote.previous);
  } else if (req.indexOf("/tv/volumePlus") != -1) {
    val = "volumePlus";
    irCode.insert(samsungTvRemote.volumePlus);
  } else if (req.indexOf("/tv/mute") != -1) {
    val = "mute";
    irCode.insert(samsungTvRemote.mute);
  } else if (req.indexOf("/tv/channelUp") != -1) {
    val = "channelUp";
    irCode.insert(samsungTvRemote.channelUp);
  } else if (req.indexOf("/tv/volumeMinus") != -1) {
    val = "volumeMinus";
    irCode.insert(samsungTvRemote.volumeMinus);
  } else if (req.indexOf("/tv/chanelList") != -1) {
    val = "chanelList";
    irCode.insert(samsungTvRemote.channelList);
  } else if (req.indexOf("/tv/channelDown") != -1) {
    val = "channelDown";
    irCode.insert(samsungTvRemote.channelDown);
  } else if (req.indexOf("/tv/menu") != -1) {
    val = "menu";
    irCode.insert(samsungTvRemote.menu);
  } else if (req.indexOf("/tv/smartHub") != -1) {
    val = "smartHub";
    irCode.insert(samsungTvRemote.smartHub);
  } else if (req.indexOf("/tv/guide") != -1) {
    val = "guide";
    irCode.insert(samsungTvRemote.guide);
  } else if (req.indexOf("/tv/tools") != -1) {
    val = "tools";
    irCode.insert(samsungTvRemote.tools);
  } else if (req.indexOf("/tv/up") != -1) {
    val = "up";
    irCode.insert(samsungTvRemote.up);
  } else if (req.indexOf("/tv/info") != -1) {
    val = "info";
    irCode.insert(samsungTvRemote.info);
  } else if (req.indexOf("/tv/left") != -1) {
    val = "left";
    irCode.insert(samsungTvRemote.left);
  } else if (req.indexOf("/tv/enter") != -1) {
    val = "enter";
    irCode.insert(samsungTvRemote.enter);
  } else if (req.indexOf("/tv/right") != -1) {
    val = "right";
    irCode.insert(samsungTvRemote.right);
  } else if (req.indexOf("/tv/returning") != -1) {
    val = "returning";
    irCode.insert(samsungTvRemote.returning);
  } else if (req.indexOf("/tv/down") != -1) {
    val = "down";
    irCode.insert(samsungTvRemote.down);
  } else if (req.indexOf("/tv/exiting") != -1) {
    val = "exiting";
    irCode.insert(samsungTvRemote.exiting);
  }

  std::set<unsigned long>::iterator irCodeIterator;
  for (irCodeIterator = irCode.begin(); irCodeIterator != irCode.end(); ++irCodeIterator) {
    irsend.sendSAMSUNG(*irCodeIterator, 32);
    delay(100);
    Serial.println("handleTv: send " + val + " irCode " + String(*irCodeIterator));
  }

  return val;
}

String handleReceiver(String req) {

  String val = "";
  unsigned int irCode = 0xFFFFFFFF;
  
  if (req.indexOf("/recv/power") != -1) { 
    val = "power";
    irCode = kenwoodReceiverRemote.power;
  } else if (req.indexOf("/recv/mute") != -1) {
    val = "mute";
    irCode = kenwoodReceiverRemote.mute;
  } else if (req.indexOf("/recv/volumePlus") != -1) {
    val = "volumePlus";
    irCode = kenwoodReceiverRemote.volumePlus;
  } else if (req.indexOf("/recv/volumeMinus") != -1) {
    val = "volumeMinus";
    irCode = kenwoodReceiverRemote.volumeMinus;
  }

  irsend.sendNEC(irCode, 32);
  Serial.println("handleReceiver: send " + val + " irCode " + String(irCode));

  return val;
}

String handleGigablue(String req) {

  String val = "";
  unsigned int irCode = 0xFFFFFFFF;
  
  if (req.indexOf("/gigablue/power") != -1) { 
    val = "power";
    irCode = gigablueReceiverRemote.power;
  } else if (req.indexOf("/gigablue/up") != -1) {
    val = "up";
    irCode = gigablueReceiverRemote.up;
  } else if (req.indexOf("/gigablue/down") != -1) {
    val = "down";
    irCode = gigablueReceiverRemote.down;
  } else if (req.indexOf("/gigablue/exiting") != -1) {
    val = "exiting";
    irCode = gigablueReceiverRemote.exiting;
  }

  irsend.sendNEC(irCode, 32);
  Serial.println("handleReceiver: send " + val + " irCode " + String(irCode));

  return val;
}

String handleDvd(String req) {

  String val = "";
  unsigned int irCode = 0xFFFFFFFF;
  
  if (req.indexOf("/dvd/power") != -1) { 
    val = "power";
    irCode = segDvdRemote.power;
  } else if (req.indexOf("/dvd/up") != -1) {
    val = "up";
    irCode = segDvdRemote.up;
  } else if (req.indexOf("/dvd/down") != -1) {
    val = "down";
    irCode = segDvdRemote.down;
  } else if (req.indexOf("/dvd/left") != -1) {
    val = "left";
    irCode = segDvdRemote.left;
  } else if (req.indexOf("/dvd/right") != -1) {
    val = "right";
    irCode = segDvdRemote.right;
  } else if (req.indexOf("/dvd/play") != -1) {
    val = "play";
    irCode = segDvdRemote.play;
  } else if (req.indexOf("/dvd/pause") != -1) {
    val = "pause";
    irCode = segDvdRemote.pause;
  } else if (req.indexOf("/dvd/stopping") != -1) {
    val = "stopping";
    irCode = segDvdRemote.stopping;
  } else if (req.indexOf("/dvd/eject") != -1) {
    val = "eject";
    irCode = segDvdRemote.eject;
  }

  irsend.sendNEC(irCode, 32);
  Serial.println("handleReceiver: send " + val + " irCode " + String(irCode));

  return val;
}

/**
 * @param req is the first line of a get request http header like
 *   'GET /tv/info HTTP/1.1'
 * /
DeviceCommand parseRequestPath(String req) {

  req.remove(0, req.indexOf("/") + 1);
  req.remove(req.indexOf(" "));

  DeviceCommand deviceCommand;
  deviceCommand.device = req.substring(0, req.indexOf("/"));
  deviceCommand.command = req.substring(req.indexOf("/") + 1);

  Serial.println("DeviceCommand: device: '" + deviceCommand.device + "'; command: '" + deviceCommand.command + "'");
  return deviceCommand;
}
/ * */




#pragma once
#include "ofMain.h"
#include "AppEvent.h"

#define NUM_BYTES 2
const char Opcode = '#';

class Arduino {
    
public:
    
    Arduino()
    {
        // detect available serial ports //
        string arduinoPort = "";
        vector<ofSerialDeviceInfo> list = serial.getDeviceList();
        serial.listDevices();
        for (int i=0; i < list.size(); i++) {
            string n = list[i].getDevicePath();
            if (std::string::npos != n.find("/dev/tty.usbserial") || std::string::npos != n.find("dev/TTYACM")) ports.push_back(n);      // for boards that use FTDI serial
            if(std::string::npos != n.find("/dev/tty.usbmodem") || std::string::npos != n.find("/dev/TTYACM")) ports.push_back(n);        // for newer boards (Mega, Uno, etc)
            //ofLogNotice(ofToString(n));
        }
        
	// fallback - choose first available serial device
	if (ports.size() == 0 && list.size() != 0) ports.push_back(list[0].getDevicePath());

	// success!
        if (ports.size() != 0) {
            ofLogNotice("arduinoPort :: "+ports[0]);
            serialReady = serial.setup(ports[0], 9600);
     	}

	//else ofLogError() << "No arduino port found";
        
        // serialReady is broken, returns 255 if device is not connected ...
        if (serialReady){
        }   else{
            ofLogNotice("*arduino not connected*");
        }
    }
    
    void update() {
        unsigned char bytesReturned[NUM_BYTES];
        memset(bytesReturned, 0, NUM_BYTES);
        
        while(serial.readBytes(bytesReturned, NUM_BYTES) > 0) { }
        
        if(bytesReturned[0] == Opcode) {
            int btnIndex = (int)bytesReturned[1];
            ofLogNotice("BYTES RETURNED :: " + ofToString((int)bytesReturned[1]));
            ofNotifyEvent(AppEvent::BUTTON_PRESSED, btnIndex);
        }

	//else ofLogError("Opcode not found. Byte read: " + ofToString(bytesReturned[0]));
    }
    
private:
    
    ofSerial            serial;
    vector<string>      ports;
    bool                serialReady;
    int                 mode;
    
    unsigned char bytes[NUM_BYTES];
    static int bytesRemaining;
    
    void writeString(string &msg)
    {
        unsigned char* msguc = new unsigned char[msg.size()];
        memcpy(msguc, msg.c_str(), msg.size());
        int numSent = serial.writeBytes(msguc, msg.size());
        delete [] msguc;
    }
    
};

#include <WiFiUdp.h>
WiFiUDP wifiUdp;

int oldMinutes = -1;

const int NTP_PACKET_SIZE = 48;    // NTP time stamp is in the first 48 bytes of the message.
byte packetBuffer[NTP_PACKET_SIZE]; // Buffer for both incoming and outgoing packets.

void ntpSetup()
{
  if(typeOfConnection == WIFI)
  {
    wifiUdp.begin(localPort);
  }
}

void ntpLoop()
{
    int minutes = getUtcTimeInMinutes();
    if(oldMinutes != minutes)
    {   
      sendActualTime(String(minutes));
      oldMinutes = minutes;
    }
}

int getUtcTimeInMinutes() 
{
    sendNTPpacket(timeServer);  // Send an NTP packet to the time server.

    // Wait to see if a reply is available.
    delay(1000);
    int isParsePacket = 0;
    if(typeOfConnection == ETHERNET)
    {
      isParsePacket = ethernetUdp.parsePacket();
    }
    else
    {
       isParsePacket = wifiUdp.parsePacket();
    }
  
  
    if (isParsePacket) 
    {
        // We've received a packet, read the data from it.
        // Read the packet into the buffer.
        if(typeOfConnection == ETHERNET)
        {
          ethernetUdp.read(packetBuffer, NTP_PACKET_SIZE);     
        }
        else
        {
          wifiUdp.read(packetBuffer, NTP_PACKET_SIZE);    
        }

        // The timestamp starts at byte 40 of the received packet and is four bytes,
        // or two words, long. First, extract the two words.
        unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
        unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

        // Next, combine the four bytes (two words) into a long integer.
        // This is NTP time (seconds since Jan 1 1900).
        unsigned long secsSince1900 = highWord << 16 | lowWord;

        // Now convert NTP time into everyday time.
        // Unix time starts on Jan 1 1970. In seconds, that's 2208988800.
        const unsigned long seventyYears = 2208988800UL;
        // Subtract seventy years.
        unsigned long epoch = secsSince1900 - seventyYears;

        // UTC is the time at Greenwich Meridian (GMT).
        // The hour (86400 equals secs per day).
        int hours = ((epoch % 86400L) / 3600);  

        // The minute (3600 equals secs per minute).
        int minutes = ((epoch % 3600) / 60);      

        return minutes + (hours *60);
    }
    return oldMinutes;
}

void sendNTPpacket(const char *address) 
{
    // Set all bytes in the buffer to 0.
    memset(packetBuffer, 0, NTP_PACKET_SIZE);

    // Initialize values needed to form NTP request
    // (see http://en.wikipedia.org/wiki/Network_Time_Protocol).
    packetBuffer[0] = 0b11100011;      // LI, Version, Mode
    packetBuffer[1] = 0;        // Stratum, or type of clock
    packetBuffer[2] = 6;        // Polling Interval
    packetBuffer[3] = 0xEC;     // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;

    // All NTP fields have been given values, now
    // send a packet requesting a timestamp.
    
  if(typeOfConnection == ETHERNET)
  {
    ethernetUdp.beginPacket(address, 123);      // NTP requests are to port 123
    ethernetUdp.write(packetBuffer, NTP_PACKET_SIZE);
    ethernetUdp.endPacket();
  }
  else
  {
    wifiUdp.beginPacket(address, 123);      // NTP requests are to port 123
    wifiUdp.write(packetBuffer, NTP_PACKET_SIZE);
    wifiUdp.endPacket();
  }
}

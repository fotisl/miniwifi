#include <Arduino.h>
#include "MiniWiFi.h"

MiniWiFi::MiniWiFi(Stream *s)
{
    this->stream = s;
}

boolean MiniWiFi::pingModule()
{
    uint8_t val, ret;

    val = random(256);
    stream->write((uint8_t) 0x00);
    writebuf((char *) &val, 1);
    readbuf((char *) &ret);

    return ret == val;
}

void MiniWiFi::reset()
{
    unsigned long m;

    stream->write((uint8_t) 0x01);
    m = millis();
    while((millis() - m) < 1000)
        if(stream->available())
            stream->read();
}

void MiniWiFi::setBaud(uint32_t baud)
{
    stream->write((uint8_t) 0x02);
    writebuf((char *) &baud, 4);
}

uint32_t MiniWiFi::getChipID()
{
    uint32_t ret;

    stream->write((uint8_t) 0x03);
    readbuf((char *) &ret);

    return ret;
}

uint16_t MiniWiFi::getVcc()
{
    uint16_t ret;

    stream->write((uint8_t) 0x04);
    readbuf((char *) &ret);

    return ret;
}

void MiniWiFi::clearInterrupt()
{
    stream->write((uint8_t) 0x05);
}

void MiniWiFi::connectWiFi(char *ssid, char *pass)
{
    stream->write((uint8_t) 0x10);
    writestr(ssid);
    writestr(pass);
}

void MiniWiFi::disconnectWiFi()
{
    stream->write((uint8_t) 0x11);
}

int8_t MiniWiFi::getStatus()
{
    return singlefunc(0x12);
}

uint32_t MiniWiFi::getIPConfig(uint8_t value)
{
    uint32_t ret;

    stream->write((uint8_t) 0x13);
    writebuf((char *) &value, 1);
    readbuf((char *) &ret);
    return ret;
}

uint8_t MiniWiFi::setIPConfig(uint32_t localIP, uint32_t gateway, uint32_t subnet, uint32_t dns1, uint32_t dns2)
{
    uint8_t ret;

    stream->write((uint8_t) 0x14);
    writebuf((char *) &localIP, 4);
    writebuf((char *) &gateway, 4);
    writebuf((char *) &subnet, 4);
    writebuf((char *) &dns1, 4);
    writebuf((char *) &dns2, 4);
    readbuf((char *) &ret);

    return ret;
}

void MiniWiFi::getHostname(char *hostname)
{
    stream->write((uint8_t) 0x15);
    readstr(hostname);
}

int8_t MiniWiFi::setHostname(char *hostname)
{
    int8_t ret;

    stream->write((uint8_t) 0x16);
    writestr(hostname);
    readbuf((char *) &ret);

    return ret;
}

void MiniWiFi::getMAC(char *mac)
{
    stream->write((uint8_t) 0x17);
    readstr(mac);
}

void MiniWiFi::setMAC(uint8_t mac[6])
{
    stream->write((uint8_t) 0x18);
    writebuf((char *) mac, 6);
}

int8_t MiniWiFi::connectTCP(char *host, uint16_t port)
{
    int8_t ret;

    stream->write((uint8_t) 0x20);
    writestr(host);
    writebuf((char *) &port, 2);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::connectedTCP(int8_t s)
{
    return singlefunc8(0x21, s);
}

int8_t MiniWiFi::closeTCP(int8_t s)
{
    return singlefunc8(0x22, s);
}

int8_t MiniWiFi::availableTCP(int8_t s)
{
    return singlefunc8(0x23, s);
}

int8_t MiniWiFi::writeTCP(int8_t s, uint8_t *data, uint8_t len)
{
    int8_t ret;

    stream->write((uint8_t) 0x24);
    writebuf((char *) &s, 1);
    writebuf((char *) data, len);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::printTCP(int8_t s, char *str)
{
    int8_t ret;

    stream->write((uint8_t) 0x24);
    writebuf((char *) &s, 1);
    writestr(str);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::printTCP(int8_t s, const __FlashStringHelper *str)
{
    int8_t ret;

    stream->write((uint8_t) 0x24);
    writebuf((char *) &s, 1);
    writestr(str);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::readTCP(int8_t s)
{
    return singlefunc8(0x25, s);
}

int8_t MiniWiFi::readTCP(int8_t s, uint8_t *data, uint8_t len)
{
    int8_t ret;

    stream->write((uint8_t) 0x26);
    writebuf((char *) &s, 1);
    writebuf((char *) &len, 1);
    readbuf((char *) &ret);
    readbuf((char *) data);

    return ret;
}

int8_t MiniWiFi::interruptTCP(int8_t s, bool enable)
{
    int8_t ret, param;

    if(enable)
        param = 1;
    else
        param = 0;
    stream->write((uint8_t) 0x27);
    writebuf((char *) &s, 1);
    writebuf((char *) &param, 1);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::connectSSL(char *host, uint16_t port)
{
    int8_t ret;

    stream->write((uint8_t) 0x30);
    writestr(host);
    writebuf((char *) &port, 2);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::connectedSSL(int8_t s)
{
    return singlefunc8(0x31, s);
}

int8_t MiniWiFi::closeSSL(int8_t s)
{
    return singlefunc8(0x32, s);
}

int8_t MiniWiFi::availableSSL(int8_t s)
{
    return singlefunc8(0x33, s);
}

int8_t MiniWiFi::writeSSL(int8_t s, uint8_t *data, uint8_t len)
{
    int8_t ret;

    stream->write((uint8_t) 0x34);
    writebuf((char *) &s, 1);
    writebuf((char *) data, len);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::printSSL(int8_t s, char *str)
{
    int8_t ret;

    stream->write((uint8_t) 0x34);
    writebuf((char *) &s, 1);
    writestr(str);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::printSSL(int8_t s, const __FlashStringHelper *str)
{
    int8_t ret;

    stream->write((uint8_t) 0x34);
    writebuf((char *) &s, 1);
    writestr(str);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::readSSL(int8_t s)
{
    return singlefunc8(0x35, s);
}

int8_t MiniWiFi::readSSL(int8_t s, uint8_t *data, uint8_t len)
{
    int8_t ret;

    stream->write((uint8_t) 0x36);
    writebuf((char *) &s, 1);
    writebuf((char *) &len, 1);
    readbuf((char *) &ret);
    readbuf((char *) data);

    return ret;
}

int8_t MiniWiFi::interruptSSL(int8_t s, bool enable)
{
    int8_t ret, param;

    if(enable)
        param = 1;
    else
        param = 0;
    stream->write((uint8_t) 0x37);
    writebuf((char *) &s, 1);
    writebuf((char *) &param, 1);
    readbuf((char *) &ret);

    return ret;
}

void MiniWiFi::sendUDP(char *host, uint16_t port, uint8_t *data, uint8_t len)
{
    stream->write((uint8_t) 0x40);
    writestr(host);
    writebuf((char *) &port, 2);
    writebuf((char *) data, len);
}

void MiniWiFi::printUDP(char *host, uint16_t port, char *str)
{
    stream->write((uint8_t) 0x40);
    writestr(host);
    writebuf((char *) &port, 2);
    writestr(str);
}

void MiniWiFi::printUDP(char *host, uint16_t port, const __FlashStringHelper *str)
{
    stream->write((uint8_t) 0x40);
    writestr(host);
    writebuf((char *) &port, 2);
    writestr(str);
}

int8_t MiniWiFi::listenUDP(uint16_t port)
{
    int8_t ret;

    stream->write((uint8_t) 0x41);
    writebuf((char *) &port, 2);
    readbuf((char *) &ret);

    return ret;
}

void MiniWiFi::stopUDP()
{
    stream->write((uint8_t) 0x42);
}

uint8_t MiniWiFi::readUDP(uint8_t *data)
{
    uint8_t ret;

    stream->write((uint8_t) 0x43);
    ret = readbuf((char *) data);

    return ret;
}

int8_t MiniWiFi::listenTCP(uint16_t port)
{
    int8_t ret;

    stream->write((uint8_t) 0x50);
    writebuf((char *) &port, 2);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::stopTCP()
{
    return singlefunc(0x51);
}

int8_t MiniWiFi::acceptTCP()
{
    return singlefunc(0x52);
}

int8_t MiniWiFi::interruptServer(bool enable)
{
    int8_t param;

    if(enable)
        param = 1;
    else
        param = 0;
    return singlefunc8(0x53, param);
}

int8_t MiniWiFi::httpOpen(char *url)
{
    int8_t ret;

    stream->write((uint8_t) 0x60);
    writestr(url);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::httpsOpen(char *url, char *fingerprint)
{
    int8_t ret;

    stream->write((uint8_t) 0x61);
    writestr(url);
    writestr(fingerprint);
    readbuf((char *) &ret);

    return ret;
}

uint32_t MiniWiFi::httpLength()
{
    uint32_t ret;

    stream->write((uint8_t) 0x62);
    readbuf((char *) &ret);

    return ret;
}

uint32_t MiniWiFi::httpAvailable()
{
    uint32_t ret;

    stream->write((uint8_t) 0x63);
    readbuf((char *) &ret);

    return ret;
}

uint8_t MiniWiFi::httpRead(char *buf, uint8_t len)
{
    uint8_t ret;

    stream->write((uint8_t) 0x64);
    writebuf((char *) &len, 1);
    ret = readbuf(buf);

    return ret;
}

void MiniWiFi::httpClose()
{
    stream->write((uint8_t) 0x65);
}

int8_t MiniWiFi::mdnsEnable(char *host)
{
    int8_t ret;

    stream->write((uint8_t) 0x70);
    writestr(host);
    readbuf((char *) &ret);

    return ret;
}

void MiniWiFi::mdnsAddService(char *service, char *proto, uint16_t port)
{
    stream->write((uint8_t) 0x71);
    writestr(service);
    writestr(proto);
    writebuf((char *) &port, 2);
}

void MiniWiFi::mdnsAddServiceTXT(char *name, char *proto, char *key, char *value)
{
    stream->write((uint8_t) 0x72);
    writestr(name);
    writestr(proto);
    writestr(key);
    writestr(value);
}

int8_t MiniWiFi::mdnsQueryService(char *service, char *proto)
{
    int8_t ret;

    stream->write((uint8_t) 0x73);
    writestr(service);
    writestr(proto);
    readbuf((char *) &ret);

    return ret;
}

void MiniWiFi::mdnsGetQueryResult(uint8_t res, char *host, uint32_t *ip, uint16_t *port)
{
    stream->write((uint8_t) 0x74);
    writebuf((char *) &res, 1);
    readstr(host);
    readbuf((char *) ip);
    readbuf((char *) port);
}

void MiniWiFi::ssdpEnable(uint16_t port, boolean enablews)
{
    uint8_t en;

    stream->write((uint8_t) 0x80);
    writebuf((char *) &port, 2);
    if(enablews)
        en = 1;
    else
        en = 0;
    writebuf((char *) &en, 1);
}

void MiniWiFi::ssdpDisableWS()
{
    stream->write((uint8_t) 0x81);
}

void MiniWiFi::ssdpSetOption(uint8_t option, char *value)
{
    stream->write((uint8_t) 0x81);
    writebuf((char *) &option, 1);
    writestr(value);
}

char MiniWiFi::syncread()
{
    while(!stream->available())
        ;
    return (char) stream->read();
}

uint8_t MiniWiFi::readbuf(char *buf)
{
    uint8_t i, len;

    len = (uint8_t) syncread();
    for(i = 0; i < len; i++)
        buf[i] = syncread();

    return len;
}

void MiniWiFi::readstr(char *buf)
{
    uint8_t len;

    len = readbuf(buf);
    buf[len] = '\0';
}

void MiniWiFi::writebuf(char *buf, uint8_t len)
{
    uint8_t i;

    stream->write(len);
    for(i = 0; i < len; i++)
        stream->write(buf[i]);
}

void MiniWiFi::writebuf(const __FlashStringHelper *buf, uint8_t len)
{
    PGM_P p = reinterpret_cast<PGM_P>(buf);
    uint8_t i;

    stream->write(len);
    for(i = 0; i < len; i++)
        stream->write(pgm_read_byte(p++));
}

void MiniWiFi::writestr(char *buf)
{
    writebuf(buf, strlen(buf));
}

void MiniWiFi::writestr(const __FlashStringHelper *buf)
{
    writebuf(buf, strlen_P((PGM_P) buf));
}

int8_t MiniWiFi::singlefunc(uint8_t func)
{
    int8_t ret;

    stream->write(func);
    readbuf((char *) &ret);

    return ret;
}

int8_t MiniWiFi::singlefunc8(uint8_t func, int8_t param1)
{
    int8_t ret;

    stream->write(func);
    writebuf((char *) &param1, 1);
    readbuf((char *) &ret);

    return ret;
}

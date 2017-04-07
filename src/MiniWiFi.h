#ifndef MiniWiFi_h
#define MiniWiFi_h

#include <Arduino.h>

enum {
    WIFI_CONF_LOCALIP,
    WIFI_CONF_GATEWAYIP,
    WIFI_CONF_SUBNET,
    WIFI_CONF_DNS1,
    WIFI_CONF_DNS2
};

enum {
    WIFI_IDLE_STATUS,
    WIFI_NO_SSID_AVAIL,
    WIFI_SCAN_COMPLETED,
    WIFI_CONNECTED,
    WIFI_CONNECT_FAILED,
    WIFI_CONNECTION_LOST,
    WIFI_DISCONNECTED
};

enum {
    WIFI_SSDP_DEVICE_TYPE,
    WIFI_SSDP_NAME,
    WIFI_SSDP_URL,
    WIFI_SSDP_SCHEMA_URL,
    WIFI_SSDP_SN,
    WIFI_SSDP_MODEL_NAME,
    WIFI_SSDP_MODEL_NUMBER,
    WIFI_SSDP_MODEL_URL,
    WIFI_SSDP_MANUFACTURER,
    WIFI_SSDP_MANUFACTURER_URL
};


class MiniWiFi
{
    public:
        MiniWiFi(Stream *s);

        boolean pingModule();
        void reset();
        void setBaud(uint32_t baud);
        uint32_t getChipID();
        uint16_t getVcc();

        void connectWiFi(char *ssid, char *pass);
        void disconnectWiFi();
        int8_t getStatus();
        uint32_t getIPConfig(uint8_t value);
        uint8_t setIPConfig(uint32_t localIP, uint32_t gateway, uint32_t subnet, uint32_t dns1, uint32_t dns2);
        void getHostname(char *hostname);
        int8_t setHostname(char *hostname);
        void getMAC(char *mac);
        void setMAC(uint8_t mac[6]);

        int8_t connectTCP(char *host, uint16_t port);
        int8_t connectedTCP(uint8_t s);
        int8_t closeTCP(uint8_t s);
        int8_t availableTCP(uint8_t s);
        int8_t writeTCP(uint8_t s, uint8_t *data, uint8_t len);
        int8_t printTCP(uint8_t s, char *str);
        int8_t printTCP(uint8_t s, const __FlashStringHelper *str);
        int8_t readTCP(uint8_t s);
        int8_t readTCP(uint8_t s, uint8_t *data, uint8_t len);

        int8_t connectSSL(char *host, uint16_t port);
        int8_t connectedSSL(uint8_t s);
        int8_t closeSSL(uint8_t s);
        int8_t availableSSL(uint8_t s);
        int8_t writeSSL(uint8_t s, uint8_t *data, uint8_t len);
        int8_t printSSL(uint8_t s, char *str);
        int8_t printSSL(uint8_t s, const __FlashStringHelper *str);
        int8_t readSSL(uint8_t s);
        int8_t readSSL(uint8_t s, uint8_t *data, uint8_t len);

        void sendUDP(char *host, uint16_t port, uint8_t *data, uint8_t len);
        void printUDP(char *host, uint16_t port, char *str);
        void printUDP(char *host, uint16_t port, const __FlashStringHelper *str);
        int8_t listenUDP(uint16_t port);
        void stopUDP();
        uint8_t readUDP(uint8_t *data);

        int8_t listenTCP(uint16_t port);
        int8_t stopTCP();
        int8_t acceptTCP();

        int8_t httpOpen(char *url);
        int8_t httpsOpen(char *url, char *fingerprint);
        uint32_t httpLength();
        uint32_t httpAvailable();
        uint8_t httpRead(char *buf, uint8_t len);
        void httpClose();

        int8_t mdnsEnable(char *host);
        void mdnsAddService(char *service, char *proto, uint16_t port);
        void mdnsAddServiceTXT(char *name, char *proto, char *key, char *value);
        int8_t mdnsQueryService(char *service, char *proto);
        void mdnsGetQueryResult(uint8_t res, char *host, uint32_t *ip, uint16_t *port);

        void ssdpEnable(uint16_t port, boolean enablews);
        void ssdpDisableWS();
        void ssdpSetOption(uint8_t option, char *value);
    private:
        Stream *stream;

        char syncread();
        uint8_t readbuf(char *buf);
        void readstr(char *buf);
        void writebuf(char *buf, uint8_t len);
        void writebuf(const __FlashStringHelper *buf, uint8_t len);
        void writestr(char *buf);
        void writestr(const __FlashStringHelper *buf);

        int8_t singlefunc(uint8_t func);
        int8_t singlefunc8(uint8_t func, int8_t param1);
};

#endif

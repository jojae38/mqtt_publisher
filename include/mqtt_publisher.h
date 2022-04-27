#include <iostream>
#include <stdio.h>
#include <ros/ros.h>
#include <mosquitto.h>

#define mos_host "localhost"
#define mos_port 1883
class mqtt_publisher
{
    public:
        mqtt_publisher();
        ~mqtt_publisher();
    private:
        struct mosquitto *mosq;
        int error;
};
mqtt_publisher::mqtt_publisher()
{
    mosquitto_lib_init();
    mosq=mosquitto_new("publisher-test",true,NULL);
    error=mosquitto_connect(mosq,mos_host,mos_port,60);

    if(error!=0)
    {
        printf("Publisher could not connect to broker! Error Code: %d\n",error);
        mosquitto_destroy(mosq);
    }
    printf("We are now connected to the broker");
    mosquitto_publish(mosq,NULL,"test/t1",6,"Hello",0,false);

    mosquitto_disconnect(mosq);
}

mqtt_publisher::~mqtt_publisher()
{
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}
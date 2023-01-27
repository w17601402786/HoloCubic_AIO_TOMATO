//
// Created by user on 2023/1/20.
//
#include "MyMQTT.h"
#include "network.h"
#include<sys/app_controller.h>
#include "app/mood/mood.h"

MyMQTT *mqtt;

MyMQTT::MyMQTT(AppController *sys,MQTT_CALLBACK_SIGNATURE) {

    wiFiClient = WiFiClient();
    client = PubSubClient(wiFiClient);

//    //打开wifi
//    Network network = Network();

    this->sys = sys;

    this->client.setServer(mqttServer,mqttPort);

    client.setCallback(callback);
//    client.setKeepAlive(60);

    Serial.println("尝试开始链接。。。");

//    this->loop();


}


void MyMQTT::loop() {


    //如果WIFI未连接，就提示控制器更新wifi，并且不再执行后面的代码
    if(!WiFi.isConnected() && sys->eventList.size()< 3){

        //提醒控制器更新wifi
        this->sys->send_to(MOOD_APP_NAME, CTRL_NAME,
                           APP_MESSAGE_WIFI_DISCONN,NULL,NULL);
        this->sys->send_to(MOOD_APP_NAME, CTRL_NAME,
                           APP_MESSAGE_WIFI_CONN,NULL,NULL);
        return;
    }

    //wifi没连接就别更新mqtt了
    if(!WiFi.isConnected()){
        return;
    }

    //内存再套循环太卡了
    if(WiFi.isConnected() && !this->client.connected() && this->sys->eventList.size() < 3){

        //提醒控制权更新mqtt
        this->sys->send_to(MOOD_APP_NAME, CTRL_NAME,
                           APP_MESSAGE_UPDATE_MQTT,NULL,NULL);
    }

    if (WiFi.isConnected()){
        this->client.loop();
    }
}

boolean MyMQTT::sendPropertiesReport(char *payload) {

    //发送当前设备的某些属性


    return 0;
}


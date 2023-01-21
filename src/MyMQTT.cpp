//
// Created by user on 2023/1/20.
//
#include "MyMQTT.h"
#include "network.h"
// #include<sys/app_controller.h>


MyMQTT::MyMQTT(const char * sid, const char * password, MQTT_CALLBACK_SIGNATURE) {

    wiFiClient = WiFiClient();
    client = PubSubClient(wiFiClient);

    //打开wifi
    Network network = Network();
    network.start_conn_wifi(sid,password);


    this->client.setServer(mqttServer,mqttPort);

    client.setCallback(callback);
    client.setKeepAlive(60);

    Serial.println("尝试开始链接。。。");

    this->loop();


}


void MyMQTT::loop() {

    if(!this->client.connected()){


        Serial.println("连接失败");

        while (!client.connected())
        {
            if(client.connect(clientId,mqttUser,mqttPassword)){
                Serial.println("connected");
            }else{
                Serial.println("fail:");
                Serial.print(client.state());
                delay(6000);
            }
        }


        boolean result = this->client.subscribe(topic_Commands);
        Serial.println(topic_Commands);
        Serial.println(result == 1 ? "订阅成功" : "订阅失败");
    }
    this->client.loop();
}

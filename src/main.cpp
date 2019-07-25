#include "main.h"

//---------------------------- WIFI --------------------------------------
const char *ssid = "OnePlus6";
const char *pwd = "vikiscool";
const IPAddress ip(192, 168, 43, 120);
IPAddress gateway;
const IPAddress subnet(255, 255, 255, 0);

//---------------------------- OSC --------------------------------------
OscWiFi osc;
String host;
const uint16_t recv_port = 10000;
const uint16_t send_port = 12000;

//---------------------------- CONTROL & COUNT --------------------------------------
int times_run = 0;
const int period = 1000;
unsigned long time_now = 0;

//---------------------------- SENSORS --------------------------------------
const String gsr_sensor = "GSR";

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, pwd);
  delay(500);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
  }
  gateway = WiFi.gatewayIP(); // Onze gateway IP = onze host IP. Dit omdat de smartphone in AP mode staat en zijn eigen IP = gatewayIP.
  host = String(gateway);
  WiFi.config(ip, gateway, subnet);

  Serial.print("WiFi connected,      IP = ");
  Serial.println(WiFi.localIP());
  Serial.print("WiFi connected, GATEWAY = ");
  Serial.println(gateway);

  osc.begin(recv_port);
  String osc_send_succes = "Succes";
  bool send = true;
  osc.send(host, send_port, "/start", osc_send_succes, send);

} //--- setup()

void loop()
{
  time_now = millis();
  osc.parse();

  if (time_now % period == 0)
  {
    times_run++;
    Serial.printf("There have %2.fs passed since start, executed %i times\n", time_now * 0.001, times_run);
    Serial.println("------------------------------------------------------------");
    Serial.print("Msg[] size: ");
    Serial.print(" | ");
    //sensor_to_container(gsr_sensor, getGsrData());
    sensor_to_container(0, gsr_sensor, getGsrData());
  }
} //--- loop()
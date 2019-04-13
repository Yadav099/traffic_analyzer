#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#define TRIGGERPIN D1
#define ECHOPIN    D2

int defolt=1000;//can be different for different places


int x=0,y=2,vehicle=0;
int begin_time=0,calc_time,pres_time;
char g[256];
char h[128];
char ssid[] = "6";
char pass[] = "12345678";  //mobile wifi password



IPAddress server_addr(192,168,43,130);
String INSERT_DATA= "INSERT INTO arduino.ultra (Time,id) VALUES ('NOW()','%d');";
char user[] = "eeee";
char password[] = "eeee";

WiFiClient client;
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

void setup() {

  Serial.begin(115200);

WiFi.begin(ssid,pass);
 while(WiFi.status()!= WL_CONNECTED) {
 delay(500);
}

 if (conn.connect(server_addr,3306,user,password)){
  Serial.println("Connected");
     }else{Serial.println("Not Connected");}


pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);


}

void loop(){

long duration, distance;

  digitalWrite(TRIGGERPIN, LOW);
  delayMicroseconds(3);

  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12);

  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);
  Serial.println("Cm");
  if(distance <= defolt)
 { vehicle=vehicle+1;
   delay(100);

    }
 pres_time=millis();
 calc_time = pres_time - begin_time;

if(calc_time>= 10000)
{Serial.println("Vehicle count");
MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    INSERT_DATA.toCharArray(g,128);
    sprintf(h,g,vehicle);

    cur_mem->execute(h);
    Serial.println(vehicle);
 vehicle=0;

 begin_time=pres_time;
}delay(1000);
 }

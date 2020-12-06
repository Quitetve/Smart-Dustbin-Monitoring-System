#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

 int trigPinA = 13;
 int echoPinA = 12;
 
 int trigPinB = 8;
 int echoPinB = 7;

int ledPinA = 5;
int ledPinB = 3;

void setup() {
  Serial.begin (9600);
pinMode(trigPinA, OUTPUT);
pinMode(echoPinA, INPUT);

pinMode(trigPinB, OUTPUT);
pinMode(echoPinB, INPUT);

pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  
// Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {

 // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close"); // the connection will be closed after completion of the response
 //client.println("Refresh: 20");  // refresh the page automatically every 20 sec
client.println();
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<style>html { font-family: Cairo; display: block; margin: 0px auto; text-align: center;color: #333333; background-color: ##f3ffee;}");
client.println("body{margin-top: 50px;}");
client.println("h1 {margin: 50px auto 30px; font-size: 50px; text-align: center;}");
client.println(".side_adjust{display: inline-block;vertical-align: middle;position: relative;}");
client.println(".text1{font-weight: 180; padding-left: 5px; font-size: 50px; width: 170px; text-align: left; color: #3498db;}");
client.println(".data1{font-weight: 180; padding-left: 1px; font-size: 50px;color: #3498db;}");
client.println(".data{padding: 1px;}");
client.println("</style>");
client.println("</head>");
client.println("<body>");
client.println("<div id=\"webpage\">");
client.println("<h1>IoT Based Dustbin</h1>");
client.println("<h1>Dustbin A</h1>");
client.println("<div class=\"data\">");
client.println("<div class=\"side_adjust text1\">Status:</div>");
long durationA;
int distanceA;
int levelA;

digitalWrite(trigPinA, LOW);
delayMicroseconds(2);
digitalWrite(trigPinA, HIGH);

delayMicroseconds(10);
digitalWrite(trigPinA, LOW);
durationA = pulseIn(echoPinA, HIGH);
distanceA = durationA * 0.0340 / 2;
Serial.println("Distance A :");
Serial.println(distanceA);
levelA =((28 -distanceA)/28.0)*100;
Serial.println("level A :");
Serial.println(levelA);
delay(1000);
client.print(levelA);
client.println("<div class=\"side_adjust text1\">% filled</div>");

    
  digitalWrite (trigPinA, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinA, LOW);
  durationA= pulseIn (echoPinA, HIGH);
  distanceA = (durationA/2) / 29.1;


  if (distanceA < 10 ) {  // Change the number for long or short distances.
    digitalWrite (ledPinA, HIGH);
  
  } else {
    digitalWrite (ledPinA, LOW);
   
      
  }   

client.println("<h1>Dustbin B</h1>");
client.println("<div class=\"data\">");
client.println("<div class=\"side_adjust text1\">Status1:</div>");

long durationB;
int distanceB;
int levelB;

     
  

digitalWrite(trigPinB, LOW);
delayMicroseconds(2);
digitalWrite(trigPinB, HIGH);

delayMicroseconds(10);
digitalWrite(trigPinB, LOW);

durationB = pulseIn(echoPinB, HIGH);
distanceB = durationB * 0.0340 / 2;
Serial.println("Distance B :");
Serial.println(distanceB);
levelB =((28 -distanceB)/28.0)*100;
Serial.println("level B :");
Serial.println(levelB);
delay(1500);
client.print(levelB);
client.println("<div class=\"side_adjust text1\">% filled</div>");
digitalWrite (trigPinB, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPinB, LOW);
  durationB = pulseIn (echoPinB, HIGH);
  distanceB = (durationB/2) / 29.1;


  if (distanceB < 10) {  // Change the number for long or short distances.
    digitalWrite (ledPinB, HIGH);

   
    
  } else {
    digitalWrite (ledPinB, LOW);
    
      
  }   
client.println("<div class=\"side_adjust data1\">");
client.println("<br />");
client.println("<input type=button value=notify onmousedown=location.href='http://abiykuomel.com/smartdustbin/notify.html'>");        
client.println("</div>");
client.println("</div>");
client.println("</body>");
client.println("</html>");


break;
}
}
    }

// give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
  }

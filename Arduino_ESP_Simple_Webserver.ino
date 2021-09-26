


//Ensure the libraries below are installed in your Arduino IDE
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80); //Server is always on port 80






//Website code 
String M = "  <!DOCTYPE html><html><body><h2>Arduino Robot<h2><h3>ESP8266 Web Server</h3><h4>Grid Coordinates</h4><form action=\"action_page\">Enter X-Value:<br><input type=\"text\" name=\"X-Value\" value=\"   \"><br>Enter Y-Value:<br><input type=\"text\" name=\"Y-Value\" value=\"   \"><br><br><input type=\"submit\" value=\"Submit\"></form> </body></html>         ";

//SSID and Password of your WiFi router
const char* ssid = "1234_WIFI";
const char* password = "iawt9904";





int Xval = 20;
int Yval = 30;






void setup() {
  Serial.begin(9600); // Starts the serial communication

  



        WiFi.begin(ssid, password);     //Connect to your WiFi router
        Serial.println("");

        // Wait for connection
        while (WiFi.status() != WL_CONNECTED)
        {
        delay(500);
        Serial.print(".");
        }

        //If connection successful show IP address in serial monitor
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println("WiFi");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());  //IP address assigned to your ESP
         
        server.on("/", handleRoot);      //Which routine to handle at root location
        server.on("/action_page", handleForm); //form action is handled here
        
        server.begin();                  //Start server
        Serial.println("HTTP server started");
        
 }


//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  
  
  while( Xval == 0 || Yval == 0){
  Serial.print("Waiting for coordinates \n");
  server.handleClient();          //Handle client requests
  }
 

    delay(100);


  Xval = 0;
  Yval = 0;
  
}



//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================

void handleRoot() {
 String s = M; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

//===============================================================
// This routine is executed when you press submit
//===============================================================

void handleForm() {
 String Xvalue = server.arg("X-Value"); 
 String Yvalue = server.arg("Y-Value"); 
 
 //convert string to int in-order to save value
 Xval = Xvalue.toInt();  
 Yval = Yvalue.toInt();
 
 Serial.print("Recived X-Value:");
 Serial.println(Xvalue);

 Serial.print("Recived Y-Value:");
 Serial.println(Yvalue);
 
 Serial.print("Coordinates are:(") ;
 Serial.print(Xvalue);
 Serial.print(",");
 Serial.print(Yvalue);
 Serial.print(")\n ");
 //Serial.print("Coordinates are:");
 
 Serial.print("\n\n");
  // String s = "<a href='/'> Go Back </a>";
  // server.send(200, "text/html", s); //Send web page
  //Refresh the webpage to the same page 
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated– Press Back Button");
}








 

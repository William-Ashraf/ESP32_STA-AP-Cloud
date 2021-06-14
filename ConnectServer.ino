int httpPost(char *link,String post)
{
  HTTPClient http;   
  http.begin(link);
  http.addHeader("Content-Type", "text/plain");              
   int httpResponseCode = http.POST(post);   //Send the actual POST request
   if(httpResponseCode>0){
    Serial.println(httpResponseCode); 
   }
   else
   {
    Serial.println("Error on sending POST");
   }
   http.end();
   return httpResponseCode; 
}

String httpGet(char *link)
{ String payload = " ";
  HTTPClient http;
    http.begin(link); //Specify the URL
    int httpCode = http.GET();         //Make the request
    if (httpCode > 0)
    { //Check for the returning code
        payload = http.getString();
    }
    else 
    {
      Serial.println("Error on HTTP request");
    }
    
    http.end(); //Free the resources
    return payload ;
  }
  

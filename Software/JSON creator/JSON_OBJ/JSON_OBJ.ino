void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int val = 6757;
  char* ID= "451632";
  char* json;
  json = JSON_get(ID,val);
  Serial.println(json);
  delay(500);
  
}

char* JSON_get(char* id, int value)
  {
    char JSON_string[50];
    char buffer[30];
    strcpy(JSON_string,"{Id:");
    strcat(JSON_string,id);
    strcat(JSON_string,",");
    strcat(JSON_string,"Value:");
  
    itoa(value,buffer,10);
  
    strcat(JSON_string,buffer);
    strcat(JSON_string,"}");
    
    char* ret_str = new char[strlen(JSON_string)];
    strcpy(ret_str,JSON_string);
  
    return ret_str;
  }
//  void append(char* a,char* b)
//  {
//    Serial.println(a[0]);
////    int lena = strlen(a);
////    
////    for(int i = 0;i<lena;i++)
////    {
////      a[lena] = b[i];
////      lena++;
////    }
//  }
  

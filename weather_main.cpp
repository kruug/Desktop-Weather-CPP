#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/pointer.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <curl/curl.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <ctime>
#include <math.h> 
// weather_main.cpp
// This is a C++ version of my Desktop Weather program.
// Original located at https://github.com/kruug/Desktop-Weather-CSharp

using namespace rapidjson;
using namespace std;

string URL_FIRST = "https://api.forecast.io/forecast/";
string API_KEY = "/"; /* Always use the `/` as the last character */
string URL_LOCATION = "44.936905,-91.392935";

string URL = URL_FIRST + API_KEY + URL_LOCATION;

char buffer_zero[80];
char buffer_one[80];
char buffer_two[80];
char buffer_three[80];

int date_zero;
int date_one;
int date_two;
int date_three;

double temp_current;
int temp_zero_high;
int temp_one_high;
int temp_two_high;
int temp_three_high;

int temp_zero_low;
int temp_one_low;
int temp_two_low;
int temp_three_low;

time_t rawtime_zero;
time_t rawtime_one;
time_t rawtime_two;
time_t rawtime_three;

string conditions_current;
string conditions_zero;
string conditions_one;
string conditions_two;
string conditions_three;

string weather_data;

struct tm * timeinfo_zero;
struct tm * timeinfo_one;
struct tm * timeinfo_two;
struct tm * timeinfo_three;

struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  std::memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}

int main(void)
{
  CURL *curl;
  CURLcode res;
  struct MemoryStruct chunk;
  Document d;
 
  chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */ 
  chunk.size = 0;    /* no data at this point */ 

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }

  d.Parse(chunk.memory);


  if (Value* currently = GetValueByPointer(d, "/currently")) {
//    rawtime = (*currently)["time"].GetInt();
    temp_current = (*currently)["temperature"].GetDouble();
    conditions_current = (*currently)["summary"].GetString();
  }

  if (Value* day_zero = GetValueByPointer(d, "/daily/data/0")) {
    rawtime_zero = (*day_zero)["time"].GetInt();
    temp_zero_high = round((*day_zero)["temperatureMax"].GetDouble());
    temp_zero_low = round((*day_zero)["temperatureMin"].GetDouble());
    conditions_zero = (*day_zero)["summary"].GetString();
  }

//  timeinfo = localtime (&rawtime);
  timeinfo_zero = localtime (&rawtime_zero);

  strftime(buffer_zero, 80, "%m/%d", timeinfo_zero);

//  cout << buffer << endl;
  cout << setw(30) << left << temp_current << setw(30) << left << to_string(temp_zero_high) + "/" + to_string(temp_zero_low) << endl;
  cout << setw(30) << left << conditions_current << setw(30) << left << conditions_zero << endl;
 
  return 0;
}

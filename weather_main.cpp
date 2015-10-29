#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <curl/curl.h>
// weather_main.cpp
// This is a C++ version of my Desktop Weather program.
// Original located at https://github.com/kruug/Desktop-Weather-CSharp

std::string URL_FIRST = "https://api.forecast.io/forecast/";
std::string API_KEY = "06fab55021a0b1d1b47ee909fb8723f9/"; /* Always use the `/` as the last character */
std::string URL_LOCATION = "37.8267,-122.423";

std::string URL = URL_FIRST + API_KEY + URL_LOCATION;

int date_current;
int date_zero;
int date_one;
int date_two;
int date_three;

float temp_current;
float temp_zero_high;
float temp_one_high;
float temp_two_high;
float temp_three_high;

float temp_zero_low;
float temp_one_low;
float temp_two_low;
float temp_three_low;

std::string conditions_current;
std::string conditions_zero;
std::string conditions_one;
std::string conditions_two;
std::string conditions_three;

std::string weather_data;

int main(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }

  return 0;
}

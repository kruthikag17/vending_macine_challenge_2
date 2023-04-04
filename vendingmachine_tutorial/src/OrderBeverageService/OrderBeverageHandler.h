#ifndef VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H
#define VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/OrderBeverageService.h"
#include "../../gen-cpp/WeatherService.h"
#include "../../gen-cpp/BeveragePreferenceService.h"
#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace vending_machine{

class OrderBeverageServiceHandler : public OrderBeverageServiceIf {
 public:
   OrderBeverageServiceHandler(
      ClientPool<ThriftClient<WeatherServiceClient>>*,
      ClientPool<ThriftClient<BeveragePreferenceServiceClient>>*);
  
~OrderBeverageServiceHandler() override=default;
  void PlaceOrder(std::string& _return, const int64_t city) override ;
 private:
  ClientPool<ThriftClient<WeatherServiceClient>> *_weather_client_pool;

ClientPool<ThriftClient<BeveragePreferenceServiceClient>> *_beverage_client_pool;
};

// Constructor
OrderBeverageServiceHandler::OrderBeverageServiceHandler(
		ClientPool<ThriftClient<WeatherServiceClient>> *weather_client_pool,
ClientPool<ThriftClient<BeveragePreferenceServiceClient>> *beverage_client_pool) {

     // Storing the clientpool
     _weather_client_pool = weather_client_pool;
_beverage_client_pool = beverage_client_pool;
}

// Remote Procedure "PlaceOrder"
void OrderBeverageServiceHandler::PlaceOrder(std::string& _return, const int64_t city){
     // Your implementation goes here
     printf("PlaceOrder\n");

     //return BeverageType::type::COLD;
#if 1   
    // 1. get the weather service client pool
    auto weather_client_wrapper = _weather_client_pool->Pop();
    if (!weather_client_wrapper) {
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
      se.message = "Failed to connect to weather-service";
      throw se;
    }
    auto weather_client = weather_client_wrapper->GetClient();

    // by default get cold
     BeverageType::type btype = BeverageType::type::HOT; //default get beverage type 
    WeatherType::type weatherType = WeatherType::type::COLD;

    // 2. call the remote procedure : GetWeather
    try {
      weatherType = weather_client->GetWeather(city);
    } catch (...) {
      _weather_client_pool->Push(weather_client_wrapper);
      LOG(error) << "Failed to send call GetWeather to weather-client";
      throw;
    }
    _weather_client_pool->Push(weather_client_wrapper);
    
 // 3. get the beverage preference service client pool
  auto beverage_client_wrapper = _beverage_client_pool->Pop();
  if (!beverage_client_wrapper) {
    ServiceException se;
    se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
    se.message = "Failed to connect to beverage-preference-service";
    throw se;
  }
  auto beverage_client = beverage_client_wrapper->GetClient();
std::string beverage;
std::string answer;
   // 3. business logic
   if(weatherType == WeatherType::type::WARM)
	{

     try {
BeverageType::type btype = BeverageType::type::COLD;
  
//  beverage_preference->GetBeverage(BeverageType::type::COLD);
beverage_client->GetBeverage(beverage,btype);
_return=beverage;
//BeverageType::type::COLD;std::string beverage = beverage_preference->getBeverage(cold);
  } catch (...) {
    _beverage_client_pool->Push(beverage_client_wrapper);
    LOG(error) << "Failed to send call getBeverage to beverage-client";
   }
   }
	
   else
   {
	   try {
BeverageType::type btype = BeverageType::type::HOT;
  
beverage_client->GetBeverage(beverage,btype);
_return=beverage;
 // beverage_preference->GetBeverage(BeverageType::type::HOT);
//verageType::type::COLD;
  } catch (...) {
    _beverage_client_pool->Push(beverage_client_wrapper);
    LOG(error) << "Failed to send call getBeverage to beverage-client";
   }
   }
#endif
}

} // namespace vending_machine


#endif //VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H


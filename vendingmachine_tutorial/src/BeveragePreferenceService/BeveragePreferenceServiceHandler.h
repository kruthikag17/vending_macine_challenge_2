#ifndef VENDING_MACHINE_MICROSERVICE_BEVERAGEPREFERENCESERVICEHANDLER_H
#define VENDING_MACHINE_MICROSERVICE_BEVERAGEPREFERENCESERVICEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/WeatherService.h"
#include "../../gen-cpp/OrderBeverageService.h"
#include "../../gen-cpp/BeveragePreferenceService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace vending_machine{

class BeveragePreferenceServiceHandler : public BeveragePreferenceServiceIf {
public:
    void GetBeverage(std::string& _return, const BeverageType::type btype) {
        if (btype == BeverageType::HOT) {
            std::vector<std::string> hot_beverages = {"cappuccino", "latte", "espresso"};
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(hot_beverages.begin(), hot_beverages.end(), g);
            _return = hot_beverages[0];
        } else {
            std::vector<std::string> cold_beverages = {"lemonade", "ice tea", "soda"};
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(cold_beverages.begin(), cold_beverages.end(), g);
            _return = cold_beverages[0];
        }
    }
};







} // namespace vending_machine


#endif 

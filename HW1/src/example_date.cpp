#include <iostream>
#include <print>
#include <vector>
#include <cmath>

#include "date.h"
#include "black_scholes.h"

class Discount {
    public:
        Discount (Date valuation_date, double rate): 
            m_valuation_date(valuation_date),
            m_rate(rate) 
        {}
        double discount(Date expiry) {
            double T=(expiry-m_valuation_date)/365; // expiry in years from valuation date
            return exp(-T*m_rate);
        }
        ~Discount() {};
    private: // this is not accessible from the outsite
        Date m_valuation_date;
        double m_rate;
};
class Forward {
    public:
        Forward(Date valuation_date, double spot, double rate, double div_yield): 
            m_valuation_date(valuation_date),
            m_spot(spot),
            m_rate(rate),
            m_div_yield(div_yield)
        {}
        double forward(Date expiry) {
            double T=(expiry-m_valuation_date)/365.0; // expiry in years from valuation date
            return m_spot*exp(T*(m_rate-m_div_yield));
        }
        ~Forward() {};
    private: // this is not accessible from the outsite
        Date m_valuation_date;
        double m_spot;
        double m_rate;
        double m_div_yield;
};

struct Option {
    std::string underlying;
    double notional; // notional number of shares of underlying 
    bool is_call;
    double strike;
    Date expiry; // number of days since 1970-01-01
    double price(Date valuation_date, Discount &discount, Forward &forward, double volatility) {
        double T=(expiry-valuation_date)/365.0;
        double df=discount.discount(expiry);
        double F=forward.forward(expiry);
        return notional*df*bs_price_fwd(is_call,strike,T,F,volatility);
    };
};

using namespace std;
int main(int argc, const char *argv[]) {
    Option opt{"SPX",1000,true,3800,Date(2022,12,21)};
    std::print("Option:\n");
    std::print("\tnotional: {}\n",opt.notional);
    std::print("\tunderlying: {}\n",opt.underlying);
    std::print("\tis_call: {}\n",(opt.is_call?"Call":"Put"));
    std::print("\tstrike: {}\n",opt.strike);
    std::print("\texpiry: {}\n",opt.expiry);

    Date valuation_date(2022,10,18);
    double rate=0.035;
    Discount discount(valuation_date,rate);
    double div_yield=0.015;
    double spot=3750;
    Forward forward(valuation_date,spot,rate,div_yield);
    double volatility=0.25;
    double price=opt.price(valuation_date,discount,forward,volatility);
    //cout<<"Price: "<<price<<endl;
    std::print("Price: {}\n",price);
    return 0; 
}
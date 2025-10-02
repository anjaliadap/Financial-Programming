#include "discount.h"
#include <cmath>
#include <iostream>
using namespace std;
int main() {
    int tenors=5;
    double Ts[tenors]={1.0,2.0,5.0,10,30};
    double coupons[tenors]={0.025,0.0325,0.045,0.045,0.0475};
    double prices[tenors]={ 1.02, 1.05,1.01,0.99,0.98};
    double freq=1.0;
    
    // Problem 1.3 Bootstrap discount curve
    //             given inputs above

    cout<<"T,zero_rate,bond_price"<<endl;
    for (int i=0;i<tenors;i++) {
        // Problem 1.3: ouput zero rate and bond prices
        //      verify that bond prices match inputs. 
    }
    return 0;
}
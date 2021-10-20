#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <random>
#include <vector>

using namespace std;

random_device rd;  
mt19937 gen(rd()); 

ostream& operator<<(ostream& o, vector<double> v)
{
    for (auto e : v) {
        o << std::fixed << std::setprecision(5) << "\t" << e;
    }
    return o;
}

vector<double> hill_climbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations)
{
    auto p = p0;
    uniform_int_distribution<> distrib(0, p.size() - 1);
    uniform_real_distribution<> distrib_r(-0.1, 0.1);

    if (!f_domain(p)) throw std::invalid_argument("The p0 point must be in domain");
    for (int i = 0; i < iterations; i++) {
        auto p2 = p;

        p[distrib(gen)] += distrib_r(gen);
        double y2 = f(p2);
        if (y2 < f(p)) {
            p = p2;
        }
    }
    return p;
}

int main()
{
    auto function1 = [](vector<double> v) {
        return 100 - (v[0] * v[0] + v[1] * v[1]);
    };

    auto matyas = [](vector<double> v) {
        double x = v.at(0), y = v.at(1);
        return -20 * exp(-0.2 * sqrt(0.5 * (x * x + y * y))) - exp(0.5 * (cos(2 * M_PI * x) + cos(2 * M_PI * y))) + M_E + 20.0;
    };

    auto matyas_domain = [](vector<double> v) {
        return (abs(v[0]) <= 5) && (abs(v[1]) <= 5);
    };

    uniform_real_distribution<> distrib_r(-5, 5);
    vector<double> matyas_p0 = {
        distrib_r(gen),
        distrib_r(gen),
    };
    auto result =  hill_climbing(matyas, matyas_domain, matyas_p0, 10000);
   cout << result << " -> " << matyas(result) << endl;

    auto matyas = [](vector <double> v){
        double x = v.at(0),y= v.at(1);
        return -0.26*(x*x -y*y)-0.48*x*y;
    };
    auto matyas_domain = [](vector <double> v){
    return (abs(v[0]) <= 10) && (abs(v[1]) <= 10);
    };
     uniform_real_distribution<> distrib_r(-10, 10);
    vector<double> matyas_p0 = {
        distrib_r(gen),
        distrib_r(gen),
    };


 auto result =  hill_climbing(matyas, matyas_domain, matyas_p0, 10000);
   cout << result << " -> " << matyas(result) << endl;
   

    

    return 0;
}
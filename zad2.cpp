#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <random>
#include <vector>

using namespace std;

random_device rd;
mt19937 gen(rd());

ostream &operator<<(ostream &o, vector<double> v)
{
    for (auto e : v)
    {
        o << std::fixed << std::setprecision(5) << "\t" << e;
    }
    return o;
}

vector<double> hill_climbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations)
{
    auto p = p0;
    uniform_int_distribution<> distrib(0, p.size() - 1);
    uniform_real_distribution<> distrib_r(-0.1, 0.1);

    if (!f_domain(p))
        throw std::invalid_argument("The p0 point must be in domain");
    for (int i = 0; i < iterations; i++)
    {
        auto p2 = p;

        p2[distrib(gen)] += distrib_r(gen);
        if (f_domain(p2))
        {
            double y2 = f(p2);
            if (y2 < f(p))
            {
                p = p2;
            }
        }
    }
    return p;
}

int main()
{
    cout << "Ktorą funkcje chcesz wykorzystac ? 1 - ackley , 2- himmelblau" << endl;
    int a;
    cin >> a;

    int b, c;

    while (!(b <= 5 && b >= (-5)))
    {
        cout << "Podaj pierwszy argument" << endl;
        cin >> b;
    };

    while (!(c <= 5 && c >= (-5)))
    {
        cout << "Podaj drugi argument" << endl;
        cin >> c;
    };

    auto function1 = [](vector<double> v)
    {
        return 100 - (v[0] * v[0] + v[1] * v[1]);
    };

    if (a == 1)
    {
        auto ackley = [](vector<double> v)
        {
            double x = v.at(0), y = v.at(1);
            return -20 * exp(-0.2 * sqrt(0.5 * (x * x + y * y))) - exp(0.5 * (cos(2 * M_PI * x) + cos(2 * M_PI * y))) + M_E + 20.0;
        };

        auto ackley_domain = [](vector<double> v)
        {
            return (abs(v[0]) <= 5) && (abs(v[1]) <= 5);
        };

        uniform_real_distribution<> distrib_r(-5, 5);
        vector<double> ackley_p0 = {
            distrib_r(gen),
            distrib_r(gen),
        };
        auto result = hill_climbing(ackley, ackley_domain, ackley_p0, 100000);
        cout << result << " -> " << ackley(result) << endl;
    }
    else
    {
        if (a == 2)
        {

            auto himmelblau = [](vector<double> v)
            {
                double x = v.at(0), y = v.at(1);
                return (x * x + y - 11) * (x * x + y - 11) + (x + y * y - 7) * (x + y * y - 7);
            };
            auto himmelblau_domain = [](vector<double> v)
            {
                return (abs(v[0]) <= 5) && (abs(v[1]) <= 5);
            };
            uniform_real_distribution<> distrib_r(-5, 5);
            vector<double> himmelblau_p0 = {
                distrib_r(gen),
                distrib_r(gen),
            };
            auto result2 = hill_climbing(himmelblau, himmelblau_domain, himmelblau_p0, 10000);
            cout << result2 << " -> " << himmelblau(result2) << endl;
        }
        else
        {
            cout << " zly argument";
        }
    }
    return 0;
}
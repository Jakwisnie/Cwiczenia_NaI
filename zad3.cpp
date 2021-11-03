#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <random>
#include <vector>
#include "gnuplot-iostream.h"

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
vector<double> simulated_annealing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations, function<vector<double>(vector<double>)> N, function<double(int)> T)
{
    auto s_current = p0;
    auto s_global_best = p0;

    //    uniform_int_distribution<> distrib(0, p.size() - 1);
    uniform_real_distribution<> u_k(0.0, 1.0);

    if (!f_domain(s_current))
        throw std::invalid_argument("The p0 point must be in domain");

    for (int k = 0; k < iterations; k++)
    {
        auto s_next = N(s_current);
        if (f_domain(s_next))
        {
            if (f(s_next) < f(s_current))
            {
                s_current = s_next;
            }
            else
            {
                double u = u_k(gen);
                if (u < exp(-abs(f(s_next) - f(s_current)) / T(k)))
                {
                    s_current = s_next;
                }
                else
                {
                    // nothing...
                }
            }
        }
        if (f(s_current) < f(s_global_best))
        {
            s_global_best = s_current;
        }
        //        cout << k << " " << f(s_current) << endl;
    }
    
    cout << s_current << " " << f(s_current) << endl;
    return s_global_best;
}
int main()
{
    cout << "Ktory algorytm chcesz wykorzystac ? 1 - hill_climbing , 2 - simulated_annealing" << endl;
    int g;
    cin >> g;

    cout << "Ktorą funkcje chcesz wykorzystac ? 1 - ackley , 2- himmelblau" << endl;
    int a;
    cin >> a;

    auto function1 = [](vector<double> v)
    {
        return 100 - (v[0] * v[0] + v[1] * v[1]);
    };
    if (g == 1)
    {
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
    }
    else
    {
        if (g == 2)
        {
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
                auto result = simulated_annealing(
                    ackley, ackley_domain, ackley_p0, 10000,
                    [](auto p)
                    {
                        normal_distribution<double> n(0.0, 0.3);
                        for (auto &e : p)
                        {
                            e = e + n(gen);
                        }
                        return p;
                    },
                    [](int k)
                    { return 1000.0 / k; });
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
                    auto result2 = simulated_annealing(
                        himmelblau, himmelblau_domain, himmelblau_p0, 10000,
                        [](auto p)
                        {
                            normal_distribution<double> n(0.0, 0.3);
                            for (auto &e : p)
                            {
                                e = e + n(gen);
                            }
                            return p;
                        },
                        [](int k)
                        { return 1000.0 / k; });
                    cout << result2 << " -> " << himmelblau(result2) << endl;
                }
                else
                {
                    cout << " zly argument";
                }
            }
        }
        else
        {
            cout << " zly argument";
        }
    }
    return 0;
}
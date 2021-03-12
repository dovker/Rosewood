#include "Benchmark.h"

namespace Rosewood
{
    static std::vector<std::pair<std::string, double>> s_Benchmarks;

    void Benchmark::Init()
    {
        s_Benchmarks = std::vector<std::pair<std::string, double>>();
        s_Benchmarks.reserve(20);
    }
    void Benchmark::Reset()
    {
        s_Benchmarks.clear();
        s_Benchmarks.reserve(20);

    }
    
    void Benchmark::Add(std::pair<std::string, double> benchmarkPair)
    {
        auto t = std::find_if( s_Benchmarks.begin(), s_Benchmarks.end(), [benchmarkPair](std::pair<std::string, double> element){
            return element.first == benchmarkPair.first;
        });
        if(t != s_Benchmarks.end())
        {
            t->second += benchmarkPair.second;
        }
        else
        {
            s_Benchmarks.push_back(benchmarkPair);
        }
    }
    std::vector<std::pair<std::string, double>> Benchmark::GetData()
    {
        return s_Benchmarks;
    }
}

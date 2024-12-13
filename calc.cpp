#include "calc.h" 
using namespace std;

calc::calc(vector<uint64_t> vector, uint32_t len)
{   v = vector;
    dl = len;}

uint64_t calc::calculate(){
    uint64_t sum=0;
    uint64_t arf=0;
    for (auto i : v){
        if (sum > 9223372036854775807 - i) {
        return 9223372036854775807;}
         sum+=i;
        }
    arf = sum / dl;
    return arf;
}

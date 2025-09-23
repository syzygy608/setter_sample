#include <iostream>

using namespace std;
using ll = long long;

int main()
{
    ll n;
    cin >> n;
    ll ans = 1;
    for(ll i = 2; i <= n; i++)
        ans ^= i;
    cout << ans << '\n';
    return 0;
}
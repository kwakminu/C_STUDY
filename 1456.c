#include <stdio.h>
#define ll long long
using namespace std;

ll n, m;
ll arr[10000011];
int main(void)
{
  scanf("%lld %lld", &n, &m);

  arr[1] = 1;
  for (ll i = 2; i * i <= m; i++)
  {
    if (arr[i])
      continue;
    for (ll j = 2; j * j * i * i <= m; j++)
    {
      arr[j * i] = 1;
    }
  }
  ll res = 0;
  for (ll i = 2; i <= m / i; i++)
  {
    if (arr[i])
      continue;

    ll tmp = i;
    while (tmp <= m / i)
    {
      if (tmp * i >= n)
      {
        res++;
        //printf("%lld ", tmp);
      }

      tmp *= i;
    }
  }

  printf("%lld\n", res);
  return 0;
}
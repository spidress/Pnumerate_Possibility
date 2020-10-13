#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int Mi = 50, Ni = 4;
int avex = 0;

double fac(int a)
{
	double result = 1;
	for (int i = a; i > 0; i--)
		result *= i;
	return result;
}

double A(int a, int b)
{
	return fac(a)/fac(a-b);
}

double C(int a, int b)
{
	return fac(a)/fac(a-b)/fac(b);
}

int min(int x, int y)
{
	return x<y?x:y;
}

int ceil(int x, int y)
{
	if(y == 0) return 1;
	else return x%y?(x/y+1):x/y;
}

double divide(int minx, int maxx, int prex, int m, int n, int maxcnt, int samecnt, int selected)
{
	int x, k;
	double P = 0, tmp, cnt=0, tmpcnt=0;

	if(m == 0)
		return 1.0*C(n+samecnt, samecnt)/maxcnt;
	for(x = minx; x <= min(maxx, m); x++)
	{
		if (x == avex) maxcnt++;
		//printf("x = %d, selected = %d\n", x, selected+1);
		if(x == prex) 
		{
			tmpcnt = divide(ceil(m-x, n-1), x, x, m-x, n-1, maxcnt, samecnt+1, selected+1);
			//printf("C(%d, %d) * %lf = ", m, x, tmpcnt);
			tmpcnt = C(m, x) * tmpcnt;
			//printf("%lf\n", tmpcnt);
		}
		else
		{
			tmpcnt = divide(ceil(m-x, n-1), x, x, m-x, n-1, maxcnt, 1, selected+1);
			//printf("C(%d, %d) * %lf * C(%d, %d) = ", m, x, tmpcnt, n+samecnt, samecnt);
			tmpcnt = C(m, x) * tmpcnt * C(n+samecnt, samecnt);
			//printf("%lf\n", tmpcnt);
		}
		cnt += tmpcnt;
		//printf("selected = %d, cnt = %lf\n", selected, tmpcnt);
	}
	return cnt;
}


int main()
{
	int m = Mi, n = Ni, minx, maxx;
	double p, q, tmp, tmpcnt, P ;
	int x;
	char buff[256];


	for (int m = 1; m <= Mi; m ++)
	{
		minx = ceil(m, n);
		maxx = m;

		sprintf(buff, "%d.csv", m) ;
		FILE *fp = fopen(buff, "w");
		if(!fp) return -1;
		for(int i = -Ni*Ni; i <= Ni*Ni; i++)
		{
			P = 0;
			if (i < -1)
			{
				p = -1.0/i/Ni/Ni;
			}
			else if(i > 0)
			{
				p = 1.0*i/Ni/Ni;
			}
			else continue;
			sprintf(buff, "%lf,", p);
			fwrite(buff, strlen(buff)+1, 1, fp);
			//sprintf(buff, "%d, ", minx) ;
			//fwrite(buff, strlen(buff)+1, 1, fp);

			q = (1-p)/(n-1);
			tmp = 0;
			tmpcnt = 0;

			for (int x = minx; x <= maxx; x++)
			{
				//printf(" C(%d, %d)", m, x);
				avex = x;
				tmpcnt = C(m,x)*divide(ceil(m-x,n-1), x, 0, m-x, n-1, 1, 0, 0);
				//printf("  x = %d, cnt = %lf\n", x, tmpcnt);
				tmp = tmpcnt*pow(p, x)*pow(q, m-x);
				P += tmp;
				//printf("  %lf\n\n", tmp);
				//sprintf(buff, "%lf, ", tmp) ;
				//fwrite(buff, strlen(buff)+1, 1, fp);
			}
			//sprintf(buff, "%d\n", maxx) ;
			//fwrite(buff, strlen(buff)+1, 1, fp);
			sprintf(buff, "%lf\n", P) ;
			fwrite(buff, strlen(buff)+1, 1, fp);
			printf("P = %lf\n", P);
		}
		fclose(fp);
	}

	return 0;
}
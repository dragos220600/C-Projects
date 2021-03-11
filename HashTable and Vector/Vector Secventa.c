#include<stdio.h>
#include<stdlib.h>
void frecv(int *v)
{
    int *rez, i, x, n = 0, j, aux, apar;
    while (scanf("%d", &x) > 0)
    {
        v[n] = x;
        n++;
    }
    for (i = 0; i < n; i++)
    {
        for (j = i+1; j < n; j++)
            if (v[i] > v[j])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
    }
	rez = calloc(2000002, sizeof(int));
    for (i = 0; i < n; i++)
    	if(rez[v[i]] == 0)
    {
    	apar = 1;
        for (j = i+1; j < n; j++)
        	if(v[i] == v[j])
	        	{
	            	apar++;
	        	}
        rez[v[i]] = apar;
    }
    i = 0;
    while (i < n)
    {
        printf("%d %d\n", v[i], rez[v[i]]);
        while (v[i] == v[i+1])
        	i++;
        i++;
    }
    free(rez);
}
int main()
{
    int *v;
    v = calloc(2000002, sizeof(int));
    frecv(v);
    free(v);
    return 0;
}

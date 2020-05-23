#include "calculating2_header.h"

using namespace std;

int main()
{
    int n=0;
    char *s=Read();
    char *st=(char *)calloc(100,sizeof(char));

    cout<<endl<<s<<endl;
    Postfix(s,st,n);
    cout<<st<<endl;
    cout<<Computing(st,n);
    return 0;
}

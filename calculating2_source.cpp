#include "calculating2_header.h"

char* Read()
{
    char * s=(char*)calloc(100,sizeof(char));
    char * st=(char*)calloc(100,sizeof(char));
    freopen("input.txt","r",stdin);
    while(cin>>s)
            strcat(st,s);
    int i=0;
    while(st[i])
        {
            if(st[i]=='=')
                st[i]=' ';
            ++i;
        }
    return(st);
}

void push(char* st, int &n, char c)
{
    st[n++]=c;
}

void push32(char* st, int &n, char c)
{
    st[n++]=c;
    st[n++]=' ';
}

void pushD(double* st, int &n, double x)
{
    st[n++]=x;
}


void strcat2(char*& st1, int &n, char* st2, int m)
{
    strcat(st1,st2);
    n+=m;
}

void strcat32(char*& st1, int &n, char* st2, int m)
{

    strcat(st1,st2);
    n=n+m+1;
    strcat(st1," ");
}

char pop(char* st, int &n)
{
    return(st[--n]);
}

double popD(double* st, int &n)
{
    return(st[--n]);
}

double Chislo(char *st)
{
    int i=0,l=0;
    char *digit=(char *)calloc(50,sizeof(char));
    double x;
    while((isdigit(st[i]))||(st[i]=='e')||(st[i]=='.')||(st[i]=='-')||(st[i]=='+'))
    {
        digit[l++]=st[i];
        ++i;
    }
    x=atof(digit);
    free(digit);
    return(x);
}

double Schet(double x, double y, char c)
{
    if(c=='/')
        {
            if(y)
                return(x/y);
            else
                exit(88);
        }
    if(c=='*')
        return(x*y);
    if(c=='-')
        return(x-y);
    if(c=='+')
        return(x+y);
    exit(99);
}

double Computing(char* s, int n)
{
    double *st=(double*)calloc(100,sizeof(double));
    int i=0,l=0;
    while(i<n)
    {
        while(s[i]==' ')
            ++i;
        if((s[i]=='-')&&(isdigit(s[i+1])))
        {
            pushD(st,l,Chislo(s+i));
            while((isdigit(s[i]))||(s[i]=='e')||(s[i]=='.')||(s[i]=='-')||(s[i]=='+'))
                ++i;
        }
        if(isdigit(s[i]))
        {
            pushD(st,l,Chislo(s+i));
            while((isdigit(s[i]))||(s[i]=='e')||(s[i]=='.')||(s[i]=='-')||(s[i]=='+'))
                ++i;
        }
        if(((s[i]=='+')||(s[i]=='-')||(s[i]=='*')||(s[i]=='/')))
        {
            st[l-2]=Schet(st[l-2],st[l-1],s[i]);
            --l;
            ++i;
        }
    }
    --l;
    return(st[l]);
}

int Postfix(char* s, char *&st, int &n)
{
    char* st1=(char*)calloc(100,sizeof(char));
    int i=0,m=0;n=0;
    if(s[0]=='-')
    {
        push(st,m,'-');
        ++i;
    }
    while(s[i])
    {
        if(isdigit(s[i]))
        {
            char *digit=(char *)calloc(100,sizeof(char));
            int l=0,f1=0,f2=0;
            while((isdigit(s[i]))||(s[i]=='e')||(s[i]=='.')||(s[i]=='+')||(s[i]=='-'))
            {
                if(s[i]=='e')
                    f1=1;
                if((s[i]=='-')||(s[i]=='+'))
                {
                    if(f1)
                        if(f2)
                            break;
                        else
                            f2=1;
                    else
                        break;
                }
                digit[l++]=s[i];
                ++i;
            }
            strcat32(st,m,digit,l);
            free(digit);
        }
        else
        {
            if(s[i]=='(')
            {
                /*push(st1,n,'(');*/st1[n++]='(';
                if(s[i+1]=='-')
                {
                    /*push(st,m,'-');*/st[m++]='-';
                    i+=2;
                    char* digit=(char *)calloc(50,sizeof(char));
                    int l=0,f1=0,f2=0;
                    while((isdigit(s[i]))||(s[i]=='e')||(s[i]=='.')||(s[i]=='+')||(s[i]=='-'))
                    {
                        if(s[i]=='e')
                            f1=1;
                        if((s[i]=='-')||(s[i]=='+'))
                        {
                            if(f1)
                                if(f2)
                                    break;
                                else
                                    f2=1;
                            else
                                break;
                        }
                        digit[l++]=s[i];
                        ++i;
                    }
                    --i;
                    strcat32(st,m,digit,l);
                    free(digit);
                }
            }
            else
                if(s[i]==')')
                {
                    while(st1[n-1]!='(')
                            push32(st,m,pop(st1,n));
                    pop(s,n);
                }
                else

                        if((s[i]=='-')||(s[i]=='+'))
                        {
                            while((st1[n-1]=='+')||(st1[n-1]=='-')||(st1[n-1]=='*')||(st1[n-1]=='/'))
                                push32(st,m,pop(st1,n));
                            //cout<<st<<endl;
                            push(st1,n,s[i]);
                        }
                        else
                        {
                            while((st1[n-1]=='*')||(st1[n-1]=='/'))
                                push32(st,m,pop(st1,n));
                            push(st1,n,s[i]);
                        }
                ++i;//
            }
        }
        //cout<<st<<endl;
    while(n>0)
        push32(st,m,pop(st1,n));
    n=m;
    //cout<<st<<endl;push(st,m,'0');cout<<st<<endl;
    //cout<<"A";
    return 0;
}
/*
bool pr1(char s){
    return (s == '+') || (s == '-');
}

bool pr2(char s){
    return (s == '*') || (s == '/');
}

int Postfixx(char *s, char *&out, int &n){
    char *stack = (char *) calloc(100, sizeof(char));
    int i = 0, m = 0; n = 0;
    if (s[0] == '-'){
        push(out, m, s[0]);
        i++;
    }
    while (s[i]){
        if (isdigit(s[i])){
            char *digit = (char *) calloc(100, sizeof(char));
            int digit_s = 0;
            bool e_flag = false, pm_flag = false;
            while (isdigit(s[i]) || (s[i] == 'e') || (s[i] == '.') || (s[i] == '-') || (s[i] == '+')){
                if (s[i] == 'e')
                    e_flag = true;
                if (s[i] == '-' || s[i] == '+') {
                    if (e_flag) {
                        if (pm_flag)
                            break;
                        else
                            pm_flag = true;
                    } else {
                        break;
                    }
                }
                digit[digit_s++] = s[i];
                i++;
            }

            strcat32(out, m, digit, digit_s);
            free(digit);
        } else {
            if (s[i] == '('){
                push(stack, n, '(');
                if (s[i+1] == '-'){
                    push(out, m, s[i+1]);
                    i += 2;
                    char *digit = (char *) calloc(100, sizeof(char));
                    int digit_s = 0;

                    bool e_flag = false, pm_flag = false;
                    while (isdigit(s[i]) || (s[i] == 'e') || (s[i] == '.') || (s[i] == '-') || (s[i] == '+')){
                        if (s[i] == 'e')
                            e_flag = true;
                        if (s[i] == '-' || s[i] == '+') {
                            if (e_flag) {
                                if (pm_flag)
                                    break;
                                else
                                    pm_flag = true;
                            } else {
                                break;
                            }
                        }
                        digit[digit_s++] = s[i];
                        i++;
                    } i--;
                    strcat32(out, m, digit, digit_s);
                    free(digit);
                }
            }
            else if (s[i] == ')'){
                while (stack[n-1] != '('){
                    push32(out, m, pop(stack, n));
                }
                pop(s, n);
            }
            else {
                if (pr1(s[i])) {
                    while (pr1(stack[n-1]) || pr2(stack[n-1])){
                        push32(out, m, pop(stack, n));
                    }
                    push(stack, n, s[i]);
                }
                else {
                    while (pr2(stack[n-1])){
                        push32(out, m, pop(stack, n));
                    }
                    push(stack, n, s[i]);
                }
            }
            i++;
        }
    }
    while (n > 0)
        push32(out, m, pop(stack, n));
    n = m;

    return 0;
}
*/

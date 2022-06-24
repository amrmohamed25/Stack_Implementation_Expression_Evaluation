int priority (char ch)
{
    switch (ch)
    {
    case '+':
    case'-':
        return 1;
    case '*':
    case'/':
        return 2;
    case '(':
    case')':
        return 4;
    case '^':
        return 3;
    }
    return -1;
}
int isNumeric(char * arr)
{
    if((*arr=='-' &&*(arr+1)!='\0') ||(*arr>='0' && *arr<='9'))
        return 1;
    else
        return 0;
}

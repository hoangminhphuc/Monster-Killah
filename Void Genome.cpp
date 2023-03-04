#include <bits/stdc++.h>
using namespace std;
int main()
{
    int TC;
    cin >> TC;
    while (TC--)
    {
        string s;
        cin >> s;
        string a,b;
        for (int i=0;i<s.length();i++)
        {
            a+=s[i];
        }
         for (int i=s.length()-1;i>=0;i--)
        {
            b+=s[i];
        }
        if(a==b)
        {
            cout << "-1" << endl;
        }
        else
        {
            for (int i=1;i<s.length();i++)
            {
                string c= "";
                string d= "";
                int k=i;
                 for (int j=0;j<s.length();j++)
                {
                    if (s[j] != s[i])
                    c+=s[j];
                }
                for (int j=s.length()-1;j>=k;j--)
                {
                    d+=s[j];
                }
                if(c==d)
                    {
                       cout << i-1 << endl;


                        break;
                    }
            }
        }
    }


    return 0;
}

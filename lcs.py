# The longest common subsequence in Python

import pyperclip

# Function to find lcs_algo
def lcs_algo(S2):
    S1 = '#include<bits/stdc++.h>\
using namespace std;\
typedef long long ll;\
#define all(x) x.begin(),x.end()\
#define tc ll tt, qq=0; cin>>tt; while(qq++<tt)\
#define cs cout<<"Case "<<qq<<": "\
#define csl cout<<"Case "<<qq<<":"<<endl'
    m = len(S1)
    n = len(S2)
    L = [[0 for x in range(n+1)] for x in range(m+1)]

    # Building the mtrix in bottom-up way
    for i in range(m+1):
        for j in range(n+1):
            if i == 0 or j == 0:
                L[i][j] = 0
            elif S1[i-1] == S2[j-1]:
                L[i][j] = L[i-1][j-1] + 1
            else:
                L[i][j] = max(L[i-1][j], L[i][j-1])

    index = L[m][n]

    lcs_algo = [""] * (index+1)
    lcs_algo[index] = ""

    i = m
    j = n
    while i > 0 and j > 0:

        if S1[i-1] == S2[j-1]:
            lcs_algo[index-1] = S1[i-1]
            i -= 1
            j -= 1
            index -= 1

        elif L[i-1][j] > L[i][j-1]:
            i -= 1
        else:
            j -= 1
            
    # Printing the sub sequences
    #print("".join(lcs_algo))
    return (len(lcs_algo) / len(S1)) * 100

S2 = pyperclip.paste();
print(lcs_algo(S2))
vi computePrefix(string &t){
    int n=t.size();
    vi pi(n);
    pi[0]=0;
    //longest proper prefix which is also a suffix
    for(int i=1;i<n;i++){
        int j= pi[i-1];
        while(j>0 && t[i]!=t[j]) j = pi[j-1];
        if(t[i]==t[j]) j++;
        pi[i]=j;
    }
    return pi;
}

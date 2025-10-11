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

//manacher and appns
// Function that returns the longest palindromic substring
string manacher(const string &s) {
    int n = s.size();

    // Step 1: Preprocess the string to handle even length palindromes
    string t = "#";
    for (char c : s) {
        t += c;
        t += "#";
    }
    int m = t.size();

    // Step 2: Initialize p[i] array, center, and right boundary
    vector<int> p(m, 0);
    int center = 0, right = 0;

    // Step 3: Main Manacher loop
    for (int i = 0; i < m; i++) {
        int mirror = 2 * center - i; // Mirror index of i around current center

        // If i is inside the rightmost palindrome, reuse info from mirror
        if (i < right)
            p[i] = min(right - i, p[mirror]);

        // Expand palindrome around i as much as possible
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < m &&
               t[i - p[i] - 1] == t[i + p[i] + 1])
            p[i]++;

        // Update center and right if palindrome at i expands beyond right
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }

    // Step 4: Find the longest palindrome
    int max_len = 0;
    int max_center = 0;
    for (int i = 0; i < m; i++) {
        if (p[i] > max_len) {
            max_len = p[i];
            max_center = i;
        }
    }

    // Step 5: Map back to original string indices
    int start = (max_center - max_len) / 2; // remove # effect
    return s.substr(start, max_len);
}

/*
Modifications / Variations for different tasks:

1. Longest palindromic substring:
   - Already implemented above. Find max p[i], map back to original string.

2. Count of all palindromic substrings:
   - Use: long long total = 0;
   - For each i in p[] (original string positions):
       total += (p[i] + 1) / 2;
   - Sum gives total number of palindromic substrings.

3. All palindromes centered at each character:
   - p[i] directly gives radius of palindrome around center i in t.
   - Convert to original string indices using:
       left = (i - p[i]) / 2
       right = left + p[i] - 1

4. Detect palindromes of certain lengths:
   - Iterate through p[], check if p[i] >= required radius.
   - Then convert back to original string indices as above.

5. Longest palindromic prefix:
   - Check for i where (i - p[i] == 0) in t (start of processed string)
   - Keep track of max p[i] among such i
   - Map back to original string.

6. Longest palindromic suffix:
   - Check for i where (i + p[i] == m - 1) in t (end of processed string)
   - Keep track of max p[i] among such i
   - Map back to original string.
*/


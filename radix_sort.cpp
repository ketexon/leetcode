constexpr int radix_mod = 256;

void count_sort(vector<int>& xs, array<int, radix_mod>& counts, vector<int>& out, int division) {
    counts.fill(0);
    
    for (int x : xs) {
        int v = (x / division) % radix_mod;
        ++counts[v];
    }
    for (int i = 1; i < counts.size(); ++i) {
        counts[i] += counts[i-1];
    }
    
    for (int i = xs.size() - 1; i >= 0; --i) {
        int x = xs[i];
        int v = (x / division) % radix_mod;
        out[counts[v] - 1] = x;
        --counts[v];
    }
}

void radix_sort(vector<int>& xs) {
    int largest = *max_element(xs.begin(), xs.end());
    vector<int> out(xs.size());
    array<int, radix_mod> counts;

    int division = 1;
    while(largest / division > 0) {
        count_sort(xs, counts, out, division);
        std::swap(xs, out);
        division *= radix_mod;
    }
}
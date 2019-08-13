unordered_map<int,int> mp;
mp.reserve(1024); // power of 2 is better
mp.max_load_factor(0.25); // 0.75 used in java


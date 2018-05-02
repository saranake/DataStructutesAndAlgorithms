#include <iostream>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
//        std::cout << i << " " << sum % 10 << "\n";
    }
    return sum % 10;
}


int fibonacci_sum_fast_int(long long n) {

    if (n <= 1)
        return n;
    int previous = 0;
    int current  = 1;
    int sum      = 1;


    for (int i = 2; i <=n  ; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        current = current %10;
        sum += current;
    } 
    sum = sum % 10;
    return sum;
}

int fibonacci_sum_fast(long long n) {
    if (n <= 1)
        return n;
    int period = 60;
    int waves = n/period;
    int partial_waves = n % period;
    if(waves) {
      int r = waves * fibonacci_sum_fast_int(period-1) +
              fibonacci_sum_fast_int(partial_waves);
      return r % 10;
    } else {
      return fibonacci_sum_fast_int(n);
    }
}

int main() {
    long long n = 0;
    std::cin >> n;
//    std::cout << fibonacci_sum_naive(n) << std::endl;
    std::cout << fibonacci_sum_fast(n) << std::endl;
}

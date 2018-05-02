#include <iostream>
#include <vector>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    if (to <= 1)
        return to;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < from - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    long long sum = current;

    for (long long i = 0; i < to - from; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

int fibonacci_sum_fast_int(long long from , long long to) {

    if (to <= 1)
        return to;
    int previous = 0;
    int current  = 1;
    int sum      = 1;


    for (int i = 2; i < from  ; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        current = current %10;
    }

    for (int i = from; i <=to  ; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        current = current %10;
        sum += current;
    }
    sum = sum % 10;
    return sum;
}

int fibonacci_sum_fast(long long from, long long to) {
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
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    long long psum = fibonacci_sum_fast(from, to);
    std::cout << psum << '\n';
}

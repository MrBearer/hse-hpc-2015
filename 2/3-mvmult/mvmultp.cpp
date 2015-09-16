#include <iostream>
#include <random>
#include <thread>
#include <vector>

typedef std::chrono::microseconds Microseconds;
typedef std::chrono::steady_clock Clock;
typedef Clock::time_point Time;

int main() {
    unsigned N = 2000;

    std::vector<std::vector<double> > A(N, std::vector<double>(N,0));
    std::vector<double> x(N,0), y(N,0);

    // double** A = new double*[N];
    // for(unsigned i = 0; i < N; ++i) {
    //     A[i] = new double[N];
    // }
    // double* x = new double[N];
    // double* y = new double[N];

    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(0, 1);

    for (unsigned i = 0; i < N; i++) {
        for (unsigned j = 0; j < N; j++) {
            A[i][j] = dist(e2);
        }
        x[i] = i;
        y[i] = 0;
    }

    Time start = Clock::now();

    for (unsigned j = 0; j < N; j++) {
        for (unsigned i = 0; i < N; i++) {
            y[i] += A[i][j]*x[j];
        }
    }

    unsigned long mult_time = std::chrono::duration_cast<Microseconds>(
        Clock::now() - start).count();
    std::cout << "Time: " << mult_time << "\n";
}
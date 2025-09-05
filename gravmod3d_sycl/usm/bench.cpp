#include <SYCL/sycl.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

template<typename T>
T gr3dprm(T x, T t, T y, T z, T sd, T alpha, T tog, T z1) {
    // Constants and variables (unchanged from your code)
    T dc, z2, al5, al6, al4, al8, q1, q2, r1, r2, r3, r4;
    T t1, t2, t3, t4, t5, ttr1, tt2, ttr2, ter1, ter2, ter3, ter4, ter5;
    T ter6, ter7, ter8, ter9, ter10, ter11;
    T t41, t42, t51, t52, t61, t62, t71, t72, t81, t82;
    T t91, t92, t101, t102, t111, t112, t122, t131, t132;
    T t141, t142, t143, t144, t145;

    dc = tog * std::pow(sd, 3);

    // Handle z = 0 case
    z2 = (z == 0) ? 11e-7 : z;

    al5 = sd - alpha * z1;
    al6 = sd - alpha * z2;
    q1 = x + t;
    q2 = x - t;
    r1 = std::sqrt(std::pow(q1, 2) + std::pow(y, 2) + std::pow(z1, 2));
    r2 = std::sqrt(std::pow(q2, 2) + std::pow(y, 2) + std::pow(z1, 2));
    r3 = std::sqrt(std::pow(q2, 2) + std::pow(y, 2) + std::pow(z2, 2));
    r4 = std::sqrt(std::pow(q1, 2) + std::pow(y, 2) + std::pow(z2, 2));

    t1 = 1 / alpha;
    t2 = (std::atan((y * q1) / (z2 * r4)) / al6) - (std::atan((y * q1) / (z1 * r1)) / al5);
    ttr1 = t1 * t2;
    tt2 = (std::atan((y * q2) / (z2 * r3)) / al6) - (std::atan((y * q2) / (z1 * r2)) / al5);
    ttr2 = t1 * tt2;
    ter1 = ttr1 - ttr2;

    t3 = y * q1;
    al8 = std::sqrt((std::pow(q1, 2) + std::pow(y, 2)) * std::pow(alpha, 2) + std::pow(sd, 2));
    t41 = alpha * (2 * std::pow(sd, 2) + std::pow(alpha, 2) * (std::pow(q1, 2) + std::pow(y, 2)));
    t42 = al8 * (std::pow(y, 2) * std::pow(alpha, 2) + std::pow(sd, 2)) * (std::pow(q1, 2) * std::pow(alpha, 2) + std::pow(sd, 2));
    t4 = t41 / t42;
    t51 = al5 * (alpha * r4 * al8 + std::pow(al8, 2) - sd * al6);
    t52 = al6 * (alpha * r1 * al8 + std::pow(al8, 2) - sd * al5);
    t5 = std::log(t51 / t52);
    ter2 = t3 * t4 * t5;

    t61 = sd / (alpha * (std::pow(sd, 2) + std::pow(y, 2) * std::pow(alpha, 2)));
    t62 = std::atan((y * r4) / (z2 * q1)) - std::atan((y * r1) / (z1 * q1));
    ter3 = t61 * t62;
    t71 = sd / (alpha * (std::pow(sd, 2) + std::pow(q1, 2) * std::pow(alpha, 2)));
    t72 = std::atan((q1 * r4) / (z2 * y)) - std::atan((q1 * r1) / (z1 * y));
    ter4 = t71 * t72;
    t81 = y / (2 * (std::pow(sd, 2) + std::pow(y, 2) * std::pow(alpha, 2)));
    t82 = std::log(((q1 - r4) * (q1 + r1)) / ((q1 + r4) * (q1 - r1)));
    ter5 = t81 * t82;
    t91 = q1 / (2 * (std::pow(sd, 2) + std::pow(q1, 2) * std::pow(alpha, 2)));
    t92 = std::log(((y - r4) * (y + r1)) / ((y + r4) * (y - r1)));
    ter6 = t91 * t92;
    t101 = sd / (alpha * (std::pow(sd, 2) + std::pow(y, 2) * std::pow(alpha, 2)));
    t102 = std::atan((y * r3) / (z2 * q2)) - std::atan((y * r2) / (z1 * q2));
    ter7 = t101 * t102;
    t111 = sd / (alpha * (std::pow(sd, 2) + std::pow(q2, 2) * std::pow(alpha, 2)));
    t112 = std::atan((q2 * r3) / (z2 * y)) - std::atan((q2 * r2) / (z1 * y));
    ter8 = t111 * t112;
    t122 = std::log(((q2 - r3) * (q2 + r2)) / ((q2 + r3) * (q2 - r2)));
    ter9 = t81 * t122;
    t131 = q2 / (2 * (std::pow(sd, 2) + std::pow(q2, 2) * std::pow(alpha, 2)));
    t132 = std::log(((y - r3) * (y + r2)) / ((y + r3) * (y - r2)));
    ter10 = t131 * t132;
    al4 = std::sqrt((std::pow(q2, 2) + std::pow(y, 2)) * std::pow(alpha, 2) + std::pow(sd, 2));
    t141 = y * q2;
    t142 = alpha * (2 * std::pow(sd, 2) + std::pow(alpha, 2) * (std::pow(q2, 2) + std::pow(y, 2)));
    t143 = al4 * (std::pow(y, 2) * std::pow(alpha, 2) + std::pow(sd, 2)) * (std::pow(q2, 2) * std::pow(alpha, 2) + std::pow(sd, 2));
    t144 = al5 * (alpha * r3 * al4 + std::pow(al4, 2) - sd * al6);
    t145 = al6 * (alpha * r2 * al4 + std::pow(al4, 2) - sd * al5);
    ter11 = (t141 * t142 / t143) * std::log(t144 / t145);

    T g = ter1 + ter2 - ter3 - ter4 + ter5 + ter6 + ter7 + ter8 - ter9 - ter10 - ter11;
    return dc * g;
}

template<typename T>
T* funcpdf(int ista, int iend, int n, int m, T sd, T alpha, T dx, T dy,
           T* xprm, T* yprm, T* z, T* xrec, T* yrec,
           sycl::queue& q, T tog, T z1) {
    // Allocate shared memory for f
    auto start_alloc = std::chrono::high_resolution_clock::now();
    T* f = static_cast<T*>(sycl::malloc_shared(m * sizeof(T), q));
    auto end_alloc = std::chrono::high_resolution_clock::now();
    auto alloc_duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_alloc - start_alloc).count();
    double alloc_duration_ms = alloc_duration_ns / 1e6;

    // Initialize on host
    for (int i = 0; i < m; ++i) f[i] = 0;

    // SYCL kernel with timing
    auto start_kernel = std::chrono::high_resolution_clock::now();
    sycl::event kernel_event = q.submit([&](sycl::handler& h) {
        h.parallel_for(sycl::range<1>(m), [=](sycl::id<1> item) {
            int i = item[0];
            if (i <= iend) {
                for (int j = 0; j < n; ++j) {
                    T dxby2 = dx / 2.0;
                    T y = yprm[j] - yrec[i];
                    T dyby2 = dy / 2.0;
                    T y1 = dyby2 + y;
                    T y2 = dyby2 - y;
                    T x = xprm[j] - xrec[i];
                    T zi = z[j];
                    T dg = gr3dprm(x, dxby2, y1, zi, sd, alpha, tog, z1);
                    dg = 0.5 * (dg + gr3dprm(x, dxby2, y2, zi, sd, alpha, tog, z1));
                    f[i] += dg;
                }
            }
        });
    });
    kernel_event.wait();
    auto end_kernel = std::chrono::high_resolution_clock::now();
    auto kernel_duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_kernel - start_kernel).count();
    double kernel_duration_ms = kernel_duration_ns / 1e6;

    // Measure kernel execution time using event profiling
    auto kernel_start = kernel_event.get_profiling_info<sycl::info::event_profiling::command_start>();
    auto kernel_end = kernel_event.get_profiling_info<sycl::info::event_profiling::command_end>();
    double kernel_profile_ms = (kernel_end - kernel_start) / 1e6;

    // Print timing results
    std::cout << "Allocation time: " << alloc_duration_ms << " ms\n";
    std::cout << "Kernel execution time (chrono): " << kernel_duration_ms << " ms\n";
    std::cout << "Kernel execution time (profile): " << kernel_profile_ms << " ms\n";

    return f;
}

int main() {
    using T = float; // Change to double if needed
    const int n = 1400; // Number of prisms
    const int m = 5600; // Number of receiver points
    const int ista = 0;
    const int iend = m - 1;

    // Constants
    T sd = -0.67f;
    T alpha = 0.026f;
    T dx = 1.5f;
    T dy = 1.5f;
    T tog = 13.3486f;
    T z1 = 1e-6f;

    // Create a queue with profiling enabled
    sycl::queue q(sycl::default_selector_v, sycl::property::queue::enable_profiling());
    std::cout << "Running on: " << q.get_device().get_info<sycl::info::device::name>() << std::endl;

    // Allocate host memory with timing
    auto start_alloc = std::chrono::high_resolution_clock::now();
    T* xprm = static_cast<T*>(sycl::malloc_host(n * sizeof(T), q));
    T* yprm = static_cast<T*>(sycl::malloc_host(n * sizeof(T), q));
    T* z = static_cast<T*>(sycl::malloc_host(n * sizeof(T), q));
    T* xrec = static_cast<T*>(sycl::malloc_host(m * sizeof(T), q));
    T* yrec = static_cast<T*>(sycl::malloc_host(m * sizeof(T), q));
    auto end_alloc = std::chrono::high_resolution_clock::now();
    auto alloc_duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_alloc - start_alloc).count();
    double alloc_duration_ms = alloc_duration_ns / 1e6;
    std::cout << "Host memory allocation time: " << alloc_duration_ms << " ms\n";

    // Read from files with timing
    auto start_io = std::chrono::high_resolution_clock::now();
    std::ifstream in1("../data/synthetic_xyz.dat"); 
    if (in1.is_open()) {
        for (int irow = 0; irow < n; ++irow) {
            in1 >> xprm[irow] >> yprm[irow] >> z[irow];
        }
        in1.close();
    } else {
        std::cerr << "Unable to open synthetic_xyz.dat\n";
        return 1;
    }

    std::ifstream in2("../data/grid_xy.dat");
    if (in2.is_open()) {
        for (int irow = 0; irow < m; ++irow) {
            in2 >> xrec[irow] >> yrec[irow];
        }
        in2.close();
    } else {
        std::cerr << "Unable to open grid_xy.dat\n";
        return 1;
    }
    auto end_io = std::chrono::high_resolution_clock::now();
    auto io_duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_io - start_io).count();
    double io_duration_ms = io_duration_ns / 1e6;
    std::cout << "File I/O time: " << io_duration_ms << " ms\n";

    // Benchmark with multiple runs
    const int num_runs = 5;
    std::vector<double> total_times(num_runs);
    for (int run = 0; run < num_runs; ++run) {
        auto start_total = std::chrono::high_resolution_clock::now();
        T* f = funcpdf<T>(ista, iend, n, m, sd, alpha, dx, dy, xprm, yprm, z,
                          xrec, yrec, q, tog, z1);
        auto end_total = std::chrono::high_resolution_clock::now();
        auto total_duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_total - start_total).count();
        total_times[run] = total_duration_ns / 1e6; // Convert to ms
        sycl::free(f, q); // Free after each run to avoid memory leaks during benchmarking
    }

    // Calculate and print average total time
    double total_avg_ms = 0;
    for (int run = 0; run < num_runs; ++run) {
        total_avg_ms += total_times[run];
    }
    total_avg_ms /= num_runs;
    std::cout << "Average total execution time over " << num_runs << " runs: " << total_avg_ms << " ms\n";

    // Final run to get results (no timing for simplicity)
    T* f = funcpdf<T>(ista, iend, n, m, sd, alpha, dx, dy, xprm, yprm, z,
                      xrec, yrec, q, tog, z1);

    // Save to text file with timing
    auto start_save = std::chrono::high_resolution_clock::now();
    std::ofstream outFile("../data/output.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < m; ++i) {
            outFile << xrec[i] << " " << yrec[i] << " " << f[i] << "\n";
        }
        outFile.close();
        std::cout << "Results saved to output.txt\n";
    } else {
        std::cerr << "Unable to open file output.txt\n";
    }
    auto end_save = std::chrono::high_resolution_clock::now();
    auto save_duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_save - start_save).count();
    double save_duration_ms = save_duration_ns / 1e6;
    std::cout << "File save time: " << save_duration_ms << " ms\n";

    // Free memory
    sycl::free(xprm, q);
    sycl::free(yprm, q);
    sycl::free(z, q);
    sycl::free(xrec, q);
    sycl::free(yrec, q);
    sycl::free(f, q);

    return 0;
}

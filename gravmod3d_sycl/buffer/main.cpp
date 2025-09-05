#include <SYCL/sycl.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

template<typename T>
T gr3dprm(T x, T t, T y, T z, T sd, T alpha, T tog, T z1) {
    // Constants and variables
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
void funcpdf(int ista, int iend, int n, int m, T sd, T alpha, T dx, T dy,
             sycl::buffer<T, 1> xprm_buf, sycl::buffer<T, 1> yprm_buf, sycl::buffer<T, 1> z_buf,
             sycl::buffer<T, 1> xrec_buf, sycl::buffer<T, 1> yrec_buf, sycl::buffer<T, 1> f_buf,
             sycl::queue& q, T tog, T z1, bool use_parallel = true) {
    // Initialize f buffer to 0
    q.submit([&](sycl::handler& h) {
        auto f_acc = f_buf.template get_access<sycl::access::mode::write>(h, sycl::range(m));
        h.parallel_for(sycl::range(iend - ista + 1), [=](sycl::id<1> idx) {
            int i = idx[0] + ista;
            if (i <= iend) f_acc[i] = 0;
        });
    }).wait();

    T dxby2 = dx / 2.0;
    T dyby2 = dy / 2.0;

    // SYCL kernel for computation
    q.submit([&](sycl::handler& h) {
        auto xprm_acc = xprm_buf.template get_access<sycl::access::mode::read>(h);
        auto yprm_acc = yprm_buf.template get_access<sycl::access::mode::read>(h);
        auto z_acc = z_buf.template get_access<sycl::access::mode::read>(h);
        auto xrec_acc = xrec_buf.template get_access<sycl::access::mode::read>(h);
        auto yrec_acc = yrec_buf.template get_access<sycl::access::mode::read>(h);
        auto f_acc = f_buf.template get_access<sycl::access::mode::read_write>(h);

        h.parallel_for(sycl::range(iend - ista + 1), [=](sycl::id<1> idx) {
            int i = idx[0] + ista;
            if (i <= iend) {
                for (int j = 0; j < n; ++j) {
                    T y = yprm_acc[j] - yrec_acc[i];
                    T y1 = dyby2 + y;
                    T y2 = dyby2 - y;
                    T x = xprm_acc[j] - xrec_acc[i];
                    T zi = z_acc[j];
                    T dg = gr3dprm(x, dxby2, y1, zi, sd, alpha, tog, z1);
                    dg = 0.5 * (dg + gr3dprm(x, dxby2, y2, zi, sd, alpha, tog, z1));
                    f_acc[i] += dg;
                }
            }
        });
    }).wait();
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

    // Allocate memory
    std::vector<T> xprm(n), yprm(n), z(n);
    std::vector<T> xrec(m), yrec(m), f(m);

    // Read from files 
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

    // Create a queue that targets the device selected by default_selector_v
    sycl::queue q(sycl::default_selector_v);
    std::cout << "Running on: " << q.get_device().get_info<sycl::info::device::name>() << std::endl;
    // Create SYCL buffers
    sycl::buffer<T, 1> xprm_buf(xprm.data(), n);
    sycl::buffer<T, 1> yprm_buf(yprm.data(), n);
    sycl::buffer<T, 1> z_buf(z.data(), n);
    sycl::buffer<T, 1> xrec_buf(xrec.data(), m);
    sycl::buffer<T, 1> yrec_buf(yrec.data(), m);
    sycl::buffer<T, 1> f_buf(f.data(), m);

    // Call funcpdf
    funcpdf<T>(ista, iend, n, m, sd, alpha, dx, dy, xprm_buf, yprm_buf, z_buf,
               xrec_buf, yrec_buf, f_buf, q, tog, z1, true);

    // Copy results back to host
    auto f_acc = f_buf.template get_access<sycl::access::mode::read>();
    std::vector<T> f_result(m);
    for (int i = 0; i < m; ++i) f_result[i] = f_acc[i];

    // Save to text file
    std::ofstream outFile("../data/output.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < m; ++i) {
            outFile << xrec[i] << " " << yrec[i] << " " << f_result[i] << "\n";
        }
        outFile.close();
        std::cout << "Results saved to output.txt\n";
    } else {
        std::cerr << "Unable to open file output.txt\n";
    }

    return 0;
}

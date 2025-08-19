#include <sycl/sycl.hpp>
using namespace sycl;

int main() {

    queue Q;                        // The queue, Q, is the object that
                                    // submits the task to a device.
    int const size = 10;
    buffer<int> A{ size };          // The buffer, A, is the memory used to
                                    // transfer data between host and device.

    Q.submit([&](handler& h) {      // The handler, h, is the object that contains
                                    // the single_task function to be used.

        accessor A_acc(A, h);       // The accessor, A_acc, is the object that
                                    // efficiently accesses the buffer elements.

        h.single_task([=]() {
            A_acc[5] = 77;
            });

        });

    host_accessor result(A);        // host_accessor is the object that allows
                                    // the host to access the buffer memory.

    for (int i = 0; i < size; i++)  // Print output
        std::cout << result[i] << " "; std::cout << "\n";
    return 0;

}

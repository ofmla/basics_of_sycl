
#include <sycl/sycl.hpp>

#include <iostream>
#include <string>
#include <string_view>

using namespace std::literals;

std::string str( sycl::device const & dev ) {
    auto const & p = dev.get_platform() ;
    return p.get_info<sycl::info::platform::name>()
        + " / " + dev.get_info<sycl::info::device::name>() ;
}

int main( int argc, char * argv[] ) {

  // Device inspection
  int rank = 0;
  for (auto const & plat : sycl::platform::get_platforms() ) {
      for (auto const & dev : plat.get_devices() ) {
          std::cout << "Rank " << rank++ << ": " << str(dev) << std::endl ;
      }
  }

  // Device selection
  sycl::device dev;
  if (argc==1) {
    dev = sycl::device(sycl::default_selector_v);
  } else if (argv[1]=="cpu"sv) {
    dev = sycl::device(sycl::cpu_selector_v);
  } else if (argv[1]=="gpu"sv) {
    dev = sycl::device(sycl::gpu_selector_v);
  } else {
    throw std::runtime_error("Unknown device type") ;
  }
  std::cout << "Selected: " <<str(dev) << std::endl ;
    
  // Device selection
  sycl::queue q { dev };
  sycl::buffer<int, 1> buffer(4);
  sycl::range<1> nb_work_items{buffer.size()};
  q.submit([&](sycl::handler &cgh) {
    auto accessor = buffer.get_access<sycl::access::mode::write>(cgh);
    cgh.parallel_for<class FillBuffer>(
        nb_work_items, [=](sycl::id<1> wi_id) {
          accessor[wi_id] = (int)wi_id.get(0);
        });
  });
  const auto hacc = buffer.get_host_access();
  bool mismatch = false;
  for (std::size_t i = 0; i < buffer.size(); ++i) {
    if (hacc[i] != static_cast<int>(i)) {
      std::cout << "The result is incorrect for element: " << i
                << " , expected: " << i << " , got: " << hacc[i]
                << std::endl;
      mismatch = true;
    }
  }
  if (!mismatch) {
    std::cout << "\nThe results are correct!" << std::endl;
  }
  return mismatch;
}



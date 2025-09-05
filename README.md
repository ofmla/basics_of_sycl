# Introduction to SYCL Programming: A Beginner's Guide

This repository provides some programs that cover the basics of SYCL programming. It includes:

- Apptainer recipes to build containers with the necessary dependencies.
- C++ programs for different applications designed to explain key SYCL features.

The course is designed to equip programmers with no prior SYCL knowledge with basic skills, preparing them to write a practical example in the geoscience domain (wave modeling simulations).

## Setting Up a SYCL Environment

This course is part of a series of HPC training events that I usually teach once a year, targeted at HPC users with access to one of the supercomputers at the Senai Cimatec computing center. Alternatively, you can use Intel oneAPI DPC++/C++ Compiler and/or AdaptiveCpp (the two mainstream SYCL compilers) installed on your personal computer. For installation details, refer to the respective [AdaptiveCpp](https://github.com/AdaptiveCpp/AdaptiveCpp/blob/develop/doc/installing.md) and [Intel oneAPI](https://www.intel.com/content/www/us/en/docs/oneapi/installation-guide-linux/2025-2/overview.html) guides. Note that a basic Intel oneAPI installation supports only Intel hardware unless specific plugins (e.g., Codeplay ones) are added. On the supercomputers we access, only NVIDIA GPUs are available, so the provided Apptainer recipe supports the [Nvidia/CUDA plugin for Intel oneAPI DPC++/C++](https://developer.codeplay.com/products/oneapi/nvidia/guides/).

### Building the Apptainer container
The first step is to build the containers on OGBON. This is done by running the following commands:
```
apptainer build icpx-cuda.sif ubuntu-icpx-cuda.def
apptainer build acpp-cuda.sif ubuntu-acpp-cuda.def
```
### Allocating a compute node

To view available nodes and partitions on OGBON, use the command:
```
sinfo -s
```
Let's pick one node on the `gpulongb` partition if using OGBON
```
salloc --nodes=1 --account=PROJECT_NAME --partition=gpulongb
```
Replace PROJECT_NAME with the project name that you work on. In my case would be `siren`. Output below is for OGBON
```
salloc: Granted job allocation 705054
salloc: Waiting for resource configuration
salloc: Nodes c036 are ready for job
```
To begin practice on the allocated compute node, identify the node name using:
```
squeue -u $USER
```
```
JOBID   PARTITION  NAME      USER       ST TIME  NODES  NODELIST(REASON)
705054  gpulonb        interact  USER_NAME  R  6:04  1      C036
```
Our allocated node is called `c036`. Connect to it via SSH
```
ssh USER_NAME@c036
```
Run the Singularity container interactively:
```
[USER_NAME@c036 ~]$ singularity shell --nv --writable-tmpfs icpx-cuda.sif
```
or
```
[USER_NAME@c036 ~]$ singularity shell --nv --writable-tmpfs acpp-cuda.sif
```
Remember to change USER_NAME, PROJECT_NAME to your own.

## Check your SYCL devices
Since OGBON nodes are equipped with NVIDIA GPUs, you can run nvidia-smi in your terminal after launching either of the two containers in interactive mode to verify proper functionality. An example of the output is:
```
Apptainer> nvidia-smi 
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 525.60.13    Driver Version: 525.60.13    CUDA Version: 12.0     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|                               |                      |               MIG M. |
|===============================+======================+======================|
|   0  Tesla V100-SXM2...  On   | 00000000:60:00.0 Off |                    0 |
| N/A   42C    P0    44W / 300W |      0MiB / 32768MiB |      0%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
|   1  Tesla V100-SXM2...  On   | 00000000:61:00.0 Off |                    0 |
| N/A   40C    P0    45W / 300W |      0MiB / 32768MiB |      0%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
|   2  Tesla V100-SXM2...  On   | 00000000:88:00.0 Off |                    0 |
| N/A   42C    P0    45W / 300W |      0MiB / 32768MiB |      0%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
|   3  Tesla V100-SXM2...  On   | 00000000:89:00.0 Off |                    0 |
| N/A   41C    P0    44W / 300W |      0MiB / 32768MiB |      0%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
|  No running processes found                                                 |
+-----------------------------------------------------------------------------+
```
If running the oneAPI container you can check what devices are seen by your SYCL runtime with the command `sycl-ls`
```
Apptainer> source /opt/intel/oneapi/setvars.sh
 
:: initializing oneAPI environment ...
   bash: BASH_VERSION = 5.1.16(1)-release
   args: Using "$@" for setvars.sh arguments: 
:: compiler -- latest
:: debugger -- latest
:: dev-utilities -- latest
:: dpl -- latest
:: tbb -- latest
:: umf -- latest
:: oneAPI environment initialized ::
 
Apptainer> sycl-ls
[cuda:gpu][cuda:0] NVIDIA CUDA BACKEND, Tesla V100-SXM2-32GB 7.0 [CUDA 12.0]
[cuda:gpu][cuda:1] NVIDIA CUDA BACKEND, Tesla V100-SXM2-32GB 7.0 [CUDA 12.0]
[cuda:gpu][cuda:2] NVIDIA CUDA BACKEND, Tesla V100-SXM2-32GB 7.0 [CUDA 12.0]
[cuda:gpu][cuda:3] NVIDIA CUDA BACKEND, Tesla V100-SXM2-32GB 7.0 [CUDA 12.0]
[opencl:cpu][opencl:0] Intel(R) OpenCL, Intel(R) Xeon(R) Gold 6240 CPU @ 2.60GHz OpenCL 3.0 (Build 0) [2025.20.8.0.06_160000]
```
If runing the acpp container run `acpp-info` which provides some basic infomation about the platform
```
=================Backend information===================
Loaded backend 0: CUDA
  Found device: Tesla V100-SXM2-32GB
  Found device: Tesla V100-SXM2-32GB
  Found device: Tesla V100-SXM2-32GB
  Found device: Tesla V100-SXM2-32GB
Loaded backend 1: OpenMP
  Found device: AdaptiveCpp OpenMP host device

=================Device information===================
***************** Devices for backend CUDA *****************
Device 0:
 General device information:
  Name: Tesla V100-SXM2-32GB
  Backend: CUDA
  Platform: Backend 0 / Platform 0
  Vendor: NVIDIA
  Arch: sm_70
  Driver version: 12000
  Is CPU: 0
  Is GPU: 1
  ... 
  ...

Device 1:
 ...

Device 2:
 ...

Device 3:
 ...

***************** Devices for backend OpenMP *****************
Device 0:
 General device information:
  Name: AdaptiveCpp OpenMP host device
  Backend: OpenMP
  Platform: Backend 4 / Platform 0
  Vendor: the AdaptiveCpp project
  Arch: <native-cpu>
  Driver version: 1.2
  Is CPU: 1
  Is GPU: 0
  ...
```
## License

This repository contains course material and code assembled from various sources, likened to a "Frankenstein creation." I have strictly adhered to the terms of the respective licenses to ensure complete compliance. The material and code are derived from the following sources:

- **Intel’s SYCL 101 Course**: Code licensed under the [MIT License](https://opensource.org/licenses/MIT).
- **Codeplay’s SYCL Academy Repository**: Code licensed under the [CC-BY-4.0 License](https://creativecommons.org/licenses/by/4.0/).
- **SYCL Workshop by EuroCC National Competence Center Sweden (ENCCS)**: Code licensed under the [MIT License](https://opensource.org/licenses/MIT), with additional material under the [CC-BY-4.0 License](https://creativecommons.org/licenses/by/4.0/).
- **Gray Scott SYCL Tutorial**: Code licensed under the [GPL-3.0 License](https://www.gnu.org/licenses/gpl-3.0.en.html).
- **Original Code**: My own contributions, licensed under the [MIT License](https://opensource.org/licenses/MIT).
- **Slides**: licensed under the [CC-BY-4.0 License](https://creativecommons.org/licenses/by/4.0/).

### License Summary
The repository is a composite work, and the applicable license depends on the specific component:
- Code from Intel’s SYCL 101, ENCCS SYCL Workshop, and my original contributions is licensed under the MIT License.
- Code and materials from Codeplay’s SYCL Academy, ENCCS additional material, and slides, are licensed under the CC-BY-4.0 License.
- Code from the Gray Scott SYCL Tutorial is licensed under the GPL-3.0 License.

Users are encouraged to review the full text of each license linked above to understand their rights and obligations. When using or distributing this material, please attribute the original sources as required by the respective licenses.

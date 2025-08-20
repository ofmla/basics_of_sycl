# Introduction to SYCL Programming: A Beginner's Guide

This repository provides some programs that cover the basics of SYCL programming. It includes:

- Apptainer recipes to build containers with the necessary dependencies.
- C++ programs for different applications designed to explain key SYCL features.

The course is designed to equip programmers with no prior SYCL knowledge with basic skills, preparing them to write a practical example in the geoscience domain (wave modeling simulations).

## Setting Up a SYCL Environment

This course is part of a series of HPC training events that I usually teach once a year, targeted at HPC users with access to one of the supercomputers at the Senai Cimatec computing center. However, you can also proceed with Intel oneAPI installed on your personal computer. The compiler is now called `icpx`, previously known as `dpcpp`, which is why installation packages are often labeled as `dpcpp`. Additionally, oneAPI encompasses a broad suite of Intel tools and libraries for SYCL, including `icpx`/`dpcpp`. Another SYCL implementation option is AdaptiveCpp, with recent tests proving successful so far. Note that a basic Intel oneAPI installation supports only Intel hardware unless specific plugins (e.g., Codeplay ones) are added. On the supercomputers we access, only NVIDIA GPUs are available, so the provided Apptainer recipe supports the Nvidia/CUDA plugin for AdaptiveCpp.

## Building the Apptainer Container

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
Remember to change USER_NAME, PROJECT_NAME to your own.

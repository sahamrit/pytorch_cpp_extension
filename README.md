# pytorch_cpp_extension
This repository contains learning exercises for writing cpp extensions in pytorch.  

Reference [Pytorch Tutorial](https://pytorch.org/tutorials/advanced/cpp_extension.html#custom-c-and-cuda-extensions) and [corresponding codebase](https://github.com/pytorch/extension-cpp)

## v3_cuda_extension

This branch uses cuda extension to implement custom operations and add it to python via `pybind`. Refer [lltm_cuda.cpp](./cuda/lltm_cuda.cpp) for the cpp boilerplate, [lltm_cuda_kernel.cu](./cuda/lltm_cuda_kernel.cu) for main kernel implementation and [lltm.py](./cuda/lltm.py) for calling this cuda extension via python. [SetupTools](./cuda/setup.py) is used to publish the cuda extension as a package .

## Benchmarking 


###  [v1_nn_module](https://github.com/sahamrit/pytorch_cpp_extension/tree/v1_nn_module): Extend nn Module

Using CPU `Intel(R) Xeon(R) CPU E5-2690 v4 @ 2.60GHz`

```
python benchmark.py py

Forward: 1747.131/11143.847 us | Backward 8096.457/30352.993 us
```

Using GPU `Tesla V100`

```
python benchmark.py py -c

Forward: 239.372/253.098 us | Backward 451.565/477.326 us
```


###  [v2_cpp_extension](https://github.com/sahamrit/pytorch_cpp_extension/tree/v2_cpp_extension): Extend via cpp extension

Using CPU `Intel(R) Xeon(R) CPU E5-2690 v4 @ 2.60GHz`

```
python benchmark.py cpp

Forward: 1838.207/10178.695 us | Backward 8268.356/33261.724 us
```

Using GPU `Tesla V100`

```
python benchmark.py cpp -c

Forward: 181.437/215.027 us | Backward 630.379/746.493 us
```

The statistics are printed in the format `min/avg`. Forward method improved via cpp extension, not the backward. This is because pytorch implementation of backward already is purely in c++ and is much optimised.

###  [v3_cuda_extension](https://github.com/sahamrit/pytorch_cpp_extension/tree/v3_cuda_extension): Extend via cuda extension

Using GPU `Tesla V100` 

```
python benchmark.py cuda -c

Forward: 177.860/196.116 us | Backward 430.584/461.504 us
```

The statistics are printed in the format `min/avg`. Note that both forward and backward methods improved than the previous best of CUDA based C++ code. Here we also saw improvement in backward because of combining many pointwise operations into a single `lltm_cuda_backward_kernel`, hence reducing overhead of multiple kernel launches.

## Installation

### Python Environment
Use a conda environment with [pytorch](https://pytorch.org/) installation. Make sure to have `setuptools` installed too.
Also make sure to have python and cuda installed in your system.

###  Building the cpp extension

```
cd cpp
python setup.py install
```
###  Building the cuda extension

```
cd cuda
python setup.py install
```
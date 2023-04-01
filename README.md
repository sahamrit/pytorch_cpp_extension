# pytorch_cpp_extension
This repository contains learning exercises for writing cpp extensions in pytorch.  

Reference [Pytorch Tutorial](https://pytorch.org/tutorials/advanced/cpp_extension.html#custom-c-and-cuda-extensions) and [corresponding codebase](https://github.com/pytorch/extension-cpp)

## v2_cpp_extension

This branch uses cpp extension to implement custom operations and add it to python via `pybind`. Refer [lltm.cpp](./cpp/lltm.cpp) for the cpp implementation and [lltm.py](./cpp/lltm.py) for calling this cpp extension via python. [SetupTools](./cpp/setup.py) is used to publish the cpp extension as a package .

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
## Installation

### Python Environment
Use a conda environment with [pytorch](https://pytorch.org/) installation. Make sure to have `setuptools` installed too.

###  Building the cpp extension

```
cd cpp
python setup.py install
```
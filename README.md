# pytorch_cpp_extension
This repository contains learning exercises for writing cpp extensions in pytorch.  

Reference [Pytorch Tutorial](https://pytorch.org/tutorials/advanced/cpp_extension.html#custom-c-and-cuda-extensions) and [corresponding codebase](https://github.com/pytorch/extension-cpp)

## v1_nn_Module

This branch contains the easiest way to add custom operations in pytorch. This is by extending `nn.Module`. Refer [lltm.py](./python/lltm.py)

### Benchmarking

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


## Installation

Use a conda environment with [pytorch](https://pytorch.org/) installation.
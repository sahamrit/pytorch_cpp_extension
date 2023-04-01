#include <bits/stdc++.h>
#include <torch/extension.h>

using namespace std;

vector<torch::Tensor> lltm_forward(
    torch::Tensor input,
    pair<torch::Tensor, torch::Tensor> state,
    torch::Tensor weights,
    torch::Tensor bias
)
{
    auto old_h = state.first;
    auto old_cell = state.second;

    auto X = torch::cat({old_h, input}, /*dim=*/ 1);

    auto gate_weights = torch::addmm(bias, X, weights.transpose(0,1));

    auto gates = gate_weights.chunk(3, /*dim=*/1);

    auto input_gate = torch::sigmoid(); 
}


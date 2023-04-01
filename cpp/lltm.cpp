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

    auto input_gate = torch::sigmoid(gates[0]);
    auto output_gate = torch::sigmoid(gates[1]);

    auto candidate_cell = torch::elu(gates[2], /*alpha=*/1.0);

    auto new_cell = old_cell + candidate_cell * input_gate;
    auto new_h = torch::tanh(new_cell) * output_gate;

    return {new_h,
            new_cell,
            input_gate,
            output_gate,
            candidate_cell,
            X,
            gate_weights};

}


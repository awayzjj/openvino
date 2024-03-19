// Copyright (C) 2018-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "default_opset.hpp"
#include "openvino/frontend/paddle/node_context.hpp"

namespace ov {
namespace frontend {
namespace paddle {
namespace op {
NamedOutputs tile(const NodeContext& node) {
    auto x = node.get_input("X");
    Output<Node> repeats;
    if (node.has_input("RepeatTimes")) {
        repeats = node.get_input("RepeatTimes");
    } else if (node.has_input("repeat_times_tensor")) {
        auto repeats_list = node.get_ng_inputs("repeat_times_tensor");
        repeats = std::make_shared<default_opset::Concat>(repeats_list, 0);
    } else {
        std::vector<int32_t> repeats_vector = node.get_attribute<std::vector<int32_t>>("repeat_times", {});
        repeats = default_opset::Constant::create(ov::element::i32, Shape{repeats_vector.size()}, repeats_vector);
    }

    return node.default_single_output_mapping({std::make_shared<default_opset::Tile>(x, repeats)}, {"Out"});
}

}  // namespace op
}  // namespace paddle
}  // namespace frontend
}  // namespace ov

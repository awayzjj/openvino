// Copyright (C) 2018-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "core/node.hpp"

namespace ov {
namespace frontend {
namespace onnx {
namespace op {
namespace set_1 {
ov::OutputVector gemm(const ov::frontend::onnx::Node& node);

}  // namespace set_1

namespace set_6 {
ov::OutputVector gemm(const ov::frontend::onnx::Node& node);

}  // namespace set_6
}  // namespace op
}  // namespace onnx
}  // namespace frontend
}  // namespace ov

// Copyright (C) 2018-2024 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "openvino/reference/softsign.hpp"

#include "evaluate_node.hpp"

template <ov::element::Type_t ET>
bool evaluate(const std::shared_ptr<ov::op::v9::SoftSign>& op,
              ov::TensorVector& outputs,
              const ov::TensorVector& inputs) {
    ov::element::Type input_et = op->get_input_element_type(0);
    switch (input_et) {
    case ov::element::f64:
        ov::reference::softsign<double>(inputs[0].data<double>(),
                                        outputs[0].data<double>(),
                                        ov::shape_size(inputs[0].get_shape()));
        break;
    case ov::element::f32:
        ov::reference::softsign<float>(inputs[0].data<float>(),
                                       outputs[0].data<float>(),
                                       ov::shape_size(inputs[0].get_shape()));
        break;
    case ov::element::f16:
        ov::reference::softsign<ov::float16>(inputs[0].data<ov::float16>(),
                                             outputs[0].data<ov::float16>(),
                                             ov::shape_size(inputs[0].get_shape()));
        break;
    case ov::element::bf16:
        ov::reference::softsign<ov::bfloat16>(inputs[0].data<ov::bfloat16>(),
                                              outputs[0].data<ov::bfloat16>(),
                                              ov::shape_size(inputs[0].get_shape()));
        break;
    default:
        return false;
    }
    return true;
}

template <>
bool evaluate_node<ov::op::v9::SoftSign>(std::shared_ptr<ov::Node> node,
                                         ov::TensorVector& outputs,
                                         const ov::TensorVector& inputs) {
    auto element_type = node->get_output_element_type(0);
    if (ov::is_type<ov::op::v1::Select>(node) || ov::is_type<ov::op::util::BinaryElementwiseComparison>(node))
        element_type = node->get_input_element_type(1);

    switch (element_type) {
    case ov::element::boolean:
        return evaluate<ov::element::boolean>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::bf16:
        return evaluate<ov::element::bf16>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::f16:
        return evaluate<ov::element::f16>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::f64:
        return evaluate<ov::element::f64>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::f32:
        return evaluate<ov::element::f32>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::i4:
        return evaluate<ov::element::i4>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::i8:
        return evaluate<ov::element::i8>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::i16:
        return evaluate<ov::element::i16>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::i32:
        return evaluate<ov::element::i32>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::i64:
        return evaluate<ov::element::i64>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::u1:
        return evaluate<ov::element::u1>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::u4:
        return evaluate<ov::element::u4>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::u8:
        return evaluate<ov::element::u8>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::u16:
        return evaluate<ov::element::u16>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::u32:
        return evaluate<ov::element::u32>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    case ov::element::u64:
        return evaluate<ov::element::u64>(ov::as_type_ptr<ov::op::v9::SoftSign>(node), outputs, inputs);
    default:
        OPENVINO_THROW("Unhandled data type ", node->get_element_type().get_type_name(), " in evaluate_node()");
    }
}

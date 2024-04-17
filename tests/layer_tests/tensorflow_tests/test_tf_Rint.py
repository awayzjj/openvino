# Copyright (C) 2018-2024 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

import numpy as np
import pytest
import tensorflow as tf
from common.tf_layer_test_class import CommonTFLayerTest

class TestRint(CommonTFLayerTest):
    def _prepare_input(self, inputs_info):
        assert 'input:0' in inputs_info
        inputs_shape = inputs_info['input:0']
        inputs_data = {}
        inputs_data['input:0'] = np.random.rand(*inputs_shape).astype(self.input_type)
        return inputs_data

    def create_tf_rint_net(self, input_shape, input_type):
        self.input_type = input_type
        tf.compat.v1.reset_default_graph()
        with tf.compat.v1.Session() as sess:
            input = tf.compat.v1.placeholder(input_type, input_shape, 'input')
            tf.raw_ops.Rint(x=input)
            tf.compat.v1.global_variables_initializer()
            tf_net = sess.graph_def

        ref_net = None

        return tf_net, ref_net

    @pytest.mark.parametrize("input_shape", [[6], [2, 5, 3], [10, 5, 1, 5]])
    @pytest.mark.parametrize("input_type", [np.float32, np.float64])
    @pytest.mark.precommit
    @pytest.mark.nightly
    def test_rint_basic(self, input_shape, input_type, ie_device, precision,
                        ir_version, temp_dir, use_legacy_frontend):
        self._test(*self.create_tf_rint_net(input_shape, input_type),
                ie_device, precision, ir_version, temp_dir=temp_dir,
                use_legacy_frontend=use_legacy_frontend)
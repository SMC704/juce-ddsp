import gin
import tensorflow as tf
import ddsp
import ddsp.training

class Rnn(tf.keras.layers.Layer):

    def __init__(self, dims, rnn_type, return_sequences=True, **kwargs):
        super(Rnn, self).__init__(**kwargs)
        self.dims = dims
        self.rnn_type = rnn_type
        rnn_class = {'lstm': tf.keras.layers.LSTM, 'gru': tf.keras.layers.GRU}[rnn_type]
        self.rnn = rnn_class(dims, return_sequences=return_sequences)

    def call(self, x, **kwargs):
        return self.rnn(x)


class Fc(tf.keras.layers.Layer):
    def __init__(self, ch=128, **kwargs):
        super(Fc, self).__init__(**kwargs)
        self.ch = ch
        self.layers = [
            tf.keras.layers.Dense(ch),
            tf.keras.layers.LayerNormalization(),
            tf.keras.layers.Activation(tf.nn.leaky_relu),
        ]

    def call(self, inputs, **kwargs):
        for layer in self.layers:
            inputs = layer(inputs)
        return inputs


class FcStack(tf.keras.layers.Layer):
    def __init__(self, ch=256, num_layers=2, **kwargs):
        super(FcStack, self).__init__(**kwargs)
        self.ch = ch
        self.num_layers = num_layers
        self.layers = [Fc(ch) for i in range(num_layers)]

    def call(self, inputs, **kwargs):
        for layer in self.layers:
            inputs = layer(inputs)
        return inputs


@gin.configurable
class FunctionalDecoder(tf.keras.Model):

    def __init__(self,
                 time_steps=1,
                 rnn_channels=512,
                 rnn_type='gru',
                 ch=512,
                 layers_per_stack=3,
                 input_keys=('f0_scaled', 'ld_scaled'),
                 output_splits=(('amps', 1), ('harmonic_distribution', 60), ('noise_magnitudes', 65)),
                 name=None):
        super(FunctionalDecoder, self).__init__(name=name)
        self.rnn_channels = rnn_channels
        self.rnn_type = rnn_type
        self.ch = ch
        self.layers_per_stack = layers_per_stack
        self.input_keys = input_keys
        self.output_splits = output_splits
        self.time_steps = time_steps
        self.n_out = sum([v[1] for v in output_splits])

        self.input_stacks = [FcStack(ch, layers_per_stack) for k in self.input_keys]
        self.rnn = Rnn(rnn_channels, rnn_type)
        self.out_stack = FcStack(ch, layers_per_stack)
        self.dense_out = tf.keras.layers.Dense(self.n_out)
        self.preprocessor = ddsp.training.preprocessing.DefaultPreprocessor(time_steps=time_steps)

    def call(self, inputs, **kwargs):
        x = self.decode(inputs[0], inputs[1])
        outputs = ddsp.training.nn.split_to_dict(x, self.output_splits)
        return outputs

    def decode(self, f0_hz, loudness_db):
        features = self.preprocessor({'f0_hz': f0_hz, 'loudness_db': loudness_db})
        f0_scaled, ld_scaled = features['f0_scaled'], features['ld_scaled']

        inputs = [stack(x) for stack, x in zip(self.input_stacks, [f0_scaled, ld_scaled])]

        # Run an RNN over the latents.
        x = tf.concat(inputs, axis=-1)
        x = self.rnn(x)
        x = tf.concat(inputs + [x], axis=-1)

        # Final processing.
        x = self.out_stack(x)
        x = self.dense_out(x)
        return x

    def get_config(self):
        return {
            'rnn_channels': self.rnn_channels,
            'rnn_type': self.rnn_type,
            'ch': self.ch,
            'layers_per_stack': self.layers_per_stack,
            'input_keys': self.input_keys,
            'output_splits': self.output_splits,
            'name': self.name,
        }

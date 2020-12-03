"""
Given a trained DDSP 0.14.0 Autoencoder model, this script
extracts the weights from the decoder and saves the isolated decoder
as a functional model, which can then be used by the TensorFlow C API.
"""

import sys
import ddsp
import gin
import numpy as np
from functional_models import FunctionalDecoder


def convert_model(config_file, ckpt_path, out_dir):
    gin.unlock_config()
    gin.parse_config_file(config_file, skip_unknown=True)
    model = ddsp.training.models.Autoencoder()
    model.restore(ckpt_path)

    time_steps = model.preprocessor.time_steps

    feats = {
        'f0_hz': 440 * np.ones((1, time_steps, 1), dtype=np.float32),
        'loudness_db': -6 * np.ones((1, time_steps, 1), dtype=np.float32)
    }

    model_outputs = model(feats, training=False)

    # build the functional model, call it to set input size
    func_decoder = FunctionalDecoder(time_steps)
    _ = func_decoder([np.ones((1, time_steps, 1), dtype=np.float32), np.ones((1, time_steps, 1), dtype=np.float32)])

    # update the weights with the one from the Autoencoder
    func_decoder.set_weights(model.decoder.get_weights())

    # make sure nothing went wrong by comparing outputs of the functional model to the Autoencoder
    functional_outputs = func_decoder([440 * np.ones((1, time_steps, 1), dtype=np.float32), -6 * np.ones((1, time_steps, 1), dtype=np.float32)])
    for output_key in ['amps', 'noise_magnitudes', 'harmonic_distribution']:
        assert((model_outputs[output_key].numpy() == functional_outputs[output_key].numpy()).all())

    func_decoder.save(out_dir, save_format='tf', include_optimizer=False)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print('Usage: python covert_model.py model_dir out_dir')
        exit()

    model_dir = sys.argv[1]
    out_dir = sys.argv[2]

    config_file = f'{model_dir}/operative_config-0.gin'
    ckpt_path = f'{model_dir}/ckpt'

    convert_model(config_file, ckpt_path, out_dir)


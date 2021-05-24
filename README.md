# Real-time Timbre Transfer and Sound Synthesis using DDSP

This repository contains source code for a real-time timbre transfer plugin.

See the paper [Real-time Timbre Transfer and Sound Synthesis using DDSP](https://arxiv.org/abs/2103.07220) for more info.

## Usage
This project is created using [Juce](https://juce.com/) version 6.0.5.
Project files should be recompiled using the Projucer.

### Compiling using Visual Studio
The Projucer exports to both Visual Studio 17 and 19.

The Visual Studio solution consists of three projects:
* SharedCode - dependency for all project types
* StandalonePlugin - Standalone version of the plugin
* VST3 - VST3 version of the plugin 

The plugins are dependent on the tensorflow.dll, libaubio-5.dll and Models folder being in the same folder path.

### Compiling using XCode
TODO

## MATLAB generated code
The functions additive, subtractive, getPitch, compute_loudness and scale_f0 are generated using the MATLAB coder plugin and located in [Source/codegen](Source/codegen). 

The source MATLAB code can be found at https://github.com/SMC704/matlab-ddsp

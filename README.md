**Swarm (Multi-Output Granular Dispersion)** is a real-time granular synthesis tool designed for immersive live performances and installations using multi-speaker setups. Unlike traditional granular synthesizers, this tool spatializes individual grains of sound across any output channel configuration, creating immersive, swarm-like soundscapes that move through a space in real time. I've uploaded it as a standalone application, but it can be trivially converted into a plugin version for direct use in DAWs.

**Granular:** meaning it takes an input audio file and parses it into grains (whose numerous properties can be varied on the fly). 

**Dispersion:** meaning it disperses those grains out across output speakers (according to a manipulable probability algorithm). 

**Multi-output:** meaning it does so for output speaker setups up to 8 speakers (chosen arbitrarily, this can be trivially upgraded within the code). 

**Manual:**

Attack: time of attack envelope of a grain; presented to user in milliseconds, but converted internally to audio blocks for its use.

Grain Size: size of a "grain" (in audio blocks)

Flux: degree of random additive variation to grain size (in audio blocks).

Spread: probability distribution curve for randomize selection of output speaker for each new grain. Closer to 0 -> successive grains more likely to stay on the current speaker or if not then adjacent speakers. Closer to 100 -> closer to evenly distributed probability.

Below are some demonstrations in stereo. While the effect is more striking in multi-channel setups, this gives a sense of the tool in action.
https://github.com/janemeenaghan/MultiOutputGranularDispersionStandalone/blob/0d9018d2f10474c64deb8ecf9c85d9c965eeba40/Swarm%20Stereo%20Demo%201.mp4
https://github.com/janemeenaghan/MultiOutputGranularDispersionStandalone/blob/0d9018d2f10474c64deb8ecf9c85d9c965eeba40/Swarm%20Stereo%20Demo%202.mov
<video src="https://github.com/janemeenaghan/MultiOutputGranularDispersionStandalone/releases/download/DemoVidsAttempt2/Swarm.Stereo.Demo.1.mp4" controls width="600"></video>


<video src="https://github.com/janemeenaghan/MultiOutputGranularDispersionStandalone/releases/latest/download/Swarm.Stereo.Demo.1.mp4" controls width="600"></video>






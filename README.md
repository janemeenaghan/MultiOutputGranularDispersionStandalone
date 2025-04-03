<img width="1142" alt="Screenshot 2025-04-02 at 11 03 35 PM" src="https://github.com/user-attachments/assets/8a48835a-aa5b-44f2-ac11-6d540d5d4201" />
**Swarm (Multi-Output Granular Dispersion)** is a real-time granular synthesis tool designed for immersive live performances and installations using multi-speaker setups. Unlike traditional granular synthesizers, this tool spatializes individual grains of sound across any output channel configuration, creating immersive, swarm-like soundscapes that move through a space in real time. I've uploaded it as a standalone application, but it can be trivially converted into a plugin version for direct use in DAWs.

**Granular:** meaning it takes an input audio file and parses it into grains (whose numerous properties can be varied on the fly). 

**Dispersion:** meaning it disperses those grains out across output speakers (according to a manipulable probability algorithm). 

**Multi-output:** meaning it does so for output speaker setups up to 8 speakers (chosen arbitrarily, this can be trivially upgraded within the code). 

**Manual:**

Attack: time of attack envelope of a grain; presented to user in milliseconds, but converted internally to audio blocks for its use.

Grain Size: size of a "grain" (in audio blocks)

Flux: degree of random additive variation to grain size (in audio blocks).

Spread: probability distribution curve for randomize selection of output speaker for each new grain. Closer to 0 -> successive grains more likely to stay on the current speaker or if not then adjacent speakers. Closer to 100 -> closer to evenly distributed probability.

Below is a demonstration in stereo. While the effect is more striking in multi-channel setups, this gives a sense of the tool in action.

https://github.com/user-attachments/assets/6e7c5513-484b-4dd3-ba80-cdb30ddae746

And here is a demonstration on four amps (hence the sound is so harsh, apologies, I didn't have speakers around), to give more of a sense for the spatialization with several outputs across a room:

https://github.com/user-attachments/assets/d15999bd-6f47-462e-9a18-a7838b37713c


https://github.com/user-attachments/assets/e60056f8-6374-4049-96f8-b752f613c516



I had to egregiously compress these video to be able to embed it here, so apologies.

This project is a granular dispersion multi-output tool. Granular: meaning it takes an input audio file and parses it into grains (whose numerous properties can be varied on the fly). Dispersion: meaning it disperses those grains out across output speakers (according to a manipulable probability algorithm). Multi-output: meaning it does so for output speaker setups up to 8 speakers (chosen arbitrarily, this can be trivially upgraded within the code).
This project was a departure from much of my Computational Sound course's material. For starters, it was made in JUCE, an environment which I was completely unfamiliar with and which I had to self-teach myself on the fly in the short span of this project.
My goal with this project was to build a high quality, interesting tool that I would actually use as a music producer. This would represent the ultimate success of the course for me, and I am happy to say I was successful.
The success of this project is a positive sign for the future - it means that I am able to freely and viably engineer solutions to my own musical needs, not limited by the landscape of current composition/production tool markets.
I was able to record a couple short demos of the in a spatialized multi-output (in this case amps, not speakers, hence the harsh sound) little rig I assembled at CU Records:

If I worked more with this kind of sound creation, I would like to create a plugin version that interacts with a live stream of sound. Given the way the standalone version handles grains, it should theoretically be easily portable. The trickier issue is troubleshooting getting JUCE plugins generally to work within a DAW, something I thought it would be best to skip for now since it isn't exactly artistic work.



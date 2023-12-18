This project is a granular dispersion multi-output tool.  
Granular: meaning it takes an input audio file and parses it into grains (whose numerous properties can be varied on the fly). 

Dispersion: meaning it disperses those grains out across output speakers (according to a manipulable probability algorithm). 

Multi-output: meaning it does so for output speaker setups up to 8 speakers (chosen arbitrarily, this can be trivially upgraded within the code). 

This project was a departure from much of my Computational Sound course's material. For starters, it was made in JUCE, an environment which I was completely unfamiliar with and which I had to self-teach myself on the fly in the short span of this project. This was by far the trickiest part - I spent dozens of hours just trying to resolve problems with my environment (weird preprocessor definitions that I had to include in specific ways, and I never figured out why even successfully built example projects wouldn't run in my DAW, etc.), implementing things that aren't natively supported (like GIFs), and familairizing myself with the idiosyncrasies of language and formating in the JUCE libraries and C++ generally. I troubleshooted using a combination of TheAudioProgrammer tutorials and Discord, JUCE forums, and  just scrutinizing the docs line by line. Somehow, with some luck, I managed to persevere through most issues.

The final product presents some real nice friendly animated imagery, buttons for loading/playing/stopping an audio file, a menu for managing audio input and output routing, and knobs for controlling the aspects of the grains, namely:

attack - time of attack envelope of a grain; presented to user in milliseconds, but converted internally to audio blocks for its use.

grain size - size of a "grain" (in audio blocks)

flux - degree of random additive variation to grain size (in audio blocks).

spread - probability distribution curve for randomize selection of output speaker for each new grain. Closer to 0 -> successive grains more likely to stay on the current speaker or if not then adjacent speakers. Closer to 100 -> closer to evenly distributed probability.

My goal with this project was to build a high quality, interesting tool that I would actually use as a music producer. This represented the ultimate success of the course for me, and I am happy to say I was successful. The success of this project is a positive sign for the future - it means that I am able to freely and viably engineer solutions to my own musical needs, not limited by the landscape of current composition/production tool markets.


!!!!!!!!!!!!!!!!WATCH THE STEREO DEMO HERE:
https://youtu.be/cSqCDROEZRg
!!!!!!!!!!!!!!!!

It's not as interesting with only two outputs, but you can clearly hear and see how the application works.
Alternatively, I was also able to record a couple short demos of an earlier version in a quad sound little rig I assembled at CU Records. I had amps, not speakers, to work with, so the sound is harsh, and I had to egregiously compress the video to be able to embed it here. But you can get more of a sense for how the spatialization with many speakers in a room would make for a much more interesting effect:

https://github.com/janemeenaghan/MultiOutputGranularDispersionStandalone/assets/106706615/0de5b86d-4e4f-4970-9ec6-39331b628cc1



https://github.com/janemeenaghan/MultiOutputGranularDispersionStandalone/assets/106706615/d4c5466c-c620-4eef-823f-93de4d01d227


If I worked more with this kind of sound creation, I would like to create a plugin version that interacts with a live stream of sound. Given the way the standalone version handles grains, it should theoretically be easily portable. The trickier issue is troubleshooting getting JUCE plugins generally to work within a DAW, something I thought it would be best to skip for now since it isn't exactly artistic work. It should be noted that these two would be fundamentally different tools. This standalone is mainly intended as an interesting way to present bounced tracks - it is geared towards performance. A plugin would be more likely a production tool. But above all, I want to test this out at the Computer Music Center with as complex a speaker system as possible. One huge plus of my tool is it's super flexible, so it should be very easy to get running on any speaker setup over there.



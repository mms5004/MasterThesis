# Uses Unreal Engine 5.4 or higher

This Unreal Engine project is the result of a master thesis made at Haute École Albert Jacquard.
The plugin developed is named Sound Holder, its objective is to automate or help with repetitive tasks in order to gain time.
It contains tools to place, edit, select and mix sounds dynamically.

Its features are inspired by:
- Electric Dream (Epic Games), for the tag selection tool
- Rage Audio's modular sound hierarchies (Rockstar), for Wwise's RTPC-like dynamic function parameters
- Solar Ash Kingdom (Heart Machine), for the dynamic sound mix and the modular logic
- Outcast 2 Static Mesh Emitters (Demute Studio), for the sound sources placing 
More sources can be found in the Mémoire.pdf

# Tools
The placement tool is a widget allowing the detection of static meshes in a level to instantiate audio sources.

https://github.com/user-attachments/assets/e8f8eff3-db24-4794-9412-36b9cdba9721

Audio sources can be tagged to create quick selection.
![Selection](https://github.com/user-attachments/assets/77742bf8-0c40-4ccd-a48b-c0943d33201b)

To edit multiple instances at once, it's possible to open an "Object Mixer" (Light Mixer for UE5.4 or less) and apply a sound filter to edit properties.
<img width="3818" height="1939" alt="SoundVisualization" src="https://github.com/user-attachments/assets/a6e6ffd9-7e0b-4285-8f8e-a716e38ca6ca" />



# Plugin structure
Sound Holder is built with 3 modules:
- SoundHolder        Runtime (audio sources)
- SoundHolderEditor  Editor tools
- SoundHolderMixer   Runtime (mixer subsystem)

# Mixer structure
SoundHolderMixer contains a subsystem, the logic allows combining values into a float called Alpha in reference to Solar Ash Kingdom presentation at GameSoundCon 2022.
<img width="1259" height="642" alt="Mixer subsystem" src="https://github.com/user-attachments/assets/5aa39095-ad81-48be-a923-0d1b25d8f8b9" />


Values can be retrieved by subscribing to the AlphaChanged subsystem's function (multicast) delegate or using GetAlpha function.
It's also possible to directly use alpha values in metasound thanks to a custom node.
<img width="650" height="336" alt="Metasound alpha node" src="https://github.com/user-attachments/assets/8ad2cfee-a4a6-4ad1-94c0-08379bd368a2" />

# Mixing exemple

Here you can see input sent by actors and components to the subsystem updating sound parameters and a widget debugger with the current Alpha values. 
[![Youtube video](https://img.youtube.com/vi/tZiV-2drFsE/maxresdefault.jpg)](https://youtu.be/tZiV-2drFsE)

^ You can click to see the runtime result on Youtube






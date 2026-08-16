# Thalrin

<p align="center">
  <img src="Static/thalrin.png" alt="Thalrin" width="400" />
</p>

Thalrin is an ancient, indestructible material discovered deep beneath the world of Chronicle. Unlike ordinary metals that are mined and smelted, Thalrin was grown as a crystalline lattice that spread through the world's bedrock like veins through a body, connecting every continent, every cavern, every forgotten ruin into one vast living network.

The ancients who first discovered it realised that Thalrin wasn’t just strong; it carried information. Strike one node and the vibration would ripple through the entire lattice instantly, regardless of distance. They built their civilisation on top of it. Communication, trade, magic all of it flowed through the Thalrin network. It was the connective tissue of their entire world.

Then something severed it. The lattice fractured. Civilisations collapsed into isolation. The world of Chronicle begins in the aftermath, players exploring the ruins, rediscovering fragments of the Thalrin network, and slowly reconnecting what was broken.

## The Engine

Thalrin is a custom game engine powering Chronicle.

It is written in **C++**, with a custom renderer built on **Vulkan**. The engine is being developed alongside the game, which means its features and architecture are driven by what Chronicle actually needs rather than trying to be a general-purpose engine for every type of game.

Thalrin handles the core systems behind Chronicle, including rendering, world management, asset loading, input, audio, networking, gameplay systems, and the tools used to build and debug the game.

Building our own engine gives us control over the entire stack. We can make technical decisions specifically for a large, persistent MMORPG, optimize the parts of the engine that matter to Chronicle, and avoid carrying systems or abstractions that the game doesn't need.

The goal isn't to build an engine that competes with Unreal or Unity.

**The goal is to build the engine Chronicle needs.**
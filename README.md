# TooManyFireworks

Don't think there's enough fireworks? This mod adds a variety of settings that can make fireworks powerful enough to explode the game itself!

<p>
<img src="docs/images/modConfigMenu.jpg" alt="Mod configuration menu under mod settings" width="200" />
<img src="docs/images/lowFrameRate.gif" alt="10000 sparks reducing frame rate" width="200" />
</p>

## Current Options

- Min / max frequency
- Rainbow color
- Specific color
- Brightness
- Min / max size
- Number of sparks
- Duration
- Gravity
- Collisions
- Bounce strength / dampen
- Spawn range
- Show on highscore
- Show on level clear
- Show on level fail
- Smooth disable

## Known Bugs

- Color will flicker when a slider is moved with rainbow color on
- Light rays will flicker when a size slider is moved
- Canceling color select will not revert color
- Sound is tied to SFX volume. If fireworks are silent, check to see if this is zero
- Smooth disable will delete fireworks even if they started again

## Future Ideas

- Show in menu
- Show in level select
- Show on score percentage
- Show on scoreboard rank
- Color over time
- Spark size
- Turbulence
- Minimum spark speed multiplier
- Different type of firework for each condition
- Color palettes
- Mute sounds / Sound probability
- Change random sound pitch
- Change audio clips
- Custom sprite
- Cheerleading
- Custom shapes
- Quick preset buttons

Or, I might create a new mod that allows customizability to the whole Unity Particle System for anything and everything!

## Build Instructions

Follow the instructions [here](https://bsmg.wiki/modding/quest-mod-dev-intro.html) to set up the software and learn the basics of compiling mods. After cloning this repository, key terminal commands will be `qpm restore` and `qpm s qmod`.

## Credits

* [zoller27osu](https://github.com/zoller27osu), [Sc2ad](https://github.com/Sc2ad) and [jakibaki](https://github.com/jakibaki) - [beatsaber-hook](https://github.com/sc2ad/beatsaber-hook)
* [raftario](https://github.com/raftario)
* [Lauriethefish](https://github.com/Lauriethefish), [danrouse](https://github.com/danrouse) and [Bobby Shmurner](https://github.com/BobbyShmurner) for [this template](https://github.com/Lauriethefish/quest-mod-template)
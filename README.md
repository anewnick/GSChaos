# GSChaos

![gsch_banner](https://raw.githubusercontent.com/ScriptedSnark/GSChaos/master/gsch_banner.png)

</div>
ASI plugin for GoldSrc Engine (steam_legacy / HL25). Adds "Chaos" in game (new chaotic effect every 30 seconds).

Inspired by Chaos mods from the GTA universe (by zolika1351), I decided to make my own for HL1 and GoldSrc in particular (you can run almost any mod with it).

**Download via Github: [CLICK](https://github.com/ScriptedSnark/GSChaos/releases/tag/continuous)**

Additional info:
- Chaos UI rendering is not visible in OBS scene if third-party overlays checkbox is unchecked (doesn't matter if you capture hl.exe as a window, not game)
- Save your game more often because of potential softlocks/crashes

## CVars and commands
- `chaos_activate` - activate effect (from 0 to (LATEST EFFECT NUM - 1)) | `sv_cheats 1` is required!
- `chaos_reset` - reset RNG, chaos bar (can be useful for potential runs)
- `chaos_version` - prints version and Chaos Mod details
- `chaos_effectname_ypos` - sets position of effect name text by vertical (Y coord)

## Twitch voting integration (WIP)
GSChaos supports Twitch chat voting. If you want to use it, then do some steps:
1. Download [latest continuous release](https://github.com/ScriptedSnark/GSChaos/releases/tag/continuous)
2. Install it
3. Edit `chaos/twitch.ini`. It should have your [OAuth password](https://twitchapps.com/tmi/) and Twitch username
4. Add text element (GDI) to your OBS scene
5. Create file - `chaos/voting_progress.txt`
6. Pass a path of that file in text options
![obs_voting](https://github.com/ScriptedSnark/GSChaos/assets/51358194/b944b93a-f429-49e4-90e2-3da60d2d9026)

7. Run the game and check if everything is installed successfully (wait for 10 seconds in game after chaos bar activating so you can check voting system)

To vote, you need to type `effectNUMBER` in chat (for example, `effect2`).
If you don't want to play with this feature, rename `twitch.ini` to `twitch_DISABLED.ini`.

## Effects
```
> New Game :tf:
> Audio Corrupt
> Set 1 HP
> I believe I can fly
> Remove Armor
> Zero Gravity
> Invisible entities
> Ohio
> Fake Crash
> Darkness
> Totem of Undying
> Forgot to install CS 1.6 :o
> X2 Gravity
> God Mode
> Everyone has God Mode!
> Create Explosion
> Ichthyosaur jumpscare
> Give Gauss
> Human grunt ambush!
> GTA 3 HUD
> player_weaponstrip
> Spawn Griefer Shephard
> Entity spin
> 2D Camera
> 1% chance of death
> Spawn random entity
> Sleepy
> Force 20 FPS
> BSP Dementia
> HEV Madness
> Negative Stepsize
> Lobotomy
> Upside Down
> Every NPC explodes
> Let's see Jeepy's lasagna
> Hyper Gravity Field
> Ice Skating
> Invert Velocity
> Need for Speed (500 ups curse)
> Combine Effects ( 3 in 1 )
```

Credits
==============
Author: ScriptedSnark

Special thanks to:
- zolika1351 for his great, inspiring Chaos mods
- anewnick (a.k.a codque) for designing HUDs and banner
- SmileyAG for provided help about some aspects of hooking
- BlueNightHawk for late precache system
- suXinjke for [Half-Payne](https://github.com/suXinjke/HalfPayne)
- un4seen (a.k.a. yanny) for supporting/playtesting
- Tankfird, StereoBucket, prolert, gatar and other people for suggesting effects, ideas

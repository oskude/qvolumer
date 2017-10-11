# qvolumer

`qvolumer` is a *daemon-cli-x-splash-thing* for setting and displaying PulseAudio default sink volume, intended for use with keyboard media keys.

![screenshot](screenshot.gif?raw=true "screenshot of qvolumer rising, lowering and muting audio volume")

## Requirements

- Usage
  - [qt5-base](https://www.qt.io/)
  - [qt5-declarative](https://www.qt.io/)
  - [pactl](https://www.freedesktop.org/wiki/Software/PulseAudio/)
- Build
  - [qpm](https://www.qpm.io/)

## Build

```
qpm install de.skycoder42.qsingleinstance
make
```

Availabe `make` targets:
- `build` qvolumer *(also the default target)*
- `clean` all artifacts
- `install` to `$DESTDIR$PREFIX` *(default PREFIX is /usr/local)*
- `uninstall` from `$DESTDIR$PREFIX` *(default PREFIX is /usr/local)*
- `archlinux` build archlinux package

## Usage

First start `qvolumer` without arguments and then (presumably in another terminal) send commands to it:
- `qvolumer 5` to raise volume 5%
- `qvolume -5` to lower volume 5%
- `qvolumer toggle` to toggle mute

## Example

Set your X session to start `xbindkeys` and `qvolumer` on login. In case of JWM it could be by adding following to `~/.jwmrc`:
```
<JWM>
	...
	<StartupCommand>xbindkeys</StartupCommand>
	<StartupCommand>qvolumer</StartupCommand>
	...
</JWM>
```

Set `xbindkeys` to bind volume and mute keys to `qvolumer` commands by adding following to `~/.xbindkeysrc`:

```
"qvolumer 5"
	XF86AudioRaiseVolume

"qvolumer -5"
	XF86AudioLowerVolume

"qvolumer toggle"
	XF86AudioMute
```

# Dwm

Mamiza's Custom Build of Dwm

# Patches and features

- Clickable statusbar with my build of [dwmblocks](https://github.com/mamizaxyz/dwmblocks).
- New layouts: you can check them out with <kbd>super+ctrl+,/.</kbd>.
- [Actual fullscreen](https://dwm.suckless.org/patches/actualfullscreen/).
- [Hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/) hides tags with to windows.
- [Stacker](https://dwm.suckless.org/patches/stacker/): move windows up the stack manually (<kbd>super+shift+k/j</kbd>).
- [VanityGaps](https://dwm.suckless.org/patches/vanitygaps/) adds useless gaps.
- [Swallow](https://dwm.suckless.org/patches/swallow/): if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.

**_NOTE:_** I also have a the actual patches used to configure this build in the 'patches' folder if you want to use that.

# Installation

``` shell
git clone https://github.com/mamizaxyz/dwm
cd dwm
sudo make install
```

### You must also install `libxft-git`

This build of dwm does not block colored emojis in the statusbar, so you must install [libxft-git](https://aur.archlinux.org/packages/libxft-git), which solves a libxft color emoji rendering problem, If you choose not to install this package dwm will crash upon rendering a colored emoji.


with the autostart patch:
add this
```
#!/bin/sh

xrandr --output Virtual-1 --mode 1920x1080
feh --bg-scale ~/bg.jpeg
slstatus &

```
to `~/.local/share/dwm/autostart.sh` and don't forget to set it as executable.

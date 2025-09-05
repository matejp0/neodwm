#!/bin/dash

CURRENT=$(xrandr --query --verbose | grep eDP | cut -d ' ' -f 6)
TNAME="ELAN0634:00 04F3:3124 Touchpad"

if [ "$CURRENT" = "normal" ]; then
  xrandr -o left
  xinput set-prop "$TNAME" --type=float "Coordinate Transformation Matrix" 0 -1 1 1 0 0 0 0 1 
# xrandr -o right
# xinput set-prop "$TNAME" --type=float "Coordinate Transformation Matrix" 0 1 0 -1 0 1 0 0 1
else
  xrandr -o normal
  xinput set-prop "$TNAME" --type=float "Coordinate Transformation Matrix" 0 0 0 0 0 0 0 0 0
fi

#| grep -q 'normal' && xrandr -o right || xrandr -o normal

#!/bin/zsh
app_root="${0:A:h}"
cd "$app_root" || exit 1
if [[ ! -d MuJoCoCAD.app ]]; then
  /usr/bin/unzip -q NativeLauncher.zip || exit 1
fi
open "$app_root/MuJoCoCAD.app"

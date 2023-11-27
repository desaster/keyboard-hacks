#!/bin/sh

set -e

QMK_VIAL_COMMIT_ID="9caabddf4cfa187d2a77ee27e896d25c30a6c125"

# check if directory is a git repo
if [ ! -d "./qmk-vial-git" ]; then
  echo "Cloning qmk-vial into ./qmk-vial-git"
  git clone https://github.com/vial-kb/vial-qmk qmk-vial-git
  git -C ./qmk-vial-git checkout "$QMK_VIAL_COMMIT_ID"
fi

echo "Copying extra files into cloned repository"

cp -rv ./users qmk-vial-git
cp -rv ./keyboards qmk-vial-git

# https://docs.qmk.fm/#/getting_started_docker
cd qmk-vial-git
./util/docker_build.sh keychron/q3/iso:desaster

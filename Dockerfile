#
# Dockerfile for qmk-vial userspace compilation
#
# Includes the qmk-cli and the vial-qmk repository
#
# To ensure reproducability, the base image is tagged by a sha256 hash, and
# the qmk repository cloned at a specific commit id.
#

FROM ghcr.io/qmk/qmk_cli:latest@sha256:d8ebfab96c46d3ab948dd4e87be8a976095bd31268700021a74716cbd6e5b4c1

ENV QMK_GIT_REPO https://github.com/vial-kb/vial-qmk
ENV QMK_COMMIT_ID 63e10d6cdc404d04f8e53afe5eebe7f1d3a1ceed

RUN mkdir /qmk-userspace && \
    git clone $QMK_GIT_REPO --recurse-submodules /qmk-firmware && \
    cd /qmk-firmware && \
    git checkout $QMK_COMMIT_ID && \
    qmk setup -H /qmk-firmware && \
    qmk config user.qmk_home=/qmk-firmware

WORKDIR /qmk-userspace

CMD [ "qmk", "userspace-compile"]

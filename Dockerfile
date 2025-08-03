FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

ARG HOST_UID=1000
ARG HOST_GID=1000
ARG USER_NAME=developer

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    git \
    wget \
    gcc-arm-none-eabi \
    gdb-multiarch \
    openocd && \
    groupadd -g ${HOST_GID} ${USER_NAME} && \
    useradd -u ${HOST_UID} -g ${USER_NAME} -m -s /bin/bash ${USER_NAME} && \
    rm -rf /var/lib/apt/lists/*

USER ${USER_NAME}

WORKDIR /project

CMD ["bash"]

#!/bin/bash

GREEN='\e[32m'
YELLOW='\e[33m'
CYAN='\e[36m'
BOLD='\e[1m'
RESET='\e[0m'


# Exit immediately if a command exits with a non-zero status
set -e

#Get version number
echo -n "Enter version number: "
read version

# Set Docker image name and tag
IMAGE_NAME="stm32f103-arm-baremetal"
IMAGE_TAG="1.0.$version"

# Print build start message
echo "${YELLOW}=================================================${RESET}"
echo " Building Docker development environment..."
echo " Image Name: ${IMAGE_NAME}:${IMAGE_TAG}"
echo "${YELLOW}=================================================${RESET}"


# Build the Docker image with user-specific build arguments
docker build \
  --build-arg HOST_UID=$(id -u) \
  --build-arg HOST_GID=$(id -g) \
  --build-arg USER_NAME=$(whoami) \
  -t "${IMAGE_NAME}:${IMAGE_TAG}" .

echo ""
# Print build completion message and usage instructions
echo "================================================="
echo "${BOLD}${GREEN} Build complete!${RESET}"
echo " You can now run the container using:"
echo " docker run -it --rm -v \$(pwd):/project ${IMAGE_NAME}:${IMAGE_TAG}"
echo "================================================="

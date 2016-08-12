#!/bin/bash

# Paths
SCRIPT=$(realpath $0)
SCRIPT_ROOT_PATH=$(dirname $SCRIPT)
LIBRARY_PATH="${SCRIPT_ROOT_PATH}/../libs"

# URLs
OPENFRAMEWORKS_SOURCE_URL="http://openframeworks.cc/versions/v0.9.3/of_v0.9.3_linux64_release.tar.gz"

function main()
{
	# Create library directory
	mkdir ${LIBRARY_PATH}

	# Download OpenFrameworks source code
	wget -O "/tmp/openframeworks.tar.gz" ${OPENFRAMEWORKS_SOURCE_URL}

	# Unpack the source
	tar -C "${LIBRARY_PATH}" -zxvf "/tmp/openframeworks.tar.gz"

	# Install dependencies
	gksudo "${LIBRARY_PATH}/of_v0.9.3_linux64_release/scripts/linux/ubuntu/install_dependencies.sh"
	gksudo "${LIBRARY_PATH}/of_v0.9.3_linux64_release/scripts/linux/ubuntu/install_codecs.sh"

	# Compile OpenFrameworks
	gksudo "${LIBRARY_PATH}/of_v0.9.3_linux64_release/scripts/linux/compileOF.sh"
}

# Start script
main

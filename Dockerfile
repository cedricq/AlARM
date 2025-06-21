FROM ubuntu:22.04

# Avoid tzdata interactive prompt
ENV DEBIAN_FRONTEND=noninteractive

# Set timezone to UTC and install dependencies
RUN apt-get update && \
    apt-get install -y tzdata && \
    ln -fs /usr/share/zoneinfo/Etc/UTC /etc/localtime && \
    dpkg-reconfigure -f noninteractive tzdata && \
    apt-get install -y \
        build-essential \
        cmake \
        git  \
        gcovr && \
    rm -rf /var/lib/apt/lists/*

# Create app directory
WORKDIR /app

# Copy project files
COPY . .

# Create build directory
RUN mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug -DCODE_COVERAGE=ON && make

# Define default command
WORKDIR /app/build
CMD ctest -V --output-on-failure && mkdir -p coverage-html && gcovr --root .. \
          --exclude '.*test.*' --exclude '.*Fake.*' --exclude '_deps' \
          --html --html-details -o coverage-html/index.html \
          --print-summary \
          --branches \
          --fail-under-line=100 \
          #--fail-under-function=100 \
          --fail-under-branch=90

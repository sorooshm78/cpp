FROM ubuntu:24.10

WORKDIR /src

RUN apt-get update

# Install required tools
RUN apt-get install -y build-essential \ 
    swig

# Install additional tools
RUN apt-get install -y tmux \
    vim 
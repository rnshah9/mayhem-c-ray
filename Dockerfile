FROM --platform=linux/amd64 ubuntu:20.04

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential cmake

ADD . /repo
WORKDIR /repo/build
RUN cmake .. -DNO_SDL2=True
RUN make -j8

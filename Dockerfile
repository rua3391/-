FROM ubuntu:20.04

ADD . /data/
WORKDIR /data/

RUN apt-get update && apt-get install -y g++ cmake
RUN mkdir build && cd build && cmake .. && cmake --build .

ENTRYPOINT ["sh", "entrypoint.sh"]

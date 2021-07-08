FROM harbor.corp.sdo.com/library/ubuntu:20.04_local

ADD . /data/
WORKDIR /data/

RUN apt-get update && apt-get install -y g++ cmake
RUN mkdir build && cd build && cmake .. && cmake --build .

ENTRYPOINT ["sh", "entrypoint.sh"]

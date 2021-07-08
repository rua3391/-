FROM harbor.corp.sdo.com/library/ubuntu:20.04_local as builder

ADD . /build/
WORKDIR /build/

RUN apt-get update && apt-get install -y g++ cmake
RUN mkdir build && cd build && cmake .. && cmake --build .

FROM harbor.corp.sdo.com/library/ubuntu:20.04_local

WORKDIR /data/

COPY --from=builder /build/bin /data/bin 

WORKDIR /data/

ENTRYPOINT ["sh", "entrypoint.sh"]
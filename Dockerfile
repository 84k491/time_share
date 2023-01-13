# syntax=docker/dockerfile:1
FROM silkeh/clang:latest AS builder

COPY ./ /src/
WORKDIR /src

RUN \
mkdir /output; \
./clean.sh; \
apt-get update ; apt-get install libgtest-dev -y; \
./build.sh; \
./bin/Tests && \
cp bin/* /output

##################################################

FROM ubuntu:20.04

WORKDIR /root/
COPY --from=builder /output/TimeSyncServer .

ENTRYPOINT ["./TimeSyncServer"]

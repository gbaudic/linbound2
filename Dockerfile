# Dockerfile draft for the server part
FROM ubuntu:bionic
WORKDIR /usr/src/app
COPY linbound_server .
COPY res/ res/
EXPOSE 6545
RUN apt-get update && apt-get install -y libsdl2-mixer-2.0-0 libsdl2-image-2.0-0 libsdl2-ttf-2.0-0 \
	libsdl2-net-2.0-0 libsdl2-gfx-1.0-0 libsdl2-2.0-0 libtinyxml2-6 libbox2d2.3.0 libsqlite3-0 libstdc++6
# Put the db outside the image so it can be made persistent
RUN mkdir /database
VOLUME /database
CMD linbound_server
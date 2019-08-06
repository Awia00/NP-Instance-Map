FROM ubuntu:19.04
COPY install_deps.sh .
RUN ./install_deps.sh
COPY . .
RUN cd solver && ./build.sh && cd ..
CMD bash
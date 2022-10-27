FROM debian
COPY lab3.cpp .
RUN chmod ugo+x lab3.cpp
CMD ./lab3.cpp

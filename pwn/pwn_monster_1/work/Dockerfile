FROM ubuntu:20.04

ARG BINARY_NAME

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get -y update --fix-missing \
	&& apt-get -y upgrade \
	&& apt-get -y install xinetd

RUN groupadd -r pwn && useradd -r -g pwn pwn

COPY ./flag.txt /home/pwn/flag.txt
COPY ./${BINARY_NAME} /home/pwn/${BINARY_NAME}
COPY ./pwn.xinetd /etc/xinetd.d/pwn
COPY ./entry.sh /home/pwn/entry.sh

RUN chmod 440 /home/pwn/flag.txt
RUN chmod 550 /home/pwn/${BINARY_NAME}
RUN chmod 550 /home/pwn/entry.sh
RUN chmod 1733 /tmp /var/tmp /dev/shm

RUN chown -R root:pwn /home/pwn

ENTRYPOINT service xinetd restart && /bin/sleep infinity

# Overview
PJSIP is a free and open source multimedia communication library written in C language, implementing standard based protocols such as SIP, SDP, RTP, STUN, TURN, and ICE. It combines signaling protocol (SIP) with rich multimedia framework and NAT traversal functionality into high level API that is portable and suitable for almost any type of systems ranging from desktops, embedded systems, to mobile handsets.

PJSIP is both compact and feature rich. It supports audio, video, presence, and instant messaging, and has extensive documentation. PJSIP is very portable. On mobile devices, it abstracts system dependent features and in many cases is able to utilize the native multimedia capabilities of the device.

PJSIP is developed by a small team working exclusively for the project since 2005, with participation of hundreds of developers from around the world, and is routinely tested at SIP Interoperability Event (SIPit) since 2007.

# Libraries Architecture
PJSIP contains several libraries, which can be grouped into three main components:

* SIP protocol stack, in PJSIP
* Media stack, in PJMEDIA
* NAT traversal stack, in PJNATH

These libraries are then integrated into high-level libraries, namely PJSUA-LIB API (written in C) and PJSUA2 API (written in C++).
There are also low level libraries that abstracts operating system differences (PJLIB) as well as a utility libraries (PJLIB-UTIL)

To avoid naming confusion between PJSIP as organization name (as in PJSIP.ORG) and PJSIP as libraries that provide SIP protocol implementation above, we also call this project PJPROJECT.

Below is architecture diagram of libraries in PJPROJECT. Click the link on the diagram to go to the documentation.

![](https://docs.pjsip.org/en/latest/pjsua2/intro.html)
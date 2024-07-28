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

# PJSIP, PJMEDIA, and PJNATH Level
At the lower level there are collection of C libraries, which consist of PJSIP, PJMEDIA, and PJNATH, with PJLIB-UTIL and PJLIB as support libraries. This level provides the most flexibility, but it’s also more low level.

Some of the reasons for wanting to use libraries at this level are:

* You only need the individual library (say, PJNATH)
* You need to be very very tight in footprint (say when things need to be measured in Kilobytes instead of Megabytes)
* You are not developing a SIP client

Use the corresponding PJSIP, PJMEDIA, and PJNATH manuals and samples for information on how to use the libraries.

# PJSUA-LIB API
Next up is PJSUA-LIB API that combines all those libraries into a high level, integrated client user agent library written in C. This is the library that most PJSIP users use, and the highest level abstraction before PJSUA2 was created.

Motivations for using PJSUA-LIB library include:

* Developing client application (PJSUA-LIB is optimized for developing client app)
* Better efficiency than higher level API

# PJSUA-LIB API
Next up is PJSUA-LIB API that combines all those libraries into a high level, integrated client user agent library written in C. This is the library that most PJSIP users use, and the highest level abstraction before PJSUA2 was created.

Motivations for using PJSUA-LIB library include:

* Developing client application (PJSUA-LIB is optimized for developing client app)
* Better efficiency than higher level API

# PJSUA2 C++ API
PJSUA2 API is an objected oriented, C++ API created on top of PJSUA-LIB. The API is different than PJSUA-LIB, but it should be even easier to use and it should have better documentation too (see PJSUA2 Guide). The PJSUA2 API removes most cruxes typically associated with PJSIP, such as the pool and pj_str_t, and adds new features such as object persistence so you can save your configs to JSON file, for example. All data structures are rewritten for more clarity.

A C++ application can use PJSUA2 natively, while at the same time still has access to the lower level C objects if it needs to. This means that the C++ application should not lose any information from using the C++ abstraction, compared to if it is using PJSUA-LIB directly. The C++ application also should not lose the ability to extend the library. It would still be able to register a custom PJSIP module, pjmedia_port, pjmedia_transport, and so on.

Benefits of using PJSUA2 C++ API include:
* Cleaner object oriented API
* Uniform API for higher level language such as Java, Python, and C#
* Persistence API
* The ability to access PJSUA-LIB and lower level libraries when needed (including the ability to extend the libraries, for example creating custom PJSIP module, pjmedia_port, pjmedia_transport, etc.)

Some considerations on using PJSUA2 C++ API are:
* Instead of returning error, the API uses exception for error reporting
* It uses standard C++ library (STL)
* The performance penalty due to the API abstraction should be negligible on typical modern device

# PJSUA2 API for Java, Python, C#, and Others
The PJSUA2 API is also available for non-native code via SWIG binding. Configurations for Java, Python, and C# are provided with the distribution. See Building PJSUA2 section for more information. Thanks to SWIG, other language bindings may be generated relatively easily in the future.

The PJSUA2 API for non-native code is effectively the same as PJSUA2 C++ API. You can peek at the Hello world section to see how these look like. However, unlike C++, you cannot access PJSUA-LIB and the underlying C libraries from the scripting language, hence you are limited to what PJSUA2 provides.

You can use this API if native application development is not available in target platform (such as Android), or if you prefer to develop with non-native code instead of C/C++.


# Introduction to PJSUA2
PJSUA2 API is a C++ library on top of PJSUA-LIB API to provide high level API for constructing Session Initiation Protocol (SIP) multimedia user agent applications (a.k.a Voice over IP/VoIP softphones).

PJSUA2 wraps together the signaling, media, and NAT traversal functionality into easy to use call control API, account management, buddy list management, presence, and instant messaging, along with multimedia features such as local audio and video conferencing, file streaming, local playback, and voice recording, and powerful NAT traversal techniques utilizing STUN, TURN, ICE, and uPnP.

PJSUA2 provides SWIG interface for generating modules for high level languages such as Java, Python, and C#. In the next sections we will learn how to build and use PJSUA2 in these languages.

# Building PJSUA2
The PJSUA2 C++ library is built by default by PJSIP build system. Standard C++ library is required.

## Common Requirements
1. On Linux/MacOS X/Unix, you need to build PJPROJECT with -fPIC option. You can either put it in user.mak file in root pjproject directory like this:

```
CFLAGS += -fPIC
```

or you can specify it when calling ./configure:

```
./configure CFLAGS="-fPIC"
```
Then rebuild pjproject.

2. Install SWIG
For Debian based distributions (such as Ubuntu):

```
sudo apt-get install swig
```
For Windows and other platforms please see https://www.swig.org/download.html

## Classes Overview
Here are the main classes of the PJSUA2:

## pj::Endpoint
This is the main class of PJSUA2. You need to instantiate one and exactly one of this class, and from the instance you can then initialize and start the library.

## pj::Account
An account specifies the identity of the person (or endpoint) on one side of SIP conversation. At least one account instance needs to be created before anything else, and from the account instance you can start making/receiving calls as well as adding buddies.

## pj::Media
This is an abstract base class that represents a media element which is capable to either produce media or takes media. It is then subclassed into pj::AudioMedia, which is then subclassed into concrete classes such as pj::AudioMediaPlayer and pj::AudioMediaRecorder.

## pj::Call
This class represents an ongoing call (or speaking technically, an INVITE session) and can be used to manipulate it, such as to answer the call, hangup the call, put the call on hold, transfer the call, etc.

## pj::Buddy
This class represents a remote buddy (a person, or a SIP endpoint). You can subscribe to presence status of a buddy to know whether the buddy is online/offline/etc., and you can send and receive instant messages to/from the buddy.

## Guidelines
## Class Usage Patterns
With the methods of the main classes above, you will be able to invoke various operations to the object quite easily. But how can we get events/notifications from these classes? Each of the main classes above (except Media) will get their events in the callback methods. So to handle these events, just derive a class from the corresponding class (Endpoint, Call, Account, or Buddy) and implement/override the relevant method (depending on which event you want to handle). More will be explained in later sections.

## Error Handling
We use exceptions as means to report error, as this would make the program flows more naturally. Operations which yield error will raise pj::Error exception. If you prefer to display the error in more structured manner, the pj::Error class has several members to explain the error, such as the operation name that raised the error, the error code, and the error message itself.

## Asynchronous Operations
If you have developed applications with PJSIP, you’ll know about this already. In PJSIP, all operations that involve sending and receiving SIP messages are asynchronous, meaning that the function that invokes the operation will complete immediately, and you will be given the completion status in a callback.

Take a look for example the pj::Call::makeCall() method of the pj::Call class. This function is used to initiate outgoing call to a destination. When this function returns successfully, it does not mean that the call has been established, but rather it means that the call has been initiated successfully. You will be given the report of the call progress and/or completion in the pj::Call::onCallState() callback method of pj::Call class.

## Threading
For platforms that require polling, the PJSUA2 module provides its own worker thread to poll PJSIP, so it is not necessary to instantiate own your polling thread. Application should be prepared to have the callbacks called by different thread than the main thread. The PJSUA2 module itself is thread safe.

Often though, especially if you use PJSUA2 with high level languages such as Python, it is required to disable PJSUA2 internal worker threads by setting EpConfig.uaConfig.threadCnt to 0, because Python doesn’t like to be called by external thread (such as PJSIP’s worker thread).

## Problems with Garbage Collection
Garbage collection (GC) exists in run-time such as Java and Python, and there are some problems with it when it comes to PJSUA2 usage:

it delays the destruction of objects (including PJSUA2 objects), causing the code in object’s destructor to be executed out of order

the GC operation may run on different thread not previously registered to PJLIB, causing assertion

Due to problems above, application ‘’’MUST immediately destroy PJSUA2 objects using object’s delete() method (in Java)’’’, instead of relying on the GC to clean up the object.

For example, to delete an Account, it’s NOT enough to just let it go out of scope. Application MUST delete it manually like this (in Java):

```
acc.delete();
```

## Objects Persistence
PJSUA2 includes pj::PersistentObject class to provide functionality to read/write data from/to a document (string or file). The data can be simple data types such as boolean, number, string, and string arrays, or a user defined object. Currently the implementation supports reading and writing from/to JSON document (RFC 4627), but the framework allows application to extend the API to support other document formats.

As such, classes which inherit from PersistentObject, such as pj::EpConfig (endpoint configuration), pj::AccountConfig (account configuration), and pj::BuddyConfig (buddy configuration) can be loaded/saved from/to a file. Heres an example to save a config to a file:
```
EpConfig epCfg;
JsonDocument jDoc;
epCfg.uaConfig.maxCalls = 61;
epCfg.uaConfig.userAgent = "Just JSON Test";
jDoc.writeObject(epCfg);
jDoc.saveFile("jsontest.json");
```

To load from the file:

```
EpConfig epCfg;
JsonDocument jDoc;
jDoc.loadFile("jsontest.json");
jDoc.readObject(epCfg);
```

## C++
Below is a sample application that initializes the library, creates an account, registers to our pjsip.org SIP server, and quit.

```
#include <pjsua2.hpp>
#include <iostream>

using namespace pj;

// Subclass to extend the Account and get notifications etc.
class MyAccount : public Account {
public:
    virtual void onRegState(OnRegStateParam &prm) {
        AccountInfo ai = getInfo();
        std::cout << (ai.regIsActive? "*** Register:" : "*** Unregister:")
                  << " code=" << prm.code << std::endl;
    }
};

int main()
{
    Endpoint ep;

    ep.libCreate();

    // Initialize endpoint
    EpConfig ep_cfg;
    ep.libInit( ep_cfg );

    // Create SIP transport. Error handling sample is shown
    TransportConfig tcfg;
    tcfg.port = 5060;
    try {
        ep.transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
    } catch (Error &err) {
        std::cout << err.info() << std::endl;
        return 1;
    }

    // Start the library (worker threads etc)
    ep.libStart();
    std::cout << "*** PJSUA2 STARTED ***" << std::endl;

    // Configure an AccountConfig
    AccountConfig acfg;
    acfg.idUri = "sip:test@sip.pjsip.org";
    acfg.regConfig.registrarUri = "sip:sip.pjsip.org";
    AuthCredInfo cred("digest", "*", "test", 0, "secret");
    acfg.sipConfig.authCreds.push_back( cred );

    // Create the account
    MyAccount *acc = new MyAccount;
    acc->create(acfg);

    // Here we don't have anything else to do..
    pj_thread_sleep(10000);

    // Delete the account. This will unregister from server
    delete acc;

    // This will implicitly shutdown the library
    return 0;
}
```

### Tip
View this file: pjsip-apps/src/samples/pjsua2_hello_reg.cpp

The C++ sample app above is built along with standard build, you can run the executable from pjsip-apps/bin/samples/.. directory.

# The Endpoint
Table of Contents

The Endpoint
* Instantiating the endpoint
* Creating the library
* Initializing and configuring the library
* Creating one or more transports
* Starting the library
* Shutting down the library

The pj::Endpoint class is a singleton class, and application MUST create this class instance before it can do anything else, and similarly, once this class is destroyed, application must NOT call any library API. This class is the core class of PJSUA2, and it provides the following functions:

* Starting up and shutting down
* Customization of configurations, such as core UA (User Agent) SIP configuration, media configuration, and logging configuration

This chapter will describe the functions above.

## Instantiating the endpoint
Before anything else, you must instantiate the Endpoint class:

```
Endpoint *ep = new Endpoint;
```

Once the endpoint is instantiated, you can retrieve the Endpoint instance using pj::Endpoint::instance() static method.

## Creating the library
Create the library by calling its pj::Endpoint::libCreate() method:
```
try {
    ep->libCreate();
} catch(Error& err) {
    cout << "Startup error: " << err.info() << endl;
}
```
The libCreate() method will raise exception if error occurs, so we need to trap the exception using try/catch clause as above. See pj::Error for reference.

## Initializing and configuring the library
The pj::EpConfig class provides endpoint configuration which allows the customization of the following settings:

* pj::UAConfig, to specify core SIP user agent settings.
* pj::MediaConfig, to specify various media global settings
* pj::LogConfig, to customize logging settings.

### Tip
Some settings can be specified on per account basis, in the pj::AccountConfig, when creating an pj::Account. Creating accounts will be explained in next section.

To customize the settings, create instance of EpConfig class and specify them during the endpoint initialization (will be explained more later), for example:
```
EpConfig ep_cfg;
ep_cfg.logConfig.level = 5;
ep_cfg.uaConfig.maxCalls = 4;
ep_cfg.mediaConfig.sndClockRate = 16000;
```

Next, you can initialize the library by calling pj::Endpoint::libInit():

```
try {
    EpConfig ep_cfg;
    // Specify customization of settings in ep_cfg
    ep->libInit(ep_cfg);
} catch(Error& err) {
    cout << "Initialization error: " << err.info() << endl;
}
```
The snippet above initializes the library with the default settings.

## Creating one or more transports
Application needs to create one or more transports before it can send or receive SIP messages:
```
try {
    TransportConfig tcfg;
    tcfg.port = 5060;
    TransportId tid = ep->transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
} catch(Error& err) {
    cout << "Transport creation error: " << err.info() << endl;
}
```
The pj::Endpoint::transportCreate() method returns the newly created Transport ID and it takes the transport type and pj::TransportConfig object to customize the transport settings like bound address and listening port number. Without this, by default the transport will be bound to INADDR_ANY and any available port.

There is no real use of the Transport ID, except to create userless account (with pj::Account::create(), as will be explained later), and perhaps to display the list of transports to user if the application wants it.

## Starting the library
Now we’re ready to start the library. We need to start the library to finalize the initialization phase, e.g. to complete the initial STUN address resolution, initialize/start the sound device, etc. To start the library, call pj::Endpoint::libStart() method:
```
try {
    ep->libStart();
} catch(Error& err) {
    cout << "Startup error: " << err.info() << endl;
}
```

## Shutting down the library
Once the application exits, the library needs to be shutdown so that resources can be released back to the operating system. Although this can be done by deleting the Endpoint instance, which will internally call pj::Endpoint::libDestroy(), it is better to call it manually because on Java or Python there are problems with garbage collection as explained earlier:
```
ep->libDestroy();
delete ep;
```

# Accounts
Table of Contents

Accounts
* Subclassing the Account class
* Creating userless accounts
* Creating account
* Account configurations
* Account operations

Accounts provide identity (or identities) of the user who is currently using the application. Each account has one SIP Uniform Resource Identifier (URI) associated with it. In SIP terms, this URI acts as Address of Record (AOR) of the person and is used in the From header in outgoing requests.

Account may or may not have client registration associated with it. An account is also associated with route-set and some authentication credentials, which are used when sending SIP request messages using the account. An account also has presence status, which will be reported to remote peer when they subscribe to the account’s presence, or which is published to a presence server if presence publication is enabled for the account.

At least one account MUST be created in the application, since any outgoing requests require an account context. If no user association is required, application can create a userless (see Creating userless accounts below). A userless account identifies local endpoint instead of a particular user, and it corresponds to a particular transport ID.

Also one account must be set as the default account, which will be used as the account identity when pjsua fails to match incoming request with any accounts using the stricter matching rules.

## Subclassing the Account class
To use the pj::Account class, normally application SHOULD create its own subclass, in order to receive notifications for the account. For example:
```
class MyAccount : public Account
{
public:
    MyAccount() {}
    ~MyAccount() {}

    virtual void onRegState(OnRegStateParam &prm)
    {
        AccountInfo ai = getInfo();
        cout << (ai.regIsActive? "*** Register: code=" : "*** Unregister: code=")
             << prm.code << endl;
    }

    virtual void onIncomingCall(OnIncomingCallParam &iprm)
    {
        Call *call = new MyCall(*this, iprm.callId);

        // Just hangup for now
        CallOpParam op;
        op.statusCode = PJSIP_SC_DECLINE;
        call->hangup(op);

        // And delete the call
        delete call;
    }
};
```

In the subclass, application can implement the account callbacks to process events related to the account, such as:

* the status of SIP registration
* incoming calls
* incoming presence subscription requests
* incoming instant message not from buddy
Application can override the relevant callback methods in the derived class to handle these particular events.
If the events are not handled, default actions will be invoked:

* incoming calls will not be handled
* incoming presence subscription requests will be accepted
* incoming instant messages from non-buddy will be ignored

## Creating userless accounts
A userless account identifies a particular SIP endpoint rather than a particular user. Some other SIP softphones may call this peer-to-peer mode, which means that we are calling another computer via its address rather than calling a particular user ID. For example, we might identify ourselves as “sip:192.168.0.15” (a userless account) rather than, say, “sip:alice@pjsip.org”.

In the lower layer PJSUA-LIB API, a userless account is associated with a SIP transport, and is created with pjsua_acc_add_local() API. This concept has been deprecated in PJSUA2, and rather, a userless account is a “normal” account with a userless ID URI (e.g. “sip:192.168.0.15”) and without registration. Thus creating a userless account is exactly the same as creating “normal” account.

## Creating account
Configure pj::AccountConfig and call pj::Account::create() to create the account. At the very minimum, only account ID is required, which is an URI to identify the account. Note that the URI can also be enclosed in name-addr form ([ display-name ] <SIP/SIPS URI>) (this is also applicable for all URI parameters used in PJSIP library, such as when making a call, adding a buddy, etc). Below is an example:
```
AccountConfig acc_cfg;
acc_cfg.idUri = "sip:test1@pjsip.org";
// This is also valid
// acc_cfg.idUri = "Test <sip:test1@pjsip.org>";

MyAccount *acc = new MyAccount;
try {
    acc->create(acc_cfg);
} catch(Error& err) {
    cout << "Account creation error: " << err.info() << endl;
}
```

The account created above doesn’t do anything except to provide identity in the “From:” header for outgoing requests. The account will not register to SIP server.

In order to register to a SIP server, we will need to configure some more settings in pj::AccountConfig, something like this:
```
AccountConfig acc_cfg;
acc_cfg.idUri = "sip:test1@pjsip.org";
acc_cfg.regConfig.registrarUri = "sip:pjsip.org";
acc_cfg.sipConfig.authCreds.push_back( AuthCredInfo("digest", "*", "test1", 0, "secret1") );

MyAccount *acc = new MyAccount;
try {
    acc->create(acc_cfg);
} catch(Error& err) {
    cout << "Account creation error: " << err.info() << endl;
}
```
## Account configurations
More settings can be specified in pj::AccountConfig:

* pj::AccountRegConfig, the registration settings, such as registrar server and retry interval.
* pj::AccountSipConfig, the SIP settings, such as credential information and proxy server.
* pj::AccountCallConfig, the call settings, such as whether reliable provisional response (SIP 100rel) is required.
* pj::AccountPresConfig, the presence settings, such as whether presence publication (PUBLISH) is enabled.
* pj::AccountMwiConfig, the MWI (Message Waiting Indication) settings.
* pj::AccountNatConfig, the NAT settings, such as whether STUN or ICE is used.
* pj::AccountMediaConfig, the media settings, such as Secure RTP (SRTP) related settings.
* pj::AccountVideoConfig, the video settings, such as default capture and render device.
* pj::AccountIpChangeConfig, the settings during IP change.

## Account operations
Some of the operations to the pj::Account object:

* manage registration
* manage buddies/contacts
* manage presence online status

Please see the reference documentation for pj::Account for more info. Calls, presence, and buddy will be explained in later chapters.


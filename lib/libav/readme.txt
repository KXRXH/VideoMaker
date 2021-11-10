You can download libav library from: http://builds.libav.org/windows/release-gpl/libav-11.3-win64.7z
Then put bin, include, lib and share folders into readme file's folder and to Qt libs folder (example: C:\Qt\6.2.1\mingw81_64)
It will be looks like:
lib
└───libav
    ├───bin
    ├───include
    │   ├───libavcodec
    │   ├───libavdevice
    │   ├───libavfilter
    │   ├───libavformat
    │   ├───libavutil
    │   └───libswscale
    ├───lib
    │   └───pkgconfig
    └───share
        └───avconv

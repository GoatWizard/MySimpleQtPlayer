#TEMPLATE = lib

INCLUDEPATH += $$PWD/out
INCLUDEPATH += $$PWD/taglib
INCLUDEPATH += $$PWD/taglib/it
INCLUDEPATH += $$PWD/taglib/xm
INCLUDEPATH += $$PWD/taglib/ape
INCLUDEPATH += $$PWD/taglib/asf
INCLUDEPATH += $$PWD/taglib/flac
INCLUDEPATH += $$PWD/taglib/mp4
INCLUDEPATH += $$PWD/taglib/mpc
INCLUDEPATH += $$PWD/taglib/s3m
INCLUDEPATH += $$PWD/taglib/mod
INCLUDEPATH += $$PWD/taglib/mpeg
INCLUDEPATH += $$PWD/taglib/ogg
INCLUDEPATH += $$PWD/taglib/ogg/opus
INCLUDEPATH += $$PWD/taglib/riff
INCLUDEPATH += $$PWD/taglib/toolkit
INCLUDEPATH += $$PWD/taglib/trueaudio
INCLUDEPATH += $$PWD/taglib/wavpack
INCLUDEPATH += $$PWD/taglib/mpeg/id3v1
INCLUDEPATH += $$PWD/taglib/mpeg/id3v2
INCLUDEPATH += $$PWD/taglib/mpeg/id3v2/frames
INCLUDEPATH += $$PWD/taglib/ogg/flac
INCLUDEPATH += $$PWD/taglib/ogg/speex
INCLUDEPATH += $$PWD/taglib/ogg/vorbis
INCLUDEPATH += $$PWD/taglib/riff/aiff
INCLUDEPATH += $$PWD/taglib/riff/wav

HEADERS += $$PWD/taglib/ape/apefile.h
HEADERS += $$PWD/taglib/ape/apefooter.h
HEADERS += $$PWD/taglib/ape/apeitem.h
HEADERS += $$PWD/taglib/ape/apeproperties.h
HEADERS += $$PWD/taglib/ape/apetag.h
HEADERS += $$PWD/taglib/asf/asfattribute.h
HEADERS += $$PWD/taglib/asf/asffile.h
HEADERS += $$PWD/taglib/asf/asfpicture.h
HEADERS += $$PWD/taglib/asf/asfproperties.h
HEADERS += $$PWD/taglib/asf/asftag.h
HEADERS += $$PWD/taglib/asf/asfutils.h
HEADERS += $$PWD/taglib/audioproperties.h
HEADERS += $$PWD/taglib/fileref.h
HEADERS += $$PWD/taglib/flac/flacfile.h
HEADERS += $$PWD/taglib/flac/flacmetadatablock.h
HEADERS += $$PWD/taglib/flac/flacpicture.h
HEADERS += $$PWD/taglib/flac/flacproperties.h
HEADERS += $$PWD/taglib/flac/flacunknownmetadatablock.h
HEADERS += $$PWD/taglib/headers
HEADERS += $$PWD/taglib/it/itfile.h
HEADERS += $$PWD/taglib/it/itproperties.h
HEADERS += $$PWD/taglib/mod/modfile.h
HEADERS += $$PWD/taglib/mod/modfilebase.h
HEADERS += $$PWD/taglib/mod/modfileprivate.h
HEADERS += $$PWD/taglib/mod/modproperties.h
HEADERS += $$PWD/taglib/mod/modtag.h
HEADERS += $$PWD/taglib/mp4/mp4atom.h
HEADERS += $$PWD/taglib/mp4/mp4coverart.h
HEADERS += $$PWD/taglib/mp4/mp4file.h
HEADERS += $$PWD/taglib/mp4/mp4item.h
HEADERS += $$PWD/taglib/mp4/mp4properties.h
HEADERS += $$PWD/taglib/mp4/mp4tag.h
HEADERS += $$PWD/taglib/mpc/mpcfile.h
HEADERS += $$PWD/taglib/mpc/mpcproperties.h
HEADERS += $$PWD/taglib/mpeg/id3v1/id3v1genres.h
HEADERS += $$PWD/taglib/mpeg/id3v1/id3v1tag.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/attachedpictureframe.cpp
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/attachedpictureframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/chapterframe.cpp
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/chapterframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/commentsframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/eventtimingcodesframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/ownershipframe.cpp
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/ownershipframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/popularimeterframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/privateframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/relativevolumeframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/synchronizedlyricsframe.cpp
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/synchronizedlyricsframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/tableofcontentsframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/textidentificationframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/unknownframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.cpp
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/frames/urllinkframe.h
HEADERS += $$PWD/taglib/mpeg/id3v2/id3v2extendedheader.cpp
HEADERS += $$PWD/taglib/mpeg/id3v2/id3v2extendedheader.h
HEADERS += $$PWD/taglib/mpeg/id3v2/id3v2footer.h
HEADERS += $$PWD/taglib/mpeg/id3v2/id3v2frame.h
HEADERS += $$PWD/taglib/mpeg/id3v2/id3v2framefactory.h
HEADERS += $$PWD/taglib/mpeg/id3v2/id3v2header.cpp
HEADERS += $$PWD/taglib/mpeg/id3v2/id3v2header.h
HEADERS += $$PWD/taglib/mpeg/id3v2/id3v2synchdata.cpp
HEADERS += $$PWD/taglib/mpeg/id3v2/id3v2synchdata.h
HEADERS += $$PWD/taglib/mpeg/id3v2/id3v2tag.h
HEADERS += $$PWD/taglib/mpeg/mpegfile.h
HEADERS += $$PWD/taglib/mpeg/mpegheader.cpp
HEADERS += $$PWD/taglib/mpeg/mpegheader.h
HEADERS += $$PWD/taglib/mpeg/mpegproperties.h
HEADERS += $$PWD/taglib/mpeg/xingheader.cpp
HEADERS += $$PWD/taglib/mpeg/xingheader.h
HEADERS += $$PWD/taglib/ogg/flac/oggflacfile.h
HEADERS += $$PWD/taglib/ogg/oggfile.h
HEADERS += $$PWD/taglib/ogg/oggpage.h
HEADERS += $$PWD/taglib/ogg/oggpageheader.cpp
HEADERS += $$PWD/taglib/ogg/oggpageheader.h
HEADERS += $$PWD/taglib/ogg/opus/opusfile.h
HEADERS += $$PWD/taglib/ogg/opus/opusproperties.h
HEADERS += $$PWD/taglib/ogg/speex/speexfile.h
HEADERS += $$PWD/taglib/ogg/speex/speexproperties.h
HEADERS += $$PWD/taglib/ogg/vorbis/vorbisfile.h
HEADERS += $$PWD/taglib/ogg/vorbis/vorbisproperties.h
HEADERS += $$PWD/taglib/ogg/xiphcomment.cpp
HEADERS += $$PWD/taglib/ogg/xiphcomment.h
HEADERS += $$PWD/taglib/riff/aiff/aifffile.h
HEADERS += $$PWD/taglib/riff/aiff/aiffproperties.h
HEADERS += $$PWD/taglib/riff/rifffile.h
HEADERS += $$PWD/taglib/riff/wav/infotag.h
HEADERS += $$PWD/taglib/riff/wav/wavfile.h
HEADERS += $$PWD/taglib/riff/wav/wavproperties.h
HEADERS += $$PWD/taglib/s3m/s3mfile.h
HEADERS += $$PWD/taglib/s3m/s3mproperties.h
HEADERS += $$PWD/taglib/tag.h
HEADERS += $$PWD/taglib/taglib_config.h.cmake
HEADERS += $$PWD/taglib/taglib_export.h
HEADERS += $$PWD/taglib/tagunion.h
HEADERS += $$PWD/taglib/toolkit/taglib.h
HEADERS += $$PWD/taglib/toolkit/tbytevector.h
HEADERS += $$PWD/taglib/toolkit/tbytevectorlist.h
HEADERS += $$PWD/taglib/toolkit/tbytevectorstream.h
HEADERS += $$PWD/taglib/toolkit/tdebug.h
HEADERS += $$PWD/taglib/toolkit/tdebuglistener.h
HEADERS += $$PWD/taglib/toolkit/tfile.h
HEADERS += $$PWD/taglib/toolkit/tfilestream.h
HEADERS += $$PWD/taglib/toolkit/tiostream.h
HEADERS += $$PWD/taglib/toolkit/tlist.h
HEADERS += $$PWD/taglib/toolkit/tmap.h
HEADERS += $$PWD/taglib/toolkit/tpropertymap.h
HEADERS += $$PWD/taglib/toolkit/trefcounter.h
HEADERS += $$PWD/taglib/toolkit/tstring.h
HEADERS += $$PWD/taglib/toolkit/tstringlist.h
HEADERS += $$PWD/taglib/toolkit/tutils.h
HEADERS += $$PWD/taglib/toolkit/unicode.h
HEADERS += $$PWD/taglib/trueaudio/trueaudiofile.h
HEADERS += $$PWD/taglib/trueaudio/trueaudioproperties.h
HEADERS += $$PWD/taglib/wavpack/wavpackfile.h
HEADERS += $$PWD/taglib/wavpack/wavpackproperties.h
HEADERS += $$PWD/taglib/xm/xmfile.h
HEADERS += $$PWD/taglib/xm/xmproperties.h


SOURCES += $$PWD/taglib/ape/apefile.cpp
SOURCES += $$PWD/taglib/ape/apefooter.cpp
SOURCES += $$PWD/taglib/ape/apeitem.cpp
SOURCES += $$PWD/taglib/ape/apeproperties.cpp
SOURCES += $$PWD/taglib/ape/apetag.cpp
SOURCES += $$PWD/taglib/asf/asfattribute.cpp
SOURCES += $$PWD/taglib/asf/asffile.cpp
SOURCES += $$PWD/taglib/asf/asfpicture.cpp
SOURCES += $$PWD/taglib/asf/asfproperties.cpp
SOURCES += $$PWD/taglib/asf/asftag.cpp
SOURCES += $$PWD/taglib/audioproperties.cpp
SOURCES += $$PWD/taglib/fileref.cpp
SOURCES += $$PWD/taglib/flac/flacfile.cpp
SOURCES += $$PWD/taglib/flac/flacmetadatablock.cpp
SOURCES += $$PWD/taglib/flac/flacpicture.cpp
SOURCES += $$PWD/taglib/flac/flacproperties.cpp
SOURCES += $$PWD/taglib/flac/flacunknownmetadatablock.cpp
SOURCES += $$PWD/taglib/it/itfile.cpp
SOURCES += $$PWD/taglib/it/itproperties.cpp
SOURCES += $$PWD/taglib/mod/modfile.cpp
SOURCES += $$PWD/taglib/mod/modfilebase.cpp
SOURCES += $$PWD/taglib/mod/modproperties.cpp
SOURCES += $$PWD/taglib/mod/modtag.cpp
SOURCES += $$PWD/taglib/mp4/mp4atom.cpp
SOURCES += $$PWD/taglib/mp4/mp4coverart.cpp
SOURCES += $$PWD/taglib/mp4/mp4file.cpp
SOURCES += $$PWD/taglib/mp4/mp4item.cpp
SOURCES += $$PWD/taglib/mp4/mp4properties.cpp
SOURCES += $$PWD/taglib/mp4/mp4tag.cpp
SOURCES += $$PWD/taglib/mpc/mpcfile.cpp
SOURCES += $$PWD/taglib/mpc/mpcproperties.cpp
SOURCES += $$PWD/taglib/mpeg/id3v1/id3v1genres.cpp
SOURCES += $$PWD/taglib/mpeg/id3v1/id3v1tag.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/attachedpictureframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/chapterframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/commentsframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/eventtimingcodesframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/ownershipframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/popularimeterframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/privateframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/relativevolumeframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/synchronizedlyricsframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/tableofcontentsframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/textidentificationframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/unknownframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/frames/urllinkframe.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/id3v2extendedheader.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/id3v2footer.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/id3v2frame.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/id3v2framefactory.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/id3v2header.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/id3v2synchdata.cpp
SOURCES += $$PWD/taglib/mpeg/id3v2/id3v2tag.cpp
SOURCES += $$PWD/taglib/mpeg/mpegfile.cpp
SOURCES += $$PWD/taglib/mpeg/mpegheader.cpp
SOURCES += $$PWD/taglib/mpeg/mpegproperties.cpp
SOURCES += $$PWD/taglib/mpeg/xingheader.cpp
SOURCES += $$PWD/taglib/ogg/flac/oggflacfile.cpp
SOURCES += $$PWD/taglib/ogg/oggfile.cpp
SOURCES += $$PWD/taglib/ogg/oggpage.cpp
SOURCES += $$PWD/taglib/ogg/oggpageheader.cpp
SOURCES += $$PWD/taglib/ogg/opus/opusfile.cpp
SOURCES += $$PWD/taglib/ogg/opus/opusproperties.cpp
SOURCES += $$PWD/taglib/ogg/speex/speexfile.cpp
SOURCES += $$PWD/taglib/ogg/speex/speexproperties.cpp
SOURCES += $$PWD/taglib/ogg/vorbis/vorbisfile.cpp
SOURCES += $$PWD/taglib/ogg/vorbis/vorbisproperties.cpp
SOURCES += $$PWD/taglib/ogg/xiphcomment.cpp
SOURCES += $$PWD/taglib/riff/aiff/aifffile.cpp
SOURCES += $$PWD/taglib/riff/aiff/aiffproperties.cpp
SOURCES += $$PWD/taglib/riff/rifffile.cpp
SOURCES += $$PWD/taglib/riff/wav/infotag.cpp
SOURCES += $$PWD/taglib/riff/wav/wavfile.cpp
SOURCES += $$PWD/taglib/riff/wav/wavproperties.cpp
SOURCES += $$PWD/taglib/s3m/s3mfile.cpp
SOURCES += $$PWD/taglib/s3m/s3mproperties.cpp
SOURCES += $$PWD/taglib/tag.cpp
SOURCES += $$PWD/taglib/tagunion.cpp
SOURCES += $$PWD/taglib/toolkit/tbytevector.cpp
SOURCES += $$PWD/taglib/toolkit/tbytevectorlist.cpp
SOURCES += $$PWD/taglib/toolkit/tbytevectorstream.cpp
SOURCES += $$PWD/taglib/toolkit/tdebug.cpp
SOURCES += $$PWD/taglib/toolkit/tdebuglistener.cpp
SOURCES += $$PWD/taglib/toolkit/tfile.cpp
SOURCES += $$PWD/taglib/toolkit/tfilestream.cpp
SOURCES += $$PWD/taglib/toolkit/tiostream.cpp
SOURCES += $$PWD/taglib/toolkit/tpropertymap.cpp
SOURCES += $$PWD/taglib/toolkit/trefcounter.cpp
SOURCES += $$PWD/taglib/toolkit/tstring.cpp
SOURCES += $$PWD/taglib/toolkit/tstringlist.cpp
SOURCES += $$PWD/taglib/toolkit/unicode.cpp
SOURCES += $$PWD/taglib/trueaudio/trueaudiofile.cpp
SOURCES += $$PWD/taglib/trueaudio/trueaudioproperties.cpp
SOURCES += $$PWD/taglib/wavpack/wavpackfile.cpp
SOURCES += $$PWD/taglib/wavpack/wavpackproperties.cpp
SOURCES += $$PWD/taglib/xm/xmfile.cpp
SOURCES += $$PWD/taglib/xm/xmproperties.cpp

HEADERS += $$PWD/out/config.h
HEADERS += $$PWD/out/taglib_config.h

DEFINES += MAKE_TAGLIB_LIB
DEFINES += WITH_ASF
DEFINES += WITH_MP4

#QT -= gui

#CONFIG(debug, debug|release) {
#    DEFINES += _DEBUG
#    DESTDIR = ../taglib-debug
#    OBJECTS_DIR = ./debug-o
#} else {
#    DESTDIR = ../taglib-release
#    OBJECTS_DIR = ./release-o
#}

#win32 {
#    CONFIG += dll
#}

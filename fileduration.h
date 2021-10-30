#ifndef FILEDURATION_H
#define FILEDURATION_H

extern "C"{
    #include <libavformat/avformat.h>
}

// Getting video duration with using libav library.
void getVideoDuration(char* filename, int& duration)
{
    av_register_all();
    //-------------------------------------------------------------------------------------------------------//
    AVFormatContext* pFormatCtx = avformat_alloc_context();
    avformat_open_input(&pFormatCtx, filename, NULL, NULL);
    avformat_find_stream_info(pFormatCtx,NULL);
    duration = (int)pFormatCtx->duration / 1000000; // Getting duration and transfer it from microseconds to seconds.
    avformat_close_input(&pFormatCtx);
    //-------------------------------------------------------------------------------------------------------//
    // Memory cleaning.
    av_free(pFormatCtx);
}

#endif // FILEDURATION_H

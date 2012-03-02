#ifndef IMAGEDECODERFACTORY_H_
#define IMAGEDECODERFACTORY_H_

#include <dukeio/ImageDescription.h>

#include <vector>
#include <string>

typedef void* FormatHandle;

/**
 * Interface to load and decode images.
 */
struct ImageDecoderFactory {
    /**
     * Will return a per thread instance of the image decoder
     * NULL if no decoder found for this format
     */
    virtual FormatHandle getImageDecoder(const char* extension, bool &delegateRead, bool &isFormatUncompressed) const = 0;

    virtual bool readImageHeader(FormatHandle decoder, const char* filename, ImageDescription& description) const = 0;

    virtual bool decodeImage(FormatHandle decoder, const ImageDescription& description) const = 0;

    virtual const char** getAvailableExtensions() const = 0;

    virtual void dumpDecoderInfos() const = 0;

    virtual ~ImageDecoderFactory() = 0;
};

#endif /* IMAGEDECODERFACTORY_H_ */
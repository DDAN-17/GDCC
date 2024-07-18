#ifndef localization_h
#define localization_h

#ifndef LOCALE
#warning "No locale selected, falling back to en_US.UTF-8"
#define LOCALE en_US
#endif

#if LOCALE == en_US
#define NO_INPUT_FILE_ERR "No input file."
#endif

#if LOCALE == el_GR
#define NO_INPUT_FILE_ERR "Input file none."
#endif

#endif
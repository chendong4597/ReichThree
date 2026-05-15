LOCAL_PATH := $(call my-dir)/../../../../external/libanl/source
include $(CLEAR_VARS)
LOCAL_MODULE := libanl

LOCAL_MODULE_FILENAME := libanl

LOCAL_SRC_FILES := arrayoperations.cpp \
cellulargen.cpp \
hsv.cpp \
implicitautocorrect.cpp \
implicitbasisfunction.cpp \
implicitbias.cpp \
implicitblend.cpp \
implicitbrightcontrast.cpp \
implicitcache.cpp \
implicitcellular.cpp \
implicitclamp.cpp \
implicitcombiner.cpp \
implicitconstant.cpp \
implicitcos.cpp \
implicitcurve.cpp \
implicitextractrgbachannel.cpp \
implicitfloor.cpp \
implicitfractal.cpp \
implicitfunctiongradient.cpp \
implicitgain.cpp \
implicitgradient.cpp \
implicitmagnitude.cpp \
implicitmodulebase.cpp \
implicitnormalizecoords.cpp \
implicitpow.cpp \
implicitrgbadotproduct.cpp \
implicitrotatedomain.cpp \
implicitsawtooth.cpp \
implicitscaledomain.cpp \
implicitscaleoffset.cpp \
implicitselect.cpp \
implicitsin.cpp \
implicitsphere.cpp \
implicittiers.cpp \
implicittranslatedomain.cpp \
implicittriangle.cpp \
mapping.cpp \
noise_gen.cpp \
noise_lut.cpp \
rasterization.cpp \
rgbablend.cpp \
rgbablendops.cpp \
rgbacolorops.cpp \
rgbacomposechannels.cpp \
rgbaconstant.cpp \
rgbacurve.cpp \
rgbahsvtorgba.cpp \
rgbaimplicitgrayscale.cpp \
rgbanormalize.cpp \
rgbargbatohsv.cpp \
rgbarotatecolor.cpp \
rgbaselect.cpp \
implicitRandomMapGenerator.cpp \

LOCAL_STATIC_LIBRARIES = 

LOCAL_EXPORT_C_INCLUDE := $(LOCAL_PATH)
LOCAL_SHORT_COMMANDS := true
include $(BUILD_STATIC_LIBRARY)

# Change this Variables for your project
# TEMPLATE can be 'app' for application, 'so' for shared library, 'ar' for static library
TARGET = curl
TEMPLATE = app

SOURCES += \
./src/curl.cpp

INCLUDEPATH += ./src/

# MiddleWare Header
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/config/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/lib_config/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/hal/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/osal/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/vmf_client/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/vmf_trace/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/power_agent/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/audio/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/KeyControl/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/pss/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/tuner_proxy/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/vr_client/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/pss/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/Diagnostics/include
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/lib_config/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/config/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/osal/include/
INCLUDEPATH += ./../../ai-sdk-forMiddleware-NGI/mediainclude



# Library
LIBS += -L./../../ai-sdk-forMiddleware-NGI/lib_config/lib/ -lCONFIG
LIBS += -L./../../ai-sdk-forMiddleware-NGI/hal/lib/ -lHAL
LIBS += -L./../../ai-sdk-forMiddleware-NGI/osal/lib/ -lOSAL
LIBS += -L./../../ai-sdk-forMiddleware-NGI/vmf_client/lib/ -lvmf_client
LIBS += -L./../../ai-sdk-forMiddleware-NGI/vmf_trace/lib/ -lvmf_trace



#INSTALL_DIR		:= ../../ai-sdk-forMiddleware-NGI/EOL/
#DEPLOY_TARGET_DIR	:= /home/zero/nfs/rootfs/opt


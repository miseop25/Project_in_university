KDIR :=/work/achroimx6q/kernel
PWD :=$(shell pwd)

all: app

app:
	arm-none-linux-gnueabi-gcc -I/root/work/include -L/root/work/lib cv_test.c -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -lrt -lpthread -lm -ldl -o cv_test
install:
	cp -a cv_test /nfsroot
clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf *.o
	rm -rf cv_test
	rm -rf Module.symvers
	rm -rf modules.order
	rm -rf .fnd*
	rm -rf .tmp*

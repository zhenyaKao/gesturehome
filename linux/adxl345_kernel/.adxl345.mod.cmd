cmd_/root/adxl345/adxl345_kernel/adxl345.mod := printf '%s\n'   adxl345.o | awk '!x[$$0]++ { print("/root/adxl345/adxl345_kernel/"$$0) }' > /root/adxl345/adxl345_kernel/adxl345.mod

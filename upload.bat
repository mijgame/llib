mode com2:1200

timeout 1

"C:\ti-software\bmptk\tools\bmptk-bossac.exe" -p com2 -U false -e -v -w -b cmake-build-debug/llib.bin -R
"C:\ti-software\bmptk\tools\lpc21isp_197\lpc21isp_hr.exe" -termonly com2 115200 12000
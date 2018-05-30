#check code is new enough
filename=`pwd`"/"`find -name p4_changelist.h`
clnumber=`awk 'NR==1' $filename | cut -d' ' -f2`
isfail=$(($clnumber <1428283))
if [ "$isfail" -eq "1" ]; then 
    echo Please get code newer then CL1428283!
    exit
fi

function changedir(){
  cd ..
}
function changedirback(){
  cd -
}

#you need to give info in format bellow
#toolchain=/tools/arm/MStar/linaro-aarch64_linux-2014.09_843419-patched/bin
#config=.config_manhattan_SMP_arm64_andorid_emmc_nand
#platform=arm64

echo Please specify configuration you need:
read config
echo $config

echo Please specify target toolchain path:
read toolchain
echo $toolchain


echo Please specify platform, e.g. arm, arm64:
read platform
echo $platform


#build
export PATH=$toolchain:$PATH
#`echo $PATH`
changedir
chmod 777 -R ./;
changedirback
cp $config .config
cp $config arch/$platform/configs/mstar_config
./genlink.sh
choice=`grep MSTAR_CHIP_NAME $config | awk -F\" '{print$2}'`
cp -rf ./mstar2/hal/$choice/ ./mstar2/drv/$choice
rm -rf ./mstar2/hal/*
cp -rf ./mstar2/drv/$choice/ ./mstar2/hal/
rm -rf ./mstar2/drv/$choice
rm -rf arch/Kconfig.kdebug
rm -rf kernel/kdebugd/
cp arch/$platform/Kconfig_no_kdebug arch/$platform/Kconfig
cp kernel/Makefile_no_kdebug kernel/Makefile
make defconfig KBUILD_DEFCONFIG=mstar_config > log.txt 2>&1
make clean
make -j40
echo -e "\e[1;31mKernel building is complete.\e[0m"


#retrieve mhal_dlc.o
changedir
if [[ ! -z `find -name mhal_dlc.o` ]] ; then
   echo -e "\e[1;31mmhal_dlc.o is found.\e[0m"
   find . -name 'mhal_dlc.o' -exec rename 's/mhal_dlc.o/mhal_dlc.x/g' {} \;
else
   echo -e "\e[1;31mmhal_dlc.o is NOT found. Check your env plz.\e[0m"
   exit
fi ;


changedirback
make clean
changedir
find . -name 'mhal_dlc.x' -exec rename 's/mhal_dlc.x/mhal_dlc.o/g' {} \;
#remove LGPL file
find . -name "mhal_dlc.c" -exec rm -rf {} \;
echo -e "\e[1;31mRelease content is ready.\e[0m"


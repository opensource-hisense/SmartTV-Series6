#check code is new enough
filename=`pwd`"/"`find -name p4_changelist.h`
clnumber=`awk 'NR==1' $filename | cut -d' ' -f2`
#isfail=$(($clnumber <1428283))
#if [ "$isfail" -eq "1" ]; then 
#    echo Please get code newer then CL1428283!
#    exit
#fi

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
#changedir
#chmod 777 -R ./;
#changedirback
cp $config .config;
cp $config arch/$platform/configs/mstar_config;
cp $config ./mstar2/;

./genlink.sh
choice=`grep MSTAR_CHIP_NAME .config | awk -F\" '{print$2}'`


echo $choice
echo $choice
echo $choice
echo $choice
echo $choice

rm -rf arch/Kconfig.kdebug
rm -rf kernel/kdebugd/
cp arch/arm/Kconfig_no_kdebug arch/arm/Kconfig
cp arch/arm64/Kconfig_no_kdebug arch/arm64/Kconfig
cp kernel/Makefile_no_kdebug kernel/Makefile
make defconfig KBUILD_DEFCONFIG=mstar_config > log.txt 2>&1;
make clean
make -j32
echo -e "\e[1;31mKernel building is complete.\e[0m"


#retrieve mhal_dlc.o
#changedir
if [[ ! -z `find -name mhal_dlc.o` ]] ; then
   echo -e "\e[1;31mmhal_dlc.o is found.\e[0m"
   find . -name 'mhal_dlc.o' -exec rename 's/mhal_dlc.o/mhal_dlc.x/g' {} \;
else
   echo -e "\e[1;31mmhal_dlc.o is NOT found. Check your env plz.\e[0m"
   exit
fi ;



#changedirback


echo Do you want to release other configuration yes/1 , no/0:
read second_configuration
if [ $second_configuration = "1" ] ;then

make clean

echo Please specify configuration you need:
read config1
echo $config1

echo Please specify target toolchain1 path:
read toolchain1
echo $toolchain1


echo Please specify platform, e.g. arm, arm64:
read platform1
echo $platform1



#build
export PATH=$toolchain1:$PATH
#`echo $PATH`
#changedir
#chmod 777 -R ./;
#changedirback
cp $config1 .config;
cp $config1 arch/$platform1/configs/mstar_config;
cp $config1 ./mstar2/;

choice1=`grep MSTAR_CHIP_NAME .config | awk -F\" '{print$2}'`

echo $choice1
echo $choice1
echo $choice1
echo $choice1
echo $choice1

make defconfig KBUILD_DEFCONFIG=mstar_config > log.txt 2>&1;
make clean
make -j32
echo -e "\e[1;31mKernel building is complete.\e[0m"

#retrieve mhal_dlc.o
#changedir
if [[ ! -z `find -name mhal_dlc.o` ]] ; then
   echo -e "\e[1;31mmhal_dlc.o is found.\e[0m"
   find . -name 'mhal_dlc.o' -exec rename 's/mhal_dlc.o/mhal_dlc.x/g' {} \;
else
   echo -e "\e[1;31mmhal_dlc.o is NOT found. Check your env plz.\e[0m"
   exit
fi ;

else

echo -e " ok ,Only one configuration "

fi ;



rm -rf .config*
cp -rf ./mstar2/.config* ./
rm -rf ./mstar2/.config*


cp -rf ./mstar2/hal/$choice/ ./mstar2/drv/$choice

if [ $second_configuration = "1" ] ;then
cp -rf ./mstar2/hal/$choice1/ ./mstar2/drv/$choice1
fi ;

rm -rf ./mstar2/hal/*
cp -rf ./mstar2/drv/$choice/ ./mstar2/hal/
cp -rf ./mstar2/drv/$choice/ ./mstar2/hal/

rm -rf ./mstar2/drv/$choice

if [ $second_configuration = "1" ] ;then
rm -rf ./mstar2/drv/$choice1s
fi ;

#changedir
#find . -name 'mhal_dlc.x' -exec rename 's/mhal_dlc.x/mhal_dlc.o/g' {} \;
#remove LGPL file

find . -name "mhal_dlc.c" -exec rm -rf {} \;
find -type d -name *.git | xargs rm -rf
find -name *.git* | xargs rm -rf
echo -e "\e[1;31mRelease content is ready.\e[0m"


## Build Client Server Example:
```shell
mkdir build
cd build
cmake ..
make
```

## install systemtap

### use apt
sudo apt install systemtap

### from source
```shell
sudo apt install elfutils libdw-dev gettext
git clone http://sourceware.org/git/systemtap.git
cd systemtap
./configure
make -j $(nproc)
sudo make install
```

## Setup systemtap
add 'source' to apt source list
```shell
echo "deb http://ddebs.ubuntu.com $(lsb_release -cs) main restricted universe multiverse" | sudo tee -a /etc/apt/sources.list.d/ddebs.list
echo -e "deb http://ddebs.ubuntu.com $(lsb_release -cs)-updates main restricted universe multiverse\ndeb http://ddebs.ubuntu.com $(lsb_release -cs)-proposed main restricted universe multiverse" | sudo tee -a /etc/apt/sources.list.d/ddebs.list
sudo apt update
sudo apt-get install pkg-config-dbgsym
sudo apt-get install libncurses-dev gawk flex bison openssl libssl-dev dkms libelf-dev libudev-dev libpci-dev libiberty-dev autoconf zfs-dkms kernel-wedge
apt-get source linux-image-unsigned-$(uname -r)
cd linux-hwe-5.11-5.11.0
LANG=C fakeroot debian/rules clean
AUTOBUILD=1 fakeroot debian/rules binary-generic skipdbg=false
sudo dpkg -i ../linux-image-unsigned-5.11.0-38-generic-dbgsym_5.11.0-38.42~20.04.1_amd64.ddeb
sudo apt-get install linux-image-$(uname -r)-dbgsym
sudo stap-prep
```

## Check install
```shell
sudo stap -v -e 'probe vfs.read {printf("read performed\n"); exit()}'

```
1.项目介绍

* qemu可以模拟vexpress arm开发板，本项目在qemu里面为这款开发板实现了一个虚拟网卡硬件，并为其开发linux网卡驱动程序。

* 这套虚拟网卡硬件及驱动支持如下特性：NAPI、multi queue、DMA ring buffer、 scatter I/O、GRO/GSO、IRQ affinity等。

* 借助host NAT转发，在guest里面使用该虚拟网卡可以成功访问了互联网。

* 交叉编译了iperf工具放进开发板进行了一番性能测试，qemu可以模拟的vexpress arm开发板原有的虚拟网卡TCP TX极限性能大概80 Mbits/sec，RX极限性能小于10 Mbits/sec且十分不稳定qemu会报错。这套虚拟网卡硬件及linux网卡驱动在TCP TX/RX极限性能上均超过300Mbits/sec。（具体性能的绝对值肯定跟host相关，毕竟是用qemu模拟的开发板）



2.构建方法(linux x86-64 host)

构建过程中肯定会遇到一些组件的缺失，缺啥百度一下错误信息，然后apt安装

* 编译内核

  ```
  source env.sh
  cd linux-6.1.15
  ./build.sh
  ```

* 编译qemu-system-arm，注意在第一次执行build.sh前修改build.sh将configure放开，之后可将其注释掉以加快构建速度。

  ```
  cd qemu
  ./build.sh
  ```

* 构建根文件系统镜像

  ```
  //直接使用已经做好的根文件系统(里面有busybox+iperf)
  cd rootfs
  ./tgz2img.sh
  ```

  如需定制根文件系统可自行编译busybox去构建或直接使用ubuntu base做一个rootfs，考虑到调试时会经常需要重启且软件模拟的arm CPU性能有限，最好选用busybox这样启动最快。

* 编译虚拟网卡驱动（需要内核先编译好），并将ko文件放到nfs文件系统供开发板启动后使用

  ```
  source env.sh
  cd driver
  ./build.sh
  ```



3.使用root权限执行编译出的qemu-system-arm来启动开发板，

```
./run_root.sh
```



4.在开发板中装载驱动

开发板在启动后会利用自带的虚拟网卡dhcp，然后挂载host上的nfs网络文件系统到/mnt/nfs，开发板起来后直接在根目录下执行如下脚本,将host上ko文件通过nfs拷贝到开发板中，然后装载，配置mac ip，最后把开发板自带的虚拟网卡down掉，使用本项目开发的mynet网卡:

```
./install_mynet.sh
```
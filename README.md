## 时间设置误差

RTC示例代码中，`rtc.adjust(DateTime(__DATE__, __TIME__))`的含义是将时间设置为编译时的时间，根据实际烧录结果来看，RTC芯片最后设置的时间要晚于实际时间，我使用 ds1302 时会晚8s,这个误差会随着时间流逝而加大，这其中误差大头来源有编译耗时、烧录耗时、启动耗时、RTC设置耗时。

更换硬件的方式可以换带温度补偿的时钟芯片，那不换硬件的方式呢？肯定是有的。自古以来时间同步一直是一个现实问题，而且是已经被解决的问题，不然导航卫星就乱成一锅粥了。

编译耗时取决于电脑性能，这个提升比较不显著；而烧录耗时倒是可以显著提升，新建一个工程，这个工程只用来设置时间，把无关的代码和库都删除，实际测试上编译后的大小由 16520 B 减小到 4432 字节，代码量减小->体积减小->编译烧录变快->误差减小，实际测试误差由8s减小到5s。

计算机网络时间同步技术原理介绍中的第三小节介绍了单向授时、双向授时、网络时间同步的基本概念。由于没发现RTC如何进行双向授时（电脑也有硬件RTC,那电脑是怎么处理的呢），因此下面处理的是单向授时问题。

这种单向设置RTC的过程中，编译、烧录、启动、设置这些流程是不可避免的，必然会导致时间误差的产生，那么能否测量出这些阶段加起来的误差呢？当然是可以的。比如日常生活中调节时间，就是通过把时间设置的比实际时间快一点点，当两个时间同步的时刻确认设置，这样就完成了一次减小误差并且设置了时间。

现在问题就是如何测量这个误差然后在代码里把误差加上了。其实很简单，运行一次设置时间的代码，记录误差，重复三次，取平均值。然后修改代码，在代码里加上这一个误差即可。在代码里体现为变量 timeDelta 的值，如果时间慢5秒，就把 timeDelta 设置为 5。

# 相关阅读

[Arduino IDE - Get current date at compile time and insert into sketch? 2013.9](https://forum.arduino.cc/t/arduino-ide-get-current-date-at-compile-time-and-insert-into-sketch/184602/6)
> The C and C++ standards mandate that the compilers provide two magic macros that resolve to string literals: DATE gives the time the file was compiled, and TIME gives the current time of day. So you could use:
> 
> const char compile_date[] = __DATE__ " " __TIME__;

[计算机网络时间同步技术原理介绍 idenny 2016-05-24](https://segmentfault.com/a/1190000005337116)

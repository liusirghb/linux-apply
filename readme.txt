readme
1.pipe.c:无名管道通信编程实例

2.fifo_read.c,fifo_write.c:有名管道编程

3.sig_send.c,sig_recv.c:信号编程

4.student1.c,student2.c:信号量互斥编程
解决公告板问题 
student1去公告板写入一段字符，期间休息10s，student2在student1休息期间也写入一串字符，结果导致公告板的信息就是studen1想要表达的，也不是student2想要表达。 
为了防止这种糟糕情况的出现，于是引入了信号量，student1.在未完成写入之前不会释放信号量，student2得不到信号量，就无法使用公告板，从而避免上述情形的出现。

5.consumer.c,producter.c：信号量同步编程
描述了消费者和生产着的关系。

6.shm_read.c,shmwrite.c:共享内存编程

7.pthread.c:多线程编程
两人垒墙问题 
（1）线程1 
创建线程 
等待线程结束 
结束线程 
（2）线程2 
创建线程 
等待线程结束 
结束线程

8.tcp_server.c,tcp_client.c:tcp协议实现客户机与服务器之间通信程序（创建收发进程）

9.udp_server.c,udp_client.c:udp协议实现聊天程序。（创建线程）

10.deamon.c：守护进程编程
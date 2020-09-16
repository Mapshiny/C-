
#设计电子一个签名系统




###采用图片的方式存储用户手写的签名

###用户在终端手写输入签名(可用鼠标模拟手写,界面类似windows画图软件)


###签名使用图片保存(分辨率不低于640*480)


####图片存储格式要求:

* ####图片不允许采用通用的图片格式保存(如bmp/jpg/tiff),需采用自定义格式(格式自主决定).
* ####图片必须采用2色存储,即每个像素点用一个二进制位保存,0代表黑色,1代表白色
* ####保存的图片必须经过无损压缩算法压缩,保证图片占用的存储单元数尽量的小.压缩算法建议采用行程编码进行压缩(压缩算法必须是无损的,不允许用通用的jpg里的离散余弦变换进行压缩.压缩算法必须自己实现,不能用网上的函数库.行程编码的定义参阅互联网.
* ####系统能正确读取保存的电子签名图片并显示出来.
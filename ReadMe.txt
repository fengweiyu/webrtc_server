
1.编译：
	安装boost：
	boost_1_63_0-msvc-14.0-32
		msvc-14.0对应vs2017

	使用vs2017进行编译,打开webrtcgateway目录下的webrtcgateway.sln,配置boost安装路径后即可编译

2.使用：

1).安装python
	为了部署web服务端，即脚本startpythonweb.bat可以运行
2).运行	webrtcgateway.exe
	进入bin目录执行 webrtcgateway.exe
3).运行	webrtc_client
		
3).运行 startpythonweb.bat
	进入webrtchtml目录执行startpythonweb.bat
4).打开浏览器
	打开谷歌浏览器，访问http://localhost/
5). 点击call按钮出图
	
******************************************************************************

1.compile
	before compile,must install cmake,then 
	eg:
	ywf@ywf-pc:/work/workspace/webrtc_with_libnice_and_srtp$ ./build.sh x86
	after make success:
	ywf@ywf-pc:/work/workspace/webrtc_with_libnice_and_srtp/build/x86$ ls webrtc
	webrtc
2.usage	
	./webrtc StunIP StunPort SelfName VideoFile offer/answer
	eg:
	./webrtc 192.168.0.103 8888 ywf555 sintel.h264 answer
 
	
******************************************************************************

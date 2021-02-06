# 移动机器人蒙特卡罗定位和目标点发布与导航

* Turtlebot3的Model需要进行固定`export TURTLEBOT3_MODEL=burger`

* 移动机器人的地图可以自己修改，并通过matlab将pgm格式的图片 转换成矩阵形式并以`dat`格式的文件进行保存。

* 在蒙特卡罗模拟的包中需要对全局变量的格式进行修改

  ```xml
  <node name="pf_localization" pkg="pf_localization"  type="localization_node" output="screen" >
  	<param name="package_path_param" type="string" value="/home/hemingshan/robot-localisation/src/" />
  </node>
  ```

  
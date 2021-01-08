# ros_raspi_motor_control
SG90 controller for ros noetic on raspberrypi
---
2020年ロボットシステム学 課題2の為に作成したリポジトリです。
<br>
サーボモータ(SG90)を任意の角度に動かす事が可能なノードを提供します。課題の都合上publisherノードも含まれていますが、モータを動かすという用途に関してはこのパッケージのsubscriberノードとメッセージを他のパッケージ等から利用して頂く事が可能です。

---
## 動作環境

### OS : ubuntu 20.04 server
### ROS distribution : Noetic Ninjemys

---
## 使用したもの

・ [Raspberry Pi3 model B+](https://www.switch-science.com/catalog/3850/)　× 1

・ [SG90(サーボモータ)](https://akizukidenshi.com/catalog/g/gM-08761/) × 1

・ [メスメスジャンパーピン](https://akizukidenshi.com/catalog/g/gP-03475/) × 3

・ [オスオスジャンパーピン](https://akizukidenshi.com/catalog/g/gP-02932/) × 3


---
## Raspi 3b+とサーボの接続

・[Raspi 3b+のピン配置](https://pinout.xyz/pinout/ground)
### 以下の表に対応する様にサーボとRaspi 3b+を接続する

| サーボ    | ピン        |
|:-----------|:------------|
| オレンジの信号線  | :GPIO 12       |
| 茶色の信号線  | :GND         |
|  赤色の信号線 | :5v Power         |
### オレンジの信号線の所に接続するピンは上記のとは違うGPIOピンでも可能です。その場合は使用方法の欄を参照の上適切な番号をメッセージに設定しpublishして下さい。


---
## デモ動画
https://www.youtube.com/watch?v=tgQEQut9-lM

### サーボが初期位置(0°)に戻った後、40°から-40°まで繰り返し動きます。


---
## インストール方法

パッケージを利用したいworkspaceのsrcフォルダ直下で以下のコマンドを実行してください。

```sh
$ git clone https://github.com/AD58-3104/ros_raspi_motor_control.git
$ cd ..
$ catkin_make
```


---
## 使用方法
上記の方法でcatkin_makeまで終わったのち

```sh
$ roscd ros_raspi_motor_control 
$ cd scripts 
$ chmod +x motor_sub.py 
$ roslaunch ros_raspi_motor_control motor_move.launch
```

を実行してください。

他のパッケージ等からモータを制御する用途で利用したい場合は以下のコマンドでmotor_subノードのみ起動してご利用下さい。
```sh
$ rosrun ros_raspi_motor_control motor_sub.py
```

msgフォルダにて定義されているraspi_servo.msgではpinNumberでSG90のオレンジの信号線に接続されているraspi 3b+のGPIOピン番号を、degreeで目標角度を指定します。topicはRASPI_MOTOR/move_servoです。

---
## ライセンス
[BSD 3-Clause "New" or "Revised" License](https://github.com/AD58-3104/ros_raspi_motor_control/blob/main/COPYING)
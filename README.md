ProjectCARS for SIMVR
-------------
Slightly Mad Studios社が開発をしたレーシングシミュレーションゲーム「Project CARS」にVRライドシミュレータ「SIMVR」を動作させるためのツール・プログラム群。

ProjectCARS - http://www.projectcarsgame.com/  
SIMVR - http://simvr01.com/  

# Console
起動するとProjectCarsのデータをSIMVRに流し続ける。

## 使い方
1. SIMVRとPCを接続する。  
2. Consoleプログラムを起動する。  
3. Project Carsを起動する。  
4. Options -> Visual -> HardwareからShared Memoryを有効にする。  
5. 車を運転できるシーンに遷移するとSIMVRが動作する。

## build方法
[Release](https://github.com/Wizapply/ProjectCarsForSIMVR/releases)からProjectCarsForSIMVR.zipを取得する。  
zipを展開し、ProjectCarsForSIMVR/Console/build/windows_vs2015/ProjectCarsForSIMVR.slnからVisual Studioを起動する。  
ビルド設定をDebug/Releaseのx86にしてビルドするとProjectCarsForSIMVR.exeが生成される。  
動作させるためにはSimvrSDK\bin\x86へのパスを通すかexeと同じディレクトリにsimvr.dllを配置する。  

# Unity
CRESTを起動してこのスクリプトを動作させるとインスペクタからデータの動きを見ることができる。 

CRESTについては[Wiki](https://github.com/Wizapply/ProjectCarsForSIMVR/wiki/CREST)か[公式](https://cars-rest-api.com/)に詳細が書いてある。  

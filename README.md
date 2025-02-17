# IOT_jaeinmoon

## 프로젝트 설명
간단하게 저희 프로젝트를 소개해본다면 재난 상황(**적 포탄 낙하, 지진, 차량 부착 시 교통사고, 함선에 부착 시 좌초상황, 화재상황, 함선과 전차등의 증기실에서 연기가 샐 경우**)에 자동으로 문을 열어 탈출구를 확보하고 비상탈출로와 현 상황을 알려주는 장치입니다.

## 프로젝트 구현 내용
 자세하게 구현한 제품을 소개한다면 전원을 공급해주었을 때 충격 감지 센서, 기울기 센서, 포토 인터럽트와 불꽃 감지 센서와 로 구성된 재난인지 센서 유닛이 작동하게 됩니다. 첫째로 **충격 감지센서는 ‘적 포탄 낙하, 차량 부착 시 교통사고, 함선에 부착 시 좌초상황’을 인지**할 수 있습니다. 둘째로 **기울기 센서는 ‘지진, 함선의 위기상황’ 등을 인식**할 수 있습니다. 셋째로 **포토 인터럽트**의 경우 현재 자욱해진 연기가 적외선 라인을 차단시킬 경우 작동하며, 향후 연기 감지 센서로 대체될 예정입니다. 이는 **‘화재상황, 함선과 전차등의 증기실에서 연기가 샐 경우’ 등을 인지**할 수 있습니다. 마지막으로 **불꽃 감지 센서는 화재 상황을 인식**할 수 있습니다.
 각각의 센서들은 4자리 수의 세그먼트를 통해 각각의 센서들이 인지한 상황을 아두이노의 시리얼통신을 통해 지휘통제실에 시각화하여 전파하게 됩니다. 보고를 받은 지휘통제실은 대처 사항을 전달과 상급부대에 보고를 신속히 할 수 있습니다.
 한편 재난 상황이 인지되었을 때 주변의 타 “재인 문”과의 네트워킹으로 상황을 전달받을 수 있으며 비상대피로에 매설된 LED 들이 점멸하면서 탈출로를 표시해 줍니다.
 특히 **피에조 부저는 재난 상황에 DTMF**(Dual Tone Multiple Frequency, 이중 톤 다중 주파수)에 따른 주파수를 발생합니다. 이 소리에는 119에 전화를 걸게 하는 톤을 코딩해 두었기에 **자동으로 유선전화기가 119에 전화를 걸게 만듭니다.** 또한 문이 열릴 때 문에 맞아 다치는 일이 없도록 하는 경고음의 역할도 수행합니다.
 또한 **릴레이 모듈이 작동하여 재난 상황에서 전력을 자동으로 차단**하여 줍니다. 이를 통해 화재상황 등에서 보다 안전성을 보장받을 수 있습니다. 현재는 적외선 송수신 모듈을 통해 구현되어 있으나 개발 환경에 따라 블루투스, 와이파이 등의 신호를 통해 향상시킬 수 있으리라 전망합니다.

## 팀 소개
 육군 1군단 30사단 조용운 일병이 프로그래머로서 전반적인 코딩을 담당하였으며, 육군 8군단 직할대 유현우 병장이 프로젝트 디자이너로 서포팅 하였습니다.저희 팀은 “재인 문 (Jaein Moon, 재난을 인지하는 문)”입니다.

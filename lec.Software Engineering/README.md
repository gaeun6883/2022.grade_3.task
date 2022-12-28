# 3-2 Software Engineering Team Project: Siro's Revenge
  
#### team: 6 monkeys
#### 프로젝트 파일
https://github.com/KYH-AI/SoftWareDesign.git  
  
#### 주요 사용 툴: unity, sourcetree, slack  
#### 주요 실행 화면  
- 스테이지 1: 몬스터 등장->스테이지 보스 등장  
![image](https://user-images.githubusercontent.com/93725108/209768330-c0712907-fa0c-4e4b-ba7e-08372fc2aef8.png)  
![image](https://user-images.githubusercontent.com/93725108/209768340-637d38e3-9bd3-4644-99c2-c220a8463823.png)  
![image](https://user-images.githubusercontent.com/93725108/209768366-4c5e0330-794d-4ab0-991a-13731616c9bd.png)  
- 스테이지 2,3,4   
![image](https://user-images.githubusercontent.com/93725108/209768593-37fbb236-ce70-4492-a3f9-8493c7c08687.png)  
![image](https://user-images.githubusercontent.com/93725108/209768630-7875469b-73b6-4178-8d4f-1227cc30802d.png)  
![image](https://user-images.githubusercontent.com/93725108/209768715-24b2d679-0351-4ac7-bdc6-9ce47a0cca32.png)  
- 보스/스테이지 클리어  
![image](https://user-images.githubusercontent.com/93725108/209768375-91701ce4-47a0-41b5-993b-5c32f0b959c3.png)  
![image](https://user-images.githubusercontent.com/93725108/209768406-f3935085-293d-44ca-abe0-fe7b0a18a1be.png)  
![image](https://user-images.githubusercontent.com/93725108/209768423-e14501ae-0710-4b5d-800f-12ba731f9722.png)  
![image](https://user-images.githubusercontent.com/93725108/209768430-9106e84b-8a71-4654-a6dd-eb346b1912e1.png)  

  
  
#### 맡은 일 : SRS 4~6
- 기본 몬스터 제작: 8종의 하위 몬스터/4종의 상위 몬스터  
> 상위 몬스터  
>> mushroom: 공격범위 내에 들어올 시 터져서 독연기 생성. 내부에 들어올 시 데미지  
>> crab: 6개의 폭탄 생성/날려서 터뜨리기  
>> bone: blue skull 일정시간마다 소환  
>> golem2: 일정시간마다 레이저 발사  
- 스포너 제작: 일정 시간마다 하나씩 생성/스테이지 내 일정 개수만 나타나도록 생성  
> 보스 등장시 생성 멈춤  
> 보스 연출이 끝난 후 다시 재생성  
  
- SRS: 기본 몬스터(4)  
![image](https://user-images.githubusercontent.com/93725108/209770708-87b3ba87-7e81-42e7-8fd7-e79d6647c4d2.png)  

#### 몬스터 구현 설계도: 클래스 다이어그램, 상태 다이어그램  
-class diagram  
![image](https://user-images.githubusercontent.com/93725108/209770206-73347485-3fb2-436b-b0a5-6f9ec720b467.png)
-state diagram  
![image](https://user-images.githubusercontent.com/93725108/209770246-73f63e67-55e2-403c-ac00-47acc72db0a7.png)  
![image](https://user-images.githubusercontent.com/93725108/209770259-a91073af-0d28-4c3d-956e-6354cb831397.png)  
  
#### 개발 기간 내 진행 상황 기록(슬랙 기록)  
Monster asset  
Stage 1. map visual: 초원, 들판  
             -Spiked Slime, Mushroom, Flying eye  
느낌 키워드: 모험의 시작, 초심자  
Stage 2.  
             -Rat, Bat, Crab  
느낌 키워드: 습하고 어두움, 동굴  
Stage 3.  
            -Skull, Bone, Skeleton  
느낌 키워드: 모험가들의 무덤, 뼈, 해골  
Stage 4.  
            -Golem Phase 1,2,3  
느낌 키워드: 최종 보스를 지키는 최종관문, 보스를 지키는 수호 몬스터  
asset1: Spiked Slime, Golem, Rat, Skull, Bat  
asset2: Mushroom, Flying Eye, Skeleton  
asset3: Bone(enemy1) (편집됨)   
  
Unity Asset StoreUnity Asset Store  
Enemy Galore 1 - Pixel Art | 2D Characters | Unity Asset Store  
Elevate your workflow with the Enemy Galore 1 - Pixel Art asset from Admurin. Find this & more Characters on the Unity Asset Store. (24kB)  
https://assetstore.unity.com/packages/2d/characters/enemy-galore-1-pixel-art-208921#description  
  
  
Unity Asset StoreUnity Asset Store  
Monsters_Creatures_Fantasy | 2D Characters | Unity Asset Store  
Elevate your workflow with the Monsters_Creatures_Fantasy asset from Luiz Melo. Find this & more Characters on the Unity Asset Store. (10kB)  
https://assetstore.unity.com/packages/2d/characters/monsters-creatures-fantasy-167949#content  
  
  
Unity Asset StoreUnity Asset Store  
2D Dungeon Pixel Sprites (2D/ Half 2D) | 2D | Unity Asset Store  
Get the 2D Dungeon Pixel Sprites (2D/ Half 2D) package from ADONIS378 and speed up your game development process. Find this & other 2D options on the Unity Asset   Store. (137kB)  
https://assetstore.unity.com/packages/2d/2d-dungeon-pixel-sprites-2d-half-2d-221584#content  
  
  
  
최가은  
  오전 2:12  
2022.9.21.수  
개발 상항  
-각 스테이지 별 기본 몬스터(슬라임, 박쥐, 해골, 페블) 스크립트, 애니메이션 작성  
-스폰: instantiate->오브젝트 풀링 방식으로 변경  
개선 사항  
-버프 등을 넣을 수 있는 스탯 구조 새로 작성해야함(공부 필요)//현재 스크립트를 통해 hp 구현 되어있음.  
-플레이어 코드 분석 후 스킬 데미지 상호작용 구현 추가  
-pebble의 애니메이션이 어둡게 나옴(현재 이유 예상 불가능)  
고민  
-4개의 스테이지 동안 항상 같은 패턴이면 게임의 재미가 떨어질 것 같음. 각 스테이지마다 몬스터 종류가 3개씩 나오되 스테이지마다 특유의 패턴 생성이 필요할 것 같음.  
(ex. 원거리 공격, 범위 공격, 합체 공격 등등...)  
  
  
  
최가은  
  오후 11:21  
2022.9.30.금  
개발 상황  
-앞서 작성한 몬스터 스크립트를 Enemy 상속으로 재작성  
-스크립트 내 몬스터의 능력치(hp, 공격력) -> Basic Stat(scirpt) 기반 stat으로 변경  
-코인 드랍 Resouce.load() 사용  
회의 결과 몬스터 방향성  
-몬스터 자폭-> 계속 쫓아다니며 공격  
-데미지 받을 시 멈추지 않고 계속 다가가기  
-스테이지 내 2개의 기본 몬스터(계속 다가감)+1개의 특수 몬스터  
10/7 회의 때까지 할 일  
-12개의 몬스터 정리  
-공격 알고리즘 재작성(어떤 조건으로 공격할지 고민 필요)  
  
  
최가은  
  오후 1:48  
PDF  
  
소공 몬스터 정리.pdf  
PDF  
  
  
최가은  
  오후 11:45  
2022.10.8.토  
개발 상황  
-BasicMonsterController: 12종의 몬스터에 대한 행동 FSM(추상 클래스: 공격을 추상화 함수로 하위 클래스에서 구현)  
-몬스터 8종 공격 script: BasicAttack  
-몬스터 4종 공격 script: MushroomAttack, CrabAttack, BoneAttack, Golem2Attack  
-State.Attack 조건: player의 trigger 범위 진입 시(OntriggerEnter)  
                                ->trigger 범위 밖으로 나갈 시 상태 Run으로 변경  
-공격 타이밍 조정: 애니메이션 작동 중 설정 포인트에서 공격 함수 호출로 변경  
-Spawner: 한 번에 오브젝트 하나씩 생성 // 최대 생성 개수 고정  
                 : 오브젝트 풀링으로 구현  
-pdf내 player 중심 spawner 위치 조정 작성  
고민사항  
-코인 드랍 방식  
다음 구현 목표  
-4종의 몬스터(Mushroom, Crab, Bone, Golem2)의 공격 스크립트 작성->제대로 된 동작 확인  
-플레이어와의 상호작용 확인  
  
  
김원담  
  오후 8:49  
Class Diagram 리빙엔티티, 에너미 삭제 및 가독성 상향  
이진  
   
  
GE_Summary_Diagram(수정1102).mdj  
이진  
  
  
최가은  
  오전 1:52  
현재 개발 상황: 이하 영상  
    -상위 몬스터  
      -stage1: Mushroom: 터짐>>독가스 살포  
      -stage2: Crab: 6개의 폭탄 crab 중심 여섯 방향으로 투척  
      -stage3: Bone: Attack 상태가 될 때부터 blue skull 생성(개당 최대 5개)  
      -stage4: Golem2: 레이저(경고(빨강)>>공격(파랑)  
    -데미지 표시  
개발 추가 항목  
    -플레이어 공격: 현재 ui만 작업 완료  
    -데미지>>공격 상태변환 조건  
    -crab의 폭탄, Golem2의 레이저 등은 맵 뒤로 나타나 보이지 않음. 레이어 처리 필요  
 필요 회의 주제  
   -데미지 표시 텍스트의 글자 깨짐: 글자 크기가 너무 작기 때문으로 추측 중(5pt)>> 해결방안 또는 플레이어, 맵 등의 크기를 전체적으로 키워야 할 것 같음  
-추가한 스킬의 레이어 처리를 어떻게 할 지 몰라 stage 2와 4는 맵 없이 촬영했습니다. 각 스테이지의 상위 몬스터들은 정해진 수량만큼만 등장하는데, 빠른 촬영을 위해 생성 수량을 높히고 쿨타임을 낮춘 상태입니다.  
-현재 풀과 푸쉬 둘 다 하지 않았는데, 충돌이 많이 날 것 같아 팀원이 같이 있을 때 하겠습니다.  
4개 파일  
   
  
  
최가은  
  오후 12:36  
몬스터 스펙 표 // 공격 범위  
5개 파일  
   
김락준  
  오후 6:07  
"UI/DamageText"  
6:08  
GameObject floatingText = MemoryPoolManager.GetInstance().OutputGameObject  
            (Managers.Resource.GetPerfabGameObject("UI/DamageText")  
            ,Define.PrefabType.UI  
            ,new Vector3(transform.position.x, transform.position.y)  
            ,Quaternion.identity);  
  
  
최가은  
  오전 2:48  
stage1: mushroom  
-애니메이션으로 버섯이 터져 큰 보라색 연기 생성  
-연기로 터질 시 데미지를 받으면 안되기에 collider를 꺼놓는다.  
-2초 간격으로 지속 데미지를 받음  
-연기가 터진 후 일정시간(현 5초)이 지나 사라질 때, 크기, 색상 등 원래 형태로 복귀  
stage2: Crab  
-6개의 폭탄이 crab 주위로 생성, 발사, 터짐  
-터질 때 애니메이션에서(BombAnimator-explosion) AttackPlayer함수를 부름->폭탄이 날라갈 때 부딪히는 것은 플레이어가 데미지 입지 않음//원할 시 trigger 사용  
-터지는 애니메이션 시간, 쿨타임, Bomb의 시간이 안 맞을 시 오류날 가능성이 다분  
stage3: Bone  
-개체당 최대 5개의 Blue Skull 생성  
-Blue Skull은 Bone stat 사용  
-쿨타임과 Blue skull의 최대 생성개수, Bone의 최대 생성개수 등 조정 필요  
stage4: Golem2  
-12종의 몬스터 중 가장 큰 개체  
-긴 레이저로 공격//느린 이동속도  
-cool time-warning time-attack time  
-attack time일 때만 collider on (trigger)  
-setActive(true/false)시 beam 상태의 초기화를 위해 OnEnable() 사용  
         ->Start/Awake/this.enable=false; 등 다 약간의 문제점이 있기에 OnEnable의 사용은 건들지 말 것  
2:51  
이하 팀원들의 코드를 받아 고칠 것  
-생성 시 Ouput~사용해 큐로 객체 관리  
-Managers.player로 타겟 설정  
-Bone에서 Blue Skull을 생성할 시 Instiate와 StageManager.Player 사용 -> Output~와 Managers.player로 고칠 것  
-데미지 텍스트  
-코인 드랍    
    
최가은  
  오후 8:46  
Mushroom: 상황에 따라 time+=time.deltaTime이 제대로 작동되지 않음>>count 식으로 time+=1로 사용//현 5번 초과 SetActive(false)  
Bone: 원래 basic monster과 같이 attack range에 들어갈 시 blue skull을 생성시킬 생각이었지만 플레이 시, 너무 느리게 전개됨>>생성되자마자 blue skull 생성 시작(Start와  OnEnable의 사용)//쿨타임: 5초,  개당 blue 생성 max: 7개  
-현재 오브젝트 풀링 방식으로 생성: bone이 죽어도 생성된 blue skull은 죽지 않음 (편집됨)   
  
  
- slack/sourcetree  
![image](https://user-images.githubusercontent.com/93725108/209770373-5f88b3e2-b8ec-4072-9a5b-e1bd510308e1.png)  
![image](https://user-images.githubusercontent.com/93725108/209770441-35628e98-9faa-4ea5-8551-1ff95b97dbbb.png)  

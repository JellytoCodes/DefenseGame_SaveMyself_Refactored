# 🛡️ SaveMyself [Single-player Defence Survival Game]
> “플레이어가 직접 컨트롤하는 디펜스를 만들어보고 싶다”는 아이디어에서 시작된 **싱글 플레이어 생존 디펜스** 게임입니다. 각 스테이지마다  
> 구조물·함정을 배치하고, 제한된 자원으로 아이템을 구매해 몰려오는 적을 모두 처치하면 다음 스테이지로 진입합니다.
---

<br>

## 프로젝트 개요
1. 폴더 관리 및 SOLID 원칙에 좀더 근접할 수 있는 방법을 고민하여 리팩토링하기 위한 목적
2. 기존 C++ 90% 이상의 지분을 차지하여 협업이 어려운 점을 고려하여 C++ / Blueprint 분할
3. Subsystem 활용도를 높혀 결합도를 낮추는 것을 목표

<br>

## 리팩토링 주요 내용
| 영역         | Legacy (Flat)                                        | Refactoring (모듈식)                           | 개선 효과           |
| ---------- | ---------------------------------------------------- | ------------------------------------------- | --------------- |
| **디렉터리**   | `.h/.cpp` 95 여개가 `Public`·`Private` 바로 하위에 **평면** 배치 | 도메인별 9 개 폴더 + 세부 서브폴더 **계층화**               | 탐색·모듈 관리 용이     |
| **의존성**    | 위젯이 데이터 직접 조작, 다중 Cast                               | **Subsystem → Event/Request** 패턴            | 결합도↓, 테스트성↑     |
| **컴포넌트화**  | 기능이 Character/Enemy에 집중                              | Health·Effect·Spawn 등 **ActorComponent** 분리 | 재사용성·가독성↑       |
| **이벤트 처리** | 직접 호출                                                | **Delegate + Timer** 비동기                    | UI 지연·레이스 조건 제거 |
| **코딩 규칙**  | Camel/Pascal 혼용                                      | UE 가이드 준수(`U`,`A`,`F` 접두)                   | 일관성 확보          |

<br>

## 폴더 구조
```text
Source/Defense_SaveMyself/
├── Public/                # 헤더
└── Private/               # 소스
    ├── Actor/             # 스테이지 오브젝트(구조물 등) ─ 비캐릭터 액터
    ├── Character/         # 플레이어·Enemy 기반 클래스
    ├── Components/        # 재사용 ActorComponent (Health, Spawn, Effect …)
    ├── Data/              # 데이터 구조체·DataAsset 래퍼 
    ├── Enemy/
    │   ├── AIController/  # Enemy 전용 AIController 구현
    │   └── Stats/         # 몬스터 스탯 정의
    ├── Game/
    │   └── Subsystem/     # Stage, Item 등 게임 전역 Subsystem
    ├── Interact/          # 상호작용 인터페이스·액터
    ├── Player/            # PlayerController, 입력 매핑
    └── UI/
        ├── HUD/              # AHUD 파생 클래스
        ├── Widget/           # 기본 UserWidget
        ├── WidgetComponents/ # 3D WidgetComponent (HP Bar 등)
        └── WidgetController/ # 아이템 등 데이터 정보 출력 Controller
```

<br>

## Author & Acknowledgements
**JellytoCodes – Programmer**  
**Thanks To. 강상용 교수님**  


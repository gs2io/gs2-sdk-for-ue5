[日本語](README.md) | [English](README-en.md) | **한국어**

# GS2 SDK for Unreal Engine 5

Game Server Services(https://gs2.io)를 Unreal Engine 5에서 사용하기 위한 SDK입니다.

## Game Server Services란?

Game Server Services(GS2)는 게임 개발에 특화된 서비스형 백엔드(BaaS)입니다.

GS2는 게임 개발의 효율을 높이기 위해 만들어진 범용 게임 서버 솔루션으로, Games as a Service(GaaS)와 Live Gaming 등을 지원합니다.

플레이어 데이터를 유연하게 관리하고 분석할 수 있습니다. 게임 내 자원이 어떻게 유통되고 소비되는지 분석해 게임 경제의 균형을 유지할 수 있습니다.
또한 스토리 진행 관리와 소지품 관리 등의 기능을 제공하여 게임의 수익화와 플레이어 참여도 향상에 기여합니다.
GS2는 온라인 기능을 지원하고, 게임 개발자가 데이터 분석과 경제 관리를 손쉽게 할 수 있도록 하여 게임의 성공을 돕습니다.

## 시작하기

※소스 코드의 컴파일 및 링크가 필요하므로, Windows/Mac 환경에 Microsoft Visual Studio 2019 이상(UE5.2부터는 2022)을 설치해야 합니다.

### 프로젝트 플러그인으로 설치

다운로드한 소스 코드를 Unreal Engine 프로젝트 내의 다음 폴더에 배치해 주세요.

`(Unreal Engine 프로젝트)/Plugins/Gs2Plugin`

### 엔진 플러그인으로 설치

Unreal Engine 소스 코드를 Github 또는 Perforce에서 받아 엔진을 빌드하는 환경이라면
엔진 플러그인으로 설치할 수 있습니다.
다운로드한 소스 코드를 Unreal Engine 소스 코드 내의 다음 폴더에 배치해 주세요.

`(Unreal Engine 소스 코드)/Engine/Plugins/Gs2Plugin`

SDK를 사용하려면 GS2 크리덴셜(클라이언트 ID와 클라이언트 시크릿)이 필요합니다.
[GS2 설정](https://docs.gs2.io/ko/get_start/tutorial/setup_gs2/) 절차에 따라 크리덴셜을 발급해 주세요.

### 동작 환경

- Unreal Engine 5.1 이상

[⇒GS2 이용 시작 - SDK - Game Engine](https://docs.gs2.io/ko/get_start/#game-engine)

## SDK 상세 사양

서비스별·통신 방식별 API는 [API 레퍼런스](https://docs.gs2.io/ko/api_reference/)를, SDK 초기화 방법은 [초기화 처리](https://docs.gs2.io/ko/api_reference/initialize/) 문서를 참고해 주세요.

## GS2-SDK for UE5 Blueprint 튜토리얼

https://docs.gs2.io/ko/get_start/blueprint/

*이 프로젝트의 코드는 Core를 제외하고 모두 자동 생성되므로, 개별 풀 리퀘스트는 수용할 수 없습니다.*

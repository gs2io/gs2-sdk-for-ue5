[⇒README in English](README-en.md)

# GS2 SDK for Unreal Engine 5

Game Server Services(https://gs2.io) を Unreal Engine 5 で利用するためのSDKです。

## Game Server Services とは

Game Server Services(GS2) とはモバイルゲーム開発に特化したバックエンドサーバサービス(BaaS)です。

ゲーム開発に必要なネットワーク機能をコンポーネント化してサービスとして提供します。
ゲーム内から必要な一部のコンポーネント単位で利用することができるよう設計されており、手軽に・手頃な価格で・高性能なサーバ機能を利用できます。

## Getting Started

### エンジンプラグインとしてインストール

ダウンロードしたソースコードを、Unreal Engineソースコード内の以下のフォルダに配置してください。

`(Unreal Engineソースコード)/Engine/Plugins/Gs2Plugin`

### プロジェクトプラグインとしてインストール

ダウンロードしたソースコードを、Unreal Engineプロジェクト内の以下のフォルダに配置してください。

`(Unreal Engineプロジェクト)/Plugins/Gs2Plugin`

SDKを利用するには GS2 のクレデンシャルが必要です。
[GS2のセットアップ](https://docs.gs2.io/ja/get_start/tutorial/setup_gs2/) の手順に従ってクレデンシャルを発行してください。

### 動作条件

- Unreal Engine 5.1 以上

## SDK の詳細仕様

https://docs.gs2.io/ja/

*本プロジェクトのコードは Core 以外は全て自動生成されているため、個別に Pull-Request を頂いても対応できません。*

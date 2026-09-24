/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 *
 * deny overwrite
 */

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Distributor/Gs2Distributor.h"

// Model
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/DistributorModel.h"
#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Distribute.h"
#include "Distributor/Domain/Model/Expression.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"
#include "Distributor/Domain/Model/TransactionResult.h"
#include "Distributor/Domain/Model/TransactionResultAccessToken.h"

// Iterator
#include "Distributor/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelMastersIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelsIterator.h"

// Notification
#include "Distributor/Model/AutoRunStampSheetNotification.h"
#include "Distributor/Model/AutoRunTransactionNotification.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Distributor::Domain
{
    DECLARE_EVENT_OneParam(FGs2DistributorDomain, FAutoRunStampSheetNotificationEvent, Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2DistributorDomain, FAutoRunTransactionNotificationEvent, Gs2::Distributor::Model::FAutoRunTransactionNotificationPtr);

    class GS2DISTRIBUTOR_API FGs2DistributorDomain:
        public TSharedFromThis<FGs2DistributorDomain>
    {

        TSharedPtr<TArray<Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr>> CompletedStampSheets;
        TSharedPtr<FCriticalSection> CompletedStampSheetsMutex;
/* diff +++ start */
        // 一括取得（DescribeUserData）の振り分け（service → 生成物の PutUserData / SetListCached）は Core（FGs2）が持つ。
        // Gs2Distributor モジュールから Gs2Domain モジュールの関数を参照しない（循環依存）ため、Core が SetUserDataStore で登録する
        TFunction<TOptional<FString>(const FString&, const TOptional<FString>&, const TOptional<FString>&, const TOptional<int32>&, const FString&, const FString&)> PutUserDataFunc;
        TFunction<bool(const FString&, const TOptional<int32>&, const FString&, const FString&)> SetListCachedFunc;
/* diff +++ end */
        TSharedPtr<TArray<Gs2::Distributor::Model::FAutoRunTransactionNotificationPtr>> CompletedTransactions;
        TSharedPtr<FCriticalSection> CompletedTransactionsMutex;
        FAutoRunStampSheetNotificationEvent AutoRunStampSheetNotificationEvent;
        FAutoRunTransactionNotificationEvent AutoRunTransactionNotificationEvent;
        const Core::Domain::FGs2Ptr Gs2;
        const Gs2::Distributor::FGs2DistributorRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2DistributorDomain(
            const Core::Domain::FGs2Ptr& Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2DistributorDomain(
            const FGs2DistributorDomain& From
        );



        class GS2DISTRIBUTOR_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2DistributorDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2DistributorDomain>& Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Distributor::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        class FCollectNamespacesTask;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateNamespaces(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2DISTRIBUTOR_API FSubscribeNamespacesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeNamespacesWithInitialCallTask>
        {
            const TSharedPtr<FGs2DistributorDomain> Self;
            const TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeNamespacesWithInitialCallTask(const TSharedPtr<FGs2DistributorDomain>& Self, TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeNamespacesWithInitialCallTask(const FSubscribeNamespacesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeNamespacesWithInitialCallTask>> SubscribeNamespacesWithInitialCall(
            TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
        );

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result,
            const TOptional<int32> TimeOffset = TOptional<int32>()
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result,
            const TOptional<int32> TimeOffset = TOptional<int32>()
        );

        /* diff +++ start */
        // Gs2Distributor:DescribeUserData（ユーザーの全データの一括取得）の 1 エントリを、Kind に対応するモデルのキャッシュへ入れる。
        // 戻り値は親キー（未設定は知らない Kind ＝ SDK が古い / 対応表に無い / Payload が読めない）。呼び手は全ページを読み終えてから
        // SetListCached(TimeOffset, Kind, ParentKey) を呼ぶ。対応表は sdk-gen の type/user_data_cache.py（kind → モデル）。
        TOptional<FString> PutUserData(
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<int32> TimeOffset,
            const FString Kind,
            const FString Payload
        );

        // 一括取得で入れた Kind の親キーに「リストが揃った印」を立てる（Describe のイテレータがサーバーへ出なくなる）。
        bool SetListCached(
            const TOptional<int32> TimeOffset,
            const FString Kind,
            const FString ParentKey
        );
        /* diff +++ end */

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result,
            const TOptional<int32> TimeOffset = TOptional<int32>()
        );
        FAutoRunStampSheetNotificationEvent& OnAutoRunStampSheetNotification();
        FAutoRunTransactionNotificationEvent& OnAutoRunTransactionNotification();

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

/* diff +++ start */
        // Core（FGs2::Initialize）が呼ぶ。Put は (Service, NamespaceName, UserId, TimeOffset, Kind, Payload) → 親キー（知らない service / kind は未設定）、
        // SetListCached は (Service, TimeOffset, Kind, ParentKey) → 印を立てたか
        void SetUserDataStore(
            TFunction<TOptional<FString>(const FString&, const TOptional<FString>&, const TOptional<FString>&, const TOptional<int32>&, const FString&, const FString&)> Put,
            TFunction<bool(const FString&, const TOptional<int32>&, const FString&, const FString&)> SetListCached
        );

/* diff +++ start */
        // 登録済みの振り分けを呼ぶ（イテレータ DescribeUserData / DescribeUserDataByUserId とローダーが使う）。未登録なら未設定 / false
        TOptional<FString> PutUserData(
            const FString& Service,
            const TOptional<FString>& NamespaceName,
            const TOptional<FString>& UserId,
            const TOptional<int32>& TimeOffset,
            const FString& Kind,
            const FString& Payload
        ) const;
        bool SetListCached(
            const FString& Service,
            const TOptional<int32>& TimeOffset,
            const FString& Kind,
            const FString& ParentKey
        ) const;

/* diff +++ end */
        // 一括取得（Gs2Distributor:DescribeUserData）で AccessToken のユーザーの全データを、各モデルのキャッシュへ入れる。
        // ログイン直後に 1 回待つと、以後の Get / Describe はサーバーへ出ない。キー方式 v2 のプロジェクトでだけ使える（v1 は BadRequest）。
        // 「リストが揃った印」は全ページを読み終えてから (service, kind, 親キー) ごとにまとめて立てる。途中で失敗したら印は立てない。
        // 読めないエントリは数えず続行する。結果はキャッシュへ入れたエントリ数（知らない service / kind は数えない）。
        class GS2DISTRIBUTOR_API FLoadUserDataTask final :
            public Gs2::Core::Util::TGs2Future<int32>,
            public TSharedFromThis<FLoadUserDataTask>
        {
            const TSharedPtr<FGs2DistributorDomain> Self;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        public:
            explicit FLoadUserDataTask(
                const TSharedPtr<FGs2DistributorDomain> Self,
                const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<int32>> Result
            ) override;
        };
        friend FLoadUserDataTask;

        TSharedPtr<FAsyncTask<FLoadUserDataTask>> LoadUserData(
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

/* diff +++ end */
        class GS2DISTRIBUTOR_API FDispatchTask final :
            public Gs2::Core::Util::TGs2Future<FGs2DistributorDomain>,
            public TSharedFromThis<FDispatchTask>
        {
            const TSharedPtr<FGs2DistributorDomain> Self;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        public:
            explicit FDispatchTask(
                const TSharedPtr<FGs2DistributorDomain> Self,
                const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2DistributorDomain>> Result
            ) override;
        };
        friend FDispatchTask;

        TSharedPtr<FAsyncTask<FDispatchTask>> Dispatch(
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        class GS2DISTRIBUTOR_API FDispatchByUserIdTask final :
            public Gs2::Core::Util::TGs2Future<FGs2DistributorDomain>,
            public TSharedFromThis<FDispatchByUserIdTask>
        {
            const TSharedPtr<FGs2DistributorDomain> Self;
            const FString UserId;
        public:
            explicit FDispatchByUserIdTask(
                const TSharedPtr<FGs2DistributorDomain> Self,
                const FString UserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2DistributorDomain>> Result
            ) override;
        };
        friend FDispatchByUserIdTask;

        TSharedPtr<FAsyncTask<FDispatchByUserIdTask>> DispatchByUserId(
            const FString UserId
        );

        DECLARE_MULTICAST_DELEGATE_OneParam(FIssueTransactionDelegate, Gs2::Core::Domain::Model::FIssueTransactionEventPtr);
        FIssueTransactionDelegate OnIssueTransaction;
    };
    typedef TSharedPtr<FGs2DistributorDomain> FGs2DistributorDomainPtr;
}

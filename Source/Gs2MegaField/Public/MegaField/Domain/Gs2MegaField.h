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
 */

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "JobQueue/Gs2JobQueue.h"
#include "MegaField/Gs2MegaField.h"

// Model
#include "MegaField/Domain/Model/Namespace.h"
#include "MegaField/Domain/Model/AreaModel.h"
#include "MegaField/Domain/Model/AreaModelMaster.h"
#include "MegaField/Domain/Model/LayerModel.h"
#include "MegaField/Domain/Model/LayerModelMaster.h"
#include "MegaField/Domain/Model/CurrentFieldMaster.h"
#include "MegaField/Domain/Model/User.h"
#include "MegaField/Domain/Model/UserAccessToken.h"
#include "MegaField/Domain/Model/Spatial.h"
#include "MegaField/Domain/Model/SpatialAccessToken.h"

// Iterator
#include "MegaField/Domain/Iterator/DescribeNamespacesIterator.h"
#include "MegaField/Domain/Iterator/DescribeAreaModelsIterator.h"
#include "MegaField/Domain/Iterator/DescribeAreaModelMastersIterator.h"
#include "MegaField/Domain/Iterator/DescribeLayerModelsIterator.h"
#include "MegaField/Domain/Iterator/DescribeLayerModelMastersIterator.h"

// Notification

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::MegaField::Domain
{

    class GS2MEGAFIELD_API FGs2MegaFieldDomain:
        public TSharedFromThis<FGs2MegaFieldDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Gs2::MegaField::FGs2MegaFieldRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2MegaFieldDomain(
            const Core::Domain::FGs2Ptr& Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2MegaFieldDomain(
            const FGs2MegaFieldDomain& From
        );



        class GS2MEGAFIELD_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::MegaField::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2MegaFieldDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2MegaFieldDomain>& Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::MegaField::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        class FCollectNamespacesTask;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void(TArray<Gs2::MegaField::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateNamespaces(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2MEGAFIELD_API FSubscribeNamespacesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeNamespacesWithInitialCallTask>
        {
            const TSharedPtr<FGs2MegaFieldDomain> Self;
            const TFunction<void(TArray<Gs2::MegaField::Model::FNamespacePtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeNamespacesWithInitialCallTask(const TSharedPtr<FGs2MegaFieldDomain>& Self, TFunction<void(TArray<Gs2::MegaField::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeNamespacesWithInitialCallTask(const FSubscribeNamespacesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeNamespacesWithInitialCallTask>> SubscribeNamespacesWithInitialCall(
            TFunction<void(TArray<Gs2::MegaField::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::MegaField::Domain::Model::FNamespaceDomain> Namespace(
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

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result,
            const TOptional<int32> TimeOffset = TOptional<int32>()
        );

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

        DECLARE_MULTICAST_DELEGATE_OneParam(FIssueTransactionDelegate, Gs2::Core::Domain::Model::FIssueTransactionEventPtr);
        FIssueTransactionDelegate OnIssueTransaction;
    };
    typedef TSharedPtr<FGs2MegaFieldDomain> FGs2MegaFieldDomainPtr;
}

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
#include "Freeze/Gs2Freeze.h"

// Model
#include "Freeze/Domain/Model/Stage.h"
#include "Freeze/Domain/Model/Output.h"

// Iterator
#include "Freeze/Domain/Iterator/DescribeStagesIterator.h"
#include "Freeze/Domain/Iterator/DescribeOutputsIterator.h"

// Notification

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Freeze::Domain
{

    class GS2FREEZE_API FGs2FreezeDomain:
        public TSharedFromThis<FGs2FreezeDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Gs2::Freeze::FGs2FreezeRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2FreezeDomain(
            const Core::Domain::FGs2Ptr& Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2FreezeDomain(
            const FGs2FreezeDomain& From
        );

        Gs2::Freeze::Domain::Iterator::FDescribeStagesIteratorPtr Stages(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStages(
            TFunction<void()> Callback
        );

        class FCollectStagesTask;

        Gs2::Core::Domain::CallbackID SubscribeStages(
            TFunction<void(TArray<Gs2::Freeze::Model::FStagePtr>)> Callback
        );

        void InvalidateStages();

        class GS2FREEZE_API FSubscribeStagesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeStagesWithInitialCallTask>
        {
            const TSharedPtr<FGs2FreezeDomain> Self;
            const TFunction<void(TArray<Gs2::Freeze::Model::FStagePtr>)> Callback;

        public:
            FSubscribeStagesWithInitialCallTask(const TSharedPtr<FGs2FreezeDomain>& Self, TFunction<void(TArray<Gs2::Freeze::Model::FStagePtr>)> Callback);
            FSubscribeStagesWithInitialCallTask(const FSubscribeStagesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeStagesWithInitialCallTask>> SubscribeStagesWithInitialCall(
            TFunction<void(TArray<Gs2::Freeze::Model::FStagePtr>)> Callback
        );
        void UnsubscribeStages(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain> Stage(
            const FString StageName
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
    typedef TSharedPtr<FGs2FreezeDomain> FGs2FreezeDomainPtr;
}

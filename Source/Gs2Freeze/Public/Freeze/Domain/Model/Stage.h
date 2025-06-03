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
#include "Auth/Gs2Auth.h"
#include "Freeze/Domain/Iterator/DescribeStagesIterator.h"
#include "Freeze/Domain/Iterator/DescribeOutputsIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Freeze::Domain
{
    class FGs2FreezeDomain;
    typedef TSharedPtr<FGs2FreezeDomain> FGs2FreezeDomainPtr;
}

namespace Gs2::Freeze::Domain::Model
{
    class FStageDomain;
    class FOutputDomain;

    class GS2FREEZE_API FStageDomain:
        public TSharedFromThis<FStageDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Freeze::Domain::FGs2FreezeDomainPtr Service;
        const Gs2::Freeze::FGs2FreezeRestClientPtr Client;

        public:
        TSharedPtr<TArray<TSharedPtr<Gs2::Freeze::Model::FMicroservice>>> Source;
        TSharedPtr<TArray<TSharedPtr<Gs2::Freeze::Model::FMicroservice>>> Current;
        TOptional<FString> NextPageToken;
        TSharedPtr<TArray<TSharedPtr<Gs2::Freeze::Model::FMicroservice>>> GetSource() const
        {
            return Source;
        }
        TSharedPtr<TArray<TSharedPtr<Gs2::Freeze::Model::FMicroservice>>> GetCurrent() const
        {
            return Current;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> StageName;
    private:

        FString ParentKey;

    public:

        FStageDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Freeze::Domain::FGs2FreezeDomainPtr& Service,
            const TOptional<FString> StageName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FStageDomain(
            const FStageDomain& From
        );

        class GS2FREEZE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Freeze::Model::FStage>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FStageDomain> Self;
            const Request::FGetStageRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FStageDomain>& Self,
                const Request::FGetStageRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Freeze::Model::FStage>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetStageRequestPtr Request
        );

        class GS2FREEZE_API FPromoteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Freeze::Domain::Model::FStageDomain>,
            public TSharedFromThis<FPromoteTask>
        {
            const TSharedPtr<FStageDomain> Self;
            const Request::FPromoteStageRequestPtr Request;
        public:
            explicit FPromoteTask(
                const TSharedPtr<FStageDomain>& Self,
                const Request::FPromoteStageRequestPtr Request
            );

            FPromoteTask(
                const FPromoteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain>> Result
            ) override;
        };
        friend FPromoteTask;

        TSharedPtr<FAsyncTask<FPromoteTask>> Promote(
            Request::FPromoteStageRequestPtr Request
        );

        class GS2FREEZE_API FRollbackTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Freeze::Domain::Model::FStageDomain>,
            public TSharedFromThis<FRollbackTask>
        {
            const TSharedPtr<FStageDomain> Self;
            const Request::FRollbackStageRequestPtr Request;
        public:
            explicit FRollbackTask(
                const TSharedPtr<FStageDomain>& Self,
                const Request::FRollbackStageRequestPtr Request
            );

            FRollbackTask(
                const FRollbackTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain>> Result
            ) override;
        };
        friend FRollbackTask;

        TSharedPtr<FAsyncTask<FRollbackTask>> Rollback(
            Request::FRollbackStageRequestPtr Request
        );

        Gs2::Freeze::Domain::Iterator::FDescribeOutputsIteratorPtr Outputs(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeOutputs(
            TFunction<void()> Callback
        );

        void UnsubscribeOutputs(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Freeze::Domain::Model::FOutputDomain> Output(
            const FString OutputName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> StageName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> StageName
        );

        class GS2FREEZE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Freeze::Model::FStage>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FStageDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FStageDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Freeze::Model::FStage>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Freeze::Model::FStagePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FStageDomain> FStageDomainPtr;
}

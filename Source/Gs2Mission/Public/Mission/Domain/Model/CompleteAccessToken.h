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
#include "Mission/Gs2Mission.h"
#include "Mission/Domain/Iterator/DescribeCompletesIterator.h"
#include "Mission/Domain/Iterator/DescribeCompletesByUserIdIterator.h"
#include "Mission/Domain/Iterator/DescribeCounterModelMastersIterator.h"
#include "Mission/Domain/Iterator/DescribeMissionGroupModelMastersIterator.h"
#include "Mission/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Mission/Domain/Iterator/DescribeCountersIterator.h"
#include "Mission/Domain/Iterator/DescribeCountersByUserIdIterator.h"
#include "Mission/Domain/Iterator/DescribeCounterModelsIterator.h"
#include "Mission/Domain/Iterator/DescribeMissionGroupModelsIterator.h"
#include "Mission/Domain/Iterator/DescribeMissionTaskModelsIterator.h"
#include "Mission/Domain/Iterator/DescribeMissionTaskModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Mission::Domain
{
    class FGs2MissionDomain;
    typedef TSharedPtr<FGs2MissionDomain> FGs2MissionDomainPtr;
}

namespace Gs2::Mission::Domain::Model
{
    class FCompleteDomain;
    class FCompleteAccessTokenDomain;
    class FCounterModelMasterDomain;
    class FMissionGroupModelMasterDomain;
    class FNamespaceDomain;
    class FCounterDomain;
    class FCounterAccessTokenDomain;
    class FCurrentMissionMasterDomain;
    class FCounterModelDomain;
    class FMissionGroupModelDomain;
    class FMissionTaskModelDomain;
    class FMissionTaskModelMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2MISSION_API FCompleteAccessTokenDomain:
        public TSharedFromThis<FCompleteAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Mission::Domain::FGs2MissionDomainPtr Service;
        const Gs2::Mission::FGs2MissionRestClientPtr Client;

        public:
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<FString> GetTransactionId() const
        {
            return TransactionId;
        }
        TOptional<bool> GetAutoRunStampSheet() const
        {
            return AutoRunStampSheet;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> MissionGroupName;
    private:

        FString ParentKey;

    public:

        FCompleteAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Mission::Domain::FGs2MissionDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> MissionGroupName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCompleteAccessTokenDomain(
            const FCompleteAccessTokenDomain& From
        );

        class GS2MISSION_API FCompleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FCompleteAccessTokenDomain>,
            public TSharedFromThis<FCompleteTask>
        {
            const TSharedPtr<FCompleteAccessTokenDomain> Self;
            const Request::FCompleteRequestPtr Request;
            bool SpeculativeExecute;
        public:
            explicit FCompleteTask(
                const TSharedPtr<FCompleteAccessTokenDomain>& Self,
                const Request::FCompleteRequestPtr Request,
                bool SpeculativeExecute
            );

            FCompleteTask(
                const FCompleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteAccessTokenDomain>> Result
            ) override;
        };
        friend FCompleteTask;

        TSharedPtr<FAsyncTask<FCompleteTask>> Complete(
            Request::FCompleteRequestPtr Request,
            bool SpeculativeExecute = true
        );

        class GS2MISSION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Model::FComplete>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCompleteAccessTokenDomain> Self;
            const Request::FGetCompleteRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCompleteAccessTokenDomain>& Self,
                const Request::FGetCompleteRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Model::FComplete>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCompleteRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> MissionGroupName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> MissionGroupName
        );

        class GS2MISSION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Model::FComplete>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCompleteAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCompleteAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Model::FComplete>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Mission::Model::FCompletePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCompleteAccessTokenDomain> FCompleteAccessTokenDomainPtr;
}

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

    class GS2MISSION_API FCounterDomain:
        public TSharedFromThis<FCounterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Mission::Domain::FGs2MissionDomainPtr Service;
        const Gs2::Mission::FGs2MissionRestClientPtr Client;

        public:
        TSharedPtr<TArray<TSharedPtr<Gs2::Mission::Model::FComplete>>> ChangedCompletes;
        TSharedPtr<TArray<TSharedPtr<Gs2::Mission::Model::FComplete>>> GetChangedCompletes() const
        {
            return ChangedCompletes;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> CounterName;
    private:

        FString ParentKey;

    public:

        FCounterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Mission::Domain::FGs2MissionDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> CounterName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCounterDomain(
            const FCounterDomain& From
        );

        class GS2MISSION_API FIncreaseTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FCounterDomain>,
            public TSharedFromThis<FIncreaseTask>
        {
            const TSharedPtr<FCounterDomain> Self;
            const Request::FIncreaseCounterByUserIdRequestPtr Request;
        public:
            explicit FIncreaseTask(
                const TSharedPtr<FCounterDomain>& Self,
                const Request::FIncreaseCounterByUserIdRequestPtr Request
            );

            FIncreaseTask(
                const FIncreaseTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCounterDomain>> Result
            ) override;
        };
        friend FIncreaseTask;

        TSharedPtr<FAsyncTask<FIncreaseTask>> Increase(
            Request::FIncreaseCounterByUserIdRequestPtr Request
        );

        class GS2MISSION_API FSetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FCounterDomain>,
            public TSharedFromThis<FSetTask>
        {
            const TSharedPtr<FCounterDomain> Self;
            const Request::FSetCounterByUserIdRequestPtr Request;
        public:
            explicit FSetTask(
                const TSharedPtr<FCounterDomain>& Self,
                const Request::FSetCounterByUserIdRequestPtr Request
            );

            FSetTask(
                const FSetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCounterDomain>> Result
            ) override;
        };
        friend FSetTask;

        TSharedPtr<FAsyncTask<FSetTask>> Set(
            Request::FSetCounterByUserIdRequestPtr Request
        );

        class GS2MISSION_API FDecreaseTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FCounterDomain>,
            public TSharedFromThis<FDecreaseTask>
        {
            const TSharedPtr<FCounterDomain> Self;
            const Request::FDecreaseCounterByUserIdRequestPtr Request;
        public:
            explicit FDecreaseTask(
                const TSharedPtr<FCounterDomain>& Self,
                const Request::FDecreaseCounterByUserIdRequestPtr Request
            );

            FDecreaseTask(
                const FDecreaseTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCounterDomain>> Result
            ) override;
        };
        friend FDecreaseTask;

        TSharedPtr<FAsyncTask<FDecreaseTask>> Decrease(
            Request::FDecreaseCounterByUserIdRequestPtr Request
        );

        class GS2MISSION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Model::FCounter>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCounterDomain> Self;
            const Request::FGetCounterByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCounterDomain>& Self,
                const Request::FGetCounterByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Model::FCounter>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCounterByUserIdRequestPtr Request
        );

        class GS2MISSION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FCounterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FCounterDomain> Self;
            const Request::FDeleteCounterByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FCounterDomain>& Self,
                const Request::FDeleteCounterByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCounterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteCounterByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> CounterName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> CounterName
        );

        class GS2MISSION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Model::FCounter>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCounterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCounterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Model::FCounter>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Mission::Model::FCounterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCounterDomain> FCounterDomainPtr;
}

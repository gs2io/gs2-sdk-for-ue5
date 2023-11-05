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

    class GS2MISSION_API FMissionGroupModelMasterDomain:
        public TSharedFromThis<FMissionGroupModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Mission::FGs2MissionRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> MissionGroupName;
    private:

        FString ParentKey;

    public:

        FMissionGroupModelMasterDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> MissionGroupName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMissionGroupModelMasterDomain(
            const FMissionGroupModelMasterDomain& From
        );

        class GS2MISSION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Model::FMissionGroupModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMissionGroupModelMasterDomain> Self;
            const Request::FGetMissionGroupModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMissionGroupModelMasterDomain> Self,
                const Request::FGetMissionGroupModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetMissionGroupModelMasterRequestPtr Request
        );

        class GS2MISSION_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FMissionGroupModelMasterDomain> Self;
            const Request::FUpdateMissionGroupModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FMissionGroupModelMasterDomain> Self,
                const Request::FUpdateMissionGroupModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateMissionGroupModelMasterRequestPtr Request
        );

        class GS2MISSION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FMissionGroupModelMasterDomain> Self;
            const Request::FDeleteMissionGroupModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FMissionGroupModelMasterDomain> Self,
                const Request::FDeleteMissionGroupModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteMissionGroupModelMasterRequestPtr Request
        );

        class GS2MISSION_API FCreateMissionTaskModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>,
            public TSharedFromThis<FCreateMissionTaskModelMasterTask>
        {
            const TSharedPtr<FMissionGroupModelMasterDomain> Self;
            const Request::FCreateMissionTaskModelMasterRequestPtr Request;
        public:
            explicit FCreateMissionTaskModelMasterTask(
                const TSharedPtr<FMissionGroupModelMasterDomain> Self,
                const Request::FCreateMissionTaskModelMasterRequestPtr Request
            );

            FCreateMissionTaskModelMasterTask(
                const FCreateMissionTaskModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>> Result
            ) override;
        };
        friend FCreateMissionTaskModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateMissionTaskModelMasterTask>> CreateMissionTaskModelMaster(
            Request::FCreateMissionTaskModelMasterRequestPtr Request
        );

        Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelMastersIteratorPtr MissionTaskModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMissionTaskModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeMissionTaskModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain> MissionTaskModelMaster(
            const FString MissionTaskName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> MissionGroupName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> MissionGroupName
        );

        class GS2MISSION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Model::FMissionGroupModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FMissionGroupModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMissionGroupModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Mission::Model::FMissionGroupModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FMissionGroupModelMasterDomain> FMissionGroupModelMasterDomainPtr;
}

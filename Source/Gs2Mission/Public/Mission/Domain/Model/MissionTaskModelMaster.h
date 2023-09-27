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

    class GS2MISSION_API FMissionTaskModelMasterDomain:
        public TSharedFromThis<FMissionTaskModelMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Mission::FGs2MissionRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> MissionGroupName;
        TOptional<FString> MissionTaskName;
    private:

        FString ParentKey;

    public:

        FMissionTaskModelMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> MissionGroupName,
            const TOptional<FString> MissionTaskName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMissionTaskModelMasterDomain(
            const FMissionTaskModelMasterDomain& From
        );

        class GS2MISSION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Model::FMissionTaskModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMissionTaskModelMasterDomain> Self;
            const Request::FGetMissionTaskModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMissionTaskModelMasterDomain> Self,
                const Request::FGetMissionTaskModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionTaskModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetMissionTaskModelMasterRequestPtr Request
        );

        class GS2MISSION_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FMissionTaskModelMasterDomain> Self;
            const Request::FUpdateMissionTaskModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FMissionTaskModelMasterDomain> Self,
                const Request::FUpdateMissionTaskModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateMissionTaskModelMasterRequestPtr Request
        );

        class GS2MISSION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FMissionTaskModelMasterDomain> Self;
            const Request::FDeleteMissionTaskModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FMissionTaskModelMasterDomain> Self,
                const Request::FDeleteMissionTaskModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteMissionTaskModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> MissionGroupName,
            TOptional<FString> MissionTaskName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> MissionTaskName
        );

        class GS2MISSION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Model::FMissionTaskModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FMissionTaskModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMissionTaskModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionTaskModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Mission::Model::FMissionTaskModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FMissionTaskModelMasterDomain> FMissionTaskModelMasterDomainPtr;
}

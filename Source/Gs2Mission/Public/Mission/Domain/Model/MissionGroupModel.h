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

    class GS2MISSION_API FMissionGroupModelDomain:
        public TSharedFromThis<FMissionGroupModelDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Mission::FGs2MissionRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> MissionGroupName;
    private:

        FString ParentKey;

    public:

        FMissionGroupModelDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> MissionGroupName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMissionGroupModelDomain(
            const FMissionGroupModelDomain& From
        );

        class GS2MISSION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Model::FMissionGroupModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMissionGroupModelDomain> Self;
            const Request::FGetMissionGroupModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMissionGroupModelDomain> Self,
                const Request::FGetMissionGroupModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetMissionGroupModelRequestPtr Request
        );

        Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIteratorPtr MissionTaskModels(
        ) const;

        TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelDomain> MissionTaskModel(
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
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Model::FMissionGroupModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FMissionGroupModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMissionGroupModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FMissionGroupModelDomain> FMissionGroupModelDomainPtr;
}

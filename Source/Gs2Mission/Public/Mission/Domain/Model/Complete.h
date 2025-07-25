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

    class GS2MISSION_API FCompleteDomain:
        public TSharedFromThis<FCompleteDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Mission::Domain::FGs2MissionDomainPtr Service;
        const Gs2::Mission::FGs2MissionRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> MissionGroupName;
    private:

        FString ParentKey;

    public:

        FCompleteDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Mission::Domain::FGs2MissionDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> MissionGroupName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCompleteDomain(
            const FCompleteDomain& From
        );

        class GS2MISSION_API FCompleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionDomain>,
            public TSharedFromThis<FCompleteTask>
        {
            const TSharedPtr<FCompleteDomain> Self;
            const Request::FCompleteByUserIdRequestPtr Request;
        public:
            explicit FCompleteTask(
                const TSharedPtr<FCompleteDomain>& Self,
                const Request::FCompleteByUserIdRequestPtr Request
            );

            FCompleteTask(
                const FCompleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
            ) override;
        };
        friend FCompleteTask;

        TSharedPtr<FAsyncTask<FCompleteTask>> Complete(
            Request::FCompleteByUserIdRequestPtr Request
        );

        class GS2MISSION_API FBatchTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionDomain>,
            public TSharedFromThis<FBatchTask>
        {
            const TSharedPtr<FCompleteDomain> Self;
            const Request::FBatchCompleteByUserIdRequestPtr Request;
        public:
            explicit FBatchTask(
                const TSharedPtr<FCompleteDomain>& Self,
                const Request::FBatchCompleteByUserIdRequestPtr Request
            );

            FBatchTask(
                const FBatchTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
            ) override;
        };
        friend FBatchTask;

        TSharedPtr<FAsyncTask<FBatchTask>> Batch(
            Request::FBatchCompleteByUserIdRequestPtr Request
        );

        class GS2MISSION_API FReceiveTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FCompleteDomain>,
            public TSharedFromThis<FReceiveTask>
        {
            const TSharedPtr<FCompleteDomain> Self;
            const Request::FReceiveByUserIdRequestPtr Request;
        public:
            explicit FReceiveTask(
                const TSharedPtr<FCompleteDomain>& Self,
                const Request::FReceiveByUserIdRequestPtr Request
            );

            FReceiveTask(
                const FReceiveTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
            ) override;
        };
        friend FReceiveTask;

        TSharedPtr<FAsyncTask<FReceiveTask>> Receive(
            Request::FReceiveByUserIdRequestPtr Request
        );

        class GS2MISSION_API FBatchReceiveTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FCompleteDomain>,
            public TSharedFromThis<FBatchReceiveTask>
        {
            const TSharedPtr<FCompleteDomain> Self;
            const Request::FBatchReceiveByUserIdRequestPtr Request;
        public:
            explicit FBatchReceiveTask(
                const TSharedPtr<FCompleteDomain>& Self,
                const Request::FBatchReceiveByUserIdRequestPtr Request
            );

            FBatchReceiveTask(
                const FBatchReceiveTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
            ) override;
        };
        friend FBatchReceiveTask;

        TSharedPtr<FAsyncTask<FBatchReceiveTask>> BatchReceive(
            Request::FBatchReceiveByUserIdRequestPtr Request
        );

        class GS2MISSION_API FRevertReceiveTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FCompleteDomain>,
            public TSharedFromThis<FRevertReceiveTask>
        {
            const TSharedPtr<FCompleteDomain> Self;
            const Request::FRevertReceiveByUserIdRequestPtr Request;
        public:
            explicit FRevertReceiveTask(
                const TSharedPtr<FCompleteDomain>& Self,
                const Request::FRevertReceiveByUserIdRequestPtr Request
            );

            FRevertReceiveTask(
                const FRevertReceiveTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
            ) override;
        };
        friend FRevertReceiveTask;

        TSharedPtr<FAsyncTask<FRevertReceiveTask>> RevertReceive(
            Request::FRevertReceiveByUserIdRequestPtr Request
        );

        class GS2MISSION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Model::FComplete>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCompleteDomain> Self;
            const Request::FGetCompleteByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCompleteDomain>& Self,
                const Request::FGetCompleteByUserIdRequestPtr Request
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
            Request::FGetCompleteByUserIdRequestPtr Request
        );

        class GS2MISSION_API FEvaluateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FCompleteDomain>,
            public TSharedFromThis<FEvaluateTask>
        {
            const TSharedPtr<FCompleteDomain> Self;
            const Request::FEvaluateCompleteByUserIdRequestPtr Request;
        public:
            explicit FEvaluateTask(
                const TSharedPtr<FCompleteDomain>& Self,
                const Request::FEvaluateCompleteByUserIdRequestPtr Request
            );

            FEvaluateTask(
                const FEvaluateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
            ) override;
        };
        friend FEvaluateTask;

        TSharedPtr<FAsyncTask<FEvaluateTask>> Evaluate(
            Request::FEvaluateCompleteByUserIdRequestPtr Request
        );

        class GS2MISSION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FCompleteDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FCompleteDomain> Self;
            const Request::FDeleteCompleteByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FCompleteDomain>& Self,
                const Request::FDeleteCompleteByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteCompleteByUserIdRequestPtr Request
        );

        class GS2MISSION_API FVerifyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Mission::Domain::Model::FCompleteDomain>,
            public TSharedFromThis<FVerifyTask>
        {
            const TSharedPtr<FCompleteDomain> Self;
            const Request::FVerifyCompleteByUserIdRequestPtr Request;
        public:
            explicit FVerifyTask(
                const TSharedPtr<FCompleteDomain>& Self,
                const Request::FVerifyCompleteByUserIdRequestPtr Request
            );

            FVerifyTask(
                const FVerifyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
            ) override;
        };
        friend FVerifyTask;

        TSharedPtr<FAsyncTask<FVerifyTask>> Verify(
            Request::FVerifyCompleteByUserIdRequestPtr Request
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
            const TSharedPtr<FCompleteDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCompleteDomain> Self
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

    typedef TSharedPtr<FCompleteDomain> FCompleteDomainPtr;
}

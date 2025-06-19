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

#pragma once

#include "CoreMinimal.h"
#include "Mission/Domain/Model/CompleteAccessToken.h"
#include "Mission/Model/Gs2MissionEzComplete.h"
#include "Mission/Model/Gs2MissionEzCounterScopeModel.h"
#include "Mission/Model/Gs2MissionEzConfig.h"
#include "Mission/Model/Gs2MissionEzAcquireAction.h"
#include "Mission/Model/Gs2MissionEzConsumeAction.h"
#include "Mission/Model/Gs2MissionEzVerifyAction.h"
#include "Mission/Model/Gs2MissionEzCounter.h"
#include "Mission/Model/Gs2MissionEzCounterModel.h"
#include "Mission/Model/Gs2MissionEzMissionGroupModel.h"
#include "Mission/Model/Gs2MissionEzMissionTaskModel.h"
#include "Mission/Model/Gs2MissionEzTargetCounterModel.h"
#include "Mission/Model/Gs2MissionEzScopedValue.h"
#include "Mission/Model/Gs2MissionEzVerifyActionResult.h"
#include "Mission/Model/Gs2MissionEzConsumeActionResult.h"
#include "Mission/Model/Gs2MissionEzAcquireActionResult.h"
#include "Mission/Model/Gs2MissionEzTransactionResult.h"
#include "Gs2MissionEzCompleteGameSessionDomain.h"
#include "Mission/Domain/Iterator/Gs2MissionEzDescribeCompletesIterator.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    class EZGS2_API FEzCompleteGameSessionDomain final :
        public TSharedFromThis<FEzCompleteGameSessionDomain>
    {
        Gs2::Mission::Domain::Model::FCompleteAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> MissionGroupName() const;

        FEzCompleteGameSessionDomain(
            Gs2::Mission::Domain::Model::FCompleteAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FReceiveRewardsTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>,
            public TSharedFromThis<FReceiveRewardsTask>
        {
            TSharedPtr<FEzCompleteGameSessionDomain> Self;
            FString MissionTaskName;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConfig>>> Config;

        public:
            explicit FReceiveRewardsTask(
                TSharedPtr<FEzCompleteGameSessionDomain> Self,
                FString MissionTaskName,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>> Result
            ) override;
        };
        friend FReceiveRewardsTask;

        TSharedPtr<FAsyncTask<FReceiveRewardsTask>> ReceiveRewards(
            FString MissionTaskName,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConfig>>>()
        );

        class EZGS2_API FBatchReceiveRewardsTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>,
            public TSharedFromThis<FBatchReceiveRewardsTask>
        {
            TSharedPtr<FEzCompleteGameSessionDomain> Self;
            TArray<FString> MissionTaskNames;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConfig>>> Config;

        public:
            explicit FBatchReceiveRewardsTask(
                TSharedPtr<FEzCompleteGameSessionDomain> Self,
                TArray<FString> MissionTaskNames,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>> Result
            ) override;
        };
        friend FBatchReceiveRewardsTask;

        TSharedPtr<FAsyncTask<FBatchReceiveRewardsTask>> BatchReceiveRewards(
            TArray<FString> MissionTaskNames,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConfig>>>()
        );

        class EZGS2_API FEvaluateCompleteTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Mission::Domain::Model::FEzCompleteGameSessionDomain>,
            public TSharedFromThis<FEvaluateCompleteTask>
        {
            TSharedPtr<FEzCompleteGameSessionDomain> Self;

        public:
            explicit FEvaluateCompleteTask(
                TSharedPtr<FEzCompleteGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Domain::Model::FEzCompleteGameSessionDomain>> Result
            ) override;
        };
        friend FEvaluateCompleteTask;

        TSharedPtr<FAsyncTask<FEvaluateCompleteTask>> EvaluateComplete(
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Mission::Model::FEzComplete>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzCompleteGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzCompleteGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Mission::Model::FEzCompletePtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Mission::Model::FEzCompletePtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzCompleteGameSessionDomain> FEzCompleteGameSessionDomainPtr;
}

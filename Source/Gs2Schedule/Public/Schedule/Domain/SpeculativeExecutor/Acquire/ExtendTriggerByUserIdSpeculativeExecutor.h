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
#include "Core/Model/AcquireAction.h"
#include "Core/Model/ConsumeAction.h"
#include "Core/Model/VerifyAction.h"
#include "Schedule/Model/Trigger.h"
#include "Schedule/Request/ExtendTriggerByUserIdRequest.h"
#include "Math/BigInt.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Schedule::Domain
{
    class FGs2ScheduleDomain;
    typedef TSharedPtr<FGs2ScheduleDomain> FGs2ScheduleDomainPtr;
}

namespace Gs2::Schedule::Domain::SpeculativeExecutor
{

    class GS2SCHEDULE_API FExtendTriggerByUserIdSpeculativeExecutor
    {
        static Gs2::Core::Model::FGs2ErrorPtr Transform(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request,
            Gs2::Schedule::Model::FTriggerPtr Item
        );

    public:

        static FString Action();

        class FCommitTask final :
            public Gs2::Core::Util::TGs2Future<TFunction<void()>>,
            public TSharedFromThis<FCommitTask>
        {
            const Gs2::Core::Domain::FGs2Ptr Domain;
            const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr Service;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
            const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr Request;

        public:
            explicit FCommitTask(
                const Gs2::Core::Domain::FGs2Ptr& Domain,
                const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
                const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
                const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request
            );

            FCommitTask(
                const FCommitTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TFunction<void()>>> Result
            ) override;
        };
        friend FCommitTask;

        static TSharedPtr<FAsyncTask<FCommitTask>> Execute(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request
        );

        static Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr Rate(
            const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request,
            const double Rate
        );

        static Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr Rate(
            const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request,
            TBigInt<1024, false> Rate
        );
    };
}

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
#include "Lottery/Request/DrawByUserIdRequest.h"
#include "Math/BigInt.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Core::Domain::SpeculativeExecutor
{
    class FPreparedSpeculativeCommit;
}

namespace Gs2::Lottery::Domain
{
    class FGs2LotteryDomain;
    typedef TSharedPtr<FGs2LotteryDomain> FGs2LotteryDomainPtr;
}

namespace Gs2::Lottery::Domain::SpeculativeExecutor
{

    class GS2LOTTERY_API FDrawByUserIdSpeculativeExecutor
    {

    public:

        static FString Action();

        class FCommitTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>,
            public TSharedFromThis<FCommitTask>
        {
            const Gs2::Core::Domain::FGs2Ptr Domain;
            const Gs2::Lottery::Domain::FGs2LotteryDomainPtr Service;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
            const Gs2::Lottery::Request::FDrawByUserIdRequestPtr Request;

        public:
            GS2LOTTERY_API explicit FCommitTask(
                const Gs2::Core::Domain::FGs2Ptr& Domain,
                const Gs2::Lottery::Domain::FGs2LotteryDomainPtr& Service,
                const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
                const Gs2::Lottery::Request::FDrawByUserIdRequestPtr& Request
            );

            GS2LOTTERY_API FCommitTask(
                const FCommitTask& From
            );

            GS2LOTTERY_API virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
            ) override;
        };
        friend FCommitTask;

        static TSharedPtr<FAsyncTask<FCommitTask>> Execute(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const Gs2::Lottery::Domain::FGs2LotteryDomainPtr& Service,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const Gs2::Lottery::Request::FDrawByUserIdRequestPtr& Request
        );

        static Gs2::Lottery::Request::FDrawByUserIdRequestPtr Rate(
            const Gs2::Lottery::Request::FDrawByUserIdRequestPtr& Request,
            const double Rate
        );

        static Gs2::Lottery::Request::FDrawByUserIdRequestPtr Rate(
            const Gs2::Lottery::Request::FDrawByUserIdRequestPtr& Request,
            TBigInt<1024, false> Rate
        );
    };
}

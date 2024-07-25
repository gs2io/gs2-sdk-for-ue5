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
#include "Experience/Model/Status.h"
#include "Experience/Request/SetRankCapByUserIdRequest.h"
#include "Math/BigInt.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Experience::Domain
{
    class FGs2ExperienceDomain;
    typedef TSharedPtr<FGs2ExperienceDomain> FGs2ExperienceDomainPtr;
}

namespace Gs2::Experience::Domain::SpeculativeExecutor
{

    class GS2EXPERIENCE_API FSetRankCapByUserIdSpeculativeExecutor
    {
        static Gs2::Core::Model::FGs2ErrorPtr Transform(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr& Request,
            Gs2::Experience::Model::FStatusPtr Item
        );

    public:

        static FString Action();

        class FCommitTask final :
            public Gs2::Core::Util::TGs2Future<TFunction<void()>>,
            public TSharedFromThis<FCommitTask>
        {
            const Gs2::Core::Domain::FGs2Ptr Domain;
            const Gs2::Experience::Domain::FGs2ExperienceDomainPtr Service;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
            const Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr Request;

        public:
            explicit FCommitTask(
                const Gs2::Core::Domain::FGs2Ptr& Domain,
                const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
                const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
                const Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr& Request
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
            const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr& Request
        );

        static Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr Rate(
            const Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr& Request,
            const double Rate
        );

        static Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr Rate(
            const Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr& Request,
            TBigInt<1024, false> Rate
        );
    };
}

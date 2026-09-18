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
 * deny overwrite
 */

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Core/Model/AcquireAction.h"
#include "Core/Model/ConsumeAction.h"
#include "Core/Model/VerifyAction.h"
#include "Stamina/Model/Stamina.h"
#include "Stamina/Request/VerifyStaminaOverflowValueByUserIdRequest.h"
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

namespace Gs2::Stamina::Domain
{
    class FGs2StaminaDomain;
    typedef TSharedPtr<FGs2StaminaDomain> FGs2StaminaDomainPtr;
}

namespace Gs2::Stamina::Domain::SpeculativeExecutor
{

    class GS2STAMINA_API FVerifyStaminaOverflowValueByUserIdSpeculativeExecutor
    {
        static Gs2::Core::Model::FGs2ErrorPtr Transform(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const Gs2::Stamina::Request::FVerifyStaminaOverflowValueByUserIdRequestPtr& Request,
            Gs2::Stamina::Model::FStaminaPtr Item
        );

    public:

        static FString Action();

        class FCommitTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>,
            public TSharedFromThis<FCommitTask>
        {
            const Gs2::Core::Domain::FGs2Ptr Domain;
            const Gs2::Stamina::Domain::FGs2StaminaDomainPtr Service;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
            const Gs2::Stamina::Request::FVerifyStaminaOverflowValueByUserIdRequestPtr Request;

        public:
            GS2STAMINA_API explicit FCommitTask(
                const Gs2::Core::Domain::FGs2Ptr& Domain,
                const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
                const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
                const Gs2::Stamina::Request::FVerifyStaminaOverflowValueByUserIdRequestPtr& Request
            );

            GS2STAMINA_API FCommitTask(
                const FCommitTask& From
            );

            GS2STAMINA_API virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
            ) override;
        };
        friend FCommitTask;

        static TSharedPtr<FAsyncTask<FCommitTask>> Execute(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const Gs2::Stamina::Request::FVerifyStaminaOverflowValueByUserIdRequestPtr& Request
        );

        static TSharedPtr<FAsyncTask<FCommitTask>> ExecuteInverse(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const Gs2::Stamina::Request::FVerifyStaminaOverflowValueByUserIdRequestPtr& Request
        );

        static Gs2::Stamina::Request::FVerifyStaminaOverflowValueByUserIdRequestPtr Rate(
            const Gs2::Stamina::Request::FVerifyStaminaOverflowValueByUserIdRequestPtr& Request,
            const double Rate
        );

        static Gs2::Stamina::Request::FVerifyStaminaOverflowValueByUserIdRequestPtr Rate(
            const Gs2::Stamina::Request::FVerifyStaminaOverflowValueByUserIdRequestPtr& Request,
            TBigInt<1024, false> Rate
        );
    };
}

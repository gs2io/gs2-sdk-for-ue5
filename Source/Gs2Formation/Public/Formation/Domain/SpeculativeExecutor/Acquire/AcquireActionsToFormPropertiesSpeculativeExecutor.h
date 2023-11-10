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
#include "Formation/Request/AcquireActionsToFormPropertiesRequest.h"
#include "Math/BigInt.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Formation::Domain
{
    class FGs2FormationDomain;
    typedef TSharedPtr<FGs2FormationDomain> FGs2FormationDomainPtr;
}

namespace Gs2::Formation::Domain::SpeculativeExecutor
{

    class GS2FORMATION_API FAcquireActionsToFormPropertiesSpeculativeExecutor
    {

    public:

        static FString Action();

        class GS2FORMATION_API FCommitTask final :
            public Gs2::Core::Util::TGs2Future<TFunction<void()>>,
            public TSharedFromThis<FCommitTask>
        {
            const Gs2::Core::Domain::FGs2Ptr Domain;
            const Gs2::Formation::Domain::FGs2FormationDomainPtr Service;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
            const Gs2::Formation::Request::FAcquireActionsToFormPropertiesRequestPtr Request;

        public:
            explicit FCommitTask(
                const Gs2::Core::Domain::FGs2Ptr& Domain,
                const Gs2::Formation::Domain::FGs2FormationDomainPtr& Service,
                const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
                const Gs2::Formation::Request::FAcquireActionsToFormPropertiesRequestPtr& Request
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
            const Gs2::Formation::Domain::FGs2FormationDomainPtr& Service,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const Gs2::Formation::Request::FAcquireActionsToFormPropertiesRequestPtr& Request
        );

        static Gs2::Formation::Request::FAcquireActionsToFormPropertiesRequestPtr Rate(
            const Gs2::Formation::Request::FAcquireActionsToFormPropertiesRequestPtr& Request,
            const double Rate
        );

        static Gs2::Formation::Request::FAcquireActionsToFormPropertiesRequestPtr Rate(
            const Gs2::Formation::Request::FAcquireActionsToFormPropertiesRequestPtr& Request,
            TBigInt<1024, false> Rate
        );
    };
}

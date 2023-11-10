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
#include "Deploy/Domain/Iterator/DescribeStacksIterator.h"
#include "Deploy/Domain/Iterator/DescribeResourcesIterator.h"
#include "Deploy/Domain/Iterator/DescribeEventsIterator.h"
#include "Deploy/Domain/Iterator/DescribeOutputsIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Deploy::Domain
{
    class FGs2DeployDomain;
    typedef TSharedPtr<FGs2DeployDomain> FGs2DeployDomainPtr;
}

namespace Gs2::Deploy::Domain::Model
{
    class FStackDomain;
    class FResourceDomain;
    class FEventDomain;
    class FOutputDomain;

    class GS2DEPLOY_API FResourceDomain:
        public TSharedFromThis<FResourceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Deploy::Domain::FGs2DeployDomainPtr Service;
        const Gs2::Deploy::FGs2DeployRestClientPtr Client;

        public:
        TOptional<FString> StackName;
        TOptional<FString> ResourceName;
    private:

        FString ParentKey;

    public:

        FResourceDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Deploy::Domain::FGs2DeployDomainPtr& Service,
            const TOptional<FString> StackName,
            const TOptional<FString> ResourceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FResourceDomain(
            const FResourceDomain& From
        );

        class GS2DEPLOY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Model::FResource>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FResourceDomain> Self;
            const Request::FGetResourceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FResourceDomain>& Self,
                const Request::FGetResourceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FResource>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetResourceRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> StackName,
            TOptional<FString> ResourceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ResourceName
        );

        class GS2DEPLOY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Model::FResource>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FResourceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FResourceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FResource>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Deploy::Model::FResourcePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FResourceDomain> FResourceDomainPtr;
}
